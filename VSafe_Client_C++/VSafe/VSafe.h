
// VSafe.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CVSafeApp: 
// �йش����ʵ�֣������ VSafe.cpp
//

class CVSafeApp : public CWinApp
{
public:
	CVSafeApp();

// ��д
public:
	virtual BOOL InitInstance();
	
	virtual int ExitInstance();

	ULONG_PTR m_gdiplusToken;

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVSafeApp theApp;