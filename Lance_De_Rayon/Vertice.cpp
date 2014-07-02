#include "stdafx.h"
#include "Vertice.h"


Vertice::Vertice(float _x, float _y, float _z, Color8 _color)
{
	color = _color;
	x=_x;
	y=_y;
	z=_z;
}

Vertice::Vertice(void)
{
	color = Color8(255, 255, 255, 255);
	x = 0;
	y = 0;
	z = 0;
}

Vertice::~Vertice(void)
{
}

Vertice Vertice::operator-(Vector3 p2)
{
	Vertice diff;
	diff.x = x-p2.x;
	diff.y = y-p2.y;
	diff.z = z-p2.z;
	diff.color = color;
	return diff;
}

Vertice Vertice::operator+(Vector3 p2)
{
	Vertice diff;
	diff.x = x+p2.x;
	diff.y = y+p2.y;
	diff.z = z+p2.z;
	diff.color = color;
	return diff;
}
