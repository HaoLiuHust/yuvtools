
// yuvPSNR.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CyuvPSNRApp:
// �йش����ʵ�֣������ yuvPSNR.cpp
//

class CyuvPSNRApp : public CWinApp
{
public:
	CyuvPSNRApp();

// ��д
public:
	virtual BOOL InitInstance();


// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CyuvPSNRApp theApp;