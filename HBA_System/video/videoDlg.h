
// videoDlg.h : ��� ����
//

#pragma once
#include "Dib.h"
#include "DibColor.h"
#include "Avi.h"
#include <string>
#include "afxwin.h"

using namespace std;

// CvideoDlg ��ȭ ����
class CvideoDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CvideoDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VIDEO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedLoad();



public:
	CDib m_Dib; 
	CAvi m_Avi;

	CString temp_path; // ���� ���� ��ġ ���� (DIR)
	CString load_path; // ���� �ε��ϴ� ��ġ ����(Load)
	CString save_path; // ���� ������ ��ġ ����(SAVE)
	CString num_key; // �ڸ�����ŭ 0����.
	CString eb_curFrame; // ����������
	CString eb_totalFrame; // ��ü������
	CString eb_processtime; // ó���ð�
	CListBox m_lb_fname; // ����Ʈ�ڽ� ���
	string* bmpsaved; // bmp�� �̸��� ����ȴ�.

	LARGE_INTEGER Frequency; // �ý��� ���� �ð�.

	int m_nCurrentFrame; // ���� ������	
	int count; // ���� ����Ű�� ������

	int count_bmp;
	int cur_bmp;
	int num_length;
	//Picture Control - Local Adaptive thresholding Binarization
	int lo_width;
	int lo_height;
	int lo_left;
	int lo_top;
	//Picture Control - Global Adaptive thresholding Binarization
	int gl_width;
	int gl_height;
	int gl_left;
	int gl_top;
	//Picture Control -	Original 
	int or_width;
	int or_height;
	int or_left;
	int or_top;
	bool m_bPlay; // �������
	bool m_load; // �ε忩��
	bool ischecked; // üũ�ڽ� Ȱ������
	
	
public:
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedPrev();
	afx_msg void OnBnClickedOpendir();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedSavedir();

public:
	void processImage();
	void drawImage(CDib dib);
	// //Global Iterative Binarization
	void G_Binarization();
	// //Local Iterative Binarization
	void L_Binarization();
	void gl_drawImage(CDib dib);
	void or_drawImage(CDib dib);
	void lo_drawImage(CDib dib);
	void OriginalImage();
};
