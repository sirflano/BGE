#include "PhysicsGame1.h"
#include "PhysicsController.h"
#include "Sphere.h"
#include "PhysicsCamera.h"
#include "Box.h"
#include "Cylinder.h"
#include "Steerable3DController.h"
#include "Ground.h"
#include "Content.h"
#include <btBulletDynamicsCommon.h>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/euler_angles.hpp>
#include <gtx/norm.hpp>
#include "VectorDrawer.h"
#include "Utils.h"

#include "PhysicsFactory.h"
#include "Game.h" 
#include "Model.h"
#include "dirent.h"
#include "Capsule.h" 

#include "Tiger.h"

using namespace BGE;

Tiger::Tiger(void)
{
}

Tiger::~Tiger(void)
{
}

bool Tiger::Initialise()
{
	int tigerSize = 5;
	physicsFactory->CreateGroundPhysics();
	physicsFactory->CreateCameraPhysics();
	dynamicsWorld->setGravity(btVector3(0, -30, 0));
	shared_ptr<PhysicsController> taiga = CreateTiger(glm::vec3(10, tigerSize * 3, 0), tigerSize);
	shoulderForward = false;

	if (!Game::Initialise()) {
		return false;
	}

	return true;
}

void BGE::Tiger::Update(float timeDelta)
{
	if (keyState[SDL_SCANCODE_T])
	{
	
		if (bodyRightForeShoulderConstraint->getHingeAngle() >= (shoulderHighLimit * 1.1f) && !shoulderForward) {
		shoulderForward = true;
		}
			if (bodyRightForeShoulderConstraint->getHingeAngle() <= (shoulderLowLimit * 0.9f) && shoulderForward) {
			shoulderForward = false;
		}
		if (bodyRightHindShoulderConstraint->getHingeAngle() >= (shoulderHighLimit*1.1f) && !hindShoulderForward && bodyLeftHindShoulderConstraint->getHingeAngle() <= (shoulderLowLimit * 0.9f)) {
			hindShoulderForward = true;
		}
		if (bodyRightHindShoulderConstraint->getHingeAngle() <= (shoulderLowLimit * 0.9f) && hindShoulderForward && bodyLeftHindShoulderConstraint->getHingeAngle() >= (shoulderHighLimit*1.1f)) {
			hindShoulderForward = false;
		}


	
		if (shoulderForward) {
			bodyRightForeShoulderConstraint->enableAngularMotor(true, -250 * timeDelta, 500);
			rightForeShoulderLimbConstraint->enableAngularMotor(true, 500 * timeDelta, 500);
			rightForeLimbPawConstraint->enableAngularMotor(true, 500 * timeDelta, 500);
		}
		if (!shoulderForward) {
			bodyRightForeShoulderConstraint->enableAngularMotor(true, 250 * timeDelta, 500);
			rightForeShoulderLimbConstraint->enableAngularMotor(true, -500 * timeDelta, 500);
			rightForeLimbPawConstraint->enableAngularMotor(true, -500 * timeDelta, 500);
		}

		if (shoulderForward) {
			bodyLeftForeShoulderConstraint->enableAngularMotor(true, 250 * timeDelta, 500);
			leftForeShoulderLimbConstraint->enableAngularMotor(true, -500 * timeDelta, 500);
			leftForeLimbPawConstraint->enableAngularMotor(true, -500 * timeDelta, 500);
		}
		if (!shoulderForward) {
			bodyLeftForeShoulderConstraint->enableAngularMotor(true, -250 * timeDelta, 500);
			leftForeShoulderLimbConstraint->enableAngularMotor(true, 500 * timeDelta, 500);
			leftForeLimbPawConstraint->enableAngularMotor(true, 500 * timeDelta, 500);
		}
		if (hindShoulderForward) {
			bodyRightHindShoulderConstraint->enableAngularMotor(true, -250 * timeDelta, 500);
			rightHindShoulderKneeConstraint->enableAngularMotor(true, 500 * timeDelta, 500);
			
			rightHindKneeLimbConstraint->enableAngularMotor(true, 500 * timeDelta, 500);
			
			rightHindLimbPawContrstaint->enableAngularMotor(true, -125 * timeDelta, 500);
		}

		if (!hindShoulderForward) {
			bodyRightHindShoulderConstraint->enableAngularMotor(true, 250 * timeDelta, 500);
			rightHindShoulderKneeConstraint->enableAngularMotor(true, -500 * timeDelta, 500);
			rightHindKneeLimbConstraint->enableAngularMotor(true, -500 * timeDelta, 500);
			rightHindLimbPawContrstaint->enableAngularMotor(true, 125 * timeDelta, 500);
		}
		if (hindShoulderForward) {
			bodyLeftHindShoulderConstraint->enableAngularMotor(true, 250 * timeDelta, 500);
			leftHindShoulderKneeConstraint->enableAngularMotor(true, -500 * timeDelta, 500);
			leftHindKneeLimbConstraint->enableAngularMotor(true, -500 * timeDelta, 500);
			leftHindLimbPawContrstaint->enableAngularMotor(true, 125 * timeDelta, 500);
		}

		if (!hindShoulderForward) {
			bodyLeftHindShoulderConstraint->enableAngularMotor(true, -250 * timeDelta, 500);
			leftHindShoulderKneeConstraint->enableAngularMotor(true, -500 * timeDelta, 500);
				leftHindKneeLimbConstraint->enableAngularMotor(true, 500 * timeDelta, 500);
			leftHindLimbPawContrstaint->enableAngularMotor(true, -125 * timeDelta, 500);
		}
	}

	else {
		bodyLeftForeShoulderConstraint->enableAngularMotor(true, 250, 500);
		leftForeShoulderLimbConstraint->enableAngularMotor(true, 250, 500);
		leftForeLimbPawConstraint->enableAngularMotor(true, 250, 500);
		bodyRightForeShoulderConstraint->enableAngularMotor(true, 250, 500);
		rightForeShoulderLimbConstraint->enableAngularMotor(true, 250, 500);
		rightForeLimbPawConstraint->enableAngularMotor(true, 250, 500);
		bodyLeftHindShoulderConstraint->enableAngularMotor(true, -250, 500);
		leftHindShoulderKneeConstraint->enableAngularMotor(true, -250, 500);
		leftHindKneeLimbConstraint->enableAngularMotor(true, 250, 500);
		leftHindLimbPawContrstaint->enableAngularMotor(true, 250, 500);
		bodyRightHindShoulderConstraint->enableAngularMotor(true, -250, 500);
		rightHindShoulderKneeConstraint->enableAngularMotor(true, -250, 500);
		rightHindKneeLimbConstraint->enableAngularMotor(true, 250, 500);
		rightHindLimbPawContrstaint->enableAngularMotor(true, 250, 500);
	}
	Game::Update(timeDelta);
}

void BGE::Tiger::Cleanup()
{
	Game::Cleanup();
}

shared_ptr<PhysicsController> Tiger::CreateTiger(glm::vec3 position, float scale) {
	float bodyRad = scale * 0.55;
	float bodyLength = scale * 3.5;
	float headRad = scale / 2;
	float shoulderRad = scale / 4;
	float foreShoulderLength = scale;
	float limbRad = scale / 6;
	float foreLimbLength = scale;
	float pawLength = scale / 2;
	float hindShoulderLength = scale;
	float hindKneeRad = scale / 6;
	float hindKnessLength = scale / 2;
	float hindLimbRad = scale / 6;
	float hindLimbLength = scale / 2;
	float tailRad = scale / 8;
	float tailLength = scale;
	
	shoulderHighLimit = -glm::radians(75.0f);
	shoulderLowLimit = -glm::radians(150.0f);
	foreLimbHighLimit = -glm::radians(40.0f);
	foreLimbLowLimit = -glm::radians(180.0f);
	hindKneeHighLimit = glm::radians(15.0f);
	hindKneeLowLimit = glm::radians(45.0f);
	hindLimbHighLimit = -glm::radians(45.0f);
	hindLimbLowLimit = -glm::radians(130.0f);
	pawHighLimit = glm::radians(90.0f);
	pawLowLimit = -glm::radians(90.0f);
	hindPawHighLimit = glm::radians(170.0f);
	hindPawLowLimit = glm::radians(90.0f);
	hindShoulderHighLimit = -glm::radians(75.0f);
	hindShoulderLowLimit = -glm::radians(150.0f);
	
	glm::quat bodyRot = glm::quat(1, 0, 0, 1);
	glm::quat foreShoulderRot = glm::quat(-0.1, 0, 0, 1);
	glm::quat foreLimbRot = glm::quat(0.3, 0, 0, 1);
	glm::quat pawRot = glm::quat(1,0,0,1);
	glm::quat hindShoulderRot = glm::quat(0.1, 0, 0, 1);
	glm::quat kneeRot = glm::quat(-0.5, 0, 0, 1);
	glm::quat tailRot = glm::quat(-0.5, 0, 0, 1);

	glm::vec3 headRelPos = position + glm::vec3(-bodyLength/2 - headRad * 1.2, bodyRad, 0);
	glm::vec3 rfsRelPos = position + glm::vec3(-bodyLength/2 + bodyLength / 6, -bodyRad / 2, bodyRad + shoulderRad);
	glm::vec3 lfsRelPos = position + glm::vec3(-bodyLength/2 + bodyLength / 6, -bodyRad / 2, -bodyRad - shoulderRad);
	glm::vec3 rflRelPos = rfsRelPos + glm::vec3(-shoulderRad * 2, -foreShoulderLength * 1.1, 0);
	glm::vec3 lflRelPos = lfsRelPos + glm::vec3(-shoulderRad * 2, -foreShoulderLength * 1.1, 0);
	glm::vec3 rpRelPos = rflRelPos + glm::vec3(-foreLimbLength * 0.6, -foreLimbLength * 0.6, 0);
	glm::vec3 lpRelPos = lflRelPos + glm::vec3(-foreLimbLength * 0.6, -foreLimbLength * 0.6, 0);
	glm::vec3 rhsRelPos = position + glm::vec3(bodyLength/2 - bodyLength/6, -hindShoulderLength/ 2, bodyRad+shoulderRad);
	glm::vec3 lhsRelPos = position + glm::vec3(bodyLength / 2 - bodyLength / 6, -hindShoulderLength / 2, -bodyRad - shoulderRad);
	glm::vec3 rkRelPos = rhsRelPos + glm::vec3(shoulderRad*1.5, -hindShoulderLength /1.5, 0);
	glm::vec3 lkRelPos = lhsRelPos + glm::vec3(shoulderRad*1.5, -hindShoulderLength /1.5, 0);
	glm::vec3 rhlRelPos = rkRelPos + glm::vec3(hindKnessLength * 0.7, -hindKnessLength, 0);
	glm::vec3 lhlRelPos = lkRelPos + glm::vec3(hindKnessLength * 0.7, -hindKnessLength, 0);
	glm::vec3 rhpRelPos = rhlRelPos + glm::vec3(-hindLimbRad*2, -hindLimbLength, 0);
	glm::vec3 lhpRelPos = lhlRelPos + glm::vec3(-hindLimbRad * 2, -hindLimbLength, 0);
	glm::vec3 tailStartPos = position + glm::vec3(bodyLength / 2 + tailLength /1.2, bodyRad/2, 0);
	glm::vec3 tailRelPos = glm::vec3(tailLength, -tailLength , 0);

	shared_ptr<PhysicsController> body = physicsFactory->CreateCylinder(bodyRad, bodyLength, position, bodyRot, true, true);
	shared_ptr<PhysicsController> head = physicsFactory->CreateSphere(headRad, headRelPos, bodyRot);
	shared_ptr<PhysicsController> rightForeShoulder = physicsFactory->CreateCylinder(shoulderRad, scale, rfsRelPos, foreShoulderRot, false, true);
	shared_ptr<PhysicsController> leftForeShoulder = physicsFactory->CreateCylinder(shoulderRad, scale, lfsRelPos, foreShoulderRot, false, true);
	shared_ptr<PhysicsController> rightForeLimb = physicsFactory->CreateCylinder(limbRad, foreLimbLength, rflRelPos, foreLimbRot, false, true);
	shared_ptr<PhysicsController> leftForeLimb = physicsFactory->CreateCylinder(limbRad, foreLimbLength, lflRelPos, foreLimbRot, false, true);
	shared_ptr<PhysicsController> rightPaw = physicsFactory->CreateCylinder(limbRad, pawLength, rpRelPos, pawRot, false, true);
	shared_ptr<PhysicsController> leftPaw = physicsFactory->CreateCylinder(limbRad, pawLength, lpRelPos, pawRot, false, true);
	shared_ptr<PhysicsController> rightHindShoulder = physicsFactory->CreateCylinder(shoulderRad, hindShoulderLength, rhsRelPos, hindShoulderRot, false, true);
	shared_ptr<PhysicsController> leftHindShoulder = physicsFactory->CreateCylinder(shoulderRad, hindShoulderLength, lhsRelPos, hindShoulderRot, false, true);
	shared_ptr<PhysicsController> rightHindKnee = physicsFactory->CreateCylinder(hindKneeRad, hindKnessLength, rkRelPos, kneeRot, false, true);
	shared_ptr<PhysicsController> leftHindKnee = physicsFactory->CreateCylinder(hindKneeRad, hindKnessLength, lkRelPos, kneeRot, false, true);
	shared_ptr<PhysicsController> rightHindLimb = physicsFactory->CreateCylinder(hindLimbRad, hindLimbLength, rhlRelPos, glm::quat(), false, true);
	shared_ptr<PhysicsController> leftHindLimb = physicsFactory->CreateCylinder(hindLimbRad, hindLimbLength, lhlRelPos, glm::quat(), false, true);
	shared_ptr<PhysicsController> rightHindPaw = physicsFactory->CreateCylinder(limbRad, pawLength, rhpRelPos, pawRot, false, true);
	shared_ptr<PhysicsController> leftHindPaw = physicsFactory->CreateCylinder(limbRad, pawLength, lhpRelPos, pawRot, false, true);
	shared_ptr<PhysicsController> tailStart = physicsFactory->CreateCylinder(tailRad, tailLength, tailStartPos, tailRot, false, true);


	bodyRightForeShoulderConstraint = new btHingeConstraint(*body->rigidBody, *rightForeShoulder->rigidBody, btVector3(bodyRad / 4, bodyLength / 2 - bodyLength / 6, bodyRad), btVector3(0, -bodyRad / 4, -shoulderRad), btVector3(0, 0, 1), btVector3(0, 0, 1), false);
	bodyRightForeShoulderConstraint->setLimit(shoulderLowLimit, shoulderHighLimit);
	Game::dynamicsWorld->addConstraint(bodyRightForeShoulderConstraint);
	rightForeShoulderLimbConstraint = new btHingeConstraint(*rightForeShoulder->rigidBody, *rightForeLimb->rigidBody, btVector3(0, foreShoulderLength*0.5 + shoulderRad*0.5, 0), btVector3(0, -foreLimbLength*0.5 - limbRad*0.5, 0), btVector3(0, 0, 1), btVector3(0, 0, 1), true);
	rightForeShoulderLimbConstraint->setLimit(foreLimbLowLimit, foreLimbHighLimit);
	Game::dynamicsWorld->addConstraint(rightForeShoulderLimbConstraint);
	rightForeLimbPawConstraint = new btHingeConstraint(*rightForeLimb->rigidBody, *rightPaw->rigidBody, btVector3(0, foreLimbLength*0.5 + limbRad*0.5, 0), btVector3(0, -pawLength*0.5 - limbRad*0.5, 0), btVector3(0, 0, 1), btVector3(0, 0, 1), false);
	rightForeLimbPawConstraint->setLimit(pawLowLimit, pawHighLimit);
	Game::dynamicsWorld->addConstraint(rightForeLimbPawConstraint);
	bodyRightHindShoulderConstraint = new btHingeConstraint(*body->rigidBody, *rightHindShoulder->rigidBody, btVector3(bodyRad / 4, -bodyLength / 2 + bodyLength / 6, bodyRad), btVector3(0, -bodyRad / 4, -shoulderRad), btVector3(0, 0, 1), btVector3(0, 0, 1), false);
	bodyRightHindShoulderConstraint->setLimit(hindShoulderLowLimit, hindShoulderHighLimit);
	Game::dynamicsWorld->addConstraint(bodyRightHindShoulderConstraint);
	rightHindShoulderKneeConstraint = new btHingeConstraint(*rightHindShoulder->rigidBody, *rightHindKnee->rigidBody, btVector3(0, (hindShoulderLength + shoulderRad)*0.5, 0), btVector3(0, -(hindKnessLength + hindKneeRad)*0.5, 0), btVector3(0, 0, 1), btVector3(0, 0, 1), true);
	rightHindShoulderKneeConstraint->setLimit(hindKneeLowLimit, hindKneeHighLimit);
	Game::dynamicsWorld->addConstraint(rightHindShoulderKneeConstraint);
	rightHindKneeLimbConstraint = new btHingeConstraint(*rightHindKnee->rigidBody, *rightHindLimb->rigidBody, btVector3(0, (hindKnessLength + hindKneeRad)*0.5, 0), btVector3(0, -(hindLimbLength + hindLimbRad)*0.5, 0), btVector3(0, 0, 1), btVector3(0, 0, 1), false);
	rightHindKneeLimbConstraint->setLimit(hindLimbLowLimit, hindLimbHighLimit);
	Game::dynamicsWorld->addConstraint(rightHindKneeLimbConstraint);
	rightHindLimbPawContrstaint = new btHingeConstraint(*rightHindLimb->rigidBody, *rightHindPaw->rigidBody, btVector3(0, (hindLimbLength + hindLimbRad)*0.5, 0), btVector3(0, -(pawLength + limbRad)*0.5, 0), btVector3(0, 0, 1), btVector3(0, 0, 1), false);
	rightHindLimbPawContrstaint->setLimit(hindPawLowLimit, hindPawHighLimit);
	Game::dynamicsWorld->addConstraint(rightHindLimbPawContrstaint);

	bodyLeftForeShoulderConstraint = new btHingeConstraint(*body->rigidBody, *leftForeShoulder->rigidBody, btVector3(bodyRad / 4, bodyLength / 2 - bodyLength / 6, -bodyRad), btVector3(0, -bodyRad / 4, shoulderRad), btVector3(0, 0, 1), btVector3(0, 0, 1), false);
	bodyLeftForeShoulderConstraint->setLimit(shoulderLowLimit, shoulderHighLimit);
	Game::dynamicsWorld->addConstraint(bodyLeftForeShoulderConstraint);
	leftForeShoulderLimbConstraint = new btHingeConstraint(*leftForeShoulder->rigidBody, *leftForeLimb->rigidBody, btVector3(0, foreShoulderLength*0.5 + shoulderRad*0.5, 0), btVector3(0, -foreLimbLength*0.5 - limbRad*0.5, 0), btVector3(0, 0, 1), btVector3(0, 0, 1), true);
	leftForeShoulderLimbConstraint->setLimit(foreLimbLowLimit, foreLimbHighLimit);
	Game::dynamicsWorld->addConstraint(leftForeShoulderLimbConstraint);
	leftForeLimbPawConstraint = new btHingeConstraint(*leftForeLimb->rigidBody, *leftPaw->rigidBody, btVector3(0, foreLimbLength*0.5 + limbRad*0.5, 0), btVector3(0, -pawLength*0.5 - limbRad*0.5, 0), btVector3(0, 0, 1), btVector3(0, 0, 1), false);
	leftForeLimbPawConstraint->setLimit(pawLowLimit, pawHighLimit);
	Game::dynamicsWorld->addConstraint(leftForeLimbPawConstraint);
	bodyLeftHindShoulderConstraint = new btHingeConstraint(*body->rigidBody, *leftHindShoulder->rigidBody, btVector3(bodyRad / 4, -bodyLength / 2 + bodyLength / 6, -bodyRad), btVector3(0, -bodyRad / 4, shoulderRad), btVector3(0, 0, 1), btVector3(0, 0, 1), false);
	bodyLeftHindShoulderConstraint->setLimit(hindShoulderLowLimit, hindShoulderHighLimit);
	Game::dynamicsWorld->addConstraint(bodyLeftHindShoulderConstraint);
	leftHindShoulderKneeConstraint = new btHingeConstraint(*leftHindShoulder->rigidBody, *leftHindKnee->rigidBody, btVector3(0, (hindShoulderLength + shoulderRad)*0.5, 0), btVector3(0, -(hindKnessLength + hindKneeRad)*0.5, 0), btVector3(0, 0, 1), btVector3(0, 0, 1), true);
	leftHindShoulderKneeConstraint->setLimit(hindKneeLowLimit, hindKneeHighLimit);
	Game::dynamicsWorld->addConstraint(leftHindShoulderKneeConstraint);
	leftHindKneeLimbConstraint = new btHingeConstraint(*leftHindKnee->rigidBody, *leftHindLimb->rigidBody, btVector3(0, (hindKnessLength + hindKneeRad)*0.5, 0), btVector3(0, -(hindLimbLength + hindLimbRad)*0.5, 0), btVector3(0, 0, 1), btVector3(0, 0, 1), false);
	leftHindKneeLimbConstraint->setLimit(hindLimbLowLimit, hindLimbHighLimit);
	Game::dynamicsWorld->addConstraint(leftHindKneeLimbConstraint);
	leftHindLimbPawContrstaint = new btHingeConstraint(*leftHindLimb->rigidBody, *leftHindPaw->rigidBody, btVector3(0, (hindLimbLength + hindLimbRad)*0.5, 0), btVector3(0, -(pawLength + limbRad)*0.5, 0), btVector3(0, 0, 1), btVector3(0, 0, 1), false);
	leftHindLimbPawContrstaint->setLimit(hindPawLowLimit, hindPawHighLimit);
	Game::dynamicsWorld->addConstraint(leftHindLimbPawContrstaint);

	btTransform t1, t2;
	t1.setIdentity();
	t2.setIdentity();
	t1.setOrigin(btVector3(0, -(headRad), 0));
	t2.setOrigin(btVector3(bodyRad, bodyLength / 2, 0));
	head_body = new btFixedConstraint(*head->rigidBody, *body->rigidBody, t1, t2);
	dynamicsWorld->addConstraint(head_body);

	BodyTailConstraint = new btPoint2PointConstraint(*body->rigidBody, *tailStart->rigidBody, btVector3(bodyRad*0.75, -(bodyLength + tailRad) / 2, 0), btVector3(0, -tailLength * 0.5, 0));
	Game::dynamicsWorld->addConstraint(BodyTailConstraint);

	return body;
}