#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "SString.h"
#include "Worm.h"
#include "EntityManager.h"
#include "ModuleAudio.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->UI->Enable();

	App->renderer->camera.x = App->renderer->camera.y = 0;

	PhysObject* g = new PhysObject();
	
	g->x = 1020/ 2;
	g->y = 750.0f;
	g->mass = 1.0f;
	g->shape = Shape::RECTANGLE;
	g->w = 1020;
	g->h = 10;
	g->restitution = 0.1f;
	g->name.Create("Ground");
	g->type = Type::STATIC;

	App->physics->world.CreateObject(g);


	PhysObject* g2 = new PhysObject();

	g2->x = 500.0f;
	g2->y = 450.0f;
	g2->mass = 1.0f;
	g2->shape = Shape::RECTANGLE;
	g2->w = 100;
	g2->h = 20;
	g2->restitution = 0.1f;
	g2->name.Create("Ground2");
	g2->type = Type::STATIC;

	App->physics->world.CreateObject(g2);


	PhysObject* g3 = new PhysObject();

	g3->x = 100.0f;
	g3->y = 250.0f;
	g3->mass = 1.0f;
	g3->shape = Shape::RECTANGLE;
	g3->w = 500;
	g3->h = 20;
	g3->restitution = 0.1f;
	g3->name.Create("Ground3");
	g3->type = Type::STATIC;

	App->physics->world.CreateObject(g3);



	PhysObject* g4 = new PhysObject();

	g4->x = 100.0f;
	g4->y = 400.0f;
	g4->mass = 1.0f;
	g4->shape = Shape::RECTANGLE;
	g4->w = 500;
	g4->h = 20;
	g4->restitution = 0.1f;
	g4->name.Create("Ground4");
	g4->type = Type::STATIC;

	App->physics->world.CreateObject(g4);


	PhysObject* g5 = new PhysObject();

	g5->x = 100.0f;
	g5->y = 550.0f;
	g5->mass = 1.0f;
	g5->shape = Shape::RECTANGLE;
	g5->w = 500;
	g5->h = 20;
	g5->restitution = 0.1f;
	g5->name.Create("Ground5");
	g5->type = Type::STATIC;

	App->physics->world.CreateObject(g5);


	PhysObject* g6 = new PhysObject();

	g6->x = 900.0f;
	g6->y = 250.0f;
	g6->mass = 1.0f;
	g6->shape = Shape::RECTANGLE;
	g6->w = 500;
	g6->h = 20;
	g6->restitution = 0.1f;
	g6->name.Create("Ground6");
	g6->type = Type::STATIC;

	App->physics->world.CreateObject(g6);

	PhysObject* g7 = new PhysObject();

	g7->x = 900.0f;
	g7->y = 400.0f;
	g7->mass = 1.0f;
	g7->shape = Shape::RECTANGLE;
	g7->w = 500;
	g7->h = 20;
	g7->restitution = 0.1f;
	g7->name.Create("Ground7");
	g7->type = Type::STATIC;

	App->physics->world.CreateObject(g7);
	
	PhysObject* g8 = new PhysObject();

	g8->x = 900.0f;
	g8->y = 550.0f;
	g8->mass = 1.0f;
	g8->shape = Shape::RECTANGLE;
	g8->w = 500;
	g8->h = 20;
	g8->restitution = 0.1f;
	g8->name.Create("Ground8");
	g8->type = Type::STATIC;

	App->physics->world.CreateObject(g8);

	PhysObject* g9 = new PhysObject();

	g9->x = 500.0f;
	g9->y = 200.0f;
	g9->mass = 1.0f;
	g9->shape = Shape::RECTANGLE;
	g9->w = 100;
	g9->h = 20;
	g9->restitution = 0.1f;
	g9->name.Create("Ground9");
	g9->type = Type::STATIC;

	App->physics->world.CreateObject(g9);

	PhysObject* g10 = new PhysObject();

	g10->x = 500.0f;
	g10->y = 600.0f;
	g10->mass = 1.0f;
	g10->shape = Shape::RECTANGLE;
	g10->w = 100;
	g10->h = 20;
	g10->restitution = 0.1f;
	g10->name.Create("Ground9");
	g10->type = Type::STATIC;

	App->physics->world.CreateObject(g10);

	wormsBlue.add((Worm*)App->entman->CreateEntity(EntityType::WORM, 850, 205, Team::BLUE));
	wormsBlue.add((Worm*)App->entman->CreateEntity(EntityType::WORM, 850, 355, Team::BLUE));
	wormsBlue.add((Worm*)App->entman->CreateEntity(EntityType::WORM, 850, 515, Team::BLUE));
	wormsBlue.add((Worm*)App->entman->CreateEntity(EntityType::WORM, 850, 685, Team::BLUE));

	wormsRed.add((Worm*)App->entman->CreateEntity(EntityType::WORM, 150, 205, Team::RED));
	wormsRed.add((Worm*)App->entman->CreateEntity(EntityType::WORM, 150, 355, Team::RED));
	wormsRed.add((Worm*)App->entman->CreateEntity(EntityType::WORM, 150, 515, Team::RED));
	wormsRed.add((Worm*)App->entman->CreateEntity(EntityType::WORM, 150, 685, Team::RED));

	currentWormBlue = wormsBlue.getFirst();
	currentWormBlue->data->Select();
	currentWormRed = wormsRed.getFirst();
	blueTurn = true;
	redTurn = false;
	turnTimer = 1800;
	winner = Winner::NONE;
	background = App->textures->Load("Assets/background.png");
	return ret;
}

update_status ModuleSceneIntro::PreUpdate()
{
	for (p2List_item<Worm*>* w = wormsBlue.getFirst(); w != nullptr; w = w->next)
	{
		if (w->data->setPendingToDelete)
		{
			wormsBlue.del(w);
			currentWormBlue = wormsBlue.getFirst();
			break;
		}
	}
	for (p2List_item<Worm*>* w = wormsRed.getFirst(); w != nullptr; w = w->next)
	{
		if (w->data->setPendingToDelete)
		{
			wormsRed.del(w);
			currentWormRed = wormsRed.getFirst();
			break;
		}
	}


	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	wormsBlue.clear();
	wormsRed.clear();
	currentWormBlue = nullptr;
	currentWormRed = nullptr;
	App->textures->Unload(background);
	App->textures->Unload(floor);
	App->physics->CleanUp();
	App->entman->CleanUp();
	App->UI->Disable();
	return true;
}

void ModuleSceneIntro::UpdateChoose()
{
	if (redTurn)
	{
		if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
		{
			currentWormRed->data->UnSelect();
			currentWormRed = currentWormRed->next;
			if (currentWormRed == nullptr)
				currentWormRed = wormsRed.getFirst();
			currentWormRed->data->Select();
		}
	}
	if (blueTurn)
	{
		if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
		{
			currentWormBlue->data->UnSelect();
			currentWormBlue = currentWormBlue->next;
			if (currentWormBlue == nullptr)
				currentWormBlue = wormsBlue.getFirst();
			currentWormBlue->data->Select();
		}
	}
}

void ModuleSceneIntro::IsStarting()
{
	if (App->input->GetKey(SDL_SCANCODE_W) || App->input->GetKey(SDL_SCANCODE_A) || App->input->GetKey(SDL_SCANCODE_D) || App->input->GetKey(SDL_SCANCODE_SPACE))
		turnStarted = true;
}



void ModuleSceneIntro::EndTurn()
{
	turnTimer = 1800;
	if (redTurn)
	{
		redTurn = false;
		blueTurn = true;
		turnStarted = false;
		if (wormsBlue.count() > 0)
		{
			currentWormBlue = wormsBlue.getFirst();
			currentWormBlue->data->Select();

			currentWormRed->data->UnSelect();
		}
		return;
	}
	if (blueTurn)
	{

		redTurn = true;
		blueTurn = false;
		turnStarted = false;
		if (wormsRed.count() > 0)
		{
			currentWormRed = wormsRed.getFirst();
			currentWormRed->data->Select();

			currentWormBlue->data->UnSelect();
		}
		return;
	}
	
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{

	SString string;
	string.Create("Current FPS: %f DeltaTime: %f  Expected FPS: %i, DeltaTime: %i", 1000 / App->dt, App->dt, 1000 / App->targetDT, App->targetDT);
	if (currentWormBlue != nullptr)
	{
		weaponBlue = currentWormBlue->data->currentWeapon->data->name.GetString();
		ammoBlue = currentWormBlue->data->currentWeapon->data->ammo;

	}
	if (currentWormRed != nullptr)
	{
		weaponRed = currentWormRed->data->currentWeapon->data->name.GetString();
		ammoRed = currentWormRed->data->currentWeapon->data->ammo;
	}
	
	if (App->physics->debug)
	{
		if (App->input->GetKey(SDL_SCANCODE_1))
		{
			App->targetDT = 1000 / 15;
			App->bulletDT = 1000 / 15;
		}
		if (App->input->GetKey(SDL_SCANCODE_2))
		{
			App->targetDT = 1000 / 30;
			App->bulletDT = 1000 / 30;
		}
		if (App->input->GetKey(SDL_SCANCODE_3))
		{
			App->targetDT = 1000 / 60;
			App->bulletDT = 1000 / 60;
		}
		if (App->input->GetKey(SDL_SCANCODE_4))
		{
			App->targetDT = 1000 / 144;
			App->bulletDT = 1000 / 144;
		}

		if (App->input->GetKey(SDL_SCANCODE_F2))
			App->controll = FrameTimeControll::VARIABLEDT;
		if (App->input->GetKey(SDL_SCANCODE_F3))
			App->controll = FrameTimeControll::FIXEDDTTM;
		if (App->input->GetKey(SDL_SCANCODE_F4))
			App->controll = FrameTimeControll::CONTROLLDT;
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
			App->physics->world.atmosphere.wind.x -= 0.5f;
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
			App->physics->world.atmosphere.wind.x += 0.5f;
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
			App->physics->world.atmosphere.wind.y += 0.5f;
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
			App->physics->world.atmosphere.wind.y -= 0.5f;
		if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
		{
			for (p2List_item<Worm*>* w = wormsBlue.getFirst(); w != nullptr; w = w->next)
			{
				w->data->setPendingToDelete = true;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		{
			for (p2List_item<Worm*>* w = wormsRed.getFirst(); w != nullptr; w = w->next)
			{
				w->data->setPendingToDelete = true;
			}
		}

	}
	if (!turnStarted)
	{
		UpdateChoose();
	}
	IsStarting();
	

	printf("\nTimer %i", turnTimer);
	if (turnStarted)
	{
		turnTimer--;
		if (turnTimer <= 0)
			EndTurn();
	}
	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN && App->physics->debug)
		EndTurn();
	if (currentWormBlue != nullptr)
	{
		if (currentWormBlue->data->endTurn)
		{
			EndTurn();
			currentWormBlue->data->endTurn = false;
		}
	}
	if (currentWormRed != nullptr)
	{
		if (currentWormRed->data->endTurn)
		{
			EndTurn();
			currentWormRed->data->endTurn = false;
		}
	}

	printf("\nRed Team turn %s", redTurn ? "true" : "false");
	printf("\nBlue Team turn %s", blueTurn ? "true" : "false");
	printf("\nWorms Red %i", wormsRed.count());
	printf("\nWorms Blue %i", wormsBlue.count());

	App->renderer->Blit(background, 0, 0);

	App->window->SetTitle(string.GetString());



	if (wormsBlue.count() <= 0 && wormsRed.count() > 0) winner = Winner::RED;
	if (wormsRed.count() <= 0 && wormsBlue.count() > 0) winner = Winner::BLUE;
	else if (wormsRed.count() == 0 && wormsBlue.count() == 0) winner = Winner::DRAW;

	if (winner != NONE)
	{
		App->fadeToBlack->FadeToBlack(this, (Module*)App->scene_end);
	}

	return UPDATE_CONTINUE;
}
