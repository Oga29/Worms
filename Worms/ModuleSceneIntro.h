#pragma once
#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "Portal.h"
enum Winner
{
	NONE = -1,
	RED,
	BLUE,
	DRAW
};
class Entity;
class Worm;
class Weapon;
class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void UpdateChoose();
	void IsStarting();
	void StartTurn();
	void EndTurn();
public:
	//Current portal
	Portal* portal;

	p2List<Worm*> wormsRed;
	p2List<Worm*> wormsBlue;
	p2List_item<Worm*>* currentWormRed;
	p2List_item<Worm*>* currentWormBlue;
	SString weaponBlue;
	int ammoBlue;
	SString weaponRed;
	int ammoRed;
	int turnTimer;
	bool startTurn;
	bool redTurn;
	bool blueTurn;
	bool turnStarted;
	int music;

	Winner winner;
private:

	SDL_Texture* background;
	SDL_Texture* floor;
};
