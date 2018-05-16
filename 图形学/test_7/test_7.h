// test_7.h : main header file for the TEST_7 application
//

#if !defined(AFX_TEST_7_H__5D8AF219_2F74_4ECB_9B7B_574579ACFA4B__INCLUDED_)
#define AFX_TEST_7_H__5D8AF219_2F74_4ECB_9B7B_574579ACFA4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest_7App:
// See test_7.cpp for the implementation of this class
//

class CTest_7App : public CWinApp
{
public:
	CTest_7App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_7App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTest_7App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_7_H__5D8AF219_2F74_4ECB_9B7B_574579ACFA4B__INCLUDED_)
