
// yuvcutDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "yuvcut.h"
#include "yuvcutDlg.h"
#include "afxdialogex.h"
#include "memory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CyuvcutDlg �Ի���




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


// CyuvcutDlg ��Ϣ�������

BOOL CyuvcutDlg::OnInitDialog()
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
	m_nWidth=176;
	m_nHeight=144;
	frameSIZE=176*144*1.5;
	startfrm=0;
	endfrm=0;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CyuvcutDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
HCURSOR CyuvcutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CyuvcutDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}




void CyuvcutDlg::OnBnClickedFileOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	pBoxOne->SetWindowText( m_str );//m_strΪ�ı����Ӧ��CSTRING���͵ı���
 if(!file.Open(m_str,CFile::modeReadWrite))
 {MessageBox("�޷����ļ���","WARNING",MB_OK); 
 return;}
 len = file.GetLength();
  pReadData = new char[len]; 
    file.Read(pReadData,len); 
	file.Close();
UpdateData(FALSE);

}


void CyuvcutDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CyuvcutDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CyuvcutDlg::OnEnChangePicH()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CyuvcutDlg::OnBnClickeddisplay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CyuvcutDlg::OnEnChangePicw()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CyuvcutDlg::OnEnChangeEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CyuvcutDlg::OnEnChangePath()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}


void CyuvcutDlg::OnEnChangePicW()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(TRUE);
		m_nWidth=atoi(picWidth);
		UpdateData(FALSE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CyuvcutDlg::OnEnChangepich()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
		UpdateData(TRUE);
	m_nHeight=atoi(picHeight);
	UpdateData(FALSE);
	}


void CyuvcutDlg::OnBnClickedCut()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox("�޷����ļ���","WARNING",MB_OK); 
		return;}
   file.Write(pWriteData,length);  
	file.Close();
	MessageBox("���",NULL,MB_OK);
	UpdateData(FALSE);
}


void CyuvcutDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	frameSIZE=m_nHeight*m_nWidth*1.5;
	frameNUM=len/frameSIZE;
	CString str1;
str1.Format("%u",frameNUM);//�޷���10������ʾ���ٽ�str����MessageBoxȥ��ʾ
MessageBox(str1,"֡��",MB_OK);
}


void CyuvcutDlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CyuvcutDlg::OnEnChangeStart()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	
	UpdateData(FALSE);
}


void CyuvcutDlg::OnEnChangeEnd()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
		UpdateData(TRUE);
		frameSIZE=m_nHeight*m_nWidth*1.5;
	frameNUM=len/frameSIZE;
		CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_Start);
    CString str;
	pBoxOne->GetWindowText(str);
	startfrm=atoi(str);
	if((startfrm>=frameNUM)||(startfrm<0))
		{MessageBox("����֡������","WARNING",MB_OK);
	return;}
		CEdit* pBoxTwo;
   pBoxTwo = (CEdit*) GetDlgItem(IDC_End);
    CString strend;
	pBoxTwo->GetWindowText(strend);
	endfrm=atoi(strend);
	if((endfrm>=frameNUM)||(endfrm<startfrm))
		MessageBox("����֡������","WARNING",MB_OK);
	UpdateData(FALSE);
}


void CyuvcutDlg::OnBnClickedOutpath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	pBoxOne->SetWindowText( m_str1 );//m_strΪ�ı����Ӧ��CSTRING���͵ı���
	if(!file.Open(m_str1,CFile::modeCreate|CFile::modeWrite))
		{MessageBox("�޷����ļ���","WARNING",MB_OK); 
		return;}
	file.Close();
	UpdateData(FALSE);
}


void CyuvcutDlg::OnEnChangeSavepath()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
