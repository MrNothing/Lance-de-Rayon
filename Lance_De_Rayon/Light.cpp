#include "stdafx.h"
#include "Light.h"


Light::Light(LightType _type,Vector3 _position, Color8 _lightColor, Vector3 _direction)
{
	type=_type;
	position=_position;
	lightColor=_lightColor;
	direction=_direction;
}


Light::~Light(void)
{
}
