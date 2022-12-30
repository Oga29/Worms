#pragma once
#include "Weapon.h"
class Grenade :public Weapon
{
public:
	Grenade(Application* app_, Module* listener_, Entity* ent_);
	~Grenade();
	void Use(Vector2d position);
};
