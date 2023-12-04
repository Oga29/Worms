#pragma once
#include "Weapon.h"
class PortalGun :public Weapon
{
public:
	PortalGun(Application* app_, Module* listener_, Entity* ent_);
	~PortalGun();

	void Use(Vector2d position);
};

