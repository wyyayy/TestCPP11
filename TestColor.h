#pragma once

#include "Runable.h"


struct RGB
{
	//    unsigned char R;
	//    unsigned char G;
	//    unsigned char B;
	int r;
	int g;
	int b;

};

struct YCbCr
{
	float y;
	float cb;
	float cr;
};

static float Min(float a, float b) { return a <= b ? a : b; }
static float Max(float a, float b) { return a >= b ? a : b; }

struct RGB YCbCrToRGB(struct YCbCr ycbcr);

struct YCbCr RGBToYCbCr(struct RGB rgb);


class TestColor : Runable
{
protected:


public:
	TestColor();
	~TestColor();

public:
	virtual void Run();

};

