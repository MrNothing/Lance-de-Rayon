#pragma once
#include "stdafx.h"
#include "Vertice.h"
#include "Triangle.h"
#include <list>

std::list<Triangle> getCube(float scale, Color8 color)
{
	std::list<Triangle> tris;
	
	Triangle t_a = *(new Triangle(*(new Vertice(-scale, scale, -scale, color)),*(new Vertice(scale, scale, -scale, color)), *(new Vertice(-scale, -scale, -scale, color))));
	Triangle t_b = *(new Triangle(*(new Vertice(scale, -scale, -scale, color)),*(new Vertice(scale, scale, -scale, color)), *(new Vertice(-scale, -scale, -scale, color))));
	Triangle t_c = *(new Triangle(*(new Vertice(scale, scale, -scale, color)),*(new Vertice(scale, -scale, -scale, color)), *(new Vertice(scale, scale, scale, color))));
	Triangle t_d = *(new Triangle(*(new Vertice(scale, -scale, -scale, color)),*(new Vertice(scale, -scale, scale, color)), *(new Vertice(scale, scale, scale, color))));
	Triangle t_e = *(new Triangle(*(new Vertice(-scale, scale, -scale, color)),*(new Vertice(-scale, scale, scale, color)), *(new Vertice(scale, scale, -scale, color))));
	Triangle t_f = *(new Triangle(*(new Vertice(scale, scale, -scale, color)),*(new Vertice(-scale, scale, scale, color)), *(new Vertice(scale, scale, scale, color))));
	Triangle t_g = *(new Triangle(*(new Vertice(-scale, scale, scale, color)),*(new Vertice(-scale, scale, -scale, color)), *(new Vertice(-scale, -scale, -scale, color))));
	Triangle t_h = *(new Triangle(*(new Vertice(-scale, -scale, -scale, color)),*(new Vertice(-scale, scale, -scale, color)), *(new Vertice(-scale, -scale, scale, color))));
	Triangle t_i = *(new Triangle(*(new Vertice(-scale, -scale, -scale, color)),*(new Vertice(-scale, -scale, scale, color)), *(new Vertice(scale, -scale, scale, color))));
	Triangle t_j = *(new Triangle(*(new Vertice(-scale, -scale, -scale, color)),*(new Vertice(scale, -scale, -scale, color)), *(new Vertice(scale, -scale, scale, color))));
	Triangle t_k = *(new Triangle(*(new Vertice(scale, scale, scale, color)),*(new Vertice(-scale, scale, scale, color)), *(new Vertice(scale, -scale, scale, color))));
	Triangle t_l = *(new Triangle(*(new Vertice(-scale, -scale, scale, color)),*(new Vertice(-scale, scale, scale, color)), *(new Vertice(scale, -scale, scale, color))));
	
	tris.push_back(t_a);
	tris.push_back(t_b);
	tris.push_back(t_c);
	tris.push_back(t_d);
	tris.push_back(t_e);
	tris.push_back(t_f);
	tris.push_back(t_g);
	tris.push_back(t_h);
	tris.push_back(t_i);
	tris.push_back(t_j);
	tris.push_back(t_k);
	tris.push_back(t_l);

	return tris;
}

std::list<Triangle> getPyramid(float scale, Color8 color)
{
	std::list<Triangle> tris;
	
	Triangle t_a = *(new Triangle(*(new Vertice(-scale, 0, 0, color)),*(new Vertice(0, 0, -scale, color)), *(new Vertice(scale, 0, scale/2, color))));
	Triangle t_b = *(new Triangle(*(new Vertice(-scale, 0, 0, color)),*(new Vertice(0, 0, -scale, color)), *(new Vertice(0, 1.5f*scale, 0, color))));
	Triangle t_c = *(new Triangle(*(new Vertice(0, 0, -scale, color)),*(new Vertice(scale, 0, scale/2, color)), *(new Vertice(0, 1.5f*scale, 0, color))));
	Triangle t_d = *(new Triangle(*(new Vertice(-scale, 0, 0, color)),*(new Vertice(scale, 0, scale/2, color)), *(new Vertice(0, 1.5f*scale, 0, color))));
	
	tris.push_back(t_a);
	tris.push_back(t_b);
	tris.push_back(t_c);
	tris.push_back(t_d);

	return tris;
}

std::list<Triangle> getPlane(float scale, Color8 color)
{
	std::list<Triangle> tris;
	
	Vertice*v1=new Vertice(0, 0, 0, color);
	Vertice*v2=new Vertice(0, 0, scale, color);
	Vertice*v3=new Vertice(scale, 0, 0, color);

	Vertice*v4=new Vertice(scale, 0, scale, color);
	Vertice*v5=new Vertice(0, 0, scale, color);
	Vertice*v6=new Vertice(scale, 0, 0, color);

	Triangle* t_a = new Triangle(*v1, *v2, *v3);
	Triangle* t_b = new Triangle(*v4, *v5, *v6);
	tris.push_back(*t_a);
	tris.push_back(*t_b);
	
	return tris;
}

std::list<Triangle> getTriangle(float scale, Color8 color)
{
	std::list<Triangle> tris;

	Vertice*v1=new Vertice(0, 0, 0, color);
	Vertice*v2=new Vertice(0, scale, 0, color);
	Vertice*v3=new Vertice(scale, 0, 0, color);

	Triangle* t_a = new Triangle(*v1, *v2, *v3);

	tris.push_back(*t_a);

	return tris;
}