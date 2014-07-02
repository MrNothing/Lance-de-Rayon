#pragma once
#include "utils.h"
#include "Color.h"
#include "Triangle.h"

class Object3D
{
public:
	Object3D(void);
	Object3D(Object3DType _type, std::list<Triangle> _tris, Vector3 _position);
	~Object3D(void);
	std::list<Face> getFaces(){ return faces; }
	std::list<Face> getFacesWithGlobalPosition();
	std::list<Triangle> getTrianglesWithGlobalPosition();
	float getAvgScale(){return avgScale;}
	void setAvgScale(float val){avgScale = val;}
	Vector3 getPosition(){return position;}
	void setPosition(Vector3* _position){position = *_position;}
	void rotate(Vector3* _rotation);
	void rotate(float _rx, float _ry, float _rz);
	void scale(Vector3* _scale);
	void translate(Vector3* _offset);
	Material* getMaterial(){return &material;}
	void setType(Object3DType _type){type=_type;}
	Object3DType getType(){return type;}
private:
	
	Object3DType type;
	Vector3 position;
	Vector3 rotation;
	Vector3 scalev;

	std::list<Face> faces;
	std::list<Triangle> tris;
	Material material;

	float avgScale;

	Vertice* pivotPointWithAxisXFromCenter(Vertice point, float rotation);
	Vertice* pivotPointWithAxisYFromCenter(Vertice point, float rotation);
	Vertice* pivotPointWithAxisZFromCenter(Vertice point, float rotation);
};

