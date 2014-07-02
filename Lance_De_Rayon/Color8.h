#pragma once
class Color8
{
public:
	Color8(void);
	~Color8(void);
	Color8(int _r, int _g, int _b, int _a);

	int magnitude();
	float sizeNoAlpha();
	unsigned char r,g,b,a;
	void setColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
	Color8 operator*(float val);
	Color8 operator+(Color8 val);
	Color8 operator-(Color8 val);
	void fixColor();
};

