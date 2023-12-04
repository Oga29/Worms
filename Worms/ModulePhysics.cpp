#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include "p2List.h"

// TODO 1: Include Box 2 header and library

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
	debug = false;
	world.Start(Integrator::VERLET, 0.0f, 100.0f);
	world.atmosphere.density = 1.0f;
	world.atmosphere.wind = Vector2d(0.0f, 0.0f);
	bomb = App->textures->Load("Assets/Worms/bomb.png");
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)
	world.PreUpdate();


	return UPDATE_CONTINUE;
}

update_status ModulePhysics::Update()
{
	world.Update(App->dt / 1000);
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;


	p2List_item<PhysObject*>* w = world.objects.getFirst();

	while (w != NULL)
	{
		if (w->data->shape == Shape::RECTANGLE)
		{
			SDL_Rect rect = { w->data->x - w->data->w / 2, w->data->y - w->data->h / 2, w->data->w,w->data->h };
			if (w->data->object == ObjectType::PORTAL)
			{
				if (w->data->portal == PortalType::ORANGE)
				{
					App->renderer->DrawQuad(rect, 255, 69, 0, 100, true);

				}

				else if (w->data->portal == PortalType::PURPLE)
				{
					App->renderer->DrawQuad(rect, 127, 0, 255, 100, true);

				}
			}
			else if (w->data->object == ObjectType::WATER)
			{
				App->renderer->DrawQuad(rect, 0, 123, 255, 100, true);
			}
			else if (w->data->object == ObjectType::BULLET)
			{
				App->renderer->DrawQuad(rect, 192, 192, 192, 255, true);
			}
			else if (w->data->object == ObjectType::GRENADE)
			{
				App->renderer->DrawQuad(rect, 75, 83, 32, 255, true);
			}
			else if (w->data->object == ObjectType::BOMB)
			{
				App->renderer->Blit(bomb, rect.x, rect.y);
			}
			else if (w->data->type == Type::STATIC)
			{
				App->renderer->DrawQuad(rect, 165, 42, 42, 255, true);
			}
		}

		//printf("\nName: %s, x: %f, y: %f", o->data->name.GetString(), o->data->x, o->data->y);
		if (w->data->y >= 800)
		{
			App->physics->world.DestroyObject(w->data);
		}


		w = w->next;
	}

	if (!debug)
		return UPDATE_CONTINUE;

	p2List_item<PhysObject*>* o = world.objects.getFirst();

	while (o != NULL)
	{
		if (o->data->shape == Shape::CIRCLE)
		{
			if (o->data->object == ObjectType::PORTAL)
			{
				if (o->data->portal == PortalType::ORANGE)
				{
					App->renderer->DrawCircle(o->data->x, o->data->y, o->data->radius, 255, 69, 0, 255);
				}
				else if (o->data->portal == PortalType::PURPLE)
				{
					App->renderer->DrawCircle(o->data->x, o->data->y, o->data->radius, 127, 0, 255, 255);
				}
			}
			if (o->data->object == ObjectType::WATER)
			{
				App->renderer->DrawCircle(o->data->x, o->data->y, o->data->radius, 0, 123, 255, 255);
			}
			else
			{
				App->renderer->DrawLine(o->data->x, o->data->y, o->data->x + o->data->v.x, o->data->y + o->data->v.y, 255, 0, 0, 255);
				App->renderer->DrawCircle(o->data->x, o->data->y, o->data->radius, 255, 0, 255, 255);

			}

		}
		if (o->data->shape == Shape::RECTANGLE)
		{
			SDL_Rect rect = { o->data->x - o->data->w / 2, o->data->y - o->data->h / 2, o->data->w,o->data->h };
			if (o->data->object == ObjectType::PORTAL)
			{
				if (o->data->portal == PortalType::ORANGE)
				{
					App->renderer->DrawQuad(rect, 255, 69, 0, 255, false);

				}

				else if (o->data->portal == PortalType::PURPLE)
				{
					App->renderer->DrawQuad(rect, 127, 0, 255, 255, false);

				}
			}
			else if (o->data->object == ObjectType::WATER)
			{
				App->renderer->DrawQuad(rect, 0, 123, 255, 255, false);
			}
			else
			{
				/*App->renderer->DrawLine(o->data->x, o->data->ot, o->data->x, o->data->ob, 255, 69, 0, 255);
				App->renderer->DrawLine(o->data->ol, o->data->y, o->data->oR, o->data->y, 255, 69, 0, 255);
				App->renderer->DrawLine(o->data->x, o->data->t, o->data->x, o->data->b, 0, 255, 0, 255);
				App->renderer->DrawLine(o->data->l, o->data->y, o->data->r, o->data->y, 0, 255, 0, 255);*/
				App->renderer->DrawLine(o->data->x, o->data->y, o->data->x + o->data->v.x, o->data->y + o->data->v.y, 255, 0, 0, 255);



				App->renderer->DrawQuad(rect, 0, 255, 0, 255, false);
			}
		}

		//printf("\nName: %s, x: %f, y: %f", o->data->name.GetString(), o->data->x, o->data->y);
		if (o->data->y >= 800)
		{
			App->physics->world.DestroyObject(o->data);
		}


		o = o->next;
	}

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	world.CleanUp();

	return true;
}
