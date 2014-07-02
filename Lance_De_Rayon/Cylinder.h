#pragma once
#include "Object3D.h"
class Cylinder:
	public Object3D
{
public:
	Cylinder(void);
	Cylinder(Vector3* _position, Vector3* _axis, float _radius, Color8* _color);
	~Cylinder(void);
	Vector3 getAxis(){return axis;}
	Color8 getColor(){return color;}
	float getRadius(){return radius;}
	bool intersects(Ray ray, Vector3* hitPoint, Vector3* normal);
public:
	Vector3 axis;
	Color8 color;
	float radius;
};
