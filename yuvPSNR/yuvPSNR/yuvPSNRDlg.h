
// yuvPSNRDlg.h : ͷ�ļ�
//

#pragma once


// CyuvPSNRDlg �Ի���
class CyuvPSNRDlg : public CDialogEx
{
// ����
public:
	CyuvPSNRDlg(CWnd* pParent = NULL);
	// ��׼���캯��
	int Pic_Width;
	int Pic_Height;
	CString m_str;
	CString m_str1;
	CString m_str2;
	CFile file;
	DWORD sourcelen;
	DWORD destlen;
	DWORD frameNUM;
	DWORD frameNUM1;
    DWORD frameSIZE;
	DWORD Pic_SIZE;
	DWORD startfrm;
	DWORD endfrm;
	DWORD CalNUM;
	double sum;
	unsigned char *pSourceData;
	char *pWriteData;
	unsigned char *pDestData;
	double MSE;
	double *PSNR;
	double APSNR;

// �Ի�������
	enum { IDD = IDD_YUVPSNR_DIALOG };
	void CalMSE();
	void CalPSNR();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
			// DDX/DDV ֧��


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
	afx_msg void OnBnClickedSourcepath();
	afx_msg void OnBnClickedSourcepath2();
	afx_msg void OnBnClickedDestpath();
	afx_msg void OnEnChangedest();
	afx_msg void OnEnChangeHeight();
	afx_msg void OnEnChangeendfrm();
	afx_msg void OnBnClickedSavepath();
	afx_msg void OnBnClickedCalpsnr();
	afx_msg void OnBnClickedpath();
	afx_msg void OnEnChangesave();
	afx_msg void OnEnChangestartfrm();

	;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangePsnr();
	afx_msg void OnEnChangeWidth();
	CString Pic_width;
	CString Pic_height;
	CString start_Frm;
	CString endFrm;
};
