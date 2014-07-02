#pragma once
#include "utils.h"
#include "Scene.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Cone.h"
#include "Cylinder.h"

class Renderer
{
public:
	Renderer(void);
	Renderer(Scene scene);
	~Renderer(void);
	ppm_image render(RenderMode mode);
private:
	Scene mainScene;
	bool collision2D(std::list<Vertice> tab, Vector3 start);
	bool rayCast( Ray R, Triangle T, Vector3* I );
	bool rayCast(Ray r, Sphere s, Vector3* I, Vector3* N);
	bool rayCast(Ray r, Cone c, Vector3* I, Vector3* N);
	bool rayCast(Ray r, Cylinder c, Vector3* I, Vector3* N);
	bool rayCast(Ray r, Vertice* hitPoint);
	Vertice getGlobalDirectionalLightIntensity(Vector3* normal, float compatibility);
	Vertice getGlobalPointLightIntensity(Vector3* point);
};
