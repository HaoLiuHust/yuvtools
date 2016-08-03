
// yuvcutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "yuvcut.h"
#include "yuvcutDlg.h"
#include "afxdialogex.h"
#include "memory.h"

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


// CyuvcutDlg 对话框




CyuvcutDlg::CyuvcutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CyuvcutDlg::IDD, pParent)
	, picWidth(_T("176"))
	, picHeight(_T("144"))
	, startFrm(_T("0"))
	, endFrm(_T("0"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CyuvcutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Pic_W, picWidth);
	DDX_Text(pDX, IDC_picH, picHeight);
	DDX_Text(pDX, IDC_Start, startFrm);
	DDX_Text(pDX, IDC_End, endFrm);
}

BEGIN_MESSAGE_MAP(CyuvcutDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CyuvcutDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_File_Open, &CyuvcutDlg::OnBnClickedFileOpen)
	ON_EN_CHANGE(IDC_PATH, &CyuvcutDlg::OnEnChangePath)
	ON_EN_CHANGE(IDC_Pic_W, &CyuvcutDlg::OnEnChangePicW)
	ON_EN_CHANGE(IDC_picH, &CyuvcutDlg::OnEnChangepich)
	ON_BN_CLICKED(IDC_CUT, &CyuvcutDlg::OnBnClickedCut)
	ON_BN_CLICKED(IDC_BUTTON1, &CyuvcutDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_Start, &CyuvcutDlg::OnEnChangeStart)
	ON_EN_CHANGE(IDC_End, &CyuvcutDlg::OnEnChangeEnd)
	ON_BN_CLICKED(IDC_OUTPATH, &CyuvcutDlg::OnBnClickedOutpath)
	ON_EN_CHANGE(IDC_SAVEPATH, &CyuvcutDlg::OnEnChangeSavepath)
END_MESSAGE_MAP()


// CyuvcutDlg 消息处理程序

BOOL CyuvcutDlg::OnInitDialog()
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
	m_nWidth=176;
	m_nHeight=144;
	frameSIZE=176*144*1.5;
	startfrm=0;
	endfrm=0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CyuvcutDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CyuvcutDlg::OnPaint()
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
HCURSOR CyuvcutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CyuvcutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}




void CyuvcutDlg::OnBnClickedFileOpen()
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
	pBoxOne = (CEdit*) GetDlgItem(IDC_PATH);
	pBoxOne->SetWindowText( m_str );//m_str为文本框对应的CSTRING类型的变量
 if(!file.Open(m_str,CFile::modeReadWrite))
 {MessageBox("无法打开文件！","WARNING",MB_OK); 
 return;}
 len = file.GetLength();
  pReadData = new char[len]; 
    file.Read(pReadData,len); 
	file.Close();
UpdateData(FALSE);

}


void CyuvcutDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CyuvcutDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CyuvcutDlg::OnEnChangePicH()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CyuvcutDlg::OnBnClickeddisplay()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CyuvcutDlg::OnEnChangePicw()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CyuvcutDlg::OnEnChangeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CyuvcutDlg::OnEnChangePath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

}


void CyuvcutDlg::OnEnChangePicW()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
		m_nWidth=atoi(picWidth);
		UpdateData(FALSE);
	// TODO:  在此添加控件通知处理程序代码
}


void CyuvcutDlg::OnEnChangepich()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
		UpdateData(TRUE);
	m_nHeight=atoi(picHeight);
	UpdateData(FALSE);
	}


void CyuvcutDlg::OnBnClickedCut()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
		int length;
	int startadr=frameSIZE*startfrm;
	length=(endfrm-startfrm+1)*frameSIZE;
	char *pWriteData = new char[length];
	memcpy(pWriteData,pReadData+startadr,length);
	/*for(int i=0;i<length;i++)
	{
		int j=startadr;
		pWriteData[i]=pReadData[j];
		j++;
	}*/
	if(!file.Open(m_str1,CFile::modeWrite))
		{
		MessageBox("无法打开文件！","WARNING",MB_OK); 
		return;}
   file.Write(pWriteData,length);  
	file.Close();
	MessageBox("完成",NULL,MB_OK);
	UpdateData(FALSE);
}


void CyuvcutDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	frameSIZE=m_nHeight*m_nWidth*1.5;
	frameNUM=len/frameSIZE;
	CString str1;
str1.Format("%u",frameNUM);//无符号10进制显示，再将str传给MessageBox去显示
MessageBox(str1,"帧数",MB_OK);
}


void CyuvcutDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CyuvcutDlg::OnEnChangeStart()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	UpdateData(FALSE);
}


void CyuvcutDlg::OnEnChangeEnd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
		UpdateData(TRUE);
		frameSIZE=m_nHeight*m_nWidth*1.5;
	frameNUM=len/frameSIZE;
		CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_Start);
    CString str;
	pBoxOne->GetWindowText(str);
	startfrm=atoi(str);
	if((startfrm>=frameNUM)||(startfrm<0))
		{MessageBox("输入帧数有误！","WARNING",MB_OK);
	return;}
		CEdit* pBoxTwo;
   pBoxTwo = (CEdit*) GetDlgItem(IDC_End);
    CString strend;
	pBoxTwo->GetWindowText(strend);
	endfrm=atoi(strend);
	if((endfrm>=frameNUM)||(endfrm<startfrm))
		MessageBox("输入帧数有误！","WARNING",MB_OK);
	UpdateData(FALSE);
}


void CyuvcutDlg::OnBnClickedOutpath()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
		char BASED_CODE szFilter[] = "YUV Files (*.yuv)|*.yuv||";
	CFileDialog dlg(false,"YUV",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(IDOK!=dlg.DoModal())
	{
	 return;
	}
	m_str1=dlg.GetPathName();
  	CEdit* pBoxOne;
	pBoxOne = (CEdit*) GetDlgItem(IDC_SAVEPATH);
	pBoxOne->SetWindowText( m_str1 );//m_str为文本框对应的CSTRING类型的变量
	if(!file.Open(m_str1,CFile::modeCreate|CFile::modeWrite))
		{MessageBox("无法打开文件！","WARNING",MB_OK); 
		return;}
	file.Close();
	UpdateData(FALSE);
}


void CyuvcutDlg::OnEnChangeSavepath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
