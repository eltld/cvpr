
// ImageToolsView.cpp : CImageToolsView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageTools.h"
#endif

#include "ImageToolsDoc.h"
#include "ImageToolsView.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageToolsView

IMPLEMENT_DYNCREATE(CImageToolsView, CScrollView)

BEGIN_MESSAGE_MAP(CImageToolsView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageToolsView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_ZOOM1, &CImageToolsView::OnViewZoom1)
	ON_COMMAND(ID_VIEW_ZOOM2, &CImageToolsView::OnViewZoom2)
	ON_COMMAND(ID_VIEW_ZOOM3, &CImageToolsView::OnViewZoom3)
	ON_COMMAND(ID_VIEW_ZOOM4, &CImageToolsView::OnViewZoom4)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM1, &CImageToolsView::OnUpdateViewZoom1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM2, &CImageToolsView::OnUpdateViewZoom2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM3, &CImageToolsView::OnUpdateViewZoom3)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM4, &CImageToolsView::OnUpdateViewZoom4)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CImageToolsView 생성/소멸

CImageToolsView::CImageToolsView()
	: m_nZoom(1)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageToolsView::~CImageToolsView()
{
}

BOOL CImageToolsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageToolsView 그리기

void CImageToolsView::OnDraw(CDC* pDC)
{
	CImageToolsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->m_Dib.IsValid())
	{
		int w = pDoc->m_Dib.GetWidth();
		int h = pDoc->m_Dib.GetHeight();
		pDoc->m_Dib.Draw(pDC->m_hDC, 0, 0, w*m_nZoom, h*m_nZoom);
	}
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CImageToolsView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();


	SetScrollSizeToFit();
}
void CImageToolsView::SetScrollSizeToFit(void)
{
	CSize sizeTotal;
	CImageToolsDoc* pDoc = GetDocument();
	if (pDoc->m_Dib.IsValid())
	{
		int w = pDoc->m_Dib.GetWidth();
		int h = pDoc->m_Dib.GetHeight();

		sizeTotal.cx = w*m_nZoom;
		sizeTotal.cy = h*m_nZoom;
	}
	else
	{
		sizeTotal.cx = sizeTotal.cy = 100;
	}
	SetScrollSizes(MM_TEXT, sizeTotal);
	ResizeParentToFit(TRUE);
}


// CImageToolsView 인쇄


void CImageToolsView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageToolsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageToolsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageToolsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageToolsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageToolsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageToolsView 진단

#ifdef _DEBUG
void CImageToolsView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageToolsView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageToolsDoc* CImageToolsView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageToolsDoc)));
	return (CImageToolsDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageToolsView 메시지 처리기


BOOL CImageToolsView::OnEraseBkgnd(CDC* pDC)
{
	CBrush br;
	br.CreateHatchBrush(HS_DIAGCROSS, RGB(200, 200, 200));
	FillOutsideRect(pDC, &br);
	return TRUE;
}


void CImageToolsView::OnViewZoom1()
{
	m_nZoom = 1;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CImageToolsView::OnViewZoom2()
{
	m_nZoom = 2;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CImageToolsView::OnViewZoom3()
{
	m_nZoom = 3;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CImageToolsView::OnViewZoom4()
{
	m_nZoom = 4;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CImageToolsView::OnUpdateViewZoom1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 1);
}


void CImageToolsView::OnUpdateViewZoom2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 2);
}


void CImageToolsView::OnUpdateViewZoom3(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 3);
}


void CImageToolsView::OnUpdateViewZoom4(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 4);
}


void CImageToolsView::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint pt = point + GetScrollPosition();
	pt.x /= m_nZoom;
	pt.y /= m_nZoom;
	ShowImageInfo(pt);
	CScrollView::OnMouseMove(nFlags, point);
}

void CImageToolsView::ShowImageInfo(CPoint point)
{
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CImageToolsDoc* pDoc = GetDocument();
	int w = pDoc->m_Dib.GetWidth();
	int h = pDoc->m_Dib.GetHeight();
	int c = pDoc->m_Dib.GetPaletteNums();

	CString strText;

	if (point.x >= 0 && point.y >= 0 && point.x < w && point.y < h)
	{
		strText.Format(_T("(%d,%d)"), point.x, point.y);
		pFrame->m_wndStatusBar.SetPaneText(0, strText);
	}
	//상태바에 이미지 정보 표시
	if (c == 0)
	{
		strText.Format(_T("w:%d h:%d c16M"), w, h);
	}
	else
		strText.Format(_T("w:%d h:%d c:%d"), w, h, c);
	pFrame->m_wndStatusBar.SetPaneText(1, strText);
}