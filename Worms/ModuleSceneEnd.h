#pragma once
#include "Module.h"

class ModuleSceneEnd : public Module
{
public:
	ModuleSceneEnd(Application* app, bool start_enabled = true);
	~ModuleSceneEnd();

	bool Start();

	update_status Update();
	bool CleanUp();
private:

	SDL_Texture* bwin;
	SDL_Texture* rwin;
};
