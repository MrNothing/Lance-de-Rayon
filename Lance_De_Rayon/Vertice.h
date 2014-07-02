#pragma once
#include "vector3.h"
#include "Color8.h"
class Vertice :
	public Vector3
{
public:
	Vertice(float _x, float _y, float _z, Color8 _color);
	Vertice(void);
	~Vertice(void);
	Color8 getColor(){return color;}
	void setColor(Color8* _color){ color = *_color;}
	Vertice operator-(Vector3 p2);
	Vertice operator+(Vector3 p2);
private:
	Color8 color;
};

