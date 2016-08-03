/************************************************************************
 *
 *  Ye-Kui Wang       wyk@ieee.org
 *  Juan-Juan Jiang   juanjuan_j@hotmail.com
 *  
 *  March 14, 2002
 *
 ************************************************************************/

/*
 * Disclaimer of Warranty
 *
 * These software programs are available to the user without any
 * license fee or royalty on an "as is" basis.  The developers disclaim 
 * any and all warranties, whether express, implied, or statuary, including 
 * any implied warranties or merchantability or of fitness for a particular 
 * purpose.  In no event shall the copyright-holder be liable for any incidental,
 * punitive, or consequential damages of any kind whatsoever arising from 
 * the use of these programs.
 *
 * This disclaimer of warranty extends to the user of these programs
 * and user's customers, employees, agents, transferees, successors,
 * and assigns.
 *
 * The developers does not represent or warrant that the programs furnished 
 * hereunder are free of infringement of any third-party patents.
 *
 * */


// ChildWindow.cpp : implementation file
//

#include "stdafx.h"
#include "yuvviewer.h"
#include "ChildWindow.h"
#include "yuvviewerDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildWindow

IMPLEMENT_DYNCREATE(CChildWindow, CFrameWnd)

CChildWindow::CChildWindow()
{
}
CChildWindow::~CChildWindow()	//����
{
	GlobalUnlock(hloc);
	GlobalFree(hloc);  
	
	free(RGBbuf);
	free(Y);	
	free(Cb);
	free(Cr);
}

CChildWindow::CChildWindow( CFrameWnd *pParentWnd,int Width,int Height, BOOL bColor)
{    
	iWidth=Width;iHeight=Height;bColorImage=bColor;

	m_iCount = ((CyuvviewerDlg *)pParentWnd)->m_iCount;
	inSeqName = ((CyuvviewerDlg *)pParentWnd)->inSeqName[m_iCount];

	/* �Ӹ����ڣ�Ҳ�������Ի���ȡ�����ű��� */
    if(((CyuvviewerDlg *)pParentWnd)->m_nZoom ==0.25)
		m_nzoom=0.25;
	else if(((CyuvviewerDlg *)pParentWnd)->m_nZoom ==0.5)
		m_nzoom=0.5;
	else if(((CyuvviewerDlg *)pParentWnd)->m_nZoom ==1)
		m_nzoom = 1;
	else if(((CyuvviewerDlg *)pParentWnd)->m_nZoom == 2)
		m_nzoom = 2;
	else if(((CyuvviewerDlg *)pParentWnd)->m_nZoom == 4)
		m_nzoom=4;
	
	nPicShowOrder=0;
	buf=1;
	/* ��̬�����Ŀ��ڴ棬���Y��Cb��Crֵ�Լ�ת�����RGB */
	buf=((CyuvviewerDlg *)pParentWnd)->Frmformat;
	if(buf==3)
	{
		if (NULL== (YUY2 = (unsigned char *)malloc(iWidth*iHeight*2) ) ) //��̬�����ڴ� (���Y����)
	{//Malloc ��ϵͳ�������ָ��size���ֽڵ��ڴ�ռ䡣���������� void* ���͡�void* ��ʾδȷ�����͵�ָ�롣C,C++�涨��void* ���Ϳ���ǿ��ת��Ϊ�κ��������͵�ָ�롣����ֵ���������ɹ��򷵻�ָ�򱻷����ڴ��ָ�룬���򷵻ؿ�ָ��NULL�����ڴ治��ʹ��ʱ��Ӧʹ��free()�������ڴ���ͷš� 
		AfxMessageBox("Couldn't allocate memory for RGBbuf\n");
		return;
	}
		
		if (NULL== (Y1 = (unsigned char *)malloc(iWidth*iHeight) ) ) //��̬�����ڴ� (���Y����)
	{//Malloc ��ϵͳ�������ָ��size���ֽڵ��ڴ�ռ䡣���������� void* ���͡�void* ��ʾδȷ�����͵�ָ�롣C,C++�涨��void* ���Ϳ���ǿ��ת��Ϊ�κ��������͵�ָ�롣����ֵ���������ɹ��򷵻�ָ�򱻷����ڴ��ָ�룬���򷵻ؿ�ָ��NULL�����ڴ治��ʹ��ʱ��Ӧʹ��free()�������ڴ���ͷš� 
		AfxMessageBox("Couldn't allocate memory for RGBbuf\n");
		return;
		}
	}
	else
{if (NULL== (Y = (unsigned char *)malloc(iWidth*iHeight) ) ) //��̬�����ڴ� (���Y����)
	{//Malloc ��ϵͳ�������ָ��size���ֽڵ��ڴ�ռ䡣���������� void* ���͡�void* ��ʾδȷ�����͵�ָ�롣C,C++�涨��void* ���Ϳ���ǿ��ת��Ϊ�κ��������͵�ָ�롣����ֵ���������ɹ��򷵻�ָ�򱻷����ڴ��ָ�룬���򷵻ؿ�ָ��NULL�����ڴ治��ʹ��ʱ��Ӧʹ��free()�������ڴ���ͷš� 
		AfxMessageBox("Couldn't allocate memory for RGBbuf\n");
		return;
	}
	if (NULL== (Cb = (unsigned char *)malloc(iWidth*iHeight/4*buf) ) ) //��̬�����ڴ� (���Cbɫ��)
	{
		AfxMessageBox("Couldn't allocate memory for RGBbuf\n");
		return;
	}
	if (NULL== (Cr = (unsigned char *)malloc(iWidth*iHeight/4*buf) ) ) //��̬�����ڴ� (���Crɫ��)
	{
		AfxMessageBox("Couldn't allocate memory for RGBbuf\n");
		return;
	}
	}
	/*else if(buf==4)
	{if (NULL== (YUV = (unsigned char *)malloc(iWidth*iHeight*3) ) ) //��̬�����ڴ� (���Crɫ��)
	{
		AfxMessageBox("Couldn't allocate memory for RGBbuf\n");
		return;
	}
	}*/
	if (NULL== (RGBbuf = (unsigned char *)malloc(iWidth*iHeight*3) ) ) 
	{
		AfxMessageBox("Couldn't allocate memory for RGBbuf\n");
		return;
	}
	
	DWORD AttrStyle;
    
	hloc = GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE,
   		sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 256));
	BmpInfo = (LPBITMAPINFO) GlobalLock(hloc);

	
	AttrStyle = //WS_OVERLAPPEDWINDOW;
		WS_OVERLAPPED|WS_CAPTION|WS_THICKFRAME|WS_MAXIMIZEBOX|WS_MINIMIZEBOX;
    Create(NULL,NULL,AttrStyle,rectDefault,pParentWnd);
}

void CChildWindow::ShowGrayImage(CDC *pDC,BYTE *lpImage)
{
	int i;         
	int nNum1,nNum2;
	HANDLE hMem;
	BYTE *lpBuf;

	BmpInfo->bmiHeader.biBitCount = 8;

    hMem=GlobalAlloc(GHND,iWidth*iHeight);
	lpBuf=(BYTE *)GlobalLock(hMem);
	
    //�����õ�ͼ����� 
	//Make the inverse image normal
    for(i=0;i<iHeight;i++){
		nNum1=(iHeight-i-1)*iWidth;
		nNum2=i*iWidth;
		memcpy(lpBuf+nNum1,lpImage+nNum2,iWidth);
	}

	pDC->SetStretchBltMode(STRETCH_DELETESCANS);
	StretchDIBits(pDC->m_hDC,0,0,iWidth,iHeight,
							 0,0,iWidth,iHeight,
					  lpBuf,BmpInfo, DIB_RGB_COLORS,SRCCOPY);  

	GlobalUnlock(hMem);
	GlobalFree(hMem);
}

void CChildWindow::ShowImage(CDC *pDC,BYTE *lpImage)
{
	BmpInfo->bmiHeader.biBitCount = 24;

	/* ����ָ���豸�����е�λͼ����ģʽ int CDC::SetStretchBltMode(int nStretchMode); API��һ��ͬ���ģ�����������˾��*/
	pDC->SetStretchBltMode(STRETCH_DELETESCANS);

	if(buf==1||buf==2)
	StretchDIBits(pDC->m_hDC,0,0,m_nzoom*iWidth,m_nzoom*iHeight,
							 0,0,iWidth,iHeight,
					  lpImage,BmpInfo, DIB_RGB_COLORS,SRCCOPY);  

	else if(buf==4||buf==3)
		{StretchDIBits(pDC->m_hDC	/* hdc��ָ��Ŀ���豸�����ľ�� */
						, 0		/* XDest��ָ��Ŀ��������Ͻ�λ�õ�X�����꣬���߼���λ����ʾ���� */
						, 0		/* YDest��ָ��Ŀ��������Ͻǵ�Y�����꣬���߼���λ��ʾ���� */
						, m_nzoom*iWidth	/* ָ��Ŀ����εĿ��(ʵ�ʵĿ�*���ű���) */
						, m_nzoom*iHeight	/* ָ��Ŀ����εĸ߶�(ʵ�ʵĸ�*���ű���) */
						, 0		/* XSrc��ָ��DIB��Դ���Σ����Ͻǣ���X�����꣬���������ص��ʾ */
						, iHeight		/* YSrc��ָ��DIB��Դ���Σ����Ͻǣ���Y�����꣬���������ص��ʾ */
						, iWidth	/* �����ص�ָ��DIB��Դ���εĿ�� */
						, -iHeight	/* �����ص�ָ��DIB��Դ���εĸ߶� */
						, lpImage	/* ָ��DIBλ��ָ�룬��Щλ��ֵ���ֽ���������洢 */
						, BmpInfo	/* ָ��BITMAPINFO�ṹ��ָ�룬�ýṹ�����й�DIB�������Ϣ */
						, DIB_RGB_COLORS	
						, SRCCOPY	
						);};
}

void CChildWindow::CenterWindow(int width,int height)
{
    RECT rc;
    RECT rw;
    
    int cyBorder, cxBorder;
    int cyTotal,cxTotal;
    int cyMenuAndCaption;

    int cw, ch;

  	RECT r;
	  int nCx=GetSystemMetrics(SM_CXSCREEN),nCy=GetSystemMetrics(SM_CYSCREEN);

    cyBorder = GetSystemMetrics(SM_CYBORDER);
    cxBorder = GetSystemMetrics(SM_CXBORDER);

    // Figure out the height of the menu, toolbar, and caption
    GetWindowRect(&rw);
    GetClientRect(&rc);

    ClientToScreen ((LPPOINT) &rc);
    cyMenuAndCaption = (rc.top - rw.top) ;
  
    cyTotal =height  +
              cyMenuAndCaption +
              cyBorder * 2 ;
    cxTotal=width+cxBorder * 2;            

	r.left=(nCx-cxTotal)/2;r.top=(nCy-cyTotal)/2;
	r.right=(nCx+cxTotal)/2;r.bottom=(nCy+cyTotal)/2;
	
	MoveWindow(&r);//,FALSE);

  GetClientRect(&rc);
  while( (rc.right-rc.left != width-1) || (rc.bottom-rc.top != height-1) )
  {
  
    if(rc.right-rc.left < width-1)
      cxTotal ++;
    else if(rc.right-rc.left > width-1)
      cxTotal --;
    if(rc.bottom-rc.top < height-1)
      cyTotal ++;
    else if(rc.bottom-rc.top > height-1)
      cyTotal --;

	  r.left=(nCx-cxTotal)/2;r.top=(nCy-cyTotal)/2;
	  r.right=(nCx+cxTotal)/2;r.bottom=(nCy+cyTotal)/2;
	
    cw = rc.right-rc.left+1;
    ch = rc.bottom-rc.top+1;

    MoveWindow(&r);//,FALSE);
    GetClientRect(&rc);

    if( (cw == rc.right-rc.left+1) && (ch == rc.bottom-rc.top+1) )  // client size unchanged
      break;
  }

}


BEGIN_MESSAGE_MAP(CChildWindow, CFrameWnd)
	//{{AFX_MSG_MAP(CChildWindow)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildWindow message handlers

void CChildWindow::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(!Y || !RGBbuf) return;
	CyuvviewerDlg yuvviewer;
//	nPicShowOrder++;
	char msg[128];
	wsprintf(msg,"#%d - %s",nPicShowOrder, inSeqName);
	SetWindowText(msg);
	
	if(bColorImage){ 
		if(buf==1)
		conv.YV12_to_RGB24(Y,Cb,Cr,RGBbuf,iWidth,iHeight);
		else if(buf==4)
        yuvviewer.yuv444_to_rgb24(Y,Cb,Cr,RGBbuf,iWidth,iHeight);
		else if(buf==2)
		yuvviewer.yuv422_to_rgb24(Y,Cb,Cr,RGBbuf,iWidth,iHeight);
		else if(buf==3)
		yuvviewer.yuy2_to_rgb24(RGBbuf,YUY2,iWidth,iHeight);
		/*unsigned char *p=new unsigned char[iWidth*iHeight*3];
		for(int i=0;i<iWidth*iHeight*3;i++)
			p[i]=254;*/
		//ShowGrayImage(&dc,Y);
		ShowImage(&dc,RGBbuf);
	}
	else 
	{     
		if(buf==3)
		{
			for(int i=0;i<iWidth*iHeight;i++)
				Y1[i]=YUY2[2*i];
			ShowGrayImage(&dc,Y1);
		}
		else
		ShowGrayImage(&dc,Y);
	} 

	// Do not call CFrameWnd::OnPaint() for painting messages
}

int CChildWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    int i;
	HANDLE hloc1;
	RGBQUAD *argbq;

	hloc1 = LocalAlloc(LMEM_ZEROINIT | LMEM_MOVEABLE,(sizeof(RGBQUAD) * 256));
	argbq = (RGBQUAD *) LocalLock(hloc1);

	for(i=0;i<256;i++) {
		argbq[i].rgbBlue=i;
		argbq[i].rgbGreen=i;
		argbq[i].rgbRed=i;
		argbq[i].rgbReserved=0;
	}

	BmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BmpInfo->bmiHeader.biPlanes = 1;
	if(bColorImage) 
		BmpInfo->bmiHeader.biBitCount = 24;
	else BmpInfo->bmiHeader.biBitCount = 8;
	BmpInfo->bmiHeader.biCompression = BI_RGB;
	BmpInfo->bmiHeader.biWidth = iWidth;
	BmpInfo->bmiHeader.biHeight = iHeight;

	memcpy(BmpInfo->bmiColors, argbq, sizeof(RGBQUAD) * 256);

	LocalUnlock(hloc1);
	LocalFree(hloc1);

	return 0;
}
