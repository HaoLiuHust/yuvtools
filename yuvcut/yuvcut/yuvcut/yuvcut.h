
// yuvcut.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CyuvcutApp:
// �йش����ʵ�֣������ yuvcut.cpp
//

class CyuvcutApp : public CWinApp
{
public:
	CyuvcutApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CyuvcutApp theApp;