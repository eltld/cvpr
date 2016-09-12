// BinaraizationDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageTools.h"
#include "BinaraizationDlg.h"
#include "afxdialogex.h"

#include "DibGeometry.h"
#include "DibSegment.h"
// CBinaraizationDlg ��ȭ �����Դϴ�.

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


// CBinaraizationDlg �޽��� ó�����Դϴ�.


void CBinaraizationDlg::SetImage(CDib& dib)
{
	m_DibSrc = dib;
}
void CBinaraizationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CPaintDC dc2(GetDlgItem(IDC_IMAGE_WND));
	m_DibRes.Draw(dc2.m_hDC, 0, 0);
}


BOOL CBinaraizationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CWnd* pImageWnd = GetDlgItem(IDC_IMAGE_WND);

	CRect rect;
	pImageWnd->GetClientRect(rect);

	//���� ��Ʈ���� ũ�⿡ �°� �Է� ������ ���纻�� ũ�⸦ ����
	DibResizeNearest(m_DibSrc, rect.Width(), rect.Height());
	//����ȭ�� ����� ������ ������ ����	
	m_DibRes = m_DibSrc;
	DibBinarization(m_DibRes, m_nThreshold);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CBinaraizationDlg::OnEnChangeThreshold()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);
	m_sliderThreshold.SetPos(m_nThreshold);
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_DibRes = m_DibSrc;
	DibBinarization(m_DibRes, m_nThreshold);
	Invalidate(FALSE);
}


void CBinaraizationDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//�����̵�ٿ��� �߻��� WM_HSCROLL �޽����� ��� ó��
	if (m_sliderThreshold.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_sliderThreshold.GetPos();
		m_nThreshold = nPos;
		UpdateData(FALSE);

		//���� ������ �Ӱ谪�� �̿��Ͽ� �̸����� ������ ����ȭ�� ����
		m_DibRes = m_DibSrc;
		DibBinarization(m_DibRes, m_nThreshold);
		Invalidate(FALSE);
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
