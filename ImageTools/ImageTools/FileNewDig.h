#pragma once


// CFileNewDig dialog

class CFileNewDig : public CDialog
{
	DECLARE_DYNAMIC(CFileNewDig)

public:
	CFileNewDig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileNewDig();

// Dialog Data
	enum { IDD = IDD_FILE_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// Image Width
	int m_nWidth;
	// Image Height
	int m_nHeight;
	// Image Color Type(Gray Scale, True Color)	
	int m_nType;
};
