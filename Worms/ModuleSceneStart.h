#pragma once
#include "Module.h"

class ModuleSceneStart : public Module
{
public:
	ModuleSceneStart(Application* app, bool start_enabled = true);
	~ModuleSceneStart();

	bool Start();

	update_status Update();
	bool CleanUp();
private:
	int counter;
	SDL_Texture* background;
	SDL_Texture* enter;
};
