#include "stdafx.h"
#include "Dib.h"
#include "RGBBYTE.h"
#include "DibColor.h"
#include "DibFilter.h"
#include "DibEnhancement.h"
#define RGB2GRAY(r,g,b) (0.299*(r) + 0.587*(g) + 0.114*(b))
const double PI = 3.14159265358979323846;
void DibColorHistEqual(CDib& dib)
{
	CDib dibY, dibU, dibV;
	DibColorSplitYUV(dib, dibY, dibU, dibV);

	DibHistEqual(dibY);
	DibColorCombineYUV(dibY, dibU, dibV, dib);
}
BOOL DibColorCombineYUV(CDib& dibY, CDib& dibU, CDib& dibV, CDib& dib)
{
	register int i, j;
	
	int w = dibY.GetWidth();
	int h = dibY.GetHeight();

	if (dibU.GetWidth() != w || dibU.GetHeight() != h || dibV.GetWidth() != w || dibV.GetHeight() != h)
		return FALSE;
	dib.CreateRGBImage(w, h);

	BYTE** ptrY = dibY.GetPtr();
	BYTE** ptrU = dibU.GetPtr();
	BYTE** ptrV = dibV.GetPtr();
	RGBBYTE** ptr = dib.GetRGBPtr();

	BYTE r, g, b;

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			YUV_TO_RGB(ptrY[j][i], ptrU[j][i], ptrV[j][i], r, g, b);
			ptr[j][i].r = r;
			ptr[j][i].g = g;
			ptr[j][i].b = b;
		}
	return TRUE;
}
void DibColorSplitYUV(CDib& dib, CDib& dibY, CDib& dibU, CDib& dibV)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	dibY.CreateGrayImage(w, h);
	dibU.CreateGrayImage(w, h);
	dibV.CreateGrayImage(w, h);

	RGBBYTE** ptr = dib.GetRGBPtr();
	BYTE** ptrY = dibY.GetPtr();
	BYTE** ptrU = dibU.GetPtr();
	BYTE** ptrV = dibV.GetPtr();

	BYTE y, u, v;
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			RGB_TO_YUV(ptr[j][i].r, ptr[j][i].g, ptr[j][i].b, y, u, v);
			ptrY[j][i] = y;
			ptrU[j][i] = u;
			ptrV[j][i] = v;
		}
}
void DibColorEdge(CDib& dib)
{
	CDib dibY, dibU, dibV;
	DibColorSplitYUV(dib, dibY, dibU, dibV);

	DibEdgePrewitt(dibY);
	DibEdgePrewitt(dibU);
	DibEdgePrewitt(dibV);

	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	dib.CreateGrayImage(w, h);
	BYTE** ptr = dib.GetPtr();

	BYTE** ptrY = dibY.GetPtr();
	BYTE** ptrU = dibU.GetPtr();
	BYTE** ptrV = dibV.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			ptr[j][i] = (BYTE)limit(CalcDist(ptrY[j][i], ptrU[j][i] * 0.5, ptrV[j][i] * 0.5));
		}
}
double CalcDist(double x, double y, double z)
{
	return sqrt(x*x + y*y + z*z);
}
void DibColorSplitRGB(CDib& dib, CDib& dibR, CDib& dibG, CDib& dibB)
{
	register int i, j;
	
	int w = dib.GetWidth();
	int h = dib.GetHeight();

	dibR.CreateGrayImage(w, h);
	dibG.CreateGrayImage(w, h);
	dibB.CreateGrayImage(w, h);

	RGBBYTE** ptr = dib.GetRGBPtr();
	BYTE** ptrR = dibR.GetPtr();
	BYTE** ptrG = dibG.GetPtr();
	BYTE** ptrB = dibB.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			ptrR[j][i] = ptr[j][i].r;
			ptrG[j][i] = ptr[j][i].g;
			ptrB[j][i] = ptr[j][i].b;
		}
}
void YUV_TO_RGB(BYTE Y, BYTE U, BYTE V, BYTE& R, BYTE& G, BYTE& B)
{
	R = (BYTE)limit(Y + 1.40758*(V - 128) + 0.5);
	G = (BYTE)limit(Y - 0.3455*(U - 128) - 0.7169 * (V - 128) + 0.5);
	B = (BYTE)limit(Y + 1.7790*(Y - 128)+0.5);
}
void RGB_TO_YUV(BYTE R, BYTE G, BYTE B, BYTE& Y, BYTE& U, BYTE& V)
{
	Y = (BYTE)limit(0.299*R + 0.587*G + 0.114*B + 0.5);
	U = (BYTE)limit(-0.169*R - 0.331*G + 0.500*B + 128 + 0.5);
	V = (BYTE)limit(0.500 * R - 0.419*G - 0.081*B + 128 + 0.5);
}
void HSI_TO_RGB(double H, double S, double I, double& R, double& G, double& B)
{
	if (I == 0.0)//검정색
	{
		R = 0.0;
		G = 0.0;
		B = 0.0;
		return;
	}
	if (S == 0.0)//그레이 스케일 
	{
		R = I;
		G = I;
		B = I;
		return;
	}
	H *= 360;

	if (H <= 120)
	{
		B = I*(1 - S);
		R = I*(1 + S*cos(H*PI / 180) / cos((60 - H)*PI / 180));
		R = limit(R, 0., 1.);
		G = 3 * I - (R + B);
	}
	else if (H <= 240)
	{
		H -= 120;

		R = I*(1 - S);
		G = I*(1 + S*cos(H*PI / 180) / cos((60 - H)*PI / 180));
		G = limit(G, 0., 1.);
		B = 3 * I - (R + G);
	}
	else
	{
		H -= 240;

		G = I*(1 - S);
		B = I*(1 + S*cos(H*PI / 180) / cos((60 - H)*PI / 180));
		B = limit(B, 0., 1.);
		R = 3 * I - (G + B);
	}
}
void RGB_TO_HSI(double R, double G, double B, double& H, double& S, double& I)
{
	I = (R + G + B) / 3;
	
	if ((R == G) && (G == B))//그레이 스케일인경우
	{
		S = 0;
		H = 0;
	}
	else
	{
		double min_rgb;
		double temp;

		min_rgb = min(min(R, G), B);

		S = 1 - (min_rgb / I);
		temp = ((R - G) + (R - B) / (2 * sqrt(R - G)*(R - G) + (R - B)*(G - B)));
		H = acos(temp) * 180 / PI;

		if (B > G)
			H = 360 - H;
		H /= 360;
	}
}
void DibGrayscale(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	CDib cpy = dib;
	dib.CreateGrayImage(w, h);
	BYTE** ptr1 = dib.GetPtr();
	RGBBYTE** ptr2 = cpy.GetRGBPtr();

	BYTE r, g, b;
	for (j = 0; j < w; j++)
		for (i = 0; i < h; i++)
		{
			r = ptr2[j][i].r;
			g = ptr2[j][i].g;
			b = ptr2[j][i].b;

			ptr1[j][i] = (BYTE)limit(RGB2GRAY(r, g, b));
		}
}