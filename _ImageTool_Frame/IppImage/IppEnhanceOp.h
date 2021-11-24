#pragma once

#include "IppImage.h"

void IppAddOp(BYTE* p1, BYTE* p2, BYTE* p3, int size);
void IppAddOp(RGBBYTE* p1, RGBBYTE* p2, RGBBYTE* p3, int size);

void IppSubOp(BYTE* p1, BYTE* p2, BYTE* p3, int size);
void IppSubOp(RGBBYTE* p1, RGBBYTE* p2, RGBBYTE* p3, int size);

void IppAndOp(BYTE* p1, BYTE* p2, BYTE* p3, int size);
void IppAndOp(RGBBYTE* p1, RGBBYTE* p2, RGBBYTE* p3, int size);

void IppXorOp(BYTE* p1, BYTE* p2, BYTE* p3, int size);
void IppXorOp(RGBBYTE* p1, RGBBYTE* p2, RGBBYTE* p3, int size);
