#include "Portal.h"





Portal::Portal()
{
}

Portal::~Portal()
{
	delete p1;
	delete p2;
}

void Portal::SetPortal1(float x, float y, float w, float h, Shape shape, Type type, PortalType ptype, const char * name)
{
	if (p1 == nullptr)
	{
		p1 = new PhysObject(shape, type, x, y, w, h);
		p1->name.Create(name);
		p1->object = ObjectType::PORTAL;
		p1->portal = ptype;
		
	}
	else
	{
		active1 = true;
		p1->x = x;
		p1->y = y;
	}
	
}

void Portal::SetPortal2(float x, float y, float w, float h, Shape shape, Type type, PortalType ptype, const char* name)
{
	if (p2 == nullptr)
	{
		p2 = new PhysObject(shape, type, x, y, w, h);
		p2->name.Create(name);
		p2->object = ObjectType::PORTAL;
		p2->portal = ptype;
		
	}
	else
	{
		active2 = true;
		p2->x = x;
		p2->y = y;
	}
}

void Portal::Teletransport(PhysObject* entry, PhysObject* obj)
{
	if (p1 != nullptr && p2 != nullptr)
	{
		if (!obj->hasEnteredAPortal)
		{
			if (entry == p1)
			{
				obj->x = p2->x;
				obj->y = p2->y;

			}
			if (entry == p2)
			{

				obj->x = p1->x;
				obj->y = p1->y;

			}
		}
		obj->hasEnteredAPortal = true;
	}

}