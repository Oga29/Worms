#include "PhysObject.h"
#include <math.h>
#include "p2Point.h"



PhysObject::PhysObject(Shape shape_, Type type_, int x_, int y_, float w_, float h_)
{
	shape = shape_;
	type = type_;
	x = x_;
	y = y_;
	w = w_;
	h = h_;

	l = ol = x - w / 2;
	r = oR = x + w / 2;
	t = ot = y - h / 2;
	b = ob = y + h / 2;

	if (shape == Shape::CIRCLE)
	{
		r = w / 2;
	}
	limitSpeed.x = 300;
	limitSpeed.y = 300;

}

PhysObject::~PhysObject()
{
}

void PhysObject::SetLimit(Vector2d limit)
{
	limitSpeed = limit;
}

void PhysObject::AddForce(Vector2d force)
{
	v = v + force;
}



