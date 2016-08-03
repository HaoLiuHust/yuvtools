
// bmp2yuvDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bmp2yuv.h"
#include "bmp2yuvDlg.h"
#include "afxdialogex.h"
#include "Convert.h"
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


// Cbmp2yuvDlg �Ի���




Cbmp2yuvDlg::Cbmp2yuvDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cbmp2yuvDlg::IDD, pParent)
	, namele(_T("1"))
	, width(_T("176"))
	, height(_T("144"))
	, startFrm(_T("0"))
	, endFrm(_T("0"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cbmp2yuvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT6, namele);
	DDX_Text(pDX, IDC_picwidth, width);
	DDX_Text(pDX, IDC_picheight, height);
	DDX_Text(pDX, IDC_startfrm, startFrm);
	DDX_Text(pDX, IDC_endfrm, endFrm);
}

BEGIN_MESSAGE_MAP(Cbmp2yuvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_openbmp, &Cbmp2yuvDlg::OnBnClickedopenbmp)
	ON_EN_CHANGE(IDC_startfrm, &Cbmp2yuvDlg::OnEnChangestartfrm)
	ON_EN_CHANGE(IDC_endfrm, &Cbmp2yuvDlg::OnEnChangeendfrm)
	ON_BN_CLICKED(IDC_CHECK1, &Cbmp2yuvDlg::OnBnClickedCheck1)
	ON_EN_CHANGE(IDC_EDIT6, &Cbmp2yuvDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_picwidth, &Cbmp2yuvDlg::OnEnChangepicwidth)
	ON_EN_CHANGE(IDC_picheight, &Cbmp2yuvDlg::OnEnChangepicheight)
	ON_BN_CLICKED(IDC_savepath, &Cbmp2yuvDlg::OnBnClickedsavepath)
	ON_BN_CLICKED(IDC_convert, &Cbmp2yuvDlg::OnBnClickedconvert)
	ON_EN_CHANGE(IDC_yuvpath, &Cbmp2yuvDlg::OnEnChangeyuvpath)
	ON_EN_CHANGE(IDC_bmp_path, &Cbmp2yuvDlg::OnEnChangebmppath)
END_MESSAGE_MAP()


// Cbmp2yuvDlg ��Ϣ�������

BOOL Cbmp2yuvDlg::OnInitDialog()
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
	namel=1;
	frmwidth=176;
	frmheight=144;
	startfrm=0;
	endfrm=0;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cbmp2yuvDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cbmp2yuvDlg::OnPaint()
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
HCURSOR Cbmp2yuvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cbmp2yuvDlg::OnBnClickedopenbmp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	char BASED_CODE szFilter[] = "BMP Files (*.bmp)|*.bmp||";
	CFileDialog dlg(true,"BMP",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
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


void Cbmp2yuvDlg::OnEnChangestartfrm()
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
	if(startfrm>=NUM)
		{MessageBox("����֡������","WARNING",MB_OK);
	return;}
	UpdateData(FALSE);
}


void Cbmp2yuvDlg::OnEnChangeendfrm()
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
	if((endfrm>=NUM)||(endfrm<startfrm))
		{MessageBox("����֡������","WARNING",MB_OK);
	return;}
	UpdateData(FALSE);
}


void Cbmp2yuvDlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
		if ( BST_CHECKED == IsDlgButtonChecked( IDC_CHECK1 ) )
      {
          startfrm=0;
		  endfrm=NUM-1;
      }
    UpdateData(FALSE);
}


void Cbmp2yuvDlg::OnEnChangeEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	 UpdateData(TRUE);
	 CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_EDIT6);
    CString str;
	pBoxOne->GetWindowText(str);
	namel=atoi(str);
	 houzui=filename.Right(namel);
	int pos=filename.Find(houzui);
	 filename1=filename.Left(pos);
	UpdateData(FALSE);
	FileSearch(path);
	bmppath=new CString[NUM];
	for(int i=0;i<NUM;i++)
		bmppath[i]=m_ff.Mid(plength*i,plength);
}


void Cbmp2yuvDlg::OnEnChangepicwidth()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
		UpdateData(TRUE);
			CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_picwidth);
    CString str;
	pBoxOne->GetWindowText(str);
	frmwidth=atoi(str);
	UpdateData(FALSE);
}


void Cbmp2yuvDlg::OnEnChangepicheight()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
			UpdateData(TRUE);
			CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_picheight);
    CString str;
	pBoxOne->GetWindowText(str);
	frmheight=atoi(str);
	UpdateData(FALSE);
}

/*unsigned char *Cbmp2yuvDlg::Readbmp(unsigned char *pData,CString fpath)
{
    bool openfile=file.Open(fpath,CFile::modeRead);
	if(!openfile)
		return 0;
	file.Seek(54,CFile::begin);
	int len=frmwidth*frmheight*3;
	pData=new unsigned char[NUM];
	file.Read(pData,len);
	return pData;
}*/

void Cbmp2yuvDlg::FileSearch(CString root)
{
	CFileFind ff;
	CString FilePath;
  root+=filename1;
   plength=m_str1.GetLength();
 for(int i=0;i<namel;i++)
	 root+="*";
root+=".bmp";
 BOOL res=ff.FindFile(root);
 while (res)
 {
 res=ff.FindNextFile();
 FilePath=ff.GetFilePath();
/* if (ff.IsDirectory() && !ff.IsDots())// �ҵ������ļ���
 {
 FileSearch(FilePath);// �ݹ�
 }*/
 if (!ff.IsDirectory() && !ff.IsDots()&&(FilePath.GetLength()==plength))// �ҵ������ļ�
 {
 m_ff+=FilePath;
 }
 }
 int length=m_ff.GetLength();
 NUM=length/plength;
}



void Cbmp2yuvDlg::OnBnClickedsavepath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		UpdateData(TRUE);
		char BASED_CODE szFilter[] = "YUV Files (*.yuv)|*.yuv||";
	CFileDialog dlg(false,"YUV",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(IDOK!=dlg.DoModal())
	{
		return;
	}
	 m_str=dlg.GetPathName();
  	CEdit* pBoxOne;
	pBoxOne = (CEdit*) GetDlgItem(IDC_yuvpath);
	pBoxOne->SetWindowText( m_str );//m_strΪ�ı����Ӧ��CSTRING���͵ı���
}


void Cbmp2yuvDlg::OnBnClickedconvert()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	ColorSpaceConversions convert;
	prgbData=new unsigned char *[NUM];
	pyuvData=new unsigned char *[NUM];
	int frmsize=frmwidth*frmheight*1.5;
	for(int i=0;i<NUM;i++)
	{prgbData[i]=new unsigned char [frmwidth*frmheight*3];
	 pyuvData[i]=new unsigned char [frmsize];
	 file.Open(bmppath[i],CFile::modeRead);
	 file.Seek(54,CFile::begin);
	 file.Read(prgbData[i],frmwidth*frmheight*3);
	 file.Close();
	 /*for(int j=0;j<frmsize*2-2;j++)
	 {unsigned char temp;
	  temp=prgbData[i][j];
	  prgbData[i][j]=prgbData[i][j+2];
	  prgbData[i][j+2]=temp;
	 }*/
	convert.RGB24_to_YV12(prgbData[i],pyuvData[i],frmwidth,frmheight);
	 
	}
	pyuvsave= new unsigned char[frmsize*(endfrm-startfrm+1)];
	for(int i=startfrm;i<=endfrm;i++)
		for(int j=0;j<frmsize;j++)
		pyuvsave[(i-startfrm)*frmsize+j]=pyuvData[i][j];
	for(int i=startfrm;i<=endfrm;i++)
	{   int uvsize=frmwidth*frmheight/4;
		unsigned char *temp=new unsigned char [uvsize];
		for(int j=0;j<uvsize;j++)
		{
			temp[j]=pyuvsave[i*frmsize+frmwidth*frmheight+j];
			pyuvsave[i*frmsize+frmwidth*frmheight+j]=pyuvsave[i*frmsize+frmwidth*frmheight+uvsize+j];
			pyuvsave[i*frmsize+frmwidth*frmheight+uvsize+j]=temp[j];
		}
	}
	if(!file.Open(m_str,CFile::modeCreate|CFile::modeWrite))
		 {
		MessageBox("�޷����ļ���","WARNING",MB_OK); 
		return;}
	file.Write(pyuvsave,frmsize*(endfrm-startfrm+1));
	file.Close();
	MessageBox("���",NULL,MB_OK);
	UpdateData(FALSE);
}


void Cbmp2yuvDlg::OnEnChangeyuvpath()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void Cbmp2yuvDlg::OnEnChangebmppath()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
