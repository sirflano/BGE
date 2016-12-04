#include "Lab8.h"
#include "Content.h"
#include "VectorDrawer.h"
#include "GravityController.h"
#include "Steerable2DController.h"
#include "Steerable3DController.h"
#include "Utils.h"

using namespace BGE;

Lab8::Lab8(){

}

bool Lab8::Initialise(){
	std::shared_ptr<GameComponent> ground = make_shared<Ground>();
	Attach(ground);
	std::shared_ptr<Model> shipmodel = Content::LoadModel("cobramk3", glm::rotate(glm::mat4(1), 180.0f, glm::vec3(0, 1, 0)));

	ship1 = make_shared<GameComponent>(true);
	ship1->Attach(shipmodel);
	ship1->transform->position = glm::vec3(-10, 2, -10);
	ship1->Attach(make_shared<VectorDrawer>());
	ship1->Attach(make_shared<Steerable2DController>(dynamic_pointer_cast<Model>(ship1->FindComponentByTag(shipmodel->tag))));
	Attach(ship1);

	ship2 = make_shared<GameComponent>(true);
	ship2->Attach(shipmodel);
	ship2->transform->position = glm::vec3(-10, 2, 10);
	ship2->Attach(make_shared<VectorDrawer>());
	ship2->Attach(make_shared<Steerable3DController>(SDL_SCANCODE_W, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_Q, SDL_SCANCODE_E, SDL_SCANCODE_S, SDL_SCANCODE_X));
	Attach(ship2);
	Game::Initialise();

	camera->transform->position = glm::vec3(0, 4, 20);
	return true;
}

void Lab8::Update(float timeDelta){

	Game::Update();

}

