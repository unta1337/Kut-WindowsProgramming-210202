#pragma once

#include "IppImage.h"
#include "IppEnhanceOp.h"

void IppInverse(IppByteImage& img);
void IppInverse(IppRgbImage& img);

void IppBrightness(IppByteImage& img, int n);
void IppBrightness(IppRgbImage& img, int n);

void IppContrast(IppByteImage& img, int n);
void IppContrast(IppRgbImage& img, int n);

bool IppOperator(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3, void (*op)(BYTE*, BYTE*, BYTE*, int));
bool IppOperator(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3, void (*op)(RGBBYTE*, RGBBYTE*, RGBBYTE*, int));
