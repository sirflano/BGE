#include "Steerable2DController.h"
#include "Content.h"
#include "Model.h"
#include "Utils.h"
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/matrix_transform.hpp>
#include <sstream>
#include <string>

using namespace BGE;
using namespace std;

Steerable2DController::Steerable2DController(shared_ptr<Model> model) :GameComponent()
{
	mass = 10.0f;
	velocity = glm::vec3(0);
	force = glm::vec3(0);
	acceleration = glm::vec3(0);
	this->model = model;
}

Steerable2DController::~Steerable2DController(void)
{
}

bool Steerable2DController::Initialise()
{
	if (!model->initialised)
	{
		model->Initialise();
	}

	GameComponent::Initialise();
	return true;
}

void Steerable2DController::AddForce(glm::vec3 force)
{
	this->force += force;
}

void Steerable2DController::Draw()
{
	GameComponent::Draw();
}



void Steerable2DController::Update()
{
	const Uint8 * keyState = Game::Instance()->GetKeyState();

	float scale = 10000.0f;
	if (keyState[SDL_SCANCODE_RETURN])
	{
		//AddForce(glm::vec2(transform->look.x, transform->look.z) * scale * Time::deltaTime);
	}

	// Yaw
	if (keyState[SDL_SCANCODE_UP])
	{
		AddForce(glm::vec3(0, 0, -500));
	}
	if (keyState[SDL_SCANCODE_DOWN])
	{
		AddForce(glm::vec3(0, 0, 500));
	}
	if (keyState[SDL_SCANCODE_LEFT])
	{
		AddForce(glm::vec3(-500, 0, 0));
	}
	if (keyState[SDL_SCANCODE_RIGHT])
	{
		AddForce(glm::vec3(500, 0, 0));
	}
	// End of Yaw


	// Do the Newtonian integration
	acceleration = force / mass;
	velocity += acceleration * Time::deltaTime;
	transform->position += velocity * Time::deltaTime;

	//Game::Instance()->PrintVector("Velocity: ", velocity);

	// Normalise the velocity into the look
	// Probably not necessary as we recalculate these anyway later
	if (glm::length(velocity) > 0.0001f)
	{
		transform->look = glm::normalize(glm::vec3(velocity.x, velocity.y, 0));
		transform->right = glm::cross(transform->look, transform->up);
		velocity *= 0.99f;
	}

	// Do the Hamiltonian integration
	//angularAcceleration = torque * glm::inverse(inertialTensor);




	//glm::quat w = glm::quat(0, angularVelocity.x, angularVelocity.y, 0);

	transform->orientation = transform->orientation + (((Time::deltaTime / 2.0f)) * transform->orientation);
	transform->orientation = glm::normalize(transform->orientation);

	// Reset the accumulators
	//torque = glm::vec2(0, 0);
	force = glm::vec3(0, 0, 0);

	transform->look = RotateVector(Transform::basisLook, transform->orientation);
	transform->up = RotateVector(Transform::basisUp, transform->orientation);
	transform->right = RotateVector(Transform::basisRight, transform->orientation);

	GameComponent::Update();
}
