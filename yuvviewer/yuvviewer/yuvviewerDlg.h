
// yuvviewerDlg.h : 头文件
//
#include "stdafx.h"
#include "ChildWindow.h"

#pragma once


// CyuvviewerDlg 对话框
class CyuvviewerDlg : public CDialogEx
{
// 构造
public:
	CyuvviewerDlg(CWnd* pParent = NULL);	// 标准构造函数
		BOOL m_bPlay;				//是否播放
	int m_iCount;				//
	CWinThread* m_pWinThread;	//线程指针
	CFile *m_pFile[36];			//CFle类的指针数组
	CChildWindow *m_pWnd[36];	//自定义的类
	HANDLE hPlayTemp;			//句柄
    float m_nZoom;
	UINT picsize;
	int Frmformat;
	int frmNUM;
	BOOL Color;
	CString inSeqName[36];
	CString inSeqence[36];
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
	afx_msg void OnBnClickedSizeother();
	afx_msg void OnCbnSelchangeFrmrate();
	afx_msg void OnBnClickedPlay();
	int m_nWidth;
	int m_nHeight;
	CString frmrate;
	int startfrm;
	int endfrm;
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
	afx_msg void OnCbnSelchangefrmformat();
	CString frmformat;
	afx_msg void OnBnClickedshowgray();
	afx_msg void OnEnChangeFrmwidth();
	afx_msg void OnEnChangeStartfrm();
	afx_msg void OnEnChangeEndfrm();
};
