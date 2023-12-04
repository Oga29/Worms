#include "PortalGun.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleAudio.h"
PortalGun::PortalGun(Application* app_, Module* listener_, Entity* ent_) : Weapon(app_, listener_, ent_)
{
	ammo = 2;
	id = 2;
	name.Create("portalgun");
	SFX = app->audio->LoadFx("Assets/SFX/Teleport.wav");
}

PortalGun::~PortalGun()
{
}

void PortalGun::Use(Vector2d position)
{
	if (ammo == 2)
	{
		app->scene_intro->portal->SetPortal1((float)app->input->GetMouseX(), (float)app->input->GetMouseY(), 10, 10, Shape::RECTANGLE, Type::STATIC, PortalType::ORANGE, "Orange");
		if (!app->scene_intro->portal->active1)
			app->physics->world.CreateObject(app->scene_intro->portal->p1);

		app->physics->world.portal = app->scene_intro->portal;
	}
	if (ammo == 1)
	{
		app->scene_intro->portal->SetPortal2((float)app->input->GetMouseX(), (float)app->input->GetMouseY(), 10, 10, Shape::RECTANGLE, Type::STATIC, PortalType::PURPLE, "Purple");
		if (!app->scene_intro->portal->active2)
			app->physics->world.CreateObject(app->scene_intro->portal->p2);
	}
	app->audio->PlayFx(SFX);
	ammo--;
}
