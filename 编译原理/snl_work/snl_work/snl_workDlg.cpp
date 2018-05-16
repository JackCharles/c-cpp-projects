
// snl_workDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Csnl_workDlg �Ի���



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


// Csnl_workDlg ��Ϣ�������

BOOL Csnl_workDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	static CFont font;
	font.DeleteObject();
	font.CreatePointFont(120, _T("consolas"));
	editbox.SetFont(&font);//��������
	tokenbox.SetFont(&font);
	synbox.SetFont(&font);
	treebox.SetFont(&font);

	initGrammar(pdt);//��ʼ������ʽ
	initLL1Table(LL1Table);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Csnl_workDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Csnl_workDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL isOpen = TRUE;     //�Ƿ��(����Ϊ����)  
	CString defaultDir = "";   //Ĭ�ϴ򿪵��ļ�·��  
	CString fileName = "";         //Ĭ�ϴ򿪵��ļ���  
	CString filter = "�ļ� (*.txt)|*.txt||";   //�ļ����ǵ�����  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = "";
	if (result == IDOK)
		filePath = openFileDlg.GetPathName();
	FILE *fp = fopen(filePath, "r");//�ļ��������
	if (fp == NULL)
	{
		MessageBox("���ļ�ʧ�ܡ�", "����", MB_OK);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void Csnl_workDlg::OnEnChangeSyntax()
{
}