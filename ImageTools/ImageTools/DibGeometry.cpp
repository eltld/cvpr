#include "stdafx.h"
#include "Dib.h"
#include "DibGeometry.h"
#include <math.h>
const double PI = acos(-1.0);

void DibMirror(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	
	CDib cpy = dib;
	dib.CreateGrayImage(w, h);
	
	BYTE** ptr1 = cpy.GetPtr();
	BYTE** ptr2 = dib.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
			ptr2[j][i] = ptr1[j][w - 1 - i];
}
void DibFlip(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	CDib cpy = dib;
	dib.CreateGrayImage(w, h);

	BYTE** ptr1 = cpy.GetPtr();
	BYTE** ptr2 = dib.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
			ptr2[j][i] = ptr1[h-1-j][i];
}
void DibRotate90(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	CDib cpy = dib;

	BYTE** ptr1 = cpy.GetPtr();
	BYTE** ptr2 = dib.GetPtr();

	for (j = 0; j < w; j++)
		for (i = 0; i < h; i++)
			ptr2[j][i] = ptr1[h - 1 - i][j];
}
void DibRotate180(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	CDib cpy = dib;

	BYTE** ptr1 = cpy.GetPtr();
	BYTE** ptr2 = dib.GetPtr();

	for (j = 0; j < w; j++)
		for (i = 0; i < h; i++)
			ptr2[j][i] = ptr1[h - 1 - j][w - 1 - i];
			
}
void DibRotate270(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	CDib cpy = dib;

	BYTE** ptr1 = cpy.GetPtr();
	BYTE** ptr2 = dib.GetPtr();

	for (j = 0; j < w; j++)
		for (i = 0; i < h; i++)
			ptr2[j][i] = ptr1[i][w - 1 - j];
}
void DibRotate(CDib& dib, double angle)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	CDib cpy = dib;

	double rad = (angle*PI) / 180;
	double cos_value = cos(rad);
	double sin_value = sin(rad);

	//회전 후 생성되는 영상의 크기를 계산.
	//4개의 코너 포인트의 이동좌표를 계산하여 최대 , 최소점의 차이를 구한다.

	int nx, ny, minx, miny, maxx, maxy, nw, nh;

	minx = maxx = 0;
	miny = maxy = 0;

	nx = (int)floor(w*cos_value + 0.5);
	ny = (int)floor(w*sin_value + 0.5);
	minx = (minx < nx) ? minx : nx; maxx = (maxx > nx) ? maxx : nx;
	miny = (miny < ny) ? miny : ny; maxy = (maxy > ny) ? maxy : ny;

	nx = (int)floor(-h*sin_value + 0.5);
	ny = (int)floor(h*cos_value + 0.5);
	minx = (minx < nx) ? minx : nx; maxx = (maxx > nx) ? maxx : nx;
	miny = (miny < ny) ? miny : ny; maxy = (maxy > ny) ? maxy : ny;

	nx = (int)floor(w*cos_value - h*sin_value + 0.5);
	ny = (int)floor(w*sin_value + h*cos_value + 0.5);
	minx = (minx < nx) ? minx : nx; maxx = (maxx > nx) ? maxx : nx;
	miny = (miny < ny) ? miny : ny; maxy = (maxy > ny) ? maxy : ny;

	nw = maxx - minx;
	nh = maxy - miny;

	//실제 회전변환

	dib.CreateGrayImage(nw, nh, 0);

	BYTE** ptr1 = cpy.GetPtr();
	BYTE** ptr2 = dib.GetPtr();

	int x1, x2, y1, y2;
	double rx, ry, p, q, temp;
	for (j = miny; j < maxy; j++)
		for (i = minx; i < maxx; i++)
		{
			rx = i*cos_value + j*sin_value;
			ry = -i*sin_value + j*cos_value;
			//원본 영상 내에 포함된 좌푝 ㅏ아니라면 무시.
			if (rx  < 0 || rx > w - 1 || ry<0 || ry > h - 1)
				continue;
			x1 = (int)rx;
			y1 = (int)ry;

			x2 = x1 + 1; 
			if (x2 == w)
				x2 = w - 1;
			y2 = y1 + 1;
			if (y2 == h)
				y2 = h - 1;
			p = rx - x1;
			q = ry - y1;

			temp = (1.0 - p)*(1.0 - q)*ptr1[y1][x1] + p*(1.0 - q)*ptr1[y1][x2] + (1.0 - p)*q*ptr1[y2][x1] + p*q*ptr1[y2][x2];
			
			ptr2[j - miny][i - minx] = (BYTE)limit(temp);
		}
}
void DibResizeBilinewar(CDib& dib, int nw, int nh)
{
	CDib cpy = dib;

	register int i, j;

	int w = cpy.GetWidth();
	int h = cpy.GetHeight();

	dib.CreateGrayImage(nw, nh);

	BYTE** ptr1 = cpy.GetPtr();
	BYTE** ptr2 = dib.GetPtr();

	int x1, y1, x2, y2;
	double rx, ry, p, q, temp;

	for (j = 0; j < nh; j++)
		for (i = 0; i < nw; i++)
		{
			rx = (double)w*i / nw;
			ry = (double)h*j / nh;

			x1 = (int)rx;
			y1 = (int)ry;
			x2 = x1 + 1;
			if (x2 == w)
				x2 = w - 1;
			y2 = y1 + 1;
			if (y2 == h)
				y2 = h - 1;
			p = rx - x1;
			q = ry - y1;
			temp = (1.0 - p)*(1.0 - q)*ptr1[y1][x1] + p*(1.0 - q)*ptr1[y1][x2] + (1.0 - p)*q*ptr1[y2][x1] + p*q*ptr1[y2][x2];

			ptr2[j][i] = (BYTE)limit(temp);
		}
}
void DibResizeNearest(CDib& dib, int nw, int nh)
{
	CDib cpy = dib;
	
	register int i, j;

	int w = cpy.GetWidth();
	int h = cpy.GetHeight();

	dib.CreateGrayImage(nw, nh);

	BYTE** ptr1 = cpy.GetPtr();
	BYTE** ptr2 = dib.GetPtr();

	int x, y;

	for (j = 0; j < nh; j++)
		for (i = 0; i < nw; i++)
		{
			x = (int)w*i / nw;
			y = (int)h*j / nh;
			ptr2[j][i] = ptr1[y][x];
		}
}
void DibTranslate(CDib& dib, int sx, int sy)
{
	CDib cpy = dib;
	register int i, j;

	int w = cpy.GetWidth();
	int h = cpy.GetHeight();

	dib.CreateGrayImage(w, h, 0);

	BYTE** ptr1 = cpy.GetPtr();
	BYTE** ptr2 = dib.GetPtr(); 

	int x, y;

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			x = i - sx;
			y = j - sy;
			if (x >= 0 && x < w && y >= 0 && y < h)
				ptr2[j][i] = ptr1[y][x];
		}
}