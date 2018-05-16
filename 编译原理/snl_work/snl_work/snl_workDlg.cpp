
// snl_workDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "snl_work.h"
#include "snl_workDlg.h"
#include "afxdialogex.h"
#include "GlobalVars.h"
#include "syntax.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CEdit editbox;
CString source_text;
CEdit tokenbox;
CEdit synbox;
CEdit treebox;
PDT pdt[104];
int LL1Table[110][110] = { 0 };

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// Csnl_workDlg 对话框



Csnl_workDlg::Csnl_workDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SNL_WORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Csnl_workDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_SOURCE, editbox);
	DDX_Control(pDX, IDC_TOKEN, tokenbox);
	DDX_Control(pDX, IDC_SYNTAX, synbox);
	DDX_Control(pDX, IDC_TREE, treebox);
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Csnl_workDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Csnl_workDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_SOURCE, &Csnl_workDlg::OnEnChangeSource)
	ON_EN_CHANGE(IDC_TOKEN, &Csnl_workDlg::OnEnChangeToken)
	ON_BN_CLICKED(IDC_BUTTON2, &Csnl_workDlg::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_SYNTAX, &Csnl_workDlg::OnEnChangeSyntax)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// Csnl_workDlg 消息处理程序

BOOL Csnl_workDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	static CFont font;
	font.DeleteObject();
	font.CreatePointFont(120, _T("consolas"));
	editbox.SetFont(&font);//设置字体
	tokenbox.SetFont(&font);
	synbox.SetFont(&font);
	treebox.SetFont(&font);

	initGrammar(pdt);//初始化产生式
	initLL1Table(LL1Table);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Csnl_workDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void Csnl_workDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


BOOL Csnl_workDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return true;
	else if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB))
	{
		if (GetFocus() == GetDlgItem(IDC_SOURCE))
		{
			if (pMsg->wParam == VK_RETURN)
				editbox.ReplaceSel(TEXT("\r\n"), true);
			else
				editbox.ReplaceSel(TEXT("\t"), true);
		}
	}
	else
		return CDialog::PreTranslateMessage(pMsg);
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Csnl_workDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Csnl_workDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL isOpen = TRUE;     //是否打开(否则为保存)  
	CString defaultDir = "";   //默认打开的文件路径  
	CString fileName = "";         //默认打开的文件名  
	CString filter = "文件 (*.txt)|*.txt||";   //文件过虑的类型  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = "";
	if (result == IDOK)
		filePath = openFileDlg.GetPathName();
	FILE *fp = fopen(filePath, "r");//文件必须存在
	if (fp == NULL)
	{
		MessageBox("打开文件失败。", "错误", MB_OK);
		return;
	}
	char c = 0;
	CString t = "";
	while ((c = fgetc(fp)) != EOF)
		if (c == '\n')
			t += "\r\n";
		else
			t += c;
	fclose(fp);
	editbox.SetWindowText(t);
}


void Csnl_workDlg::OnEnChangeSource()
{
}


void Csnl_workDlg::OnEnChangeToken()
{
}


void Csnl_workDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	initialOutBuffer();
	if (getTokenlist())
	{
		TOKEN *head = getTokenFromFile("TokenList.txt");
		if (head != NULL)
			syntaxAnalyze(head, pdt, LL1Table);
	}
}


HBRUSH Csnl_workDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}


void Csnl_workDlg::OnTvnSelchangedTerr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void Csnl_workDlg::OnEnChangeSyntax()
{
}