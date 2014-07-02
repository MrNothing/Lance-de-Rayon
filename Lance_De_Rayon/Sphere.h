#pragma once
#include "object3d.h"
#include "Color8.h"

class Sphere :
	public Object3D
{
public:
	Sphere(void);
	Sphere(const float radius, Vertice* positionAndColor);
	~Sphere(void);
	bool intersects(Ray ray, float* t);
	float getRadius(){return radius;}
	Color8 getColor(){return color;}
private:
	float radius;
	Color8 color;
};

