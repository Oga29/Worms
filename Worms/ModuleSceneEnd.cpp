#include "ModuleSceneEnd.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Application.h"

ModuleSceneEnd::ModuleSceneEnd(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneEnd::~ModuleSceneEnd()
{
}

bool ModuleSceneEnd::Start()
{
	rwin = App->textures->Load("Assets/screens/REDTEAMWINS.png");
	bwin = App->textures->Load("Assets/screens/BLUETEAMWINS.png");
	return true;
}

update_status ModuleSceneEnd::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->fadeToBlack->FadeToBlack(this, (Module*)App->scene_intro, 30.0f);
	}
	switch (App->scene_intro->winner)
	{	
	case Winner::RED: App->renderer->Blit(rwin, 0, 0, NULL); break;
	case Winner::BLUE: App->renderer->Blit(bwin, 0, 0, NULL); break;
	}
	return UPDATE_CONTINUE;
}

bool ModuleSceneEnd::CleanUp()
{
	App->textures->Unload(rwin);
	App->textures->Unload(bwin);
	return true;
}
