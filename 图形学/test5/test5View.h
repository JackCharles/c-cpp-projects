// test5View.h : interface of the CTest5View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST5VIEW_H__B9C43D63_DB4B_455B_B177_B2C27DF2E3C4__INCLUDED_)
#define AFX_TEST5VIEW_H__B9C43D63_DB4B_455B_B177_B2C27DF2E3C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTest5View : public CView
{
public:
	int type;//H B B
	CPoint pts[50];//控制点
	int numpts;//控制点个数
	bool flag;
	int HermitePoint;

	CPoint BeginPoint,Beg_directPoint;
	CPoint EndPoint,End_directPoint;


protected: // create from serialization only
	CTest5View();
	DECLARE_DYNCREATE(CTest5View)

// Attributes
public:
	CTest5Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest5View)
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
	void DrawHermiteLine(CDC *pDC,int npoints);
	CPoint deboor(CPoint CP[], int i, int k, double knot[], double u);
	void DrawBLine(CDC*pDC, int k, double knot[], int npoints);
	void DrawBezierLine(CDC *pDC, int npoints);
	CPoint decas(CPoint P[], int n, double t);
	void DrawPoint(CDC*pDC, int x, int y);
	virtual ~CTest5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTest5View)
	afx_msg void OnHermite();
	afx_msg void OnBezier();
	afx_msg void OnB();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in test5View.cpp
inline CTest5Doc* CTest5View::GetDocument()
   { return (CTest5Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST5VIEW_H__B9C43D63_DB4B_455B_B177_B2C27DF2E3C4__INCLUDED_)
