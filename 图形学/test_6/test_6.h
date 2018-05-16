// test_6.h : main header file for the TEST_6 application
//

#if !defined(AFX_TEST_6_H__B116A144_6934_428C_80E6_3D8F0EEB4B03__INCLUDED_)
#define AFX_TEST_6_H__B116A144_6934_428C_80E6_3D8F0EEB4B03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest_6App:
// See test_6.cpp for the implementation of this class
//

class CTest_6App : public CWinApp
{
public:
	CTest_6App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_6App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTest_6App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_6_H__B116A144_6934_428C_80E6_3D8F0EEB4B03__INCLUDED_)
