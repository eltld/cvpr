// RotateDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTools.h"
#include "RotateDlg.h"
#include "afxdialogex.h"


// CRotateDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRotateDlg, CDialog)

CRotateDlg::CRotateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRotateDlg::IDD, pParent)
	, m_nRotate(0)
	, m_fAngle(0)
{

}

CRotateDlg::~CRotateDlg()
{
}

void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_ROTATE1, m_nRotate);
	DDX_Text(pDX, IDC_ANGLE, m_fAngle);
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialog)
END_MESSAGE_MAP()


// CRotateDlg 메시지 처리기입니다.
