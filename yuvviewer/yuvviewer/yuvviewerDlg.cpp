
// yuvviewerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "yuvviewer.h"
#include "ChildWindow.h"
#include "yuvviewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BOOL g_bPlay;
int g_nFrameNumber = 0;
BOOL g_Play = true;

int g_nStartFrame = 0;		
int g_nEndFrame = 10000;	
int g_nCurrentFrame = 0;	
BOOL g_bReversePlay = FALSE;	
int n=1;

UINT PlayVideo( LPVOID pParam )
{  int i;
	BOOL bPlay = g_bPlay;
	BOOL bEof = FALSE;

	CyuvviewerDlg *pWin = (CyuvviewerDlg *)pParam;	//���̲߳���(�ṹ��)ȡ���Ի����ָ��
	UINT picsize = pWin->m_nWidth*pWin->m_nHeight;	//ͨ���Ի����ָ����ʶԻ���ĳ�Ա����
	int timespan = 1000/atoi(pWin->frmrate);	//
	
	if(g_nCurrentFrame < g_nStartFrame) g_nCurrentFrame = g_nStartFrame;
	if(g_nCurrentFrame > g_nEndFrame) g_nCurrentFrame = g_nEndFrame;

	for(i=0; i<pWin->m_iCount; i++)
	{  
		if(pWin->Frmformat==1||pWin->Frmformat==4)
		pWin->m_pFile[i]->Seek(g_nCurrentFrame*picsize*3/2*n, SEEK_SET);
		else if(pWin->Frmformat==2||pWin->Frmformat==3)
        pWin->m_pFile[i]->Seek(g_nCurrentFrame*picsize*2, SEEK_SET);
		pWin->m_pWnd[i]->nPicShowOrder = g_nCurrentFrame;
	}
	
	HANDLE hPlayTemp1 = OpenMutex(MUTEX_ALL_ACCESS,FALSE,"����");//�������ܣ�Ϊ���е�һ����������������󴴽�һ���¾����һ��������Ҫ��ע��һ��Ҫ�� CloseHandle �رջ������������������о�����ѹرգ���ô����Ҳ��ɾ��
	
	while(g_nCurrentFrame >= g_nStartFrame && g_nCurrentFrame <= g_nEndFrame && !bEof)
	{
		DWORD t2=GetTickCount();	//�Ӳ���ϵͳ������������������elapsed���ĺ����������ķ���ֵ��DWORD��
		g_nFrameNumber = g_nCurrentFrame;//j;
 
		if ( WAIT_OBJECT_0 == WaitForSingleObject(hPlayTemp1,INFINITE) )
			ReleaseMutex( hPlayTemp1 );
		
		for(i=0; i<pWin->m_iCount; i++)
		{   
			if(pWin->Frmformat==1||pWin->Frmformat==4)
			pWin->m_pFile[i]->Seek(g_nCurrentFrame*picsize*3/2*n, SEEK_SET);//Seek ���� ����һ�� Long���� Open ���򿪵��ļ���ָ����ǰ�Ķ�/дλ�á�
			else if(pWin->Frmformat==2||pWin->Frmformat==3)
            pWin->m_pFile[i]->Seek(g_nCurrentFrame*picsize*2, SEEK_SET);
			if(pWin->Frmformat==3)
             {
		   if(picsize*2 != pWin->m_pFile[i]->Read(pWin->m_pWnd[i]->YUY2,picsize*2))
	     {
		AfxMessageBox("���");
		bEof = TRUE;
				break;
	       }
	     }
			else
			{
			if(picsize != pWin->m_pFile[i]->Read(pWin->m_pWnd[i]->Y,picsize))
			{
				AfxMessageBox("���");
				bEof = TRUE;
				break;
			}
			if(1)//bColorImage) 
			{
				if(picsize/4*pWin->Frmformat != pWin->m_pFile[i]->Read(pWin->m_pWnd[i]->Cb,picsize/4*pWin->Frmformat))
				{
					AfxMessageBox("���");
					bEof = TRUE;
					break;
				}
				if(picsize/4*pWin->Frmformat != pWin->m_pFile[i]->Read(pWin->m_pWnd[i]->Cr,picsize/4*pWin->Frmformat))
				{
					AfxMessageBox("���");
					bEof = TRUE;
					break;
				}
			}
			}
			
			pWin->m_pWnd[i]->nPicShowOrder=g_nCurrentFrame;
			pWin->m_pWnd[i]->InvalidateRect (NULL,FALSE);
			pWin->m_pWnd[i]->UpdateWindow ();
		}

		if(g_bReversePlay == FALSE&&!bEof)
			g_nCurrentFrame++;
		else 
			g_nCurrentFrame--;

		int t1=GetTickCount()-t2;
		if(t1 < timespan) 
			Sleep(timespan - t1); // sleep time in milliseconds
	}
	
	pWin->m_pWinThread = NULL;
	AfxEndThread(0);

	return 1;

}
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CyuvviewerDlg �Ի���




CyuvviewerDlg::CyuvviewerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CyuvviewerDlg::IDD, pParent)
	, m_nWidth(176)
	, m_nHeight(144)
	, frmrate ("30")
	, startfrm(0)
	, endfrm(0)
	, playsize(_T("100%"))
	, frmformat(_T("YV12"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CyuvviewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Play, m_buttonPlay);
	DDX_Control(pDX, IDC_BackOrder, m_buttonOrder);
	DDX_Control(pDX, IDC_showgray, m_buttongray);
	DDX_Text(pDX, IDC_FrmWidth, m_nWidth);
	DDX_Text(pDX, IDC_FrmHeight, m_nHeight);
	DDX_CBString(pDX, IDC_FrmRate, frmrate);
	DDX_Text(pDX, IDC_Startfrm, startfrm);
	DDX_Text(pDX, IDC_Endfrm, endfrm);
	DDX_CBString(pDX, IDC_playsize, playsize);
	DDX_CBString(pDX, IDC_frmformat, frmformat);
}

BEGIN_MESSAGE_MAP(CyuvviewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SizeCIF, &CyuvviewerDlg::OnBnClickedSizecif)
	ON_BN_CLICKED(IDC_SizeQCIF, &CyuvviewerDlg::OnBnClickedSizeqcif)
	ON_BN_CLICKED(IDC_OpenFile, &CyuvviewerDlg::OnBnClickedOpenfile)
	ON_EN_CHANGE(IDC_FrmHeight, &CyuvviewerDlg::OnEnChangeFrmheight)
	ON_BN_CLICKED(IDC_SizeOther, &CyuvviewerDlg::OnBnClickedSizeother)
	ON_CBN_SELCHANGE(IDC_FrmRate, &CyuvviewerDlg::OnCbnSelchangeFrmrate)
	ON_BN_CLICKED(IDC_Play, &CyuvviewerDlg::OnBnClickedPlay)

	ON_BN_CLICKED(IDC_BackOrder, &CyuvviewerDlg::OnBnClickedBackorder)
	ON_BN_CLICKED(IDC_NEXT, &CyuvviewerDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_NEXT5, &CyuvviewerDlg::OnBnClickedNext5)
	ON_BN_CLICKED(IDC_Previous, &CyuvviewerDlg::OnBnClickedPrevious)
	ON_BN_CLICKED(IDC_Previous5, &CyuvviewerDlg::OnBnClickedPrevious5)
	ON_BN_CLICKED(IDC_CloseAll, &CyuvviewerDlg::OnBnClickedCloseall)
	ON_BN_CLICKED(IDC_QUIT, &CyuvviewerDlg::OnBnClickedQuit)
	ON_BN_CLICKED(IDC_Return, &CyuvviewerDlg::OnBnClickedReturn)
	ON_CBN_SELCHANGE(IDC_playsize, &CyuvviewerDlg::OnCbnSelchangeplaysize)
	ON_CBN_SELCHANGE(IDC_frmformat, &CyuvviewerDlg::OnCbnSelchangefrmformat)
	ON_BN_CLICKED(IDC_showgray, &CyuvviewerDlg::OnBnClickedshowgray)
	ON_EN_CHANGE(IDC_FrmWidth, &CyuvviewerDlg::OnEnChangeFrmwidth)
	ON_EN_CHANGE(IDC_Startfrm, &CyuvviewerDlg::OnEnChangeStartfrm)
	ON_EN_CHANGE(IDC_Endfrm, &CyuvviewerDlg::OnEnChangeEndfrm)
END_MESSAGE_MAP()


// CyuvviewerDlg ��Ϣ�������

BOOL CyuvviewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_iCount = 0;
    m_bPlay = true;
	m_nZoom=1;
	Frmformat=1;
	Color=TRUE;
	m_pWinThread = NULL;
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	((CButton *)GetDlgItem(IDC_SizeQCIF))->SetCheck(TRUE);
	Disable(IDC_FrmWidth);
	Disable(IDC_FrmHeight);
	//CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_FrmRate); 
    //pBox->SetCurSel(5); //����Ϊ�����Ԫ��
		HANDLE hPlay = NULL;
	if( (hPlay=OpenMutex(MUTEX_ALL_ACCESS,FALSE,"����"))==NULL)
	{
		//���û���������̴�������������������´���
		hPlay = CreateMutex(NULL,FALSE,"����");
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CyuvviewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CyuvviewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CyuvviewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CyuvviewerDlg::OnBnClickedSizecif()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_nWidth = 352;
	m_nHeight = 288;
	Disable(IDC_FrmWidth);	
	Disable(IDC_FrmHeight);	
	UpdateData(FALSE);
}
void  CyuvviewerDlg::Disable(int nID)//��ʵ���ö������Ҳ�У�ֱ����CWnd::EnableWindow�Կؼ�����Ȼ��������й淶����
{
	CWnd *pObject1;
	pObject1 = GetDlgItem(nID);
	pObject1->EnableWindow(FALSE);//����BOOL CWnd::EnableWindow(BOOL bEnable = TRUE);
}
void  CyuvviewerDlg::Enable(int nID)//��Disableһ������
{
	CWnd *pObject1;
	pObject1 = GetDlgItem(nID);
	pObject1->EnableWindow(TRUE);
}
BOOL  CyuvviewerDlg::Enabled(int nID)//��ѯһ���ؼ���״̬
{
	CWnd *pObject1;
	pObject1 = GetDlgItem(nID);
	return (pObject1->IsWindowEnabled());//	BOOL CWnd::IsWindowEnabled() const;
}

void CyuvviewerDlg::OnBnClickedSizeqcif()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_nWidth = 176;		//Ĭ�Ϻõĳߴ�
	m_nHeight = 144;
	Disable(IDC_FrmWidth);
	Disable(IDC_FrmHeight);
	UpdateData(FALSE);
}


void CyuvviewerDlg::OnEnChangeFrmheight()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CyuvviewerDlg::OnBnClickedSizeother()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);	
	m_nWidth = 176;		
	m_nHeight = 144;
	Enable(IDC_FrmWidth);
	Enable(IDC_FrmHeight);
	UpdateData(FALSE);
}


void CyuvviewerDlg::OnCbnSelchangeFrmrate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CyuvviewerDlg::OnBnClickedPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(FALSE);
	g_nStartFrame=startfrm;
	if(endfrm==0) g_nEndFrame=10000;
	else g_nEndFrame=endfrm;
	if(m_bPlay)
	{
		m_buttonPlay.SetWindowText("��ͣ");
		m_bPlay=false;
		g_Play = true;
	}
	else
	{
		m_buttonPlay.SetWindowText("����");
		m_bPlay=true;
	}
	CString buttontitle;
	m_buttonPlay.GetWindowText(buttontitle);
	hPlayTemp = NULL;
	hPlayTemp=OpenMutex(MUTEX_ALL_ACCESS,FALSE,"����");
	if ( buttontitle.Compare("����") == 0 )			
	{
		WaitForSingleObject( hPlayTemp,0);
	}
	else
		ReleaseMutex(hPlayTemp);	
	if ( m_pWinThread == NULL)
		m_pWinThread = AfxBeginThread( (AFX_THREADPROC)PlayVideo , (void*)this);
}


void CyuvviewerDlg::OnBnClickedOpenfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(frmformat=="YV12") 
	{Frmformat=1;
	 n=1;}
	else if(frmformat=="4:4:4") 
	{Frmformat=4;n=2;}
	else if(frmformat=="4:2:2") Frmformat=2;
	else if(frmformat=="YUY2") Frmformat=3;
	//else if(frmformat=="4:2:2") Frmformat=2;
	if(playsize=="25%") m_nZoom=0.25;
	else if(playsize=="50")  m_nZoom=0.5;
	else if(playsize=="100%") m_nZoom=1;
	else if(playsize=="200%") m_nZoom=2;
	else  m_nZoom=4;
	UINT picsize = m_nWidth*m_nHeight;
	m_pFile[m_iCount] = new CFile();
		char BASED_CODE szFilter[] = "YUV Files (*.yuv)|*.yuv||";
CFileDialog dlg(true,"YUV",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
if(dlg.DoModal()!=IDOK)  
	return;
	inSeqence[m_iCount]=dlg.GetPathName();
	inSeqName[m_iCount]=dlg.GetFileTitle();
	UpdateData(FALSE);
if(!m_pFile[m_iCount]->Open(inSeqence[m_iCount], CFile::modeRead )) 
	{
		AfxMessageBox("���ܴ������ļ�");
	}
	m_pWnd[m_iCount]=new CChildWindow((CFrameWnd*)this, m_nWidth, m_nHeight,1);
	if(Frmformat==3)
	{
		if(picsize*2 != m_pFile[m_iCount]->Read(m_pWnd[m_iCount]->YUY2,picsize*2))
	{
		MessageBox("���");
	}
	}

else
{
if(picsize != m_pFile[m_iCount]->Read(m_pWnd[m_iCount]->Y,picsize))
	{
		MessageBox("���");
	}
	if(1)
	{
		if(picsize/4*Frmformat != m_pFile[m_iCount]->Read(m_pWnd[m_iCount]->Cb,picsize/4*Frmformat))
		{
			MessageBox("���");
		}
		if(picsize/4*Frmformat != m_pFile[m_iCount]->Read(m_pWnd[m_iCount]->Cr,picsize/4*Frmformat))
		{
			MessageBox("���");
		}
	}}
	/*else if(Frmformat==4)
	{
    if(picsize*3 != m_pFile[m_iCount]->Read(m_pWnd[m_iCount]->YUV,picsize*3))
			{
				AfxMessageBox("���");}
	}*/
	if(m_nZoom == 0.25) m_pWnd[m_iCount]->CenterWindow(m_nWidth*0.25,m_nHeight*0.25);
	else if(m_nZoom == 0.5) m_pWnd[m_iCount]->CenterWindow(m_nWidth*0.5,m_nHeight*0.5);
	else if(m_nZoom == 1) m_pWnd[m_iCount]->CenterWindow(m_nWidth,m_nHeight);
	else if(m_nZoom == 1.5) m_pWnd[m_iCount]->CenterWindow(m_nWidth*1.5,m_nHeight*1.5);
	else if(m_nZoom == 2) m_pWnd[m_iCount]->CenterWindow(m_nWidth*2,m_nHeight*2);
	else if(m_nZoom == 4) m_pWnd[m_iCount]->CenterWindow(m_nWidth*4,m_nHeight*4);
	m_pWnd[m_iCount]->ShowWindow(SW_SHOW);	
	m_iCount++;
	return;
}


void CyuvviewerDlg::OnBnClickedBackorder()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(g_bReversePlay == FALSE)
	{
		m_buttonOrder.SetWindowText("����");
		g_bReversePlay = TRUE;		//Reverse:����
	}
	else
	{
		m_buttonOrder.SetWindowText("����");
		g_bReversePlay = FALSE;
	}
}
void CyuvviewerDlg::OnBnClickedNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i;
	UINT picsize = m_nWidth*m_nHeight;
	UpdateData(TRUE);
	g_nStartFrame = startfrm;
	if(endfrm != 0) g_nEndFrame =endfrm;
	else g_nEndFrame = 10000;
		  g_nCurrentFrame++;
	for( i=0; i<m_iCount; i++)
	{   
		if(Frmformat==1||Frmformat==4)
		m_pFile[i]->Seek(g_nCurrentFrame*picsize*3/2*n, SEEK_SET);
		else if(Frmformat==2||Frmformat==3)
		m_pFile[i]->Seek(g_nCurrentFrame*picsize*2, SEEK_SET);
		m_pWnd[i]->nPicShowOrder = g_nCurrentFrame;
	}

	if(g_nCurrentFrame < g_nEndFrame) // && !bEof)
	{
		g_nFrameNumber = g_nCurrentFrame;
 	  
		for(i=0; i<m_iCount; i++)
		{  	
	  if(Frmformat==3)
	  {
		if(picsize*2 != m_pFile[i]->Read(m_pWnd[i]->YUY2,picsize*2))
	    {
		MessageBox("���");
				return;
	        }
	   }
	else
		{
			if(picsize!= m_pFile[i]->Read(m_pWnd[i]->Y,picsize))
			{
				MessageBox("���");
				return;
			}
			if(1)//bColorImage) 
			{
				if(picsize/4*Frmformat != m_pFile[i]->Read(m_pWnd[i]->Cb,picsize/4*Frmformat))
				{
					MessageBox("���");
					return;
				}
				if(picsize/4*Frmformat != m_pFile[i]->Read(m_pWnd[i]->Cr,picsize/4*Frmformat))
				{
					MessageBox("���");
					return;
				}
			}
	}
			m_pWnd[i]->InvalidateRect (NULL,FALSE);
			m_pWnd[i]->UpdateWindow();
		}
		}
}
void CyuvviewerDlg::OnBnClickedNext5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i;
	UINT picsize = m_nWidth*m_nHeight;
	UpdateData(TRUE);
	g_nStartFrame = startfrm;
	if(endfrm != 0) g_nEndFrame =endfrm;
	else g_nEndFrame = 10000;
		  g_nCurrentFrame+=5;
	for( i=0; i<m_iCount; i++)
	{  if(Frmformat==1||Frmformat==4)
		m_pFile[i]->Seek(g_nCurrentFrame*picsize*3/2*n, SEEK_SET);
	else if(Frmformat==2||Frmformat==3)
		m_pFile[i]->Seek(g_nCurrentFrame*picsize*2, SEEK_SET);
		m_pWnd[i]->nPicShowOrder = g_nCurrentFrame;
	}

	if(g_nCurrentFrame < g_nEndFrame) // && !bEof)
	{
		g_nFrameNumber = g_nCurrentFrame;
 	  
		for(i=0; i<m_iCount; i++)
		{  
		if(Frmformat==3)
	      {
		   if(picsize*2 != m_pFile[i]->Read(m_pWnd[i]->YUY2,picsize*2))
	     {
		MessageBox("���");
	       }
	     }
		else
		{
			if(picsize != m_pFile[i]->Read(m_pWnd[i]->Y,picsize))
			{
				MessageBox("���");
				return;
			}
			if(1)//bColorImage) 
			{
				if(picsize/4*Frmformat != m_pFile[i]->Read(m_pWnd[i]->Cb,picsize/4*Frmformat))
				{
					MessageBox("���");
					return;
				}
				if(picsize/4*Frmformat != m_pFile[i]->Read(m_pWnd[i]->Cr,picsize/4*Frmformat))
				{
					MessageBox("���");
					return;
				}
			}
		}
			m_pWnd[i]->InvalidateRect (NULL,FALSE);
			m_pWnd[i]->UpdateWindow();
		}
		}
}
void CyuvviewerDlg::OnBnClickedPrevious()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		int i;
	UINT picsize = m_nWidth*m_nHeight;
	UpdateData(TRUE);
	g_nStartFrame = startfrm;
	if(endfrm != 0) g_nEndFrame =endfrm;
	else g_nEndFrame = 10000;
		  g_nCurrentFrame--;
		  if(g_nCurrentFrame<0) g_nCurrentFrame=0;
	for( i=0; i<m_iCount; i++)
	{
		if(Frmformat==1||Frmformat==4)
		m_pFile[i]->Seek(g_nCurrentFrame*picsize*3/2*n, SEEK_SET);
	else if(Frmformat==2||Frmformat==3)
		m_pFile[i]->Seek(g_nCurrentFrame*picsize*2, SEEK_SET);
		m_pWnd[i]->nPicShowOrder = g_nCurrentFrame;
	}

	if(g_nCurrentFrame <g_nEndFrame) // && !bEof)
	{
		g_nFrameNumber = g_nCurrentFrame;
 	  
		for(i=0; i<m_iCount; i++)
		{
			if(Frmformat==3)
	      {
		   if(picsize*2 != m_pFile[i]->Read(m_pWnd[i]->YUY2,picsize*2))
	     {
		MessageBox("���");
	       }
	     }
			else
			{if(picsize != m_pFile[i]->Read(m_pWnd[i]->Y,picsize))
			{
				MessageBox("���");
				return;
			}
			if(1)//bColorImage) 
			{
				if(picsize/4*Frmformat != m_pFile[i]->Read(m_pWnd[i]->Cb,picsize/4*Frmformat))
				{
					MessageBox("���");
					return;
				}
				if(picsize/4*Frmformat != m_pFile[i]->Read(m_pWnd[i]->Cr,picsize/4*Frmformat))
				{
					MessageBox("���");
					return;
				}
			}
			}
			m_pWnd[i]->InvalidateRect (NULL,FALSE);
			m_pWnd[i]->UpdateWindow();
		}
		}
}


void CyuvviewerDlg::OnBnClickedPrevious5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		int i;
	UINT picsize = m_nWidth*m_nHeight;
	UpdateData(TRUE);
	g_nStartFrame = startfrm;
	if(endfrm != 0) g_nEndFrame =endfrm;
	else g_nEndFrame = 10000;
		  g_nCurrentFrame-=5;
		   if(g_nCurrentFrame<0) g_nCurrentFrame=0;
	for( i=0; i<m_iCount; i++)
	{
		if(Frmformat==1||Frmformat==4)
		m_pFile[i]->Seek(g_nCurrentFrame*picsize*3/2*n, SEEK_SET);
	else if(Frmformat==2||Frmformat==3)
		m_pFile[i]->Seek(g_nCurrentFrame*picsize*2, SEEK_SET);
		m_pWnd[i]->nPicShowOrder = g_nCurrentFrame;
	}

	if(g_nCurrentFrame < g_nEndFrame) // && !bEof)
	{
		g_nFrameNumber = g_nCurrentFrame;
 	  
		for(i=0; i<m_iCount; i++)
		{
			if(Frmformat==3)
	      {
		   if(picsize*2 != m_pFile[i]->Read(m_pWnd[i]->YUY2,picsize*2))
	     {
		MessageBox("���");
	       }
	     }
			else
			{
			if(picsize != m_pFile[i]->Read(m_pWnd[i]->Y,picsize))
			{
				MessageBox("���");
				return;
			}
			if(1)//bColorImage) 
			{
				if(picsize/4*Frmformat != m_pFile[i]->Read(m_pWnd[i]->Cb,picsize/4*Frmformat))
				{
					MessageBox("���");
					return;
				}
				if(picsize/4*Frmformat != m_pFile[i]->Read(m_pWnd[i]->Cr,picsize/4*Frmformat))
				{
					MessageBox("���");
					return;
				}
			}
			}
			m_pWnd[i]->InvalidateRect (NULL,FALSE);
			m_pWnd[i]->UpdateWindow();
		}
		}
}


void CyuvviewerDlg::OnBnClickedCloseall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i;
	for(i=0; i<m_iCount; i++)		
	{
		if(m_pFile[i])
			m_pFile[i]->Close();		
		if(m_pWnd[i])
			m_pWnd[i]->DestroyWindow();	
	}
	CloseHandle(hPlayTemp);
	m_iCount = 0;						
	g_nFrameNumber = 0;					
	g_Play = true;						
	g_nStartFrame = 0;					
	g_nEndFrame = 10000;				
	g_nCurrentFrame = 0;				
	g_bReversePlay = FALSE;				
}




void CyuvviewerDlg::OnBnClickedQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
   CDialog::OnCancel();
}


void CyuvviewerDlg::OnBnClickedReturn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		int i;
	int picsize = m_nWidth*m_nHeight;	
	UpdateData(TRUE);
	g_nStartFrame = startfrm=0;	
	if(endfrm != 0) 
		g_nEndFrame = endfrm;	
	else 
		g_nEndFrame = 10000;		
	g_nCurrentFrame = 0;			
	for(i=0; i<m_iCount; i++)		
	{
		m_pFile[i]->SeekToBegin();	
		m_pWnd[i]->nPicShowOrder = g_nCurrentFrame;
	}	
	if(g_nCurrentFrame < g_nEndFrame) 
	{
		for(i=0; i<m_iCount; i++)	
		{  
			if(Frmformat==3)
	      {
		   if(picsize*2 != m_pFile[i]->Read(m_pWnd[i]->YUY2,picsize*2))
	     {
		MessageBox("���");
	       }
	     }
			else
			{
			m_pFile[i]->Read(m_pWnd[i]->Y,picsize);			
			if(1)
			{
				m_pFile[i]->Read(m_pWnd[i]->Cb,picsize/4*Frmformat);	
				m_pFile[i]->Read(m_pWnd[i]->Cr,picsize/4*Frmformat);	
			}
			}
			m_pWnd[i]->InvalidateRect (NULL,FALSE);			//�������ܣ��ú�����ָ���Ĵ������һ�����Σ�Ȼ�󴰿ڿͻ��������һ���ֽ������»��ƣ�hWnd��Ҫ���µĿͻ������ڵĴ���ľ�������ΪNULL����ϵͳ���ں�������ǰ���»������еĴ���, Ȼ���� WM_ERASEBKGND �� WM_NCPAINT �����ڹ��̴������� ����2,lpRect����Ч����ľ��δ�������һ���ṹ��ָ�룬����ž��εĴ�С�����ΪNULL��ȫ���Ĵ��ڿͻ����򽫱����ӵ����������С�
			m_pWnd[i]->UpdateWindow ();						//������ڸ��µ�����Ϊ�գ�UpdateWindow����ͨ������һ��WM_PAINT��Ϣ������ָ�����ڵĿͻ����������ƹ�Ӧ�ó������Ϣ���У�ֱ�ӷ���WM_PAINT��Ϣ��ָ�����ڵĴ��ڹ��̣������������Ϊ�գ��򲻷�����Ϣ��
			m_pWnd[i]->nPicShowOrder ++;
		}
		g_nCurrentFrame++;
	}
}


void CyuvviewerDlg::OnCbnSelchangeplaysize()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CyuvviewerDlg::OnCbnSelchangefrmformat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	
}
void CyuvviewerDlg::yuv444_to_rgb24(unsigned char *y,unsigned char *u,unsigned char *v,unsigned char *rgb,int width,int height)
{  int i=0;
    int j=0;
	for(i=0;i<width*height*3;i+=3)
	{   
		if(y[j]+1.402*(v[j]-128)>255)
	       rgb[i+2] =255;
		else if(y[j]+1.402*(v[j]-128)<0)
		   rgb[i+2]=0;
		else
		rgb[i+2]=y[j]+1.402*(v[j]-128);
		if(y[j]-0.34414*(u[j]-128)-0.71414*(v[j]-128)>255)
			rgb[i+1]=255;
		else if(y[j]-0.34414*(u[j]-128)-0.71414*(v[j]-128)<0)
			rgb[i+1]=0;
		else
		 rgb[i+1]=y[j]-0.34414*(u[j]-128)-0.71414*(v[j]-128);
		if(y[j]+1.772*(u[j]-128)>255)
			rgb[i]=255;
		else if(y[j]+1.772*(u[j]-128)<0)
			rgb[i]=0;
		else
		rgb[i]=y[j]+1.772*(u[j]-128);
		j++;
	}
		
}
void CyuvviewerDlg::yuv422_to_rgb24(unsigned char *y,unsigned char *u,unsigned char *v,unsigned char *rgb,int width,int height)
{  
 int R,G,B,Y,U,V;
 int nWidth = width>>1; //ɫ���źſ��
 for (int i=0;i<height;i++)
 {
  for (int j=0;j<width;j++)
  {
   Y = *(y + i*width + j);
   U = *(u + i*nWidth + (j>>1));
   V = *(v + i*nWidth + (j>>1));
   R = Y + 1.402*(V-128);
   G = Y - 0.34414*(U-128) - 0.71414*(V-128);
   B = Y + 1.772*(U-128);
   
   //��ֹԽ��
   if (R>255)R=255;
   if (R<0)R=0;
   if (G>255)G=255;
   if (G<0)G=0;
   if (B>255)B=255;
   if (B<0)B=0;
   
   *(rgb + ((height-i-1)*width + j)*3) = B;
   *(rgb + ((height-i-1)*width + j)*3 + 1) = G;
   *(rgb + ((height-i-1)*width + j)*3 + 2) = R;  
  }
 }
}
void CyuvviewerDlg::yuy2_to_rgb24(unsigned char *pDstData,unsigned char *pSrcData,int width,int height)
{
	long R,G,B;                                                           
 int x(0), y(0);
 int i=0;
 long Y0(0), U(0), Y1(0), V(0);                                          
 for ( y = 0; y < height; y++)
 {
  for ( x = 0; x < width; x += 2)
  {
   Y0 = *pSrcData++;
   U  = *pSrcData++;
   Y1 = *pSrcData++;
   V  = *pSrcData++;
   R  = 1.164383 * (Y0 - 16) + 1.596027 * (V - 128);
   G  = 1.164383 * (Y0 - 16) - 0.812968 * (V - 128) - 0.391762 * (U - 128);
   B  = 1.164383 * (Y0 - 16) + 2.017232 * (U - 128);
   if ( R < 0 )
    R = 0;
   if ( R > 255)
    R = 255;
   if ( G < 0 )
    G = 0;
   if ( G > 255)
    G = 255;
   if ( B < 0 )
    B = 0;
   if ( B > 255 )
    B = 255;
   *pDstData++ = ( BYTE )B;
   *pDstData++ = ( BYTE )G;
   *pDstData++ = ( BYTE )R;
   R  = 1.164383 * (Y1 - 16) + 1.596027 * (V - 128);
   G  = 1.164383 * (Y1 - 16) - 0.812968 * (V - 128) - 0.391762 * (U - 128);
   B  = 1.164383 * (Y1 - 16) + 2.017232 * (U - 128);
   if ( R < 0 )
    R = 0;
   if ( R > 255)
    R = 255;
   if ( G < 0 )
    G = 0;
   if ( G > 255)
    G = 255;
   if ( B < 0 )
    B = 0;
   if ( B > 255 )
    B = 255;
   *pDstData++ = ( BYTE )B;
   *pDstData++ = ( BYTE )G;
   *pDstData++ = ( BYTE )R;
  }
 }
}


void CyuvviewerDlg::OnBnClickedshowgray()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		UpdateData();
	if(Color == TRUE)
	{
		m_buttongray.SetWindowText("��ɫͼ");
		Color = FALSE;	//Reverse:����
	}
	else
	{
		m_buttongray.SetWindowText("�Ҷ�ͼ");
		Color= TRUE;
	}
	for( int j=0; j<m_iCount; j++)
	{  	m_pWnd[j]->bColorImage=Color;
		m_pWnd[j]->InvalidateRect (NULL,FALSE);
	m_pWnd[j]->UpdateWindow();}
}


void CyuvviewerDlg::OnEnChangeFrmwidth()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CyuvviewerDlg::OnEnChangeStartfrm()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CyuvviewerDlg::OnEnChangeEndfrm()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
