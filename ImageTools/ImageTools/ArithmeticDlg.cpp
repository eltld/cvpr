// ArithmeticDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageTools.h"
#include "ArithmeticDlg.h"
#include "afxdialogex.h"
#include "ImageToolsDoc.h"

// CArithmeticDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CArithmeticDlg, CDialog)

CArithmeticDlg::CArithmeticDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CArithmeticDlg::IDD, pParent)
	, m_nFunction(0)
	, m_pDoc1(NULL)
	, m_pDoc2(NULL)
{

}

CArithmeticDlg::~CArithmeticDlg()
{
}

void CArithmeticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nFunction);
	DDX_Radio(pDX, IDC_RADIO1, m_nFunction);
	DDX_Control(pDX, IDC_COMBO1, m_comboimage1);
	DDX_Control(pDX, IDC_COMBO2, m_comboimage2);
}


BEGIN_MESSAGE_MAP(CArithmeticDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CArithmeticDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CArithmeticDlg �޽��� ó�����Դϴ�.


BOOL CArithmeticDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nIndex = 0;
	CString strTitle;
	CImageToolsApp* pApp = (CImageToolsApp*)AfxGetApp();
	CImageToolsDoc* pDoc = NULL;
	POSITION pos = pApp->m_pImageDocTemplate->GetFirstDocPosition();

	while (pos != NULL)
	{
		pDoc = (CImageToolsDoc*)pApp->m_pImageDocTemplate->GetNextDoc(pos);
		strTitle = pDoc->GetTitle();

		m_comboimage1.InsertString(nIndex, strTitle);
		m_comboimage2.InsertString(nIndex, strTitle);

		m_comboimage1.SetItemDataPtr(nIndex, (void*)pDoc);
		m_comboimage2.SetItemDataPtr(nIndex, (void*)pDoc);
		nIndex++;
	}
	m_comboimage1.SetCurSel(0);
	m_comboimage2.SetCurSel(0);
	if (nIndex > 1)
		m_comboimage2.SetCurSel(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CArithmeticDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_pDoc1 = (CImageToolsDoc*)m_comboimage1.GetItemDataPtr(m_comboimage1.GetCurSel());
	m_pDoc2 = (CImageToolsDoc*)m_comboimage2.GetItemDataPtr(m_comboimage2.GetCurSel());
	CDialog::OnOK();
}
