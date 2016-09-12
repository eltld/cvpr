// videoDlg.cpp : ���� ����
#include "stdafx.h"
#include "video.h"
#include "videoDlg.h"
#include "afxdialogex.h"
#include <io.h>
#include <windows.h>
#include "DibSegment.h"
#include "DibEnhancement.h"
#include "DibColor.h"
#include "GCD.h"
#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define D_MAX_ARRAY_SIZE 1000

using namespace std;


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CvideoDlg ��ȭ ����



CvideoDlg::CvideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CvideoDlg::IDD, pParent)
	, eb_curFrame(_T(""))
	, eb_totalFrame(_T(""))
	, eb_processtime(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CvideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lb_fname);
	DDX_Text(pDX, IDC_EB_CF, eb_curFrame);
	DDX_Text(pDX, IDC_EB_TF, eb_totalFrame);
	DDX_Text(pDX, IDC_EB_PT, eb_processtime);
}

BEGIN_MESSAGE_MAP(CvideoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_LOAD, &CvideoDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_PLAY, &CvideoDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_STOP, &CvideoDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_PAUSE, &CvideoDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_NEXT, &CvideoDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_PREV, &CvideoDlg::OnBnClickedPrev)
	ON_BN_CLICKED(IDC_OPENDIR, &CvideoDlg::OnBnClickedOpendir)
	ON_LBN_SELCHANGE(IDC_LIST1, &CvideoDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_CHECK1, &CvideoDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_SAVEDIR, &CvideoDlg::OnBnClickedSavedir)
END_MESSAGE_MAP()


// CvideoDlg �޽��� ó����

BOOL CvideoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	QueryPerformanceFrequency(&Frequency);//�ý��� ���� �ð�.
	count = 0; // ���� ���� ��ȣ �ʱ�ȭ

	m_bPlay = FALSE; // ���������
	m_load = FALSE; // �ε��ư�� ���ȴ���
	ischecked = FALSE; //SAVE�� üũ �Ǿ�����
	

	//////////////////////////////////
	//Picture Control ũ�� �޾ƿ��� // 
	//////////////////////////////////
	CStatic* lo_staticSize = (CStatic*)GetDlgItem(IDC_LOCAL);
	CStatic* gl_staticSize = (CStatic*)GetDlgItem(IDC_GLOBAL);
	CStatic* or_staticSize = (CStatic*)GetDlgItem(IDC_ORIGIN);

	CRect lo_rect,gl_rect,or_rect;

	lo_staticSize->GetClientRect(lo_rect);
	gl_staticSize->GetClientRect(gl_rect);
	or_staticSize->GetClientRect(or_rect);

	lo_width = lo_rect.Width();
	lo_height = lo_rect.Height();
	gl_width = gl_rect.Width();
	gl_height = gl_rect.Height();
	or_width = or_rect.Width();
	or_height = or_rect.Height(); 
	lo_staticSize->GetWindowRect(lo_rect);
	gl_staticSize->GetWindowRect(gl_rect);
	or_staticSize->GetWindowRect(or_rect);

	ScreenToClient(lo_rect);
	ScreenToClient(gl_rect);
	ScreenToClient(or_rect);

	lo_left = lo_rect.left;
	lo_top = lo_rect.top;
	gl_left = gl_rect.left;
	gl_top = gl_rect.top;
	or_left = or_rect.left;
	or_top = or_rect.top;
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CvideoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CvideoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CvideoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CvideoDlg::OnTimer(UINT_PTR nIDEvent) // Ÿ�̸�. ����ؼ� �Ҹ���.
{
	CString save; // ������ ���� �̸�.
	if(nIDEvent ==1 && !m_load)
	{
		m_nCurrentFrame++;
		if(m_nCurrentFrame >= m_Avi.GetTotalFrame()) // ������ ������
		{
			m_nCurrentFrame = m_Avi.GetTotalFrame() - 1;
			KillTimer(1);
			m_bPlay = FALSE;
		}
		else
		{			
			m_Avi.GetFrame(m_nCurrentFrame, m_Dib);

			processImage();

			if(ischecked)
			{
				if(save_path=="") // ��� ������ �������� C:\\test�� ����.
				{
					::CreateDirectory(_T("C:\\test"),NULL);
					save_path = "C:\\test";
					AfxMessageBox(_T("��μ����� ���� �ʾҽ��ϴ�. \n�⺻ ����� C:\\test�� ������ �˴ϴ�."));
				}

				save.Format(_T("%d"),++count);//�� ��°����
				int len=1;//���� ����Ǵ� bmp�� �ڸ���
				len = save.GetLength();
				CString temp_num_key = num_key.Left(num_key.GetLength()-len);
				m_Dib.Save(save_path+"\\"+temp_num_key+save+".bmp");
			}

			//���� �� ��° ����������.
			CString temp; 
			temp.Format(_T("%d"),m_nCurrentFrame+1);
			eb_curFrame = temp;
		}
	}

	else if(nIDEvent ==1 && m_load) // �ε��ư�� ��������
	{
		cur_bmp++;
		if(cur_bmp == count_bmp) // ������ ������
		{
			cur_bmp = count_bmp-1;
			KillTimer(1);
			m_bPlay = FALSE;
		}

		else
		{
			CString fir;
			fir = load_path;
			fir += "\\";
			fir += bmpsaved[cur_bmp].c_str();

			m_Dib.Load(fir);
			
			processImage();

			CString temp;
			temp.Format(_T("%d"),cur_bmp+1);
			eb_curFrame = temp;
		}
	}
	UpdateData(FALSE); 
	Invalidate(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}

int GetDirFilesNum(CString dirName) // ���ϼ��ý� ���ο� bmp���� ������ ���� �Լ�
{
        int count = 1;
        CFileFind finder;
       
        BOOL bWorking = finder.FindFile(dirName + "/*.bmp");
 
        while(bWorking)
        {
                bWorking = finder.FindNextFile();
                if(finder.IsDots())
                {
                        continue;
                }
               
                count++;
 
        }
        finder.Close();
 
        return count;
}


void CvideoDlg::OnBnClickedLoad() // ���� �ε�. �������� �̹������ϸ� �о����.
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.	
	if(m_bPlay) // ������ε� load��ư ������ ȭ���� ���߾� ����.
	{
		m_bPlay = FALSE;
		KillTimer(1);
	}

	TCHAR cpath[MAX_PATH] = _T("");
	LPITEMIDLIST pDirList;
	BROWSEINFO browseInfo;
	browseInfo.hwndOwner = NULL;
	browseInfo.pidlRoot = NULL;
	browseInfo.lpszTitle = _T("�̹����� �ҷ��� ������ ������ �ּ���.");
	browseInfo.pszDisplayName = cpath;
	browseInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	browseInfo.lpfn = NULL;
	browseInfo.lParam = 0;
	pDirList = SHBrowseForFolder(&browseInfo);
	if(pDirList == NULL) return;
	SHGetPathFromIDList(pDirList, cpath);

	TCHAR *return_path = cpath;

	load_path = return_path;

	count_bmp = GetDirFilesNum(load_path); // ���� ���� bmp������ ��ΰ�!
	
	if(count_bmp == 1)
	{
		AfxMessageBox(_T("bmp������ �����ϴ�."));
		return ;
	}

	cur_bmp = 0; //���� ���° bmp�ΰ�

	if(count_bmp >0){ //bmp������ ������
	bmpsaved = new string[count_bmp];
	memset(bmpsaved,NULL,count_bmp-1); // ���� ������ŭ �ʱ�ȭ
	}

	struct _finddata_t c_file;
	intptr_t hFile = _findfirst(load_path+"\\*.bmp", &c_file);
	if(hFile==-1) return;      // no files
	do
	{
		if(c_file.attrib & _A_SUBDIR)
		{
				// directory ó��
		}
		else if(c_file.attrib & _A_HIDDEN)
		{
				// hidden file ó��
		}
		else
		{
				// �Ϲ� ���� ó��
			char* temp;
			temp = c_file.name;
			
			bmpsaved[cur_bmp] = temp;
			cur_bmp++;
		}
	} while(_findnext(hFile, &c_file)==0);
	_findclose(hFile);

	CString fir;
	fir = load_path;
	fir += "\\";
	fir += bmpsaved[0].c_str();

	m_Dib.Load(fir);

	processImage();

	//��ü bmp�� �����
	CString temp;
	temp.Format(_T("%d"),count_bmp);
	eb_totalFrame = temp;
	eb_curFrame = "1";
	UpdateData(FALSE);
	
	m_load = TRUE; // �ε��ư�� ����.
	cur_bmp = 0;
}


void CvideoDlg::OnBnClickedPlay() // ���
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_Avi.IsValid() && !m_load) // �ε��ư �ȴ����� ��
	{		 
		if(!m_bPlay) // ������� �ƴ� ��
		{
			SetTimer(1, 1000/m_Avi.GetFrameRate(), NULL);
			m_bPlay = TRUE;
		}
		else// ������� ��
		{
			m_bPlay = FALSE;
			KillTimer(1);
		}
	}
	else if(m_load) // �ε��ư ������ ��
	{
		if(!m_bPlay) // ������� �ƴ� ��
		{
			SetTimer(1,70,NULL);
			m_bPlay = TRUE;
		}
		else
		{
			m_bPlay = FALSE;
			KillTimer(1);
		}
	}
}


void CvideoDlg::OnBnClickedStop() // ����
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_Avi.IsValid()&&!m_load){ // �ε����� �ƴҶ�
		count =0;
		m_bPlay = FALSE;
		KillTimer(1);
		m_nCurrentFrame = 0;
		m_Avi.GetFrame(m_nCurrentFrame,m_Dib); //������ ù ��° �������� ǥ��
		
		processImage();

		Invalidate(FALSE);

		eb_curFrame = "1";
		UpdateData(FALSE); 
	}

	else if(m_load)// �ε��ư ����
	{
		m_bPlay = FALSE;
		KillTimer(1);
		cur_bmp = 0;

		CString fir;
		fir = load_path;
		fir += "\\";
		fir += bmpsaved[cur_bmp].c_str(); // ù ȭ�� ���

		m_Dib.Load(fir);

		processImage();

		Invalidate(FALSE);

		eb_curFrame = "1";
		UpdateData(FALSE); 
	}
}


void CvideoDlg::OnBnClickedPause() // �Ͻ�����
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_bPlay = FALSE;
	KillTimer(1);
}


void CvideoDlg::OnBnClickedNext() // �� ������ �ڷ�
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_Avi.IsValid() && !m_load){
		if(m_nCurrentFrame < m_Avi.GetTotalFrame() -1)
		{
			m_nCurrentFrame++;
			m_Avi.GetFrame(m_nCurrentFrame,m_Dib);

			processImage();

			CString temp;
			temp.Format(_T("%d"),m_nCurrentFrame+1);
			eb_curFrame = temp;
			UpdateData(FALSE); 
		}
	}
	else
	{
		if(cur_bmp < count_bmp-1)
		{
			cur_bmp++;
			CString fir;
			fir = load_path;
			fir += "\\";
			fir += bmpsaved[cur_bmp].c_str(); // �� ������ �ڷ�

			m_Dib.Load(fir);

			processImage();

			CString temp;
			temp.Format(_T("%d"),cur_bmp+1);
			eb_curFrame = temp;
			UpdateData(FALSE); 
		}
	}
	Invalidate(FALSE);
}


void CvideoDlg::OnBnClickedPrev() // �� ������ ������
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_Avi.IsValid() && !m_load)
	{
		if(m_nCurrentFrame > 0)
		{
			m_nCurrentFrame--;
			m_Avi.GetFrame(m_nCurrentFrame,m_Dib);

			processImage();

			CString temp;
			temp.Format(_T("%d"),m_nCurrentFrame+1);
			eb_curFrame = temp;
			UpdateData(FALSE); 
		}
	}
	else
	{
		if(cur_bmp > 0)
		{
			cur_bmp--;
			CString fir;
			fir = load_path;
			fir += "\\";
			fir += bmpsaved[cur_bmp].c_str(); // �� ������ �ڷ�

			m_Dib.Load(fir);

			processImage();

			CString temp;
			temp.Format(_T("%d"),cur_bmp+1);
			eb_curFrame = temp;
			UpdateData(FALSE); 
		}
	}
	Invalidate(FALSE);
}


void CvideoDlg::OnBnClickedOpendir() // �������� .avi ��ü ����
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_bPlay)
	{
		m_bPlay = FALSE;
		KillTimer(1);
	}
	TCHAR cpath[MAX_PATH] = _T("");
	LPITEMIDLIST pDirList;
	BROWSEINFO browseInfo;
	browseInfo.hwndOwner = NULL;
	browseInfo.pidlRoot = NULL;
	browseInfo.lpszTitle = _T("Avi�� �ҷ��� ������ ������ �ּ���.");
	browseInfo.pszDisplayName = cpath;
	browseInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	browseInfo.lpfn = NULL;
	browseInfo.lParam = 0;
	pDirList = SHBrowseForFolder(&browseInfo);
	if(pDirList == NULL) return;
	SHGetPathFromIDList(pDirList, cpath);

	TCHAR *return_path = cpath;

	if(return_path != NULL)
		m_lb_fname.ResetContent();

	CString temp;
	//CString temp_path;
	temp_path = return_path; // ���� ��� ����

	struct _finddata_t c_file;
	intptr_t hFile = _findfirst(temp_path+"\\*.avi", &c_file);
	if(hFile==-1) 
	{
		AfxMessageBox(_T("Avi������ �����ϴ�."));
		return;      // no files
	}
	do
	{
		if(c_file.attrib & _A_SUBDIR)
		{
				// directory ó��
		}
		else if(c_file.attrib & _A_HIDDEN)
		{
				// hidden file ó��
		}
		else
		{
				// �Ϲ� ���� ó��
			temp = c_file.name;
			m_lb_fname.AddString(temp);
		}
	} while(_findnext(hFile, &c_file)==0);
	_findclose(hFile);

}


void CvideoDlg::OnLbnSelchangeList1() // ����Ʈ�ڽ����� .avi���� ����
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_load = FALSE;
	count =0;
	num_key = "";
	int level = m_lb_fname.GetCurSel(); // ���� ���õ� �ε���?
	CString tempname;

	if(m_bPlay) // ������ε� avi ������ �ϸ� ȭ���� ���߾� ����.
	{
		m_bPlay = FALSE;
		KillTimer(1);
	}

	if(level != -1) //���õ� ���� �ִٸ�
	{
		m_lb_fname.GetText(level,tempname);
		m_nCurrentFrame = 0;
		m_bPlay = FALSE;

		m_Avi.Open(temp_path+"\\"+tempname); // �ش��� avi���� ����.
		m_Avi.GetFrame(m_nCurrentFrame, m_Dib);

		drawImage(m_Dib);

		CString temp;
		temp.Format(_T("%d"),m_Avi.GetTotalFrame());
		eb_totalFrame = temp;
		eb_curFrame = "1";
		num_length = temp.GetLength(); // �� �������� ����. ���ڸ�?
		for(int i=0; i< num_length; i++)
			num_key += "0"; // �ڸ���ŭ 0�ٿ��ֱ�

		UpdateData(FALSE);
	}
}


void CvideoDlg::OnBnClickedCheck1() // üũ�ڽ� ������ ��
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(!ischecked) // �ȴ���������
		ischecked = TRUE;

	else
		ischecked = FALSE;
}


void CvideoDlg::OnBnClickedSavedir() // ���� ���� ��� ����
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_bPlay) // �ٸ� �۾����� ����� ���߸� Ÿ�̸Ӹ� ��������.
	{
		m_bPlay = FALSE;
		KillTimer(1);
	}

	TCHAR cpath[MAX_PATH] = _T("");
	LPITEMIDLIST pDirList;
	BROWSEINFO browseInfo;
	browseInfo.hwndOwner = NULL;
	browseInfo.pidlRoot = NULL;
	browseInfo.lpszTitle = _T("�̹����� ���� �� ������ ������ �ּ���.");
	browseInfo.pszDisplayName = cpath;
	//browseInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	browseInfo.ulFlags = BIF_RETURNONLYFSDIRS|BIF_NEWDIALOGSTYLE ;
	browseInfo.lpfn = NULL;
	browseInfo.lParam = 0;
	pDirList = SHBrowseForFolder(&browseInfo);
	if(pDirList == NULL) return;
	SHGetPathFromIDList(pDirList, cpath);

	TCHAR *return_path = cpath;

	save_path = return_path;
}


void CvideoDlg::processImage()
{
	LARGE_INTEGER BeginTime;
	LARGE_INTEGER Endtime;
	CDib dib = m_Dib;
	QueryPerformanceCounter(&BeginTime); // �ð� ���� ����
	//Global Iteration Binarization
	G_Binarization();
		
	//L_Binarization();
	OriginalImage();
	QueryPerformanceCounter(&Endtime); // �ð� ���� ��.

	CString temp;
	//ó���ð�. ���� ms
	temp.Format(_T("%lf"),((double)(Endtime.QuadPart - BeginTime.QuadPart)/(double)Frequency.QuadPart)*1000);
	eb_processtime = temp;	
}

void CvideoDlg::drawImage(CDib dib)
{
	CDC* pDC = GetDC();
	dib.Draw(pDC->m_hDC,lo_left,lo_top,lo_width,lo_height);
	ReleaseDC(pDC);
}

// //Global Iterative Binarization
void CvideoDlg::G_Binarization()
{
	CDib dib = m_Dib;
	//Color ������ graysclae�� ��ȯ
	DibGrayscale(dib);
	//�⺻���� ������ ����ȭ(�ݺ������� ���� �Ӱ谪 ����)
	//int th = Gl_DibBinarizationIterative(dib);
	//���� ���õ� t= �ȼ� ��հ� - k*ǥ������ �� �̿��� �Ӱ谪
	//Gl_DibBinarization(dib, 50);
	//First, ������ ���� ���Ÿ� ���� �Ӱ谪 50���ϴ� ��� 0���� set
	
	PreProcessing(dib);
	lo_drawImage(dib);
	int th =(int)AdaptiveThresholding(dib);
	Gl_DibBinarization(dib, th);
	gl_drawImage(dib);
}



// //Local Iterative Binarization
void CvideoDlg::L_Binarization()
{
	CDib dib = m_Dib;
	DibGrayscale(dib);

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	const int blockSize = gcdSubstract(w, h);
	int blockCount = (w / blockSize) * (h / blockSize);
	int *th = new int[blockCount];
	memset(th, 0, sizeof(int)*blockCount);

	Lo_DibHistEqual(dib, blockSize,th);
	Lo_DibBinarization(dib, blockSize, th);
	lo_drawImage(dib);
	delete[] th;
}


void CvideoDlg::gl_drawImage(CDib dib)
{
	CDC* pDC = GetDC();
	dib.Draw(pDC->m_hDC, gl_left, gl_top, gl_width, gl_height);
	ReleaseDC(pDC);
}


void CvideoDlg::or_drawImage(CDib dib)
{
	CDC* pDC = GetDC();
	dib.Draw(pDC->m_hDC, or_left, or_top, or_width, or_height);
	ReleaseDC(pDC);
}


void CvideoDlg::lo_drawImage(CDib dib)
{
	CDC* pDC = GetDC();
	dib.Draw(pDC->m_hDC, lo_left, lo_top, lo_width, lo_height);
	ReleaseDC(pDC);
}


void CvideoDlg::OriginalImage()
{
	CDib dib = m_Dib;
	or_drawImage(dib);
}
