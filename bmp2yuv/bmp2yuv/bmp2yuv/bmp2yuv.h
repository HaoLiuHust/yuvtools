
// bmp2yuv.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cbmp2yuvApp:
// �йش����ʵ�֣������ bmp2yuv.cpp
//

class Cbmp2yuvApp : public CWinApp
{
public:
	Cbmp2yuvApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cbmp2yuvApp theApp;