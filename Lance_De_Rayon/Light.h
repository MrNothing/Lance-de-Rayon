#pragma once
#include "utils.h"
#include "Vector3.h";
#include "Color8.h";

class Light
{
public:
	Light(void);
	Light(LightType _type,Vector3 _position, Color8 _lightColor, Vector3 _direction);
	LightType getType(){return type;}
	Vector3 getPosition(){return position;}
	Color8 getColor(){return lightColor;}
	Vector3 getDirection(){return direction;}
	~Light(void);
private:
	LightType type;
	Vector3 position;
	Color8 lightColor;
	Vector3 direction;
};

