
// yuvPSNRDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "yuvPSNR.h"
#include "yuvPSNRDlg.h"
#include "afxdialogex.h"
#include  "math.h"
#include "string.h"

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


// CyuvPSNRDlg 对话框




CyuvPSNRDlg::CyuvPSNRDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CyuvPSNRDlg::IDD, pParent)
	, Pic_width(_T("176"))
	, Pic_height(_T("144"))
	, start_Frm(_T("0"))
	, endFrm(_T("0"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CyuvPSNRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Width, Pic_width);
	DDX_Text(pDX, IDC_Height, Pic_height);
	DDX_Text(pDX, IDC_startfrm, start_Frm);
	DDX_Text(pDX, IDC_endfrm, endFrm);
}

BEGIN_MESSAGE_MAP(CyuvPSNRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Sourcepath, &CyuvPSNRDlg::OnBnClickedSourcepath)
	ON_BN_CLICKED(IDC_Destpath, &CyuvPSNRDlg::OnBnClickedDestpath)
	ON_EN_CHANGE(IDC_dest, &CyuvPSNRDlg::OnEnChangedest)
	ON_EN_CHANGE(IDC_Height, &CyuvPSNRDlg::OnEnChangeHeight)
	ON_EN_CHANGE(IDC_endfrm, &CyuvPSNRDlg::OnEnChangeendfrm)
	ON_BN_CLICKED(IDC_CalPSNR, &CyuvPSNRDlg::OnBnClickedCalpsnr)
	ON_BN_CLICKED(IDC_path, &CyuvPSNRDlg::OnBnClickedpath)
	ON_EN_CHANGE(IDC_save, &CyuvPSNRDlg::OnEnChangesave)
	ON_EN_CHANGE(IDC_startfrm, &CyuvPSNRDlg::OnEnChangestartfrm)
	ON_EN_CHANGE(IDC_EDIT1, &CyuvPSNRDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_PSNR, &CyuvPSNRDlg::OnEnChangePsnr)
	ON_EN_CHANGE(IDC_Width, &CyuvPSNRDlg::OnEnChangeWidth)
END_MESSAGE_MAP()


// CyuvPSNRDlg 消息处理程序

BOOL CyuvPSNRDlg::OnInitDialog()
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
	Pic_Width=176;
	Pic_Height=144;
	startfrm=0;
	endfrm=0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CyuvPSNRDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CyuvPSNRDlg::OnPaint()
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
HCURSOR CyuvPSNRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CyuvPSNRDlg::OnBnClickedSourcepath()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	char BASED_CODE szFilter[] = "YUV Files (*.yuv)|*.yuv||";
CFileDialog dlg(true,"YUV",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
if(IDOK!=dlg.DoModal())
 {
 return;
 }
 m_str=dlg.GetPathName();
  	CEdit* pBoxOne;
	pBoxOne = (CEdit*) GetDlgItem(IDC_source);
	pBoxOne->SetWindowText( m_str );//m_str为文本框对应的CSTRING类型的变量
 if(!file.Open(m_str,CFile::modeReadWrite))
 {MessageBox("无法打开文件！","WARNING",MB_OK); 
 return;}
 sourcelen = file.GetLength();
  pSourceData = new unsigned char[sourcelen]; 
    file.Read(pSourceData,sourcelen); 
	file.Close();
UpdateData(FALSE);
}

void CyuvPSNRDlg::OnBnClickedDestpath()
{
	// TODO: 在此添加控件通知处理程序代码
		UpdateData();
	char BASED_CODE szFilter[] = "YUV Files (*.yuv)|*.yuv||";
CFileDialog dlg(true,"YUV",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
if(IDOK!=dlg.DoModal())
 {
	return;
 }
	m_str1=dlg.GetPathName();
  	CEdit* pBoxOne;
	pBoxOne = (CEdit*) GetDlgItem(IDC_dest);
	pBoxOne->SetWindowText( m_str1 );//m_str为文本框对应的CSTRING类型的变量
	if(!file.Open(m_str1,CFile::modeReadWrite))
	{MessageBox("无法打开文件！","WARNING",MB_OK); 
 return;}
	destlen = file.GetLength();
	frameSIZE=Pic_Width*Pic_Height*1.5;
	frameNUM=sourcelen/frameSIZE;
	frameNUM1=destlen/frameSIZE;
	 pDestData = new unsigned char[destlen]; 
    file.Read(pDestData,destlen); 
	file.Close();
	UpdateData(FALSE);
}


void CyuvPSNRDlg::OnEnChangedest()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CyuvPSNRDlg::OnEnChangeHeight()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
			UpdateData(TRUE);
	CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_Width);
    CString str;
	pBoxOne->GetWindowText(str);
	Pic_Width=atoi(str);
	CEdit* pBoxTwo;
	pBoxTwo =(CEdit*) GetDlgItem(IDC_Height);
	CString str1;
	pBoxTwo->GetWindowText(str1);
	Pic_Height=atoi(str1);

	UpdateData(FALSE);
}


void CyuvPSNRDlg::OnEnChangeendfrm()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
			UpdateData(TRUE);
	CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_startfrm);
    CString str;
	pBoxOne->GetWindowText(str);
	startfrm=atoi(str);
	CEdit* pBoxTwo;
	pBoxTwo =(CEdit*) GetDlgItem(IDC_endfrm);
	CString str1;
	pBoxTwo->GetWindowText(str1);
	endfrm=atoi(str1);
	frameSIZE=Pic_Width*Pic_Height*1.5;
	frameNUM=sourcelen/frameSIZE;
	frameNUM1=destlen/frameSIZE;
	if((startfrm>endfrm)||((startfrm>=frameNUM)||startfrm>=frameNUM1))
		{MessageBox("输入帧数有误！","WARNING",MB_OK);
		return;}
	if((endfrm>=frameNUM)||(endfrm>=frameNUM1))

		{MessageBox("输入帧数有误！","WARNING",MB_OK);
		return;}
    /*DWORD sourcelenY=Pic_Width*Pic_Height*frameNUM;
	DWORD destlenY=Pic_Width*Pic_Height*frameNUM1;
	pSourceDataY=new char[sourcelen];
	pDestDataY=new char[destlen];
	DWORD k=0;
	DWORD h=0;
	Pic_SIZE=Pic_Width*Pic_Height;
		/*for(DWORD i=0;i<sourcelen;i+=frameSIZE)
		{memcpy(pSourceDataY+k,pSourceData+i,Pic_SIZE);
						k+=frameSIZE;
	    };
file.Open(_T("xxx1.yuv"),CFile::modeReadWrite|CFile::modeCreate);
file.Write(pSourceDataY,sourcelenY);
file.Close();
    for(DWORD j=0;j<destlen;j+=frameSIZE)
			{memcpy(pDestDataY+h,pDestData+j,Pic_SIZE);
			h+=frameSIZE;
	    };
	/*file.Open(_T("xxx2.yuv"),CFile::modeReadWrite|CFile::modeCreate);
file.Write(pSourceDataY,sourcelen);
file.Close();*/
	UpdateData(FALSE);
	// TODO:  在此添加控件通知处理程序代码
}

void CyuvPSNRDlg::OnBnClickedCalpsnr()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CyuvPSNRDlg::CalPSNR();
	CString str1,str3,str5;
	CString str2="平均PSNR:";
	str1.Format(_T("%lf"),APSNR);
	CString *str4=new CString[CalNUM];
	CString *str6=new CString[CalNUM];
	DWORD frameOrd=startfrm;
	for(DWORD i=0;i<CalNUM;i++)
	{
		str4[i].Format(_T("%lf"),PSNR[i]);
		str6[i].Format(_T("%u"),frameOrd);
		frameOrd++;
		str5+=("第"+str6[i]+"帧PSNR："+str4[i]+"\r\n");
	}
    str3="SourcePath:"+m_str+"\r\n"+"DestinationPath:"+m_str1+"\r\n"+str5+str2+str1+"db";
	CEdit* pBoxOne;
	pBoxOne = (CEdit*) GetDlgItem(IDC_PSNR);
	pBoxOne->SetWindowText( str1 );
	if(!file.Open(m_str2,CFile::modeReadWrite))
		{MessageBox("无法打开文件！","WARNING",MB_OK); 
		return;}
	file.Write(str3,strlen(str3));
	file.Close();
	MessageBox("完成","完成",MB_OK);
	UpdateData(FALSE);
}


void CyuvPSNRDlg::OnBnClickedpath()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	char BASED_CODE szFilter[] = "TXT Files (*.txt)|*.txt||";
	CFileDialog dlg(false,"YUV",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(IDOK!=dlg.DoModal())
	{
		 return;
	}
	m_str2=dlg.GetPathName();
  	CEdit* pBoxOne;
	pBoxOne = (CEdit*) GetDlgItem(IDC_save);
	pBoxOne->SetWindowText( m_str2 );//m_str为文本框对应的CSTRING类型的变量
	if(!file.Open(m_str2,CFile::modeReadWrite|CFile::modeCreate))
	{MessageBox("无法打开文件！","WARNING",MB_OK); 
	return;}
	file.Close();
	UpdateData(FALSE);
}


void CyuvPSNRDlg::OnEnChangesave()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CyuvPSNRDlg::OnEnChangestartfrm()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

}

void CyuvPSNRDlg::CalPSNR()
{
	DWORD Pic_SIZEY=Pic_Height*Pic_Width;
    CalNUM=endfrm-startfrm+1;
	PSNR=new double[CalNUM];
	MSE=0;
	APSNR=0;
	sum=0;
	DWORD k=0;
	int temp;
	for(DWORD j=startfrm;j<=endfrm;j++)
	  {
	    for(DWORD i=0;i<Pic_SIZEY;i++)
		{
			temp = abs(pSourceData[i+j*frameSIZE]-pDestData[i+j*frameSIZE]);
			/*if (temp >=4) 
				printf("bigger\n");*/
			sum+= temp *temp;//(pSourceData[i+j*frameSIZE]-pDestData[i+j*frameSIZE])*(pSourceData[i+j*frameSIZE]-pDestData[i+j*frameSIZE]);
		}
	     MSE=sum/Pic_SIZEY;
		 PSNR[k]=10*log10(((pow((double)2,8)-1)*(pow((double)2,8)-1))/MSE);
		 APSNR+=PSNR[k];
		 k++;
		 sum=0;
	  }
	APSNR/=CalNUM;
  
}



void CyuvPSNRDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CyuvPSNRDlg::OnEnChangePsnr()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CyuvPSNRDlg::OnEnChangeWidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
