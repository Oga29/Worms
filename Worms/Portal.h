#pragma once
#include "PhysObject.h"


class Portal
{
public:
	Portal();
	~Portal();
	void SetPortal1(float x, float y, float w, float h, Shape shape, Type type, PortalType ptype, const char* name);
	void SetPortal2(float x, float y, float w, float h, Shape shape, Type type, PortalType ptype, const char* name);

	PhysObject* p1 = nullptr;
	PhysObject* p2 = nullptr;
	bool active1 = false;
	bool active2 = false;
	void Teletransport(PhysObject* entry, PhysObject* obj);
};
