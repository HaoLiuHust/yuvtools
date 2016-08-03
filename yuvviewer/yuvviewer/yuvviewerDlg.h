
// yuvviewerDlg.h : ͷ�ļ�
//
#include "stdafx.h"
#include "ChildWindow.h"

#pragma once


// CyuvviewerDlg �Ի���
class CyuvviewerDlg : public CDialogEx
{
// ����
public:
	CyuvviewerDlg(CWnd* pParent = NULL);	// ��׼���캯��
		BOOL m_bPlay;				//�Ƿ񲥷�
	int m_iCount;				//
	CWinThread* m_pWinThread;	//�߳�ָ��
	CFile *m_pFile[36];			//CFle���ָ������
	CChildWindow *m_pWnd[36];	//�Զ������
	HANDLE hPlayTemp;			//���
    float m_nZoom;
	UINT picsize;
	int Frmformat;
	int frmNUM;
	BOOL Color;
	CString inSeqName[36];
	CString inSeqence[36];
// �Ի�������
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
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧


// ʵ��
protected:
	HICON m_hIcon;
	void Enable(int nID);			// �ؼ�����
	void Disable(int nID);			// �ؼ�����
	BOOL Enabled(int nID);			//?�ؼ�״̬
	// ���ɵ���Ϣӳ�亯��
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
