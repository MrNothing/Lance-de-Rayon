#include "stdafx.h"
#include "Cylinder.h"


Cylinder::Cylinder(void)
{
}

Cylinder::Cylinder(Vector3* _position, Vector3* _axis, float _radius, Color8* _color)
{
	setPosition(_position);
	axis = *_axis;
	radius = _radius;
	color = *_color;
	setType(PRIMITIVE_CYLINDER);
}

Cylinder::~Cylinder(void)
{
}

bool Cylinder::intersects(Ray ray, Vector3* hitPoint, Vector3* normal)
{
	//the ray has a parametric equation: q=p+vt, we are looking for t...
	float t;

	Vector3 pa = getPosition();
	Vector3 va = axis;

	//deltaP = p-pa
	Vector3 deltaP = ray.origin-pa;
	
	//we need to define A, B, C coeficients of the quadriatic equation
	Vector3 AB = axis;
	Vector3 AO = ray.origin - getPosition();
	Vector3 AOxAB = AO*AB;
	Vector3 VxAB  = ray.dir*AB;
	double ab2 = dot(AB,AB);
	double A = dot(VxAB,VxAB);
	double B = 2 * dot(VxAB,AOxAB);
	double C = dot(AOxAB,AOxAB) - (radius*radius * ab2);

	//now all we need to do is solve the Ax²+Bx+C=0 equation

	//get Delta = b²-4ac

	float delta = B*B-4*A*C;

	//delta <0 no solutions...
	if(delta<0)
	{
		return false;
	}

	//delta==0 one solution exist:
	if(delta==0)
	{
		t=-B/2*A;
	}

	//delta>0 two solutions exist, we need the closest point, so the smallest value of t prevails.
	if(delta>0)
	{
		float t1 = (-B-sqrt(delta))/(2*A);
		float t2 = (-B+sqrt(delta))/(2*A);

		if(t1>t2)
		{
			t=t1;
		}
		else
		{
			t=t2;
		}
	}

	//now that we have t, we solve the parametric equation of the ray to get the hitpoint
	*hitPoint = ray.origin+ray.dir*t;
	if(ray.origin.getDistance(*hitPoint)>150)
		return false;

	//we can get the normal with the hit point:
	*normal = *hitPoint*getPosition();

	return true;
}