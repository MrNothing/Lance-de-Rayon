#include "stdafx.h"
#include "Object3D.h"
#include "Triangle.h"
#include <math.h>

Object3D::Object3D(void)
{
}

Object3D::Object3D(Object3DType _type, std::list<Triangle> _tris, Vector3 _position)
{
	type=_type;
	tris=_tris;
	position = _position;
	rotation = Vector3();
	scalev = Vector3();
	material.init();

	float _avgScale = 0;

	for(std::list<Triangle>::iterator it = tris.begin(); it != tris.end(); it++) 
	{
		(*it).setParent(_position);
		_avgScale+=(*it).getAvgScale();
	}

	_avgScale=_avgScale/tris.size();

	avgScale = _avgScale;
}

Object3D::~Object3D(void)
{
}

void Object3D::rotate(Vector3* _rotation)
{
	rotation=rotation+*_rotation;
}

void Object3D::rotate(float _rx, float _ry, float _rz)
{
	rotation.x+=_rx;
	rotation.y+=_ry;
	rotation.z+=_rz;
}

void Object3D::scale(Vector3* _scale)
{
	scalev=scalev+*_scale;
	avgScale*=scalev.magnitude()/3;
}

void Object3D::translate(Vector3* _offset)
{
	position=position+*_offset;
}

std::list<Face> Object3D::getFacesWithGlobalPosition()
{
	std::list<Face> facesWithGlobalPosition;
	for(std::list<Face>::iterator it = faces.begin(); it != faces.end(); it++) 
	{
		Face newFace;
		Face oldFace = *it;

		/*for(std::list<Vertice>::iterator it2 = oldFace.vertices.begin(); it2 != oldFace.vertices.end(); it2++) 
		{
			Color8 color;
			//color.setColor((*it2).getColor().r, (*it2).getColor().g, (*it2).getColor().b, (*it2).getColor().a);

			//Vertice* vertice = new Vertice((*it2).x+position.x, (*it2).y+position.y,(*it2).z+position.z, color);
			
			//newFace.vertices.push_back(*vertice);
		}*/

		facesWithGlobalPosition.push_back(newFace);
	}

	return facesWithGlobalPosition;
}

std::list<Triangle> Object3D::getTrianglesWithGlobalPosition()
{
	std::list<Triangle> trisWithGlobalPosition;
	for(std::list<Triangle>::iterator it = tris.begin(); it != tris.end(); it++) 
	{
		Triangle newFace;
		Triangle oldFace = *it;

		//vert 0
		{
			Color8 color;
			color.setColor(oldFace.V0.getColor().r, oldFace.V0.getColor().g, oldFace.V0.getColor().b, oldFace.V0.getColor().a);

			Vertice* vertice = &Vertice(oldFace.V0.x, oldFace.V0.y,oldFace.V0.z, color);
			if(rotation.magnitude()>0)
			{
				vertice = pivotPointWithAxisXFromCenter(*vertice, rotation.x);
				vertice = pivotPointWithAxisYFromCenter(*vertice, rotation.y);
				vertice = pivotPointWithAxisZFromCenter(*vertice, rotation.z);
			}

			if(scalev.magnitude()>0)
			{
				vertice->x *= scalev.x;
				vertice->y *= scalev.y;
				vertice->z *= scalev.z;
			}

			*vertice=*vertice+position;

			newFace.V0 = *vertice;
		}

		//vert 1
		{
			Color8 color;
			color.setColor(oldFace.V1.getColor().r, oldFace.V1.getColor().g, oldFace.V1.getColor().b, oldFace.V1.getColor().a);

			Vertice* vertice = &Vertice(oldFace.V1.x, oldFace.V1.y,oldFace.V1.z, color);
			
			if(rotation.magnitude()>0)
			{
				vertice = pivotPointWithAxisXFromCenter(*vertice, rotation.x);
				vertice = pivotPointWithAxisYFromCenter(*vertice, rotation.y);
				vertice = pivotPointWithAxisZFromCenter(*vertice, rotation.z);
			}

			if(scalev.magnitude()>0)
			{
				vertice->x *= scalev.x;
				vertice->y *= scalev.y;
				vertice->z *= scalev.z;
			}

			*vertice=*vertice+position;

			newFace.V1 = *vertice;
		}

		//vert 2
		{
			Color8 color;
			color.setColor(oldFace.V2.getColor().r, oldFace.V2.getColor().g, oldFace.V2.getColor().b, oldFace.V2.getColor().a);

			Vertice* vertice = &Vertice(oldFace.V2.x, oldFace.V2.y,oldFace.V2.z, color);
			
			if(rotation.magnitude()>0)
			{
				vertice = pivotPointWithAxisXFromCenter(*vertice, rotation.x);
				vertice = pivotPointWithAxisYFromCenter(*vertice, rotation.y);
				vertice = pivotPointWithAxisZFromCenter(*vertice, rotation.z);
			}

			if(scalev.magnitude()>0)
			{
				vertice->x *= scalev.x;
				vertice->y *= scalev.y;
				vertice->z *= scalev.z;
			}

			*vertice=*vertice+position;

			newFace.V2 = *vertice;
		}

		newFace.updateAvgDist();
		trisWithGlobalPosition.push_back(newFace);
	}

	return trisWithGlobalPosition;
}

Vertice* Object3D::pivotPointWithAxisXFromCenter(Vertice point, float angle)
{
	float Rotated_z = point.z * cos( angle ) - point.y * sin( angle );
	float Rotated_y = point.z * sin( angle ) + point.y * cos( angle ); 
	return (new Vertice(point.x, Rotated_y, Rotated_z, point.getColor()));
}

Vertice* Object3D::pivotPointWithAxisYFromCenter(Vertice point, float angle)
{
	float Rotated_x = point.x * cos( angle ) - point.z * sin( angle );
	float Rotated_z = point.x * sin( angle ) + point.z * cos( angle ); 
	return (new Vertice(Rotated_x, point.y, Rotated_z, point.getColor()));
}

Vertice* Object3D::pivotPointWithAxisZFromCenter(Vertice point, float angle)
{
	float Rotated_x = point.x * cos( angle ) - point.y * sin( angle );
	float Rotated_y = point.x * sin( angle ) + point.y * cos( angle ); 
	return (new Vertice(Rotated_x, Rotated_y, point.z, point.getColor()));
}