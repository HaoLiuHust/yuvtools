
// bmp2yuvDlg.h : ͷ�ļ�
//

#pragma once


// Cbmp2yuvDlg �Ի���
class Cbmp2yuvDlg : public CDialogEx
{
// ����
public:
	Cbmp2yuvDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CString m_str;
	CString m_str1;
	CString m_str2;
	CString path;
	CString filename;
	unsigned char **pyuvData;
	unsigned char **prgbData;
	unsigned char *pyuvsave;
	int startfrm;
	int endfrm;
	int namel;
	int frmwidth;
	int frmheight;
	int MAXNUM;
	int NUM;
	int plength;
	CFile file;
	CString m_ff;
	CString *bmppath;
	 CString filename1;
 CString houzui;

// �Ի�������
	enum { IDD = IDD_BMP2YUV_DIALOG };
	void FileSearch(CString root);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedopenbmp();
	afx_msg void OnEnChangestartfrm();
	afx_msg void OnEnChangeendfrm();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangepicwidth();
	afx_msg void OnEnChangepicheight();
	afx_msg void OnBnClickedopensave();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedsavepath();
	afx_msg void OnBnClickedconvert();
	afx_msg void OnEnChangeyuvpath();
	CString namele;
	CString width;
	CString height;
	CString startFrm;
	CString endFrm;
	afx_msg void OnEnChangebmppath();
};
