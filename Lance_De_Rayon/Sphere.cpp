#include "stdafx.h"
#include "Sphere.h"


Sphere::Sphere(void)
{
}

Sphere::Sphere(const float _radius, Vertice* positionAndColor)
{
	radius = _radius;
	setPosition((Vector3*)positionAndColor);
	color = positionAndColor->getColor();
	getMaterial()->init();
	setType(PRIMITIVE_SPHERE);
	setAvgScale(radius*2);
}

Sphere::~Sphere(void)
{
}

bool Sphere::intersects(Ray r, float* t)
{
	Ray ray;
	ray.dir= r.dir;
	ray.origin = getPosition()-r.origin;
	//Compute A, B and C coefficients
	float a = dot(ray.dir, ray.dir);
	float b = 2 * dot(ray.dir, ray.origin);
	float c = dot(ray.origin, ray.origin) - (radius * radius);

	//Find discriminant
	float disc = b * b - 4 * a * c;
    
	// if discriminant is negative there are no real roots, so return 
	// false as ray misses sphere
	if (disc < 0)
		return false;

	// compute q as described above
	float distSqrt = sqrtf(disc);
	float q;
	if (b < 0)
		q = (-b - distSqrt)/2.0;
	else
		q = (-b + distSqrt)/2.0;

	// compute t0 and t1
	float t0 = q / a;
	float t1 = c / q;

	// make sure t0 is smaller than t1
	if (t0 > t1)
	{
		// if t0 is bigger than t1 swap them around
		float temp = t0;
		t0 = t1;
		t1 = temp;
	}

	// if t1 is less than zero, the object is in the ray's negative direction
	// and consequently the ray misses the sphere
	if (t1 < 0)
		return false;

	// if t0 is less than zero, the intersection point is at t1
	if (t0 < 0)
	{
		*t = t1;
		return true;
	}
	// else the intersection point is at t0
	else
	{
		*t = t0;
		return true;
	}
}
