#include "stdafx.h"
#include "TestColor.h"


struct RGB YCbCrToRGB(struct YCbCr ycbcr)
{
	// float4(1.0, +0.0000, +1.4020, -0.7010),
	// float4(1.0, -0.3441, -0.7141, +0.5291),
	// float4(1.0, +1.7720, +0.0000, -0.8860),
	// float4(0.0, +0.0000, +0.0000, +1.0000)

	float r = ycbcr.y + 1.4020f * ycbcr.cr - 0.7010f;
	float g = ycbcr.y - 0.3441f * ycbcr.cb - 0.7141f * ycbcr.cr + 0.5291f;
	float b = ycbcr.y + 1.7720f * ycbcr.cb - 0.8860f;

	struct RGB rgb;
	rgb.r = r * 255;
	rgb.g = g * 255;
	rgb.b = b * 255;

	return rgb;
}

struct YCbCr RGBToYCbCr(struct RGB rgb)
{
	float fr = (float)rgb.r / 255;
	float fg = (float)rgb.g / 255;
	float fb = (float)rgb.b / 255;

/*
	0.29899	0.58702	0.11399	0.00000
	- 0.16873 - 0.33127	0.50001	0.50000
	0.50001 - 0.41870 - 0.08131	0.50000
	0.00000	0.00000	0.00000	1.00000
*/

	struct YCbCr ycbcr;
	ycbcr.y = (float)(0.29899f * fr + 0.58702f * fg + 0.11399f * fb);
	ycbcr.cb = (float)(-0.16873f * fr - 0.33127f * fg + 0.50001f * fb + 0.5f);
	ycbcr.cr = (float)(0.5000 * fr - 0.41870f * fg - 0.08131f * fb + 0.5f);

	return ycbcr;
}

TestColor::TestColor()
{
}

TestColor::~TestColor()
{
}

void TestColor::Run()
{
	YCbCr ycbcr;

	/// 81, 128, 150

	ycbcr.y = 0.3f;
	ycbcr.cb = 0.4f;
	ycbcr.cr = 0.5f;
	RGB rgb = YCbCrToRGB(ycbcr); /// 76 85 31	0.298 0.333 0.122

	YCbCr original = RGBToYCbCr(rgb);
}

