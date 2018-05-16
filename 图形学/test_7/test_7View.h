// test_7View.h : interface of the CTest_7View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST_7VIEW_H__92E3F96E_E30A_4D65_8B7E_A02F60C1D0FC__INCLUDED_)
#define AFX_TEST_7VIEW_H__92E3F96E_E30A_4D65_8B7E_A02F60C1D0FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct ps
{
	float x;
	float y;
	float z;
}SPOINT;


class CTest_7View : public CView
{
protected: // create from serialization only
	CTest_7View();
	DECLARE_DYNCREATE(CTest_7View)

// Attributes
public:
	CTest_7Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_7View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTest_7View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTest_7View)
	afx_msg void OnDrawBLine();
	afx_msg void OnDuichen();
	afx_msg void OnXuanzhaun();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void XunZhuan(CDC *pDC,int x);
	void DuiChen(CDC *pDC, int x);
	void DrawResults(CDC *pDC,CPoint in[], int n);
	void DrawBLine(CDC *pDC, int k, double knot[], int npoints,CPoint ctrlPoint[]);
	CPoint deboor(CPoint CP[], int i, int k, double knot[], double u);
	CPoint pts[50];
	int numpts;
	bool isDraw;
	CPoint oldPoint;
	SPOINT results[20][50];//存储3维曲线点,最多20段，每段最多50点
	CPoint tyd[50];//旋转完的投影点
	CPoint duichen[50];
	int npoints;
	int numseg;
	COLORREF color[3];

};

#ifndef _DEBUG  // debug version in test_7View.cpp
inline CTest_7Doc* CTest_7View::GetDocument()
   { return (CTest_7Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_7VIEW_H__92E3F96E_E30A_4D65_8B7E_A02F60C1D0FC__INCLUDED_)
