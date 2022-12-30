#include "Granade.h"
#include "ModuleInput.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "Physics.h"
#include "ModuleAudio.h"
Granade::Granade(Application* app_, Module* listener_, Entity* ent_) : Weapon(app_, listener_, ent_)
{
	id = 3;
	name.Create("granade");
	ammo = 3;
	SFX = app->audio->LoadFx("Assets/SFX/MineArm.wav");
}

Granade::~Granade()
{
}

void Granade::Use(Vector2d position)
{
	if (ammo > 0)
	{
		ammo--;
		//TODO shot
		Vector2d m;
		m.x = app->input->GetMouseX();
		m.y = app->input->GetMouseY();

		Vector2d v;
		v.x = m.x - position.x;
		v.y = m.y - position.y;

		float dist = sqrtf(v.x * v.x + v.y * v.y);

		float dx = v.x / dist;
		float dy = v.y / dist;
		dx *= 1000;
		dy *= 1000;

		PhysObject* bullet = new PhysObject();
		bullet->x = position.x;
		bullet->y = position.y;
		bullet->mass = 500.0f;
		bullet->shape = Shape::RECTANGLE;
		bullet->w = 10;
		bullet->h = 10;
		bullet->v.x = dx;
		bullet->v.y = dy;
		bullet->listener = listener;
		bullet->entity = ent;
		bullet->restitution = 0.1f;
		bullet->cl = 0.0f;
		bullet->cd = 0.5f;
		bullet->name.Create("Ground2");
		bullet->type = Type::DYNAMIC;
		bullet->object = ObjectType::GRENADE;
		bullet->SetLimit(Vector2d(300.0f, 300.0f));
		app->physics->world.CreateObject(bullet);
		app->audio->PlayFx(SFX);
	}
}
