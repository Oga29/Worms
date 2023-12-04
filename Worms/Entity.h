#pragma once
#include "Vector2d.h"
#include "Animation.h"
#include "SString.h"
#include "HandGun.h"
#include "p2List.h"

enum class EntityType
{
	UNKNOWN = -1,
	WORM
};
enum class Team
{
	UNKNOWN = -1,
	RED,
	BLUE
};
class Application;
struct SDL_Texture;
class PhysObject;
class Module;
class EntityManager;
class Weapon;
class Entity
{
public:
	Entity(){}
	Entity(EntityType type_, Vector2d position_, Team team_, Application* app, Module* listener_) : type(type_), position(position_), team(team_), app_(app), listener(listener_){}

	virtual void Update(float dt){}
	virtual void Draw(SDL_Texture* tex){}

	Vector2d GetPos() { return position; }

public:
	Application* app_;
	EntityType type;
	bool isSelected;
	bool setPendingToDelete;
	Vector2d position;
	SDL_Texture* sprite;
	PhysObject* pbody;
	Animation anim;
	Team team;
	SString name;
	int health;
	bool endTurn = false;
	Module* listener;
	p2List_item<Weapon*>* currentWeapon;
	p2List<Weapon*> guns;
	bool isGrounded;
};