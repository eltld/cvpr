#pragma once 
void Gl_DibBinarization(CDib &dib, int th);
int Gl_DibBinarizationIterative(CDib& dib);
int Lo_DibBinarizationIterative(float hist[], int blockSize);
double AdaptiveThresholding(CDib& dib);
void Lo_DibBinarization(CDib& dib,int blockSize,int th[]);
void PreProcessing(CDib& dib);