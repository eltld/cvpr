#pragma once
#include "afxcmn.h"
#include "Dib.h"

// CBinaraizationDlg ��ȭ �����Դϴ�.

class CBinaraizationDlg : public CDialog
{
	DECLARE_DYNAMIC(CBinaraizationDlg)

public:
	CBinaraizationDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBinaraizationDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BINARIZATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderThreshold;
	int m_nThreshold;
	CDib m_DibSrc; // �Է� ������ ��� ���纻 
	CDib m_DibRes; // ���� �Ӱ谪�� �̿��Ͽ� m_DibSrc�� ����ȭ�� ����
public:
	void SetImage(CDib& dib);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeThreshold();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
