#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "p2List.h"
#include "p2Point.h"
#include "SString.h"
#include "PhysObject.h"
#include "Portal.h"
#define DAMPEN 0.975
struct Atmosphere
{
	float density;
	Vector2d wind;
};
enum class Integrator
{
	NONE = -1,
	VERLET,
	SEULER,
	IEULER

};
class Physics
{
public:
	Physics();
	~Physics();

	bool Start(Integrator _integrator, float gx, float gy);
	bool PreUpdate();
	bool Update(float dt);

	bool CleanUp();
	//Elastic Collision Solver
	void ComputeCollision(PhysObject* o, PhysObject* c);
	//Ground Collision solver
	void ComputeOverlaping(PhysObject* o, PhysObject* c);

	//Adding / Deleting objects
	void CreateObject(PhysObject* obj);
	void DestroyObject(PhysObject* obj);

	void ApplHydrodinamics(PhysObject* a, PhysObject* b);

	//Integrator scheme's
	void IntegratorVelocityVerlet(PhysObject* obj, float dt);
	void IntegratorVelocitySymplecticEuler(PhysObject* obj, float dt);
	void IntegratorVelocityImplicitEuler(PhysObject* obj, float dt);
	Portal* portal;
	PhysObject* water;
	Atmosphere atmosphere;
	Integrator integrator = Integrator::IEULER;
	p2List<PhysObject*> objects;
private:
	float gravityX, gravityY;
};
#endif