#include "stdafx.h"
#include "Dib.h"
#include "DibFilter.h"
#include <math.h>

const double PI = 3.14159265358979323846;


CornerPoints DibHarrisCorner(CDib& dib, double th)
{
	register int i, j, x, y;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();
	
	double** dx2 = new double*[h];
	double** dy2 = new double*[h];
	double** dxy = new double*[h];

	for (i = 0; i < h; i++)
	{
		dx2[i] = new double[w];
		dy2[i] = new double[w];
		dxy[i] = new double[w];
		memset(dx2[i], 0, sizeof(double)*w);
		memset(dy2[i], 0, sizeof(double)*w);
		memset(dxy[i], 0, sizeof(double)*w);
	}
	double tx, ty;
	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			tx = (ptr[j - 1][i + 1] + ptr[j][i + 1] + ptr[j + 1][i + 1] - ptr[j - 1][i - 1] - ptr[j][i - 1] - ptr[j + 1][i - 1]) / 6.0;
			ty = (ptr[j + 1][i - 1] + ptr[j+1][i] + ptr[j + 1][i + 1] - ptr[j - 1][i - 1] - ptr[j-1][i] - ptr[j - 1][i + 1]) / 6.0;

			dx2[j][i] = tx * tx;
			dy2[j][i] = ty * ty;
			dxy[j][i] = tx * ty;
		}
	//가우시안 필터링
	double** gdx2 = new double*[h];
	double** gdy2 = new double*[h];
	double** gdxy = new double*[h];
	for (i = 0; i < h; i++)
	{
		gdx2[i] = new double[w];
		gdy2[i] = new double[w];
		gdxy[i] = new double[w];
		memset(gdx2[i], 0, sizeof(double)*w);
		memset(gdy2[i], 0, sizeof(double)*w);
		memset(gdxy[i], 0, sizeof(double)*w);
	}
	double g[5][5] = { { 1, 4, 6, 4, 1 }, { 4, 16, 24, 16, 4 }, { 6, 24, 36, 24, 6 }, { 4, 16, 24, 16, 4 }, { 1, 4, 6, 4, 1 } };
	for (y = 0; y < 5; y++)
		for (x = 0; x < 5; x++)
			g[y][x] /= 256;
	double tx2, ty2, txy;
	for (j = 2; j < h - 2; j++)
		for (i = 2; i < w - 2; i++)
		{
			tx2 = ty2 = txy = 0;
			for (y = 0; y < 5; y++)
				for (x = 0; x < 5; x++)
				{
					tx2 += (dx2[j + y - 2][i + x - 2] * g[y][x]);
					ty2 += (dy2[j + y - 2][i + x - 2] * g[y][x]);
					txy += (dxy[j + y - 2][i + x - 2] * g[y][x]);
				}
			gdx2[j][i] = tx2;
			gdy2[j][i] = ty2;
			gdxy[j][i] = txy;
		}
	//코너 응답 함수 생성
	double** crf = new double*[h];
	for (i = 0; i < h; i++)
	{
		crf[i] = new double[w];
		memset(crf[i], 0, sizeof(double)*w);
	}
	double k = 0.04;
	for (j = 2; j < h - 2; j++)
		for (i = 2; i < w - 2; i++)
		{
			crf[j][i] = (gdx2[j][i] * gdy2[j][i] - gdxy[j][i] * gdxy[j][i] - k*(gdx2[j][i] + gdy2[j][i])*gdx2[j][i] + gdy2[j][i]);
		}
	//임계값보다 큰 국지적 최대값을 찾아 코너 포인트로 결정

	CornerPoints cp;
	cp.num = 0;

	for (j = 2; j < h - 2; j++)
		for (i = 2; i < w - 2; i++)
		{
			if (crf[j][i] > th)
			{
				if (crf[j][i] > crf[j - 1][i] && crf[j][i] > crf[j - 1][i + 1] && crf[j][i] > crf[j][i + 1] && crf[j][i] > crf[j + 1][i + 1] && crf[j][i] > crf[j + 1][i] && crf[j][i] > crf[j + 1][i - 1] && crf[j][i] > crf[j][i - 1] && crf[j][i] > crf[j - 1][i - 1])
				{
					if (cp.num < MAX_CORNER)
					{
						cp.x[cp.num] = i;
						cp.y[cp.num] = j;
						cp.num++;
					}
				}
			}
		}
	//동적 할당한 메모리 해제
	for (i = 0; i < h; i++)
	{
		delete[] dx2[i];
		delete[] dy2[i];
		delete[] dxy[i];
		delete[] gdx2[i];
		delete[] gdy2[i];
		delete[] gdxy[i];
		delete[] crf[i];
	}
	delete[] dx2;
	delete[] dy2;
	delete[] dxy;
	delete[] gdx2;
	delete[] gdy2;
	delete[] gdxy;
	delete[] crf;
	
	return cp;
}
void DibEdgeRoberts(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	CDib cpy = dib;
	dib.CreateGrayImage(w, h, 0);
	BYTE** ptr1 = dib.GetPtr();
	BYTE** ptr2 = cpy.GetPtr();

	int h1, h2;
	double hval;

	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			h1 = ptr2[j][i] - ptr2[j - 1][i - 1];
			h2 = ptr2[j][i] - ptr2[j - 1][i + 1];

			hval = sqrt((double)h1*h1 + h2*h2);

			ptr1[j][i] = (BYTE)limit(hval);
		}
}
void DibEdgePrewitt(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	CDib cpy = dib;
	dib.CreateGrayImage(w, h, 0);

	BYTE** ptr1 = dib.GetPtr();
	BYTE** ptr2 = cpy.GetPtr();

	int h1, h2;
	double hval;
	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			h1 = -ptr2[j - 1][i - 1] - ptr2[j - 1][i] - ptr2[j - 1][i + 1] + ptr2[j + 1][i - 1] + ptr2[j + 1][i] + ptr2[j + 1][i + 1];
			h2 = -ptr2[j - 1][i - 1] - ptr2[j][i-1] - ptr2[j + 1][i - 1] + ptr2[j - 1][i + 1] + ptr2[j][i+1] + ptr2[j + 1][i + 1];

			hval = sqrt((double)h1*h1 + h2*h2);

			ptr1[j][i] = (BYTE)limit(hval);
		}
}

void DibEdgeSobel(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	CDib cpy = dib;
	dib.CreateGrayImage(w, h, 0);

	BYTE** ptr1 = dib.GetPtr();
	BYTE** ptr2 = cpy.GetPtr(); 

	int h1, h2;
	double hval;

	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			h1 = -ptr2[j - 1][i - 1] - 2*ptr2[j - 1][i] - ptr2[j - 1][i + 1] + ptr2[j + 1][i - 1] + 2*ptr2[j + 1][i] + ptr2[j + 1][i + 1];
			h2 = -ptr2[j - 1][i - 1] - 2*ptr2[j][i - 1] - ptr2[j + 1][i - 1] + ptr2[j - 1][i + 1] + 2*ptr2[j][i + 1] + ptr2[j + 1][i + 1];

			hval = sqrt((double)h1*h1 + h2*h2);
			ptr1[j][i] = (BYTE)limit(hval);
		}
}
void DibFilterGaussian(CDib& dib, double sigma)
{
	register int i, j, k , x;

	int w = dib.GetWidth();
	int h = dib.GetHeight();


	BYTE** ptr = dib.GetPtr();

	//1차원 가우시안 마스크 생성

	int dim = (int)max(3.0, 2 * 4 * sigma + 1.0);
	if (dim % 2 == 0) 
		dim++;//1차원 가우시안 마스크를 홀수개로 생성
	int dim2 = (int)dim / 2;

	double* pMask = new double[dim];
	for (i = 0; i < dim; i++)
	{
		x = i - dim2;
		pMask[i] = exp(-(x*x) / (2 * sigma*sigma)) / (sqrt(2 * PI)*sigma);
	}
	/*임시 버퍼 메모리 공간 할당*/
	double** buf = new double*[h];
	for (i = 0; i < h; i++)
	{
		buf[i] = new double[w];
		memset(buf[i], 0, sizeof(double)*w);
	}
	/*세로 방향 convolution*/
	double sum1, sum2;

	for (i = 0; i < w; i++)
		for (j = 0; j < h; j++)
		{
			sum1 = sum2 = 0.0;

			for (k = 0; k < dim; k++)
			{
				x = k - dim2 + j;

				if (x >= 0 && x < h)
				{
					sum1 += pMask[k];
					sum2 += (pMask[k] * ptr[x][i]);
				}
			}
			buf[j][i] = (sum2 / sum1);
		}
	/*가로 방향 convolution*/

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			sum1 = sum2 = 0.0;
			for (k = 0; k < dim; k++)
			{
				x = k - dim2 + i;
				if (x >= 0 && x < w)
				{
					sum1 += pMask[k];
					sum2 += (pMask[k] * buf[j][x]);
				}
			}
			ptr[j][i] = (BYTE)limit(sum2 / sum1);
		}
	/*동적 할당했던 메모리 공간 해제*/
	delete[] pMask;

	for (i = 0; i < h; i++)
		delete[] buf[i];
	delete[] buf;

}
void DibFilterWeightedMean(CDib& dib)
{
	register int i, j;
	
	int w = dib.GetWidth();
	int h = dib.GetHeight();

	CDib cpy = dib;

	BYTE** ptr1 = dib.GetPtr();
	BYTE** ptr2 = cpy.GetPtr();

	int temp;

	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			temp = ptr2[j - 1][i - 1] + 2*ptr2[j - 1][i] + ptr2[j - 1][i + 1] + 2*ptr2[j][i - 1] + 4*ptr2[j][i] + 2*ptr2[j][i + 1] + ptr2[j + 1][i - 1] + 2*ptr2[j + 1][i] + ptr2[j + 1][i + 1];
			ptr1[j][i] = (BYTE)limit(temp / 16. + 0.5);
		}
}
void DibFilterMean(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	CDib cpy = dib;

	BYTE** ptr1 = dib.GetPtr();
	BYTE** ptr2 = cpy.GetPtr(); 

	int temp;

	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			temp = ptr2[j - 1][i - 1] + ptr2[j - 1][i] + ptr2[j - 1][i+ 1] + ptr2[j][i - 1] + ptr2[j][i] + ptr2[j][i + 1] + ptr2[j + 1][i - 1] + ptr2[j + 1][i] + ptr2[j + 1][i + 1];
			ptr1[j][i] = (BYTE)limit(temp / 9. + 0.5);
		}

}