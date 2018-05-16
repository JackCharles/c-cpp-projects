// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test1.h"
#include "SettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingsDlg dialog


SettingsDlg::SettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SettingsDlg, CDialog)
	//{{AFX_MSG_MAP(SettingsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingsDlg message handlers


BOOL SettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char buf[8]={0};
	gcvt(Cube.disp,4,buf);
	GetDlgItem(IDC_DCPYJL)->SetWindowText(buf);
	gcvt(Cube.rate,4,buf);
	GetDlgItem(IDC_DCSFBL)->SetWindowText(buf);
	gcvt(Cube.angl,4,buf);
	GetDlgItem(IDC_DCXZJD)->SetWindowText(buf);

	gcvt(Cube.ProjCent.x,4,buf);
	GetDlgItem(IDC_TYZX_X)->SetWindowText(buf);
	gcvt(Cube.ProjCent.y,4,buf);
	GetDlgItem(IDC_TYZX_Y)->SetWindowText(buf);
	gcvt(Cube.ProjCent.z,4,buf);
	GetDlgItem(IDC_TYZX_Z)->SetWindowText(buf);
	
	return TRUE;  // return TRUE unless you set the focus to a control              
}

void SettingsDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString str;
	GetDlgItemText(IDC_DCPYJL,str);
	Cube::disp=atof(str.GetBuffer(0));
	GetDlgItemText(IDC_DCSFBL,str);
	Cube::rate=atof(str.GetBuffer(0));
	GetDlgItemText(IDC_DCXZJD,str);
	Cube::angl=atof(str.GetBuffer(0));
	Cube::r = Cube.angl/180.0*3.1416;

	GetDlgItemText(IDC_TYZX_X,str);
	Cube::ProjCent.x=atof(str.GetBuffer(0));
	GetDlgItemText(IDC_TYZX_Y,str);
	Cube::ProjCent.y=atof(str.GetBuffer(0));
	GetDlgItemText(IDC_TYZX_Z,str);
	Cube::ProjCent.z=atof(str.GetBuffer(0));

	CDialog::OnOK();
}

void SettingsDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	int state;
	this->EndDialog(state);
	CDialog::OnCancel();
}
