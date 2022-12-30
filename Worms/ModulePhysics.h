#pragma once
#include "Module.h"
#include "Globals.h"
#include "Physics.h"


#define PIXELS_PER_METER 0.02f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 50.0f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)


class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	Physics world;
	bool debug;
	SDL_Texture* bomb;

};