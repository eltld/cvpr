#pragma once


// CHarrisDlg 대화 상자입니다.

class CHarrisDlg : public CDialog
{
	DECLARE_DYNAMIC(CHarrisDlg)

public:
	CHarrisDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CHarrisDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HARRIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nThreshold;
};
