
// ImageToolsDoc.cpp : CImageToolsDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageTools.h"
#endif
#include "FileNewDig.h"
#include "ImageToolsDoc.h"
#include "DibEnhancement.h"
#include "HistogramDlg.h"
#include "DibFilter.h"
#include "GaussianDlg.h"
#include "ArithmeticDlg.h"
#include <propkey.h>
#include "TranslateDlg.h"
#include "DibGeometry.h"
#include "ResizeDlg.h"
#include "RotateDlg.h"
#include "HarrisDlg.h"
#include "DibColor.h"
#include "BinaraizationDlg.h"
#include "DibSegment.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageToolsDoc

IMPLEMENT_DYNCREATE(CImageToolsDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageToolsDoc, CDocument)
	ON_COMMAND(ID_WINDOW_DUPLICATE, &CImageToolsDoc::OnWindowDuplicate)
	ON_COMMAND(ID_EDIT_COPY, &CImageToolsDoc::OnEditCopy)
	
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CImageToolsDoc::OnUpdateEditPaste)
	
	ON_COMMAND(ID_IMAVE_INVERSE, &CImageToolsDoc::OnImaveInverse)
	ON_COMMAND(ID_IMAGE_BRIGHTNESS, &CImageToolsDoc::OnImageBrightness)
	ON_COMMAND(ID_IMAGE_CONTRAST, &CImageToolsDoc::OnImageContrast)
	ON_COMMAND(ID_VIEW_HISTOGRAM, &CImageToolsDoc::OnViewHistogram)
	ON_COMMAND(ID_HISTOGRAM_EQUALIZATION, &CImageToolsDoc::OnHistogramEqualization)
	ON_COMMAND(ID_IMAGE_ARITHMETIC, &CImageToolsDoc::OnImageArithmetic)
	ON_COMMAND(ID_BITPLANE_SLICING, &CImageToolsDoc::OnBitplaneSlicing)
	ON_COMMAND(ID_FILTER_MEAN, &CImageToolsDoc::OnFilterMean)
	ON_COMMAND(ID_FILTER_WEIGHTED_MEAN, &CImageToolsDoc::OnFilterWeightedMean)
	ON_COMMAND(ID_FILTER_GAUSSIAN, &CImageToolsDoc::OnFilterGaussian)
	ON_COMMAND(ID_IMAGE_TRANSLATION, &CImageToolsDoc::OnImageTranslation)
	ON_COMMAND(ID_IMAGE_RESIZE, &CImageToolsDoc::OnImageResize)
	ON_COMMAND(IDC_IMAGE_ROTATE, &CImageToolsDoc::OnImageRotate)
	ON_COMMAND(ID_CHAPTER9_HOMEWORK, &CImageToolsDoc::OnChapter9Homework)
	ON_COMMAND(ID_IMAHE_MIRROR, &CImageToolsDoc::OnImaheMirror)
	ON_COMMAND(ID_IMAGE_FLIP, &CImageToolsDoc::OnImageFlip)
	ON_COMMAND(ID_EDGE_SOBEL, &CImageToolsDoc::OnEdgeSobel)
	ON_COMMAND(ID_EDGE_PREWITTER, &CImageToolsDoc::OnEdgePrewitter)
	ON_COMMAND(ID_EDGE_ROBERTS, &CImageToolsDoc::OnEdgeRoberts)
	ON_COMMAND(ID_HARRIS_CORNER, &CImageToolsDoc::OnHarrisCorner)
	ON_COMMAND(ID_IMAGE_INVERSE, &CImageToolsDoc::OnImageInverse)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GRAYSCALE, &CImageToolsDoc::OnUpdateColorGrayscale)
	ON_COMMAND(ID_COLOR_GRAYSCALE, &CImageToolsDoc::OnColorGrayscale)
	ON_COMMAND(ID_COLOR_EDGE, &CImageToolsDoc::OnColorEdge)
	ON_UPDATE_COMMAND_UI(ID_COLOR_EDGE, &CImageToolsDoc::OnUpdateColorEdge)
	ON_COMMAND(ID_COLOR_EQUALIZE, &CImageToolsDoc::OnColorEqualize)
	ON_UPDATE_COMMAND_UI(ID_COLOR_EQUALIZE, &CImageToolsDoc::OnUpdateColorEqualize)
	ON_COMMAND(ID_SEGMENT_BINARIZATION, &CImageToolsDoc::OnSegmentBinarization)
	ON_COMMAND(ID_BINARIZATION_ITERATIVE, &CImageToolsDoc::OnBinarizationIterative)
	ON_COMMAND(ID_SEGMENT_LABELING, &CImageToolsDoc::OnSegmentLabeling)
	ON_COMMAND(ID_CONTOUR_TRACING, &CImageToolsDoc::OnContourTracing)
END_MESSAGE_MAP()


// CImageToolsDoc 생성/소멸

CImageToolsDoc::CImageToolsDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageToolsDoc::~CImageToolsDoc()
{
}

BOOL CImageToolsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if (!CDocument::OnNewDocument())
		return FALSE;
	BOOL bSuccess = TRUE;
	
	if (theApp.m_pNewDib == NULL)
	{
		CFileNewDig dig;
		if (dig.DoModal() == IDOK)
		{
			if (dig.m_nType == 0) // Gray Scale Image
				bSuccess = m_Dib.CreateGrayImage(dig.m_nWidth, dig.m_nHeight);
			else //True Color Image
				bSuccess = m_Dib.CreateRGBImage(dig.m_nWidth, dig.m_nHeight);
		}
		else
			bSuccess = FALSE;
	}
	else
	{
		m_Dib.Copy(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;
	}

	return bSuccess;
}




// CImageToolsDoc serialization

void CImageToolsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageToolsDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}i

// 검색 처리기를 지원합니다.
void CImageToolsDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.
i
	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageToolsDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageToolsDoc 진단

#ifdef _DEBUG
void CImageToolsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageToolsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageToolsDoc 명령


BOOL CImageToolsDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	return m_Dib.Load(lpszPathName); 
}


BOOL CImageToolsDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return m_Dib.Save(lpszPathName);
}


void CImageToolsDoc::OnWindowDuplicate()
{
	AfxNewImage(m_Dib);
}


void CImageToolsDoc::OnEditCopy()
{
	if (m_Dib.IsValid())
		m_Dib.CopyToClipboard();
}
						   
void CImageToolsDoc::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsClipboardFormatAvailable(CF_DIB));
}



void CImageToolsDoc::OnImaveInverse()
{
	CDib dib = m_Dib;
	DibInverse(dib);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnImageBrightness()
{
	CDib dib = m_Dib;
	DibBrightness(dib,40);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnImageContrast()
{
	CDib dib = m_Dib;
	DibContrast(dib, 40);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnViewHistogram()
{
	CHistogramDlg dlg;
	dlg.SetImage(m_Dib);
	dlg.DoModal();
}


void CImageToolsDoc::OnHistogramEqualization()
{
	CDib dib = m_Dib;
	DibHistEqual(dib);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnImageArithmetic()
{
	CArithmeticDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CImageToolsDoc* pDoc1 = (CImageToolsDoc*)dlg.m_pDoc1;
		CImageToolsDoc* pDoc2 = (CImageToolsDoc*)dlg.m_pDoc2;
		
		CDib dib;
		BOOL ret = FALSE;
		
		switch (dlg.m_nFunction)
		{
		case 0:ret = DibAdd(pDoc1->m_Dib, pDoc2->m_Dib, dib); break;
		case 1:ret = DibSub(pDoc1->m_Dib, pDoc2->m_Dib, dib); break;
		case 2:ret = DibAve(pDoc1->m_Dib, pDoc2->m_Dib, dib); break;
		case 3:ret = DibDif(pDoc1->m_Dib, pDoc2->m_Dib, dib); break;
		case 4:ret = DibAND(pDoc1->m_Dib, pDoc2->m_Dib, dib); break;
		case 5:ret = DibOR(pDoc1->m_Dib, pDoc2->m_Dib, dib); break;
		case 6:ret = DibAddBitPlane(pDoc1->m_Dib, pDoc2->m_Dib,dib); break;
		}
		if (ret)
			AfxNewImage(dib);
		else
			AfxMessageBox(_T("영상의 크기가 다릅니다"));
	}
}


void CImageToolsDoc::OnBitplaneSlicing()
{
	register int i;

	int w = m_Dib.GetWidth();
	int h = m_Dib.GetHeight();

	CDib dib;
	dib.CreateGrayImage(w, h);

	for (i = 0; i < 8; i++)
	{
		DibBitPlane(m_Dib, i, dib);
		AfxNewImage(dib);
	}
}




void CImageToolsDoc::OnFilterMean()
{
	CDib dib = m_Dib;
	DibFilterMean(dib);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnFilterWeightedMean()
{
	CDib dib = m_Dib;
	DibFilterWeightedMean(dib);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnFilterGaussian()
{
	CGaussianDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		DibFilterGaussian(dib, dlg.m_fSigma);
		AfxNewImage(dib);
	}
}


void CImageToolsDoc::OnImageTranslation()
{
	CTranslateDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		DibTranslate(dib, dlg.m_nNewSX, dlg.m_nNewSY);
		AfxNewImage(dib);
	}
}


void CImageToolsDoc::OnImageResize()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CResizeDlg dlg;
	dlg.m_nOldWidth = m_Dib.GetWidth();
	dlg.m_nOldHeight = m_Dib.GetHeight();

	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		switch (dlg.m_nInterpolation)
		{
		case 0: DibResizeNearest(dib, dlg.m_nNewWidth, dlg.m_nNewHeight); break;
		case 1: DibResizeBilinewar(dib, dlg.m_nNewWidth, dlg.m_nNewHeight); break;
		}

		AfxNewImage(dib);
	}
}


void CImageToolsDoc::OnImageRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CRotateDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		switch (dlg.m_nRotate)
		{
		case 0: DibRotate90(dib); break;
		case 1: DibRotate180(dib); break;
		case 2: DibRotate270(dib); break;
		case 3: DibRotate(dib, dlg.m_fAngle); break;
		}
		AfxNewImage(dib);
	}
}


void CImageToolsDoc::OnChapter9Homework()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDib dib = m_Dib;
	DibTranslate(dib, 30, 30);
	DibResizeBilinewar(dib, 64, 64);
	DibRotate(dib, 32);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnImaheMirror()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDib dib = m_Dib;
	DibMirror(dib);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnImageFlip()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CDib dib = m_Dib;
	DibFlip(dib);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnEdgeSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDib dib = m_Dib;
	DibEdgeSobel(dib);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnEdgePrewitter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDib dib = m_Dib;
	DibEdgePrewitt(dib);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnEdgeRoberts()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDib dib = m_Dib;
	DibEdgeRoberts(dib);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnHarrisCorner()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CHarrisDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CornerPoints cp;
		cp = DibHarrisCorner(m_Dib, dlg.m_nThreshold);

		CDib dib = m_Dib;
		BYTE** ptr = dib.GetPtr();

		int i, x, y;
		for (i = 0; i < cp.num;i++)
		{
			x = cp.x[i];
			y = cp.y[i];

			ptr[y - 1][x - 1] = ptr[y - 1][x] = ptr[y - 1][x + 1] = 0;
			ptr[y][x - 1] = ptr[y][x] = ptr[y][x + 1] = 0;
			ptr[y + 1][x - 1] = ptr[y + 1][x] = ptr[y + 1][x + 1] = 0;
		}
		AfxNewImage(dib);
	}
}


void CImageToolsDoc::OnImageInverse()
{
	CDib dib = m_Dib;
	DibInverse(dib);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnUpdateColorGrayscale(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CImageToolsDoc::OnColorGrayscale()
{
	CDib dib = m_Dib;
	DibGrayscale(dib);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnColorEdge()
{
	CDib dib = m_Dib;
	DibColorEdge(dib);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnUpdateColorEdge(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CImageToolsDoc::OnColorEqualize()
{
	CDib dib = m_Dib;
	DibColorHistEqual(dib);
	AfxNewImage(dib);
}


void CImageToolsDoc::OnUpdateColorEqualize(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CImageToolsDoc::OnSegmentBinarization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CBinaraizationDlg dlg;
	dlg.SetImage(m_Dib);
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		DibBinarization(dib, dlg.m_nThreshold);
		AfxNewImage(dib);
	}
}


void CImageToolsDoc::OnBinarizationIterative()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDib dib = m_Dib;
	int th = DibBinarizationIterative(dib);
	DibBinarization(dib, th);
	AfxNewImage(dib);

	CString str;
	str.Format(_T("Thresold = %d"), th);
	AfxMessageBox(str);
}


void CImageToolsDoc::OnSegmentLabeling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDib dib = m_Dib;
	int nLabel = DibLabeling(dib);

	CString str;
	str.Format(_T("레이블 개수 = %d"), nLabel);
	AfxMessageBox(str);
}


void CImageToolsDoc::OnContourTracing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ContourPoints cp = DibContourTracing(m_Dib);

	register int i;

	int w = m_Dib.GetWidth();
	int h = m_Dib.GetHeight();

	CDib dib;
	dib.CreateGrayImage(w, h, 0);
	BYTE** ptr = dib.GetPtr();

	for (i = 0; i < cp.num; i++)
		ptr[cp.y[i]][cp.x[i]] = 255;
	AfxNewImage(dib);
}
