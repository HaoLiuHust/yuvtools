
// yuvcutDlg.h : 头文件
//

#pragma once


// CyuvcutDlg 对话框
class CyuvcutDlg : public CDialogEx
{
// 构造
public:
	CyuvcutDlg(CWnd* pParent = NULL);
	int		m_nHeight;
	int		m_nWidth;	
	CString m_str;
	CString m_str1;
	CFile file;
	DWORD len;
	DWORD frameNUM;
    DWORD frameSIZE;
	DWORD startfrm;
	DWORD endfrm;
	char *pReadData;
	char *pWriteData;

// 对话框数据
	enum { IDD = IDD_YUVCUT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnBnClickedFileOpen();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangePicH();
	afx_msg void OnBnClickeddisplay();
	afx_msg void OnEnChangePicw();
	afx_msg void OnEnChangeEdit();
	afx_msg void OnEnChangePath();
	afx_msg void OnEnChangePicW();
	afx_msg void OnEnChangepich();
	afx_msg void OnBnClickedCut();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeStart();
	afx_msg void OnEnChangeEnd();
	afx_msg void OnBnClickedOutpath();
	afx_msg void OnEnChangeSavepath();
	CString picWidth;
	CString picHeight;
	CString startFrm;
	CString endFrm;
};
