#include "stdafx.h"
#include "IppEnhanceOp.h"

void IppAddOp(BYTE* p1, BYTE* p2, BYTE* p3, int size)
{
	for (int i = 0; i < size; i++)
		p1[i] = limit(p2[i] + p3[i]);
}

void IppAddOp(RGBBYTE* p1, RGBBYTE* p2, RGBBYTE* p3, int size)
{
	for (int i = 0; i < size; i++)
	{
		p1[i].r = limit(p2[i].r + p3[i].r);
		p1[i].g = limit(p2[i].g + p3[i].g);
		p1[i].b = limit(p2[i].b + p3[i].b);
	}
}

void IppSubOp(BYTE* p1, BYTE* p2, BYTE* p3, int size)
{
	for (int i = 0; i < size; i++)
		p1[i] = limit(p2[i] - p3[i]);
}

void IppSubOp(RGBBYTE* p1, RGBBYTE* p2, RGBBYTE* p3, int size)
{
	for (int i = 0; i < size; i++)
	{
		p1[i].r = limit(p2[i].r - p3[i].r);
		p1[i].g = limit(p2[i].g - p3[i].g);
		p1[i].b = limit(p2[i].b - p3[i].b);
	}
}

void IppAndOp(BYTE* p1, BYTE* p2, BYTE* p3, int size)
{
	for (int i = 0; i < size; i++)
		p1[i] = limit(p2[i] && p3[i]);
}

void IppAndOp(RGBBYTE* p1, RGBBYTE* p2, RGBBYTE* p3, int size)
{
	for (int i = 0; i < size; i++)
	{
		p1[i].r = limit(p2[i].r && p3[i].r);
		p1[i].g = limit(p2[i].g && p3[i].g);
		p1[i].b = limit(p2[i].b && p3[i].b);
	}
}

void IppXorOp(BYTE* p1, BYTE* p2, BYTE* p3, int size)
{
	for (int i = 0; i < size; i++)
		p1[i] = limit(p2[i] ^ p3[i]);
}

void IppXorOp(RGBBYTE* p1, RGBBYTE* p2, RGBBYTE* p3, int size)
{
	for (int i = 0; i < size; i++)
	{
		p1[i].r = limit(p2[i].r ^ p3[i].r);
		p1[i].g = limit(p2[i].g ^ p3[i].g);
		p1[i].b = limit(p2[i].b ^ p3[i].b);
	}
}
