
// yuv2bmp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cyuv2bmpApp:
// �йش����ʵ�֣������ yuv2bmp.cpp
//

class Cyuv2bmpApp : public CWinApp
{
public:
	Cyuv2bmpApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cyuv2bmpApp theApp;