
// yuvviewerDlg.h : 头文件
//
#include "stdafx.h"

#pragma once


// CyuvviewerDlg 对话框
class CyuvviewerDlg : public CDialogEx
{
// 构造
public:
	CyuvviewerDlg(CWnd* pParent = NULL);	// 标准构造函数
int frmwidth;
	int frmheight;
	int frmsize;
	int count;
	int delaytime;
	int closed;
	int buffer;
	BOOL backorder;
	BOOL play;
	CFile file;
	CString path;
	CString fileTitle;
	unsigned char *pYUVData;
	unsigned char *pRGBData;
	unsigned char temp;
	int n;
	int Frmformat;
	int len;
	int frmNUM;
	int startfrm;
	int endfrm;
	int endNUM;
	int m_nZoom;
	

// 对话框数据
	enum { IDD = IDD_YUVVIEWER_DIALOG };
		CButton	m_buttonPrev5;
	CButton	m_buttonOrder;
	CButton	m_buttonNext5;
	CButton	m_buttonPrev;
	CButton	m_buttonPlay;
	CButton	m_buttonNext;
	CButton	m_buttonOpen;
	CButton m_buttongray;
	void yuv444_to_rgb24(unsigned char *y,unsigned char *u,unsigned char *v,unsigned char *rgb,int width,int height);
	void yuv422_to_rgb24(unsigned char *y,unsigned char *u,unsigned char *v,unsigned char *rgb,int width,int height);
	void yuy2_to_rgb24(unsigned char *pDstData,unsigned char *pSrcData,int width,int height);
	int displayfrm(int nFrame);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支


// 实现
protected:
	HICON m_hIcon;
	void Enable(int nID);			// 控件可用
	void Disable(int nID);			// 控件禁用
	BOOL Enabled(int nID);			//?控件状态
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSizecif();
	afx_msg void OnBnClickedSizeqcif();
	afx_msg void OnEnChangeFrmheight();
	afx_msg void OnEnChangeFrmwidth();
	afx_msg void OnBnClickedSizeother();
	afx_msg void OnCbnSelchangeFrmrate();
	afx_msg void OnBnClickedPlay();
	CString frmrate;
	CString startFrm;
	CString endFrm;
	afx_msg void OnBnClickedOpenfile();
	afx_msg void OnBnClickedBackorder();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedNext5();
	afx_msg void OnBnClickedPrevious();
	afx_msg void OnBnClickedPrevious5();
	afx_msg void OnBnClickedCloseall();
	afx_msg void OnBnClickedQuit();
	afx_msg void OnBnClickedReturn();
	CString playsize;
	afx_msg void OnCbnSelchangeplaysize();
	CString frmformat;
	CString frmNo;
	afx_msg void OnEnChangeEndfrm();
	afx_msg void OnEnChangeStartfrm();
};
