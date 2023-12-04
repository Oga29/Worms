#pragma once
#include "SString.h"
#include "Vector2d.h"
class Application;
class Module;
class Entity;
class Weapon
{
public:
	Weapon(Application* app_, Module* listener_, Entity* ent_) : app(app_), listener(listener_), ent(ent_) {}
	~Weapon(){}

	virtual void Use(Vector2d position){}
	int ammo;
	SString name;
	int id;
	Application* app;
	Module* listener;
	Entity* ent;
	int SFX;
};

