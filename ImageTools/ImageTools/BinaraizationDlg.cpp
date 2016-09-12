// BinaraizationDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTools.h"
#include "BinaraizationDlg.h"
#include "afxdialogex.h"

#include "DibGeometry.h"
#include "DibSegment.h"
// CBinaraizationDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBinaraizationDlg, CDialog)

CBinaraizationDlg::CBinaraizationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBinaraizationDlg::IDD, pParent)
	, m_nThreshold(0)
{

}

CBinaraizationDlg::~CBinaraizationDlg()
{
}

void CBinaraizationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_THRESHOLD_SLIDER, m_sliderThreshold);
	DDX_Text(pDX, IDC_THRESHOLD, m_nThreshold);
	DDV_MinMaxInt(pDX, m_nThreshold, 0, 255);
}


BEGIN_MESSAGE_MAP(CBinaraizationDlg, CDialog)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_THRESHOLD, &CBinaraizationDlg::OnEnChangeThreshold)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CBinaraizationDlg 메시지 처리기입니다.


void CBinaraizationDlg::SetImage(CDib& dib)
{
	m_DibSrc = dib;
}
void CBinaraizationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CPaintDC dc2(GetDlgItem(IDC_IMAGE_WND));
	m_DibRes.Draw(dc2.m_hDC, 0, 0);
}


BOOL CBinaraizationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CWnd* pImageWnd = GetDlgItem(IDC_IMAGE_WND);

	CRect rect;
	pImageWnd->GetClientRect(rect);

	//픽쳐 컨트롤의 크기에 맞게 입력 영상의 복사본의 크기를 조절
	DibResizeNearest(m_DibSrc, rect.Width(), rect.Height());
	//이진화된 결과를 보여줄 영상을 생성	
	m_DibRes = m_DibSrc;
	DibBinarization(m_DibRes, m_nThreshold);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBinaraizationDlg::OnEnChangeThreshold()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	UpdateData(TRUE);
	m_sliderThreshold.SetPos(m_nThreshold);
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_DibRes = m_DibSrc;
	DibBinarization(m_DibRes, m_nThreshold);
	Invalidate(FALSE);
}


void CBinaraizationDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//슬라이드바에서 발생한 WM_HSCROLL 메시지인 경우 처리
	if (m_sliderThreshold.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_sliderThreshold.GetPos();
		m_nThreshold = nPos;
		UpdateData(FALSE);

		//현재 설정된 임계값을 이용하여 미리보기 영상의 이진화를 수행
		m_DibRes = m_DibSrc;
		DibBinarization(m_DibRes, m_nThreshold);
		Invalidate(FALSE);
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
