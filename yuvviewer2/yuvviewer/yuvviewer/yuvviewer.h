
// yuvviewer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CyuvviewerApp:
// �йش����ʵ�֣������ yuvviewer.cpp
//

class CyuvviewerApp : public CWinApp
{
public:
	CyuvviewerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CyuvviewerApp theApp;