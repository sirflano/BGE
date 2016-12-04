#pragma once
#include "Game.h"
#include "PhysicsController.h"
#include "PhysicsFactory.h"
#include <btBulletDynamicsCommon.h>

namespace BGE
{
	class Tiger :
		public Game
	{
	private:
		btHingeConstraint * bodyRightForeShoulderConstraint;
		btHingeConstraint * rightForeShoulderLimbConstraint;
		btHingeConstraint * rightForeLimbPawConstraint;
		btHingeConstraint * bodyRightHindShoulderConstraint;
		btHingeConstraint * rightHindShoulderKneeConstraint;
		btHingeConstraint * rightHindKneeLimbConstraint;
		btHingeConstraint * rightHindLimbPawContrstaint;
		btHingeConstraint * bodyLeftForeShoulderConstraint;
		btHingeConstraint * leftForeShoulderLimbConstraint;
		btHingeConstraint * leftForeLimbPawConstraint;
		btHingeConstraint * bodyLeftHindShoulderConstraint;
		btHingeConstraint * leftHindShoulderKneeConstraint;
		btHingeConstraint * leftHindKneeLimbConstraint;
		btHingeConstraint * leftHindLimbPawContrstaint;
		btFixedConstraint * head_body;
		btPoint2PointConstraint * BodyTailConstraint;
		btPoint2PointConstraint * tailConstraint1;
		btPoint2PointConstraint * tailConstraint2;
		btPoint2PointConstraint * tailConstraint3;
		btPoint2PointConstraint * tailConstraint4;
		btPoint2PointConstraint * tailConstraint5;

		bool shoulderForward = false;
		bool shoulderBack = false;
		bool leftShoulderForward = false;
		bool leftShoulderBack = false;
		bool hindShoulderForward = false;
		bool hindShoulderBack = false;
		bool leftHindShoulderForward = false;
		bool leftHindShoulderBack = false;
		bool legStretch;
		bool leftLegStretch;
		bool leftStride = false;
		bool rightStride = false;
		bool foreStride = true;
		bool hindStride = false;

		int shoulderHighLimit;
		int shoulderLowLimit;
		int foreLimbHighLimit;
		int foreLimbLowLimit;
		int hindKneeHighLimit;
		int hindKneeLowLimit;
		int hindLimbHighLimit;
		int hindLimbLowLimit;
		int pawHighLimit;
		int pawLowLimit;
		int hindPawHighLimit;
		int hindPawLowLimit;
		int hindShoulderHighLimit;
		int hindShoulderLowLimit;
	public:
		Tiger(void);
		~Tiger(void);
		bool Initialise();
		void Update(float timeDelta);
		void Cleanup();
		shared_ptr<PhysicsController> CreateTiger(glm::vec3 position, float scale = 5);
	};
}
