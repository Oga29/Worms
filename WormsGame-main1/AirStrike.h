#pragma once
#include "Weapon.h"
class AirStrike :public Weapon
{
public:
	AirStrike(Application* app_, Module* listener_, Entity* ent_);
	~AirStrike();
	void Use(Vector2d position);
};

