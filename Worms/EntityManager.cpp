#include "EntityManager.h"
#include "Physics.h"
#include "Application.h"
#include "Worm.h"

#include "ModuleFonts.h"
#include "ModuleAudio.h"


EntityManager::EntityManager(Application* app, bool startEnabled) : Module(app, startEnabled), app_(app)
{
	
}

EntityManager::~EntityManager()
{
	CleanUp();
}


bool EntityManager::Start()
{
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	testFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);
	redTeamFont = App->fonts->Load("Assets/Fonts/rtype_font2.png", lookupTable, 2);
	blueTeamFont = App->fonts->Load("Assets/Fonts/rtype_font.png", lookupTable, 2);
	wormsSprite = App->textures->Load("Assets/Worms/sprites.png");
	ExSFX = App->audio->LoadFx("Assets/SFX/Explosion1.wav");
	return true;
}

update_status EntityManager::PreUpdate()
{
	for (p2List_item<Entity*>* ent = entities.getFirst(); ent != NULL; ent = ent->next)
	{
		if (ent->data->setPendingToDelete)
		{
			DestroyEntity(ent->data);
			break;
		}
	}

	return UPDATE_CONTINUE;
}
void EntityManager::UpdateAll(float dt, bool doLogic)
{
	if (!doLogic)
		return;

	for (p2List_item<Entity*>* ent = entities.getFirst(); ent != NULL; ent = ent->next)
	{
		ent->data->Update(dt);
		
		if (ent->data->type == EntityType::WORM)
		{	
			ent->data->Draw(wormsSprite);
			SString tmp("%s %i", ent->data->name.GetString(), ent->data->health);
			int font = 0;
			if (ent->data->team == Team::RED)
				font = redTeamFont;
			else if (ent->data->team == Team::BLUE)
				font = blueTeamFont;
			if (ent->data->isSelected)
			{
				App->fonts->BlitText(ent->data->GetPos().x - 20, ent->data->GetPos().y - 40, font, "selected");
			}
			App->fonts->BlitText(ent->data->GetPos().x - 20, ent->data->GetPos().y - 25, font, tmp.GetString());
		}
	}
	return;
}
update_status EntityManager::Update()
{
	accumulatedTime += App->dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;
	UpdateAll(App->dt, doLogic);
	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}
	
	return UPDATE_CONTINUE;

}

update_status EntityManager::PostUpdate()
{
	
	return UPDATE_CONTINUE;
}

bool EntityManager::CleanUp()
{
	DestroyAllEntities();
	return true;
}

void EntityManager::OnCollision(PhysObject* bodyA, PhysObject* bodyB)
{
	if (bodyA->object == ObjectType::BOMB && bodyB->object != ObjectType::PORTAL)
	{
		printf("\nBomb collision");
		bodyA->setPendingToDelete = true;
		if (bodyB->entity != nullptr)
		{
			bodyB->entity->health -= 50;
		}
		App->audio->PlayFx(ExSFX);
	}
	if (bodyA->object == ObjectType::BULLET && bodyA->entity != bodyB->entity)
	{
		bodyA->setPendingToDelete = true;
		if (bodyB->entity != nullptr)
		{
			bodyB->entity->health -= 30;
		}
		App->audio->PlayFx(ExSFX);
	}
	if (bodyA->object == ObjectType::GRENADE && bodyA->entity != bodyB->entity)
	{
		bodyA->setPendingToDelete = true;
		if (bodyB->entity != nullptr)
		{
			bodyB->entity->health -= 60;
		}
		App->audio->PlayFx(ExSFX);
	}
}


Entity* EntityManager::CreateEntity(EntityType type, float x, float y, Team team)
{
	Entity* ret = nullptr;
	Vector2d pos;
	pos.x = x;
	pos.y = y;
	switch (type)
	{
		case EntityType::WORM:
		{
			ret = new Worm(pos, team, app_, this);
			App->physics->world.CreateObject(ret->pbody);
			break;
		}
	}
	if (ret != nullptr) entities.add(ret);
	return ret;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	App->physics->world.DestroyObject(entity->pbody);
	entities.del(entities.findNode(entity));
	return;
}
void EntityManager::DestroyAllEntities()
{
	int i = 0;
	for (p2List_item<Entity*>* ent = entities.getFirst(); ent != NULL; ent = ent->next)
	{
		App->physics->world.DestroyObject(ent->data->pbody);
		i++;
	}
	entities.clear();
	printf("\nSuccesfully destroyed %i entities", i);
}