#pragma once
#include "Weapon.h"
class Granade :public Weapon
{
public:
	Granade(Application* app_, Module* listener_, Entity* ent_);
	~Granade();
	void Use(Vector2d position);
};
