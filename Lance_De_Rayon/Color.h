#pragma once
class Color
{
public:
	Color(void);
	~Color(void);
	float r,g,b,a;
	void setColor(float _r, float _g, float _b, float _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
};

