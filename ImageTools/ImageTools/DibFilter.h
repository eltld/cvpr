#pragma once
#define MAX_CORNER 5000

typedef struct _CornerPoints
{
	int num;
	int x[MAX_CORNER];
	int y[MAX_CORNER];
}CornerPoints;
void DibFilterMean(CDib& dib);
void DibFilterWeightedMean(CDib& dib);
void DibFilterGaussian(CDib& dib, double sigma);
void DibEdgeRoberts(CDib& dib);
void DibEdgePrewitt(CDib& dib);
void DibEdgeSobel(CDib& dib);
CornerPoints DibHarrisCorner(CDib& dib, double th);