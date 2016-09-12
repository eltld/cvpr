#include "stdafx.h"
#include "Dib.h"
#include "DibEnhancement.h"
#include "RGBBYTE.h"

BOOL DibAddBitPlane(CDib &dib1, CDib &dib2,CDib &dib3)
{
	register int i, j;
	//dib1 -> 원본영상
	//dib2 -> 합성할 영상
	
	int w = dib1.GetWidth();
	int h = dib1.GetHeight();

	if (w != dib2.GetWidth() || h != dib2.GetHeight())
		return FALSE;
	dib3.CreateGrayImage(w, h);

	//원본 영상
	BYTE** ptr1 = dib1.GetPtr();
	//합성할 영상
	BYTE** ptr2 = dib2.GetPtr();
	//합성된 영상
	BYTE** ptr3 = dib3.GetPtr();
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			//마스킹할 이미지 영역값이 흰색이면
			if (ptr2[j][i] == 255)
				ptr3[j][i] = (ptr1[j][i] | (1 << 0)) ;
			else if (ptr2[j][i] == 0)
				ptr3[j][i] = (ptr1[j][i] & 254);
		}
	return TRUE;
}
void DibBitPlane(CDib &dib1, int bit, CDib& dib2)
{
	register int i, j;
	int w = dib1.GetWidth();
	int h = dib1.GetHeight();

	dib2.CreateGrayImage(w, h);
	BYTE** ptr1 = dib1.GetPtr();
	BYTE** ptr2 = dib2.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
			ptr2[j][i] = (ptr1[j][i] & (1 << bit)) ? 255 : 0;
}
BOOL DibOR(CDib& dib1, CDib& dib2, CDib& dib3)
{
	register int i, j;

	int w = dib1.GetWidth();
	int h = dib1.GetHeight();

	if (w != dib2.GetWidth() || h != dib2.GetHeight())
		return FALSE;
	dib3.CreateGrayImage(w, h);

	BYTE** ptr1 = dib1.GetPtr();
	BYTE** ptr2 = dib2.GetPtr();
	BYTE** ptr3 = dib3.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
			ptr3[j][i] = (BYTE)(ptr1[j][i] | ptr2[j][i]);

	return TRUE;
}
BOOL DibAND(CDib& dib1, CDib& dib2, CDib& dib3)
{
	register int i, j;

	int w = dib1.GetWidth();
	int h = dib1.GetHeight();

	if (w != dib2.GetWidth() || h != dib2.GetHeight())
		return FALSE;
	dib3.CreateGrayImage(w, h);

	BYTE** ptr1 = dib1.GetPtr();
	BYTE** ptr2 = dib2.GetPtr();
	BYTE** ptr3 = dib3.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
			ptr3[j][i] = limit(ptr1[j][i] & ptr2[j][i]);

	return TRUE;
}
BOOL DibDif(CDib& dib1, CDib& dib2, CDib& dib3)
{
	register int i, j;

	int w = dib1.GetWidth();
	int h = dib1.GetHeight();

	if (w != dib2.GetWidth() || h != dib2.GetHeight())
		return FALSE;
	dib3.CreateGrayImage(w, h);

	BYTE** ptr1 = dib1.GetPtr();
	BYTE** ptr2 = dib2.GetPtr();
	BYTE** ptr3 = dib3.GetPtr();

	int temp = 0;
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
			ptr3[j][i] = (BYTE)((temp >=0) ? temp:-temp );

	return TRUE;
}
BOOL DibAve(CDib& dib1, CDib& dib2, CDib& dib3)
{
	register int i, j;

	int w = dib1.GetWidth();
	int h = dib1.GetHeight();

	if (w != dib2.GetWidth() || h != dib2.GetHeight())
		return FALSE;
	dib3.CreateGrayImage(w, h);

	BYTE** ptr1 = dib1.GetPtr();
	BYTE** ptr2 = dib2.GetPtr();
	BYTE** ptr3 = dib3.GetPtr();
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			ptr3[j][i] = (BYTE)((ptr1[j][i] + ptr2[j][i]) / 2);
		}

	return TRUE;
}
BOOL DibSub(CDib& dib1, CDib& dib2, CDib& dib3)
{
	register int i, j;

	int w = dib1.GetWidth();
	int h = dib1.GetHeight();

	if (w != dib2.GetWidth() || h != dib2.GetHeight())
		return FALSE;
	dib3.CreateGrayImage(w, h);

	BYTE** ptr1 = dib1.GetPtr();
	BYTE** ptr2 = dib2.GetPtr();
	BYTE** ptr3 = dib3.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
			ptr3[j][i] = limit(ptr1[j][i] - ptr2[j][i]);

	return TRUE;
}
BOOL DibAdd(CDib& dib1, CDib& dib2, CDib& dib3)
{
	register int i, j;

	int w = dib1.GetWidth();
	int h = dib1.GetHeight();

	if (w != dib2.GetWidth() || h != dib2.GetHeight())
		return FALSE;
	dib3.CreateGrayImage(w, h);

	BYTE** ptr1 = dib1.GetPtr();
	BYTE** ptr2 = dib2.GetPtr();
	BYTE** ptr3 = dib3.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
			ptr3[j][i] = limit(ptr1[j][i] + ptr2[j][i]);

	return TRUE;
}

void DibHistEqual(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	//Calcuatle Histogram
	float hist[256];
	DibHistogram(dib, hist);

	//히스토그램 누적함수 계산
	double cdf[256] = { 0.0, 0 };
	cdf[0] = hist[0];
	for (i = 1; i < 256; i++)
		cdf[i] = cdf[i - 1] + hist[i];
	//Histogram Equalization
	BYTE** ptr = dib.GetPtr();
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
			ptr[j][i] = (BYTE)limit(cdf[ptr[j][i]] * 255);
}
void DibHistogram(CDib& dib, float histo[256])
{
	register int i, j;
	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	//Calucalte Histogram

	int temp[256];
	memset(temp, 0, sizeof(int) * 256);
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
			temp[ptr[j][i]]++;
	//Histogram Normalization
	float area = (float)w*h;
	for (i = 0; i < 256; i++)
		histo[i] = temp[i] / area;
}
void DibContrast(CDib& dib, int n)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	BYTE value;
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			value = ptr[j][i];
			ptr[j][i] = limit(value + ((value - 128) * n / 100));
		}
}
void DibBrightness(CDib& dib, int n)
{
	register int i, j;
	
	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
			ptr[j][i] = limit(ptr[j][i] + n);
}
void DibInverse(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	//if Grayscale image...
	if (dib.GetBitCount() == 8)
	{
		BYTE** ptr = dib.GetPtr();
		for (j = 0; j < h; j++)
			for (i = 0; i < w; i++)
				ptr[j][i] = 255 - ptr[j][i];
	}
	//if Color RGB image...
	else
	{
		RGBBYTE** ptr = dib.GetRGBPtr();

		for (j = 0; j < h; j++)
			for (i = 0; i < w; i++)
			{
				ptr[j][i].r = 255 - ptr[j][i].r;
				ptr[j][i].g = 255 - ptr[j][i].g;
				ptr[j][i].b = 255 - ptr[j][i].b;
			}
	}
}