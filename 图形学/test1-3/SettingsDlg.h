#if !defined(AFX_SETTINGSDLG_H__5D8D60C5_0A5F_4BC8_851D_12FED3855354__INCLUDED_)
#define AFX_SETTINGSDLG_H__5D8D60C5_0A5F_4BC8_851D_12FED3855354__INCLUDED_
#include <stdio.h>
#include "ube.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SettingsDlg dialog

class SettingsDlg : public CDialog
{
// Construction
public:
	SettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SettingsDlg)
	enum { IDD = IDD_SETTINGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SettingsDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSDLG_H__5D8D60C5_0A5F_4BC8_851D_12FED3855354__INCLUDED_)
