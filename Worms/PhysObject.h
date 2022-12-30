#pragma once
#include "SString.h"
#include "Vector2d.h"
#include "Module.h"
#include "Entity.h"
enum class Shape
{
	NONE = -1,
	CIRCLE,
	RECTANGLE
};
enum class ObjectType
{
	STANDART = -1,
	PORTAL,
	PLANT,
	BOMB,
	BULLET,
	SENSOR,
	WATER,
	GRENADE
};
enum class PortalType
{
	NONE = -1,
	ORANGE,
	PURPLE
};
enum class Type
{
	NONE = -1,
	DYNAMIC,
	KYNEMATIC,
	STATIC
};

//Class: Ball
class PhysObject
{
public:
	PhysObject(){}
	PhysObject(Shape shape_, Type type_, int x_, int y_, float w_, float h_);
	~PhysObject();
	
	void SetLimit(Vector2d limit);
	void AddForce(Vector2d force);
	float w = 0.0f;
	float h = 0.0f;
	float radius = 0.0f;

	//New and old left, rigth, top and bottom coordinates
	float l, ol;
	float r, oR;
	float t, ot;
	float b, ob;
	// You could also use an array/vector
	float x, oX = 0.0f;
	float y, oY = 0.0f;

	// Velocity
	Vector2d v;

	// Acceleration
	Vector2d a;

	// Force (total) applied to the ball
	Vector2d f;

	//Player applied force
	Vector2d fp;

	// Mass
	float mass = 1.0f;

	// Aerodynamics stuff
	float surface = 2.0f; // Effective wet surface
	float cl = 1.2f; // Lift coefficient
	float cd = 0.4f; // Drag coefficient

	//Hydrodinamics stuff
	float density = 1.0f;

	
	float restitution = 1.0f; // Restitution coef
	float friction = 0.25f; // Friction coef (Wood on wood as reference 0.25)
	Module* listener;
	Entity* entity;
	Shape shape;
	Type type;
	SString name;
	ObjectType object = ObjectType::STANDART;
	PortalType portal = PortalType::NONE;
	bool setPendingToDelete = false;
	bool hasEnteredAPortal = false;
	bool hasLift = false;
	bool isOnWater = false;

	Vector2d limitSpeed;
	// Has physics enabled?
	bool physics_enabled = true;
	
};
