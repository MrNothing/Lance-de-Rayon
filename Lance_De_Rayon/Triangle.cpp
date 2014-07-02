#include "stdafx.h"
#include "Triangle.h"


Triangle::Triangle(void)
{
}

Triangle::Triangle(Vertice v0, Vertice v1, Vertice v2)
{
	V0 = v0;
	V1 = v1;
	V2 = v2;

	float avgDist0 = V0.getDistance(V1);
	float avgDist1 = V0.getDistance(V2);
	float avgDist2 = V1.getDistance(V2);
	avgDist = (avgDist0+avgDist1+avgDist2)/3;
}

Triangle::~Triangle(void)
{
}

void Triangle::updateAvgDist()
{
	float avgDist0 = V0.getDistance(V1);
	float avgDist1 = V0.getDistance(V2);
	float avgDist2 = V1.getDistance(V2);
	avgDist = (avgDist0+avgDist1+avgDist2)/3;

	vertices.push_back(V0);
	vertices.push_back(V1);
	vertices.push_back(V2);
}

Vector3 Triangle::getNormal()
{
	Vector3 vA = V1-V0;
	Vector3 vB = V2-V0;

	return vA*vB;
}

Color8 Triangle::getColorFromPoint(Vector3 point)
{
	float ratio0 = (1-V0.getDistance(point)/avgDist);

	float ratio1 = (1-V1.getDistance(point)/avgDist);

	float ratio2 = (1-V2.getDistance(point)/avgDist);

	return V0.getColor()*ratio0+V1.getColor()*ratio1+V2.getColor()*ratio2;
}

//MOLLER TRUMBORE method
bool Triangle::rayCast(Ray r, Vector3* I)
 { 
	 Vector3 v0=V0, v1=V1, v2=V2;
	 float t, u, v;
	 Vector3 edge1 = v1 - v0; 
	 Vector3 edge2 = v2 - v0; 
	 Vector3 pvec = r.dir*edge2; 
	 float det = dot(edge1, pvec); 
	 if (det > -SMALL_NUMBER && det < SMALL_NUMBER) 
		 return false; 
	 
	 float invDet = 1 / det; 
	 Vector3 tvec = r.origin - v0; 
	
	 u = dot(tvec, pvec) * invDet; 
	 if (u < 0 || u > 1) 
		 return false; 
	 Vector3 qvec = tvec*edge1; 
	 v = dot(r.dir, qvec) * invDet; 
	 if (v < 0 || u + v > 1) 
		 return false; 
	 t = dot(edge2, qvec) * invDet; 

	 (*I) = r.origin+r.dir*t;
	 return true; 
 }