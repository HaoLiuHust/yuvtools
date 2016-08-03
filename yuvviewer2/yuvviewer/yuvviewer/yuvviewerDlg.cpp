
// yuvviewerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "yuvviewer.h"
#include "yuvviewerDlg.h"
#include "Convert.h"
#include "cv.h"
#include "highgui.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define min(x,y) (x>y)?y:x
 ColorSpaceConversions con;
 IplImage *yimg;
 IplImage *src;
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
	, frmwidth(176)
	, frmheight(144)
	, frmrate ("30")
	, startFrm(_T("0"))
	, endFrm(_T("1000"))
	, playsize(_T("100%"))
	, frmformat(_T("YV12"))
	, frmNo(_T("0"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CyuvviewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Play, m_buttonPlay);
	DDX_Control(pDX, IDC_BackOrder, m_buttonOrder);
	DDX_Text(pDX, IDC_FrmWidth, frmwidth);
	DDX_Text(pDX, IDC_FrmHeight, frmheight);
	DDX_CBString(pDX, IDC_FrmRate, frmrate);
	DDX_Text(pDX, IDC_Startfrm, startFrm);
	DDX_Text(pDX, IDC_Endfrm, endFrm);
	DDX_CBString(pDX, IDC_playsize, playsize);
	DDX_Text(pDX, IDC_NO, frmNo);
}

BEGIN_MESSAGE_MAP(CyuvviewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SizeCIF, &CyuvviewerDlg::OnBnClickedSizecif)
	ON_BN_CLICKED(IDC_SizeQCIF, &CyuvviewerDlg::OnBnClickedSizeqcif)
	ON_BN_CLICKED(IDC_OpenFile, &CyuvviewerDlg::OnBnClickedOpenfile)
	ON_EN_CHANGE(IDC_FrmHeight, &CyuvviewerDlg::OnEnChangeFrmheight)
	ON_EN_CHANGE(IDC_FrmWidth, &CyuvviewerDlg::OnEnChangeFrmwidth)
	ON_BN_CLICKED(IDC_SizeOther, &CyuvviewerDlg::OnBnClickedSizeother)
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
	
	ON_EN_CHANGE(IDC_Endfrm, &CyuvviewerDlg::OnEnChangeEndfrm)
	ON_EN_CHANGE(IDC_Startfrm, &CyuvviewerDlg::OnEnChangeStartfrm)
END_MESSAGE_MAP()


// CyuvviewerDlg ��Ϣ�������

BOOL CyuvviewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
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
	play=true;
	backorder=false;
	closed=0;
	count=0;
	n=1;
	buffer=0;
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
	frmwidth = 352;
	frmheight = 288;
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
	frmwidth = 176;		//Ĭ�Ϻõĳߴ�
	frmheight = 144;
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
	frmwidth = 176;		
	frmheight = 144;
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
	if(play)
	{
		m_buttonPlay.SetWindowText("��ͣ");
		play=false;
	}
	else
	{
		m_buttonPlay.SetWindowText("����");
		play=true;
	}
	
	while(1)
	{  if(!play&&(!backorder)&&(count<endNUM))
		{if(displayfrm(count++))
		{ 		
		cvWaitKey(delaytime);}
			else break;
		 } 
	else if(!play&&(backorder)&&(count>=startfrm))
		{if(displayfrm(count--))
		{ 		
		cvWaitKey(delaytime);}
			else break;
		 } 
	else return;
	}


	
}


void CyuvviewerDlg::OnBnClickedOpenfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
    startfrm=atoi(startFrm);
	closed=0;
	endfrm=atoi(endFrm);
	frmsize=frmwidth*frmheight*3/2;
	delaytime=1000/atoi(frmrate);
	count=startfrm;
		if(playsize=="100%") m_nZoom=1;
	else if(playsize=="200%")  m_nZoom=2;
	else  m_nZoom=4;
		char BASED_CODE szFilter[] = "YUV Files (*.yuv)|*.yuv||";
	CFileDialog dlg(true,"YUV",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal()!=IDOK)  
			return;
	path=dlg.GetPathName();
	fileTitle=dlg.GetFileTitle();
	UpdateData(FALSE);
	if(!file.Open(path, CFile::modeRead )) 
	{
		AfxMessageBox("���ܴ������ļ�");
	}
	len=file.GetLength();
	frmNUM=len/frmsize;
	endNUM=min(endfrm+1,frmNUM);
	pYUVData=new unsigned char[frmsize];
    pRGBData=new unsigned char[frmsize*2];
	buffer=1;
	src = cvCreateImage(cvSize(frmwidth, frmheight),IPL_DEPTH_8U,3);
	yimg = cvCreateImage(cvSize(frmwidth*m_nZoom, frmheight*m_nZoom),IPL_DEPTH_8U,3);
	yimg->origin=1;
		cvNamedWindow(fileTitle,CV_WINDOW_AUTOSIZE );
	displayfrm(startfrm);
}


void CyuvviewerDlg::OnBnClickedBackorder()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(!backorder) {backorder=true;m_buttonOrder.SetWindowText("����");}
	else {backorder=false;m_buttonOrder.SetWindowText("����");}
	
}
void CyuvviewerDlg::OnBnClickedNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	count++;
	if(count>endNUM-1) {count=endNUM-1;MessageBox("�����ļ�β");}
	displayfrm(count);
	
}
void CyuvviewerDlg::OnBnClickedNext5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	count+=5;
	if(count>endNUM-1) {count=endNUM-1;MessageBox("�����ļ�β");}
	displayfrm(count);
	
}
void CyuvviewerDlg::OnBnClickedPrevious()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	count--;
	if(count<startfrm) count=startfrm;
	displayfrm(count);
	
}


void CyuvviewerDlg::OnBnClickedPrevious5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		count-=5;
		if(count<startfrm) count=startfrm;
		displayfrm(count);
}


void CyuvviewerDlg::OnBnClickedCloseall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(!closed)
	   {cvDestroyWindow(fileTitle);
		file.Close();
		closed=1;
		if(buffer)
		{
			free(pYUVData);
			free(pRGBData);
		}
     }
	
	else return;
		
				
}




void CyuvviewerDlg::OnBnClickedQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!closed)
	{
	cvDestroyWindow(fileTitle);
	file.Close();
	if(buffer)
		{
			free(pYUVData);
			free(pRGBData);
		}
	}
   CDialog::OnCancel();
}


void CyuvviewerDlg::OnBnClickedReturn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	count=startfrm;
	displayfrm(count);
		
}


void CyuvviewerDlg::OnCbnSelchangeplaysize()
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
	for(int k=0;k<width*height*3;k++)	
	{
		temp=rgb[i];
		rgb[i]=rgb[width*height*3-i];
		rgb[width*height*3-i]=temp;
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





void CyuvviewerDlg::OnEnChangeFrmwidth()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
int CyuvviewerDlg::displayfrm(int nFrame)
{
	file.Seek(nFrame*frmsize,CFile::begin);
	file.Read(pYUVData,frmsize);
	con.YV12_to_RGB24(pYUVData,pYUVData+frmwidth*frmheight,pYUVData+frmwidth*frmheight*5/4,pRGBData,frmwidth, frmheight);
	 cvSetData(src,pRGBData,frmwidth*3);
	cvResize(src,yimg,CV_INTER_LINEAR);
	cvShowImage(fileTitle,yimg);
	frmNo.Format("%d",nFrame);
	GetDlgItem(IDC_NO)->SetWindowTextA(frmNo);
	return 1;
}

void CyuvviewerDlg::OnEnChangeEndfrm()
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
