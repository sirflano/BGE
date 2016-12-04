#pragma once
#include "GameComponent.h"
#include "Model.h"

using namespace std;
namespace BGE {

	class Steerable2DController :
		public GameComponent
	{
	private:
		void Steerable2DController::CalculateInertiaTensor();
		shared_ptr<Model> model;
	public:
		Steerable2DController(shared_ptr<Model> model);
		~Steerable2DController(void);

		bool Initialise();
		void Update();
		void Draw();

		float mass;
		glm::vec3 velocity, force, acceleration;

		void AddForce(glm::vec3);
	};
}