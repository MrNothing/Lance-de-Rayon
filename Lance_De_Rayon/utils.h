#pragma once

#include "stdafx.h"
#include <stdint.h>
#include <list>
#include <map>
#include "Vertice.h"

#define SMALL_NUMBER 1e-8 // we avoid some compliator imprecision
#define PI 3.14
#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z) // the dot vect product

enum Object3DType { MESH, PRIMITIVE_SPHERE, PRIMITIVE_CONE, PRIMITIVE_CUBE, PRIMITIVE_CYLINDER, PRIMITIVE_CAPSULE, PRIMITIVE_ELIPSE, PRIMITIVE_TORUS};
enum RenderMode { ISOMETRIC, PERSPECTIVE };
enum LightType { POINT, DIRECTIONAL, SPOT };

typedef struct {
//	std::list<Vertice> vertices;
} Face;

typedef struct {
	Vector3 position;
	Vector3 direction;
	Vector2 viewPort;
	float focalDistance;
	float fogDistance;
} Camera;

typedef struct {
	float a;
	float b;

	//y = ax+b
	float getY(float x)
	{
		return a*x+b;
	}
} AffineFunction;

typedef struct {
	Vector2 start;
	Vector2 end;

	void setLine(Vector2 p1, Vector2 p2)
	{
		start = p1;
		end = p2;
	}

} Segment;

typedef struct {
	Vector3 start;
	Vector3 end;

	void setLine(Vector3 p1, Vector3 p2)
	{
		start = p1;
		end = p2;
	}

} Segment3D;

typedef struct
{
	Vector3 origin;
	Vector3 dir;
} Ray;

typedef struct {
    int width;
    int height;
    Color8 *data;
    size_t size;
} ppm_image;

typedef struct {
	Color8 specularColor;
	Vector3 specularDir;
	float reflectiveness;
	float refraction;

	void init()
	{
		specularColor = Color8(0, 0, 0, 0);
		Vector3 specularDir = Vector3(0, 0, 0);
		reflectiveness = 0;
		refraction = 0;
	}

	void init(Color8* specColor, Vector3* specDir, float reflect, float refraction)
	{
		specularColor = *specColor;
		Vector3 specularDir = *specDir;
		reflectiveness = reflect;
		refraction = refraction;
	}
} Material;

typedef struct serializedData{
    int size;
	std::string data;
	std::map<std::string, serializedData> childs;
};