#pragma once
#include "Object3D.h"

class Cone:
	public Object3D
{
public:
	Cone(void);
	Cone(Vector3* _position, Vector3* _axis, float _angle, Color8* _color);
	~Cone(void);
	Vector3 getAxis(){return axis;}
	float getCosAngle(){return cosAngle;}
	Color8 getColor(){return color;}
	bool intersects(Ray ray, Vector3* hitPoint, Vector3* normal);
private:
	Vector3 axis;
	float cosAngle;
	Color8 color;
};

