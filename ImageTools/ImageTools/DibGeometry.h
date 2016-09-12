#pragma once

void DibTranslate(CDib& dib, int sx, int sy);
void DibResizeNearest(CDib& dib, int nw, int nh);
void DibResizeBilinewar(CDib& dib, int nw ,int nh);
void DibRotate(CDib& dib, double angle);
void DibRotate90(CDib& dib);
void DibRotate180(CDib& dib);
void DibRotate270(CDib& dib);
void DibFlip(CDib& dib);
void DibMirror(CDib& dib);