#pragma once
#include "Weapon.h"
class HandGun :public Weapon
{
public:
	HandGun(Application* app_, Module* listener_, Entity* ent_);
	~HandGun();

	void Use(Vector2d position);

};

