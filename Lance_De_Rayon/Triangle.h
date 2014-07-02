#pragma once
#include "utils.h"

class Triangle
{
public:
	Triangle(void);
	Triangle(Vertice v0, Vertice v1, Vertice v2);
	~Triangle(void);
	Vertice V0;
	Vertice V1;
	Vertice V2;
	std::list<Vertice> vertices;
	Color8 getColorFromPoint(Vector3 point);
	void updateAvgDist();
	float getAvgScale(){return avgDist;}
	bool rayCast(Ray r, Vector3* I);
	void setParent(Vector3 _parent){parent=_parent;}
	Vector3 getParent(){return parent;}
	Vector3 getNormal();
private:
	float avgDist;
	Vector3 parent;
};

