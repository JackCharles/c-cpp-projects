
// snl_work.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Csnl_workApp: 
// �йش����ʵ�֣������ snl_work.cpp
//

class Csnl_workApp : public CWinApp
{
public:
	Csnl_workApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Csnl_workApp theApp;