#include "stdafx.h"
#include "IppEnhanceOp.h"
#include "IppEnhance.h"

void IppInverse(IppByteImage& img)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i] = 255 - p[i];
	}
}

void IppInverse(IppRgbImage& img)
{
	int size = img.GetSize();
	RGBBYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i].r = 255 - p[i].r;
		p[i].g = 255 - p[i].g;
		p[i].b = 255 - p[i].b;
	}
}

void IppBrightness(IppByteImage& img, int n)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i] = limit(p[i] + n);
	}
}

void IppBrightness(IppRgbImage& img, int n)
{
	int size = img.GetSize();
	RGBBYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i].r = limit(p[i].r + n);
		p[i].b = limit(p[i].b + n);
		p[i].g = limit(p[i].g + n);
	}
}

void IppContrast(IppByteImage& img, int n)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();
	float n_ = n / 255.0f;

	for (int i = 0; i < size; i++)
	{
		p[i] = limit(p[i] + (p[i] - 128) * n_);
	}
}

void IppContrast(IppRgbImage& img, int n)
{
	int size = img.GetSize();
	RGBBYTE* p = img.GetPixels();
	float n_ = n / 255.0f;

	for (int i = 0; i < size; i++)
	{
		p[i].r = limit(p[i].r + (p[i].r - 128) * n_);
		p[i].g = limit(p[i].g + (p[i].g - 128) * n_);
		p[i].b = limit(p[i].b + (p[i].b - 128) * n_);
	}
}

bool IppOperator(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3, void (*op)(BYTE*, BYTE*, BYTE*, int))
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight())
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	BYTE* p1 = img1.GetPixels();
	BYTE* p2 = img2.GetPixels();
	BYTE* p3 = img3.GetPixels();

	op(p1, p2, p3, size);

	return true;
}

bool IppOperator(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3, void (*op)(RGBBYTE*, RGBBYTE*, RGBBYTE*, int))
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight())
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	RGBBYTE* p1 = img1.GetPixels();
	RGBBYTE* p2 = img2.GetPixels();
	RGBBYTE* p3 = img3.GetPixels();

	op(p1, p2, p3, size);

	return true;
}
