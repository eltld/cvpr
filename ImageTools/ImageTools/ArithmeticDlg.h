#pragma once
#include "afxwin.h"


// CArithmeticDlg ��ȭ �����Դϴ�.

class CArithmeticDlg : public CDialog
{
	DECLARE_DYNAMIC(CArithmeticDlg)

public:
	CArithmeticDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CArithmeticDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ARITHMETIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_nFunction;
	virtual BOOL OnInitDialog();
	CComboBox m_comboimage1;
	CComboBox m_comboimage2;
	void* m_pDoc1;
	void* m_pDoc2;
	afx_msg void OnBnClickedOk();
};
