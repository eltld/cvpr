
// ImageTools.h : ImageTools ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CImageToolsApp:
// �� Ŭ������ ������ ���ؼ��� ImageTools.cpp�� �����Ͻʽÿ�.
//

class CDib;
class CImageToolsApp : public CWinAppEx
{
public:
	CImageToolsApp();
	~CImageToolsApp();
public:
	CMultiDocTemplate* m_pImageDocTemplate;
public:
	CDib* m_pNewDib;
// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	afx_msg void OnWindowCloseall();
};

extern CImageToolsApp theApp;

void AfxNewImage(CDib& dib);
