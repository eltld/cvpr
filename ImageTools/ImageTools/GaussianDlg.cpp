// GaussianDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTools.h"
#include "GaussianDlg.h"
#include "afxdialogex.h"


// CGaussianDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGaussianDlg, CDialog)

CGaussianDlg::CGaussianDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGaussianDlg::IDD, pParent)
	, m_fSigma(0)
{

}

CGaussianDlg::~CGaussianDlg()
{
}

void CGaussianDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SIGMA_SLIDER, m_sliderSigma);
	DDX_Text(pDX, IDC_SIGMA_EDIT, m_fSigma);
	DDV_MinMaxFloat(pDX, m_fSigma, 0.20f, 5.00f);
}


BEGIN_MESSAGE_MAP(CGaussianDlg, CDialog)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_SIGMA_EDIT,&CGaussianDlg::OnEnChangeSigmaEdit)
END_MESSAGE_MAP()


// CGaussianDlg 메시지 처리기입니다.
BOOL CGaussianDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//슬라이더 컨트롤의 초기화
	m_sliderSigma.SetRange(10, 250);
	m_sliderSigma.SetTicFreq(20);
	m_sliderSigma.SetPageSize(20);
	m_sliderSigma.SetPos((int)(m_fSigma * 50));

	return TRUE;
}

void CGaussianDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//슬라이드바에서 발생한 WM_HSCROLL 메시지인 경우 처리
	if (m_sliderSigma.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_sliderSigma.GetPos();
		m_fSigma = (nPos / 50.f);
		UpdateData(FALSE);
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CGaussianDlg::OnEnChangeSigmaEdit()
{
	UpdateData(TRUE);
	m_sliderSigma.SetPos((int)(m_fSigma * 50));
}