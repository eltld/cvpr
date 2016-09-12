// ArithmeticDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTools.h"
#include "ArithmeticDlg.h"
#include "afxdialogex.h"
#include "ImageToolsDoc.h"

// CArithmeticDlg 대화 상자입니다.

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


// CArithmeticDlg 메시지 처리기입니다.


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
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CArithmeticDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pDoc1 = (CImageToolsDoc*)m_comboimage1.GetItemDataPtr(m_comboimage1.GetCurSel());
	m_pDoc2 = (CImageToolsDoc*)m_comboimage2.GetItemDataPtr(m_comboimage2.GetCurSel());
	CDialog::OnOK();
}
