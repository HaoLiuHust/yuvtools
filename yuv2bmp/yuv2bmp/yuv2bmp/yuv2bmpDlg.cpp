
// yuv2bmpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "yuv2bmp.h"
#include "yuv2bmpDlg.h"
#include "afxdialogex.h"
#include "Convert.h"
#pragma comment(lib,"cscc.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// Cyuv2bmpDlg 对话框




Cyuv2bmpDlg::Cyuv2bmpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cyuv2bmpDlg::IDD, pParent)
	, startFrm(_T("0"))
	, endFrm(_T("0"))
	, width(_T("176"))
	, height(_T("144"))
	, namele(_T("1"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cyuv2bmpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_startfrm, startFrm);
	DDX_Text(pDX, IDC_endfrm, endFrm);
	DDX_Text(pDX, IDC_frmwidth, width);
	DDX_Text(pDX, IDC_frmheight, height);
	DDX_Text(pDX, IDC_namelen, namele);
}

BEGIN_MESSAGE_MAP(Cyuv2bmpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_openyuv, &Cyuv2bmpDlg::OnBnClickedopenyuv)
	ON_EN_CHANGE(IDC_startfrm, &Cyuv2bmpDlg::OnEnChangestartfrm)
	ON_EN_CHANGE(IDC_endfrm, &Cyuv2bmpDlg::OnEnChangeendfrm)
	ON_BN_CLICKED(IDC_allfrm, &Cyuv2bmpDlg::OnBnClickedallfrm)
	ON_EN_CHANGE(IDC_frmwidth, &Cyuv2bmpDlg::OnEnChangefrmwidth)
	ON_EN_CHANGE(IDC_frmheight, &Cyuv2bmpDlg::OnEnChangefrmheight)
	ON_BN_CLICKED(IDC_openbmp, &Cyuv2bmpDlg::OnBnClickedopenbmp)
	ON_BN_CLICKED(IDC_Convert, &Cyuv2bmpDlg::OnBnClickedConvert)
	ON_EN_CHANGE(IDC_bmp_path, &Cyuv2bmpDlg::OnEnChangebmppath)
	ON_EN_CHANGE(IDC_namelen, &Cyuv2bmpDlg::OnEnChangenamelen)
	ON_EN_CHANGE(IDC_yuv_path, &Cyuv2bmpDlg::OnEnChangeyuvpath)
END_MESSAGE_MAP()


// Cyuv2bmpDlg 消息处理程序

BOOL Cyuv2bmpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	startfrm=0;
	endfrm=0;
	frmwidth=176;
	frmheight=144;
	namel=1;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cyuv2bmpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cyuv2bmpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cyuv2bmpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cyuv2bmpDlg::OnBnClickedopenyuv()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
		char BASED_CODE szFilter[] = "YUV Files (*.yuv)|*.yuv||";
	CFileDialog dlg(true,"YUV",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
if(IDOK!=dlg.DoModal())
 {
  return;
 } 
	m_str=dlg.GetPathName();
  	CEdit* pBoxOne;
	pBoxOne = (CEdit*) GetDlgItem(IDC_yuv_path);
	pBoxOne->SetWindowText( m_str );//m_str为文本框对应的CSTRING类型的变量
 if(!file.Open(m_str,CFile::modeReadWrite))
	 {
		MessageBox("无法打开文件！","WARNING",MB_OK); 
		return;}
 len = file.GetLength();
 frmSize=frmwidth*frmheight*1.5;
	   frmNUM=len/frmSize;
  pReadData = new unsigned char[len]; 
    file.Read(pReadData,len); 
	file.Close();
UpdateData(FALSE);
}


void Cyuv2bmpDlg::OnEnChangestartfrm()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
		CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_startfrm);
    CString str;
	pBoxOne->GetWindowText(str);
	startfrm=atoi(str);
	if((startfrm>=frmNUM)||(startfrm<0))
		{MessageBox("输入帧数有误！","WARNING",MB_OK);
	return;}
	UpdateData(FALSE);
}


void Cyuv2bmpDlg::OnEnChangeendfrm()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
		CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_endfrm);
    CString str;
	pBoxOne->GetWindowText(str);
	endfrm=atoi(str);
	 frmSize=frmwidth*frmheight*1.5;
	   frmNUM=len/frmSize;

	if((endfrm>=frmNUM)||(endfrm<startfrm))
		MessageBox("输入帧数有误！","WARNING",MB_OK);
	UpdateData(FALSE);
}


void Cyuv2bmpDlg::OnBnClickedallfrm()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
		if ( BST_CHECKED == IsDlgButtonChecked( IDC_allfrm ) )
			{
				startfrm=0;
				endfrm=frmNUM-1;
			  }
	UpdateData(FALSE);
}


void Cyuv2bmpDlg::OnEnChangefrmwidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
			CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_frmwidth);
    CString str;
	pBoxOne->GetWindowText(str);
	frmwidth=atoi(str);
	UpdateData(FALSE);
}


void Cyuv2bmpDlg::OnEnChangefrmheight()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
		UpdateData(TRUE);
			CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_frmheight);
    CString str;
	pBoxOne->GetWindowText(str);
	frmheight=atoi(str);
	UpdateData(FALSE);
	

}


void Cyuv2bmpDlg::OnBnClickedopenbmp()
{
	// TODO: 在此添加控件通知处理程序代码
		UpdateData(TRUE);
		
		char BASED_CODE szFilter[] = "BMP Files (*.bmp)|*.bmp||";
	CFileDialog dlg(false,"BMP",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(IDOK!=dlg.DoModal())
	{ 
		return; 
	}
    m_str1=dlg.GetPathName();
    m_str2=dlg.GetFileName();
	int pos = m_str1.Find(m_str2);
	path = m_str1.Left(pos);
	filename=dlg.GetFileTitle();
    	CEdit* pBoxOne;
	pBoxOne = (CEdit*) GetDlgItem(IDC_bmp_path);
	pBoxOne->SetWindowText(path);
	CEdit* pBoxTwo;
	pBoxTwo=(CEdit*) GetDlgItem(IDC_filename);
	pBoxTwo->SetWindowText(filename);
	UpdateData(FALSE);
}


void Cyuv2bmpDlg::OnBnClickedConvert()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	   frmSize=frmwidth*frmheight*1.5;
	   frmNUM=len/frmSize;
			if ( BST_CHECKED == IsDlgButtonChecked( IDC_allfrm ) )
			{
				startfrm=0;
				endfrm=frmNUM-1;
			  }

	pYUVData=new unsigned char *[frmNUM];
	CString *str1=new CString[endfrm-startfrm+1];
	CString string;
	for(int i=0;i<frmNUM;i++)
		pYUVData[i]=new unsigned char[frmSize];
	prgbData=new unsigned char *[frmNUM];
	for(int i=0;i<frmNUM;i++)
		prgbData[i]=new unsigned char[frmSize*2];
	for(int i=0;i<frmNUM;i++)
		for(int j=0;j<frmSize;j++)
			pYUVData[i][j]=pReadData[i*frmSize+j];
    ColorSpaceConversions convert;
	for(int i=startfrm;i<=endfrm;i++)
		convert.YV12_to_RGB24(pYUVData[i],pYUVData[i]+frmwidth*frmheight,pYUVData[i]+frmwidth*frmheight*5/4,prgbData[i],frmwidth,frmheight);
	int *NUM=new int[endfrm-startfrm+1];
	for(int i=0;i<endfrm-startfrm+1;i++)
	{NUM[i]=startfrm+i;
	int n=NUM[i];
	int m=0;
	while(n)
	{
		n/=10;
		m++;
	}
	str1[i].Format(_T("%.100d"),NUM[i]);
	if(m>namel)
	str1[i]=str1[i].Right(m);
	else
		str1[i]=str1[i].Right(namel);
	}
	for(int i=0;i<endfrm-startfrm+1;i++)
	{filePATH=path+filename+str1[i]+".bmp";
	Snapshot(prgbData[startfrm+i],frmwidth,frmheight,filePATH);}
	UpdateData(FALSE);
	MessageBox("完成","提示",MB_OK);
}
 void Cyuv2bmpDlg::Snapshot( BYTE * pData, int width, int height, const char * file_name )
 {
	 int size = width*height*3; // 每个像素点3个字节

// 位图第一部分，文件信息

BITMAPFILEHEADER bfh;
bfh.bfType = 0x4d42; 
bfh.bfSize = size+sizeof( BITMAPFILEHEADER )+sizeof( BITMAPINFOHEADER );
bfh.bfReserved1 = 0; // reserved 
bfh.bfReserved2 = 0; // reserved
bfh.bfOffBits = bfh.bfSize - size;
// 位图第二部分，数据信息
BITMAPINFOHEADER bih;
bih.biSize = sizeof(BITMAPINFOHEADER);
bih.biWidth = width;
bih.biHeight = height;
bih.biPlanes = 1;
bih.biBitCount = 24;
bih.biCompression = 0;
bih.biSizeImage = size;
bih.biXPelsPerMeter = 0;
bih.biYPelsPerMeter = 0;
bih.biClrUsed = 0;
bih.biClrImportant = 0;
FILE * fp = fopen( file_name, "wb" );
if( !fp ) return;
fwrite( &bfh, 1, sizeof(BITMAPFILEHEADER), fp );
fwrite( &bih, 1, sizeof(BITMAPINFOHEADER), fp );
fwrite( pData, 1, size, fp );
fclose( fp );
}



 void Cyuv2bmpDlg::OnEnChangebmppath()
 {
	 // TODO:  如果该控件是 RICHEDIT 控件，它将不
	 // 发送此通知，除非重写 CDialogEx::OnInitDialog()
	 // 函数并调用 CRichEditCtrl().SetEventMask()，
	 // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	 // TODO:  在此添加控件通知处理程序代码
 }


 void Cyuv2bmpDlg::OnEnChangenamelen()
 {
	 // TODO:  如果该控件是 RICHEDIT 控件，它将不
	 // 发送此通知，除非重写 CDialogEx::OnInitDialog()
	 // 函数并调用 CRichEditCtrl().SetEventMask()，
	 // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	 // TODO:  在此添加控件通知处理程序代码
	 UpdateData(TRUE);
	 		CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_namelen);
    CString str;
	pBoxOne->GetWindowText(str);
	namel=atoi(str);
	UpdateData(FALSE);
 }


 void Cyuv2bmpDlg::OnEnChangeyuvpath()
 {
	 // TODO:  如果该控件是 RICHEDIT 控件，它将不
	 // 发送此通知，除非重写 CDialogEx::OnInitDialog()
	 // 函数并调用 CRichEditCtrl().SetEventMask()，
	 // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	 // TODO:  在此添加控件通知处理程序代码
 }
