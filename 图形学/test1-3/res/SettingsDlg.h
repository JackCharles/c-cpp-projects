#if !defined(AFX_SETTINGSDLG_H__E9A2A05F_5A94_4033_BFD4_AB8B2AAABC2A__INCLUDED_)
#define AFX_SETTINGSDLG_H__E9A2A05F_5A94_4033_BFD4_AB8B2AAABC2A__INCLUDED_

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
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSDLG_H__E9A2A05F_5A94_4033_BFD4_AB8B2AAABC2A__INCLUDED_)
