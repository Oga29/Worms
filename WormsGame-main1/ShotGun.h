#pragma once
#include "Weapon.h"
class shotGun :public Weapon
{
public:
	shotGun(Application* app_, Module* listener_, Entity* ent_);
	~shotGun();

	void Use(Vector2d position);

};

