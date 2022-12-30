#ifndef __ENMAN_H__
#define __ENMAN_H__

#include "Entity.h"
#include "Module.h"
#include "p2List.h"


class EntityManager : public Module
{
public:
	EntityManager(Application* app, bool startEnabled);
	virtual ~EntityManager();
	//Module Functions
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(PhysObject* bodyA, PhysObject* bodyB);
	
	//Updates all the entities
	void UpdateAll(float dt, bool doLogic);
	//Util functions
	Entity* CreateEntity(EntityType type_, float x, float y, Team team = Team::UNKNOWN);
	void DestroyAllEntities();
	void DestroyEntity(Entity* entity);

private:
	SDL_Texture* wormsSprite;
	p2List<Entity*> entities;
	int testFont;
	int redTeamFont;
	int blueTeamFont;
	Application* app_;
	float accumulatedTime;
	float updateMsCycle;
	bool doLogic;
	int ExSFX;
};
#endif