#pragma once

#include "IppImage.h"

void IppInverse(IppByteImage& img);
void IppInverse(IppRgbImage& img);

void IppBrightness(IppByteImage& img, int n);
void IppBrightness(IppRgbImage& img, int n);
