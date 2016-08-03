
// yuv2bmpDlg.cpp : ʵ���ļ�
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


// Cyuv2bmpDlg �Ի���




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


// Cyuv2bmpDlg ��Ϣ�������

BOOL Cyuv2bmpDlg::OnInitDialog()
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
	startfrm=0;
	endfrm=0;
	frmwidth=176;
	frmheight=144;
	namel=1;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cyuv2bmpDlg::OnPaint()
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
HCURSOR Cyuv2bmpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cyuv2bmpDlg::OnBnClickedopenyuv()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	pBoxOne->SetWindowText( m_str );//m_strΪ�ı����Ӧ��CSTRING���͵ı���
 if(!file.Open(m_str,CFile::modeReadWrite))
	 {
		MessageBox("�޷����ļ���","WARNING",MB_OK); 
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
		CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_startfrm);
    CString str;
	pBoxOne->GetWindowText(str);
	startfrm=atoi(str);
	if((startfrm>=frmNUM)||(startfrm<0))
		{MessageBox("����֡������","WARNING",MB_OK);
	return;}
	UpdateData(FALSE);
}


void Cyuv2bmpDlg::OnEnChangeendfrm()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
		CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_endfrm);
    CString str;
	pBoxOne->GetWindowText(str);
	endfrm=atoi(str);
	 frmSize=frmwidth*frmheight*1.5;
	   frmNUM=len/frmSize;

	if((endfrm>=frmNUM)||(endfrm<startfrm))
		MessageBox("����֡������","WARNING",MB_OK);
	UpdateData(FALSE);
}


void Cyuv2bmpDlg::OnBnClickedallfrm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	MessageBox("���","��ʾ",MB_OK);
}
 void Cyuv2bmpDlg::Snapshot( BYTE * pData, int width, int height, const char * file_name )
 {
	 int size = width*height*3; // ÿ�����ص�3���ֽ�

// λͼ��һ���֣��ļ���Ϣ

BITMAPFILEHEADER bfh;
bfh.bfType = 0x4d42; 
bfh.bfSize = size+sizeof( BITMAPFILEHEADER )+sizeof( BITMAPINFOHEADER );
bfh.bfReserved1 = 0; // reserved 
bfh.bfReserved2 = 0; // reserved
bfh.bfOffBits = bfh.bfSize - size;
// λͼ�ڶ����֣�������Ϣ
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
	 // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	 // ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	 // ���������� CRichEditCtrl().SetEventMask()��
	 // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	 // TODO:  �ڴ���ӿؼ�֪ͨ����������
 }


 void Cyuv2bmpDlg::OnEnChangenamelen()
 {
	 // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	 // ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	 // ���������� CRichEditCtrl().SetEventMask()��
	 // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	 // TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	 // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	 // ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	 // ���������� CRichEditCtrl().SetEventMask()��
	 // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	 // TODO:  �ڴ���ӿؼ�֪ͨ����������
 }
