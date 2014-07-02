#include "stdafx.h"
#include "Color8.h"
#include <math.h>

Color8::Color8(void)
{
	r=0;
	g=0;
	b=0;
	a=0;
}

Color8::Color8(int _r, int _g, int _b, int _a)
{
	if(_r>255)
		_r=255;
	if(_g>255)
		_g=255;
	if(_b>255)
		_b=255;
	if(_a>255)
		_a=255;

	if(_r<25)
		_r=25;
	if(_g<25)
		_g=25;
	if(_b<25)
		_b=25;
	if(_a<25)
		_a=25;

	r = _r;
	g = _g;
	b = _b;
	a = _a;

	
}

Color8::~Color8(void)
{
}

int Color8::magnitude()
{
	return abs(a)+abs(r)+abs(g)+abs(b);
}

float Color8::sizeNoAlpha()
{
	return (abs(float(r))+abs(float(g))+abs(float(b)))/3;
}

Color8 Color8::operator*(float val)
{
	return Color8(r*val, g*val, b*val, a*val);
}

Color8 Color8::operator+(Color8 val)
{
	return Color8(r+val.r, g+val.g, b+val.b, a+val.a);
}

Color8 Color8::operator-(Color8 val)
{
	return Color8(r-val.r, g-val.g, b-val.b, a-val.a);
}

void Color8::fixColor()
{
	if(r>255)
		r=255;
	if(g>255)
		g=255;
	if(b>255)
		b=255;
	if(a>255)
		a=255;

	if(r<0)
		r=0;
	if(g<0)
		g=0;
	if(b<0)
		b=0;
	if(a<0)
		a=0;
}