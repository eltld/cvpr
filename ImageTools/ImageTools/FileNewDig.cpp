// FileNewDig.cpp : implementation file
//

#include "stdafx.h"
#include "ImageTools.h"
#include "FileNewDig.h"
#include "afxdialogex.h"


// CFileNewDig dialog

IMPLEMENT_DYNAMIC(CFileNewDig, CDialog)

CFileNewDig::CFileNewDig(CWnd* pParent /*=NULL*/)
	: CDialog(CFileNewDig::IDD, pParent)
	, m_nWidth(256)
	, m_nHeight(256)
	, m_nType(0)
{

}

CFileNewDig::~CFileNewDig()
{
}

void CFileNewDig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	DDV_MinMaxInt(pDX, m_nWidth, 0, 2048);
	DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDV_MinMaxInt(pDX, m_nHeight, 0, 2048);
	DDX_CBIndex(pDX, IDC_IMAGETYPE, m_nType);
}


BEGIN_MESSAGE_MAP(CFileNewDig, CDialog)
	END_MESSAGE_MAP()


// CFileNewDig message handlers


