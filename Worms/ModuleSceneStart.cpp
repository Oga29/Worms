#include "ModuleSceneStart.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
ModuleSceneStart::ModuleSceneStart(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneStart::~ModuleSceneStart()
{
}

bool ModuleSceneStart::Start()
{
	background = App->textures->Load("Assets/screens/wormsintroscreen.png");
	enter = App->textures->Load("Assets/screens/pressenter.png");
	counter = 0;
	return true;
}

update_status ModuleSceneStart::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->fadeToBlack->FadeToBlack(this, (Module*)App->scene_intro, 30.0f);
	}
	App->renderer->Blit(background, 0, 0, NULL);

	counter++;
	if ((counter / 60) % 2 == 0)
	{		
		App->renderer->Blit(enter, 0, 0, NULL);
	}

	return UPDATE_CONTINUE;
}

bool ModuleSceneStart::CleanUp()
{
	App->textures->Unload(background);
	App->textures->Unload(enter);
	return true;
}
