#include "stdafx.h"
#include "Dib.h"
#include "DibSegment.h"
#include "DibEnhancement.h"
#include <cstdlib>
#define K -1.2
void PreProcessing(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			if (ptr[j][i] < 50)
				ptr[j][i] = 0;
		}
}
int Gl_DibBinarizationIterative(CDib& dib)
{
	register int i;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	float hist[256] = { 0, };

	//Normalized histogram을 구함. 
	DibHistogram(dib, hist);
	//초기 임계값 설정
	int T, Told;

	float sum = 0.f;
	for (i = 0; i < 256; i++)
	{
		sum += (i*hist[i]);
	}
	T = (int)sum;

	//반복에 의한 임계값 설정
	float a1, b1, u1, a2, b2, u2;

	do
	{
		Told = T;

		a1 = b1 = 0;
		for (i = 0; i <= Told; i++)
		{
			a1 += (i*hist[i]);
			b1 += hist[i];
		}
		u1 = a1 / b1;

		a2 = b2 = 0;
		for (i = Told + 1; i < 256; i++)
		{
			a2 += (i*hist[i]);
			b2 += hist[i];
		}
		u2 = a2 / b2;

		if (b1 == 0)
			b1 = 1.f;
		if (b2 == 0)
			b2 = 1.f;
		T = (int)((u1 + u2) / 2);
	} while (T == Told);
	return T;
}
void Gl_DibBinarization(CDib &dib, int th)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			ptr[j][i] = (ptr[j][i] > th) ? 255 : 0;
		}
}

int Lo_DibBinarizationIterative(float hist[], int blockSize)
{
	register int i;

	//초기 임계값 설정
	int T, Told;

	float sum = 0.f;
	for (i = 0; i < 256; i++)
	{
		sum += (i*hist[i]);
	}
	T = (int)sum;

	//반복에 의한 임계값 설정
	float a1, b1, u1, a2, b2, u2;
	int loopCount = 0;
	do
	{
		Told = T;

		a1 = b1 = 0;
		for (i = 0; i <= Told; i++)
		{
			a1 += (i*hist[i]);
			b1 += hist[i];
		}
		if (b1 == 0.f)
			u1 = 0;
		else
			u1 = a1 / b1;

		a2 = b2 = 0;
		for (i = Told + 1; i < 256; i++)
		{
			a2 += (i*hist[i]);
			b2 += hist[i];
		}
		if (a2 == 0.f)
			u2 = 0;
		else
			u2 = a2 / b2;

		if (b1 == 0)
			b1 = 1.f;
		if (b2 == 0)
			b2 = 1.f;
		T = (int)(((u1 + u2) / (double)2) + 0.5);
		loopCount++;
	} while (T == Told && loopCount <= 3);
	return T;
}
double AdaptiveThresholding(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	int pxCount = w*h;
	int pxSum = 0;
	double pxAverage = 0.0;
	double pxStandardDeviation;
	double pxVariance;
	double deviationSum = 0.0;
	double th = 0.0;
	BYTE** ptr = dib.GetPtr();
	int upperPxCount = 0;
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			if (ptr[j][i] > 0)
			{
				pxSum += ptr[j][i];
				upperPxCount++;
			}
		}
	//1프레임의 픽셀 평균값 
	pxAverage = (double)pxSum / (double)upperPxCount;

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			if (ptr[j][i] > 0)
				deviationSum += ((double)ptr[j][i] - pxAverage) * ((double)ptr[j][i] - pxAverage);
		}
	pxVariance = deviationSum / ((double)upperPxCount - 1);
	pxStandardDeviation = sqrt(pxVariance);
	 
	th = pxAverage - (K*pxStandardDeviation);
	if (th > 255.0)
		th = 255.0;
	TRACE(_T("%lf\n"), th);
	return th;
}
void Lo_DibBinarization(CDib& dib, int blockSize,int th[])
{
	register int i, j;
	BYTE** ptr = dib.GetPtr();
	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int x, y;
	int blockCount = 0;
	double fixelAverage = 0.0;
	//for (i = 0; i < 510; i++)
//		th[i] = rand() % 15 + 100;
	
	/*
	for (i = 0; i < 510; i++)
	{
		if (th[i] < 45)
			th[i] = 45;
	}
	*/
	for (y = 0; y < h; y += blockSize)
	{
		for (x = 0; x < w; x += blockSize)

		{
			for (j = y; j < y + blockSize; j++)
			{
				for (i = x; i < x + blockSize; i++)
				{
					ptr[j][i] = (ptr[j][i] > th[blockCount]) ? 255 : 0;
				}
			}
			blockCount++;
		}
	}
}