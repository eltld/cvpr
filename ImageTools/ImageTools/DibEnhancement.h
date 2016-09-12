#pragma once
//Image Inverse
void DibInverse(CDib& dib);
//Image Brightness
void DibBrightness(CDib& dib, int n);
//Image Contrast
void DibContrast(CDib& dib, int n);
//Image Histogram
void DibHistogram(CDib& dib, float histo[256]);
//Image Equalization
void DibHistEqual(CDib& dib);
//Image bitPlane
void DibBitPlane(CDib& dib, int bit, CDib& dib2);
//Image add bitPlane
BOOL DibAddBitPlane(CDib& dib1, CDib& dib2, CDib& dib3);
BOOL DibAdd(CDib& dib1, CDib& dib2, CDib& dib3);
BOOL DibSub(CDib& dib1, CDib& dib2, CDib& dib3);
BOOL DibAve(CDib& dib1, CDib& dib2, CDib& dib3);
BOOL DibDif(CDib& dib1, CDib& dib2, CDib& dib3);

BOOL DibAND(CDib& dib1, CDib& dib2, CDib& dib3);
BOOL DibOR(CDib& dib1, CDib& dib2, CDib& dib3);