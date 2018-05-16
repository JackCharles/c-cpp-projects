// test1View.h : interface of the CTest1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST1VIEW_H__2ED4C64D_3835_4A59_8E61_3B78D4042ECD__INCLUDED_)
#define AFX_TEST1VIEW_H__2ED4C64D_3835_4A59_8E61_3B78D4042ECD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "afxtempl.h"
#include "ube.h"
#include "SettingsDlg.h"

class CTest1View : public CView
{
protected: // create from serialization only
	CTest1View();
	DECLARE_DYNCREATE(CTest1View)

// Attributes
public:
	CTest1Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest1View)
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
	void FillColor(CDC *pDC);
	void L_Barsky(CDC *pDC, double x0,double x1,double y0,double y1);
	void DrawRect(int type, CDC *pDC, CPoint p1, CPoint p2);
	void PatternFill(CDC *pDC, int x,int y,COLORREF pattern[][48], int m, int n);
	void MidpointEllipse(CDC *pDC, CPoint P, CPoint Q);
	void MidpointCircle(CDC *pDC, CPoint P, CPoint Q);
	void EdgeMarkFill(CDC *pDC, CPoint *pt, int n, COLORREF color);
	virtual ~CTest1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTest1View)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawEllipse();
	afx_msg void OnDrawLine();
	afx_msg void OnDRAWMultEdge();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void On3dDraw();
	afx_msg void OnXjty();
	afx_msg void OnTsty();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSetdata();
	afx_msg void OnCut();
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool isLButtonDown;
	CPoint begPoint;
	CPoint endPoint;
	int drawType;//绘图类型
	bool isDraw;
	HCURSOR m_Cursor;
	CPoint *points;
	int numPoints;
	COLORREF pic[48][48]; //填充图案
	Cube *cube;
	int ProjectionType; //变换类型OnDraw使用

	CPoint rectPointLU;
	CPoint rectPointRD;
	bool canCut;
};

#ifndef _DEBUG  // debug version in test1View.cpp
inline CTest1Doc* CTest1View::GetDocument()
   { return (CTest1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST1VIEW_H__2ED4C64D_3835_4A59_8E61_3B78D4042ECD__INCLUDED_)
