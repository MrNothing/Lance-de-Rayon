#include "stdafx.h"
#include "Cone.h"


Cone::Cone(void)
{
}

Cone::Cone(Vector3* _position, Vector3* _axis, float _angle, Color8* _color)
{
	setPosition(_position);
	axis = *_axis;
	cosAngle = cos(_angle);
	color = *_color;
	setType(PRIMITIVE_CONE);
	setAvgScale(axis.magnitude());
}

Cone::~Cone(void)
{
}

bool Cone::intersects(Ray ray, Vector3* hitPoint, Vector3* normal)
{
	//we need to define A, B, C coeficients of the quadriatic equation
	return false;
}