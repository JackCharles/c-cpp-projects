// test_6View.h : interface of the CTest_6View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST_6VIEW_H__3BB9FCF1_BD93_44D5_992F_68EF77197D82__INCLUDED_)
#define AFX_TEST_6VIEW_H__3BB9FCF1_BD93_44D5_992F_68EF77197D82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTest_6View : public CView
{
protected: // create from serialization only
	CTest_6View();
	DECLARE_DYNCREATE(CTest_6View)

// Attributes
public:
	CTest_6Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_6View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTest_6View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTest_6View)
	afx_msg void OnBegin();
	afx_msg void OnStop();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void DrawBezierLine(CDC* pDC);
	CPoint decas(CPoint P[], int n, double t);
	void BezierLine(CDC *pDC, CPoint* cpts, int n, int npoints);
	void DrawRect(CDC* pDC);
	int numpts;
	CPoint pts[50];
	CPoint tpoint;
	bool isDrawing;
	int de[50];

};

#ifndef _DEBUG  // debug version in test_6View.cpp
inline CTest_6Doc* CTest_6View::GetDocument()
   { return (CTest_6Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_6VIEW_H__3BB9FCF1_BD93_44D5_992F_68EF77197D82__INCLUDED_)
