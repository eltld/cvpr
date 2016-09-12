#pragma once


// CRotateDlg 대화 상자입니다.

class CRotateDlg : public CDialog
{
	DECLARE_DYNAMIC(CRotateDlg)

public:
	CRotateDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRotateDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ROTATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nRotate;
	int m_fAngle;
};
