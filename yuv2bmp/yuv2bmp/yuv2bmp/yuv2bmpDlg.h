
// yuv2bmpDlg.h : ͷ�ļ�
//

#pragma once


// Cyuv2bmpDlg �Ի���
class Cyuv2bmpDlg : public CDialogEx
{
// ����
public:
	Cyuv2bmpDlg(CWnd* pParent = NULL);	// ��׼���캯��
	unsigned char **pYUVData;
	unsigned char *pReadData;
	unsigned char **prgbData;
	CString m_str;
	CFile file;
	DWORD len;
	int frmwidth;
	int frmheight;
	int frmNUM;
	int frmSize;
	int startfrm;
	int endfrm;
	int namel;
	CString m_fileName;
	CString m_str1;
	CString m_str2;
	CString path;
	CString filename;
	CString filePATH;

// �Ի�������
	enum { IDD = IDD_YUV2BMP_DIALOG };
	void Snapshot( BYTE * pData, int width, int height, const char * file_name );
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
	afx_msg void OnBnClickedopenyuv();
	afx_msg void OnEnChangestartfrm();
	afx_msg void OnEnChangeendfrm();
	afx_msg void OnBnClickedallfrm();
	afx_msg void OnEnChangefrmwidth();
	afx_msg void OnEnChangefrmheight();
	afx_msg void OnBnClickedopenbmp();
	afx_msg void OnBnClickedConvert();
	afx_msg void OnEnChangebmppath();
	afx_msg void OnEnChangenamelen();
	afx_msg void OnEnChangeyuvpath();
	CString startFrm;
	CString endFrm;
	CString width;
	CString height;
	CString namele;
};
