// test_6View.cpp : implementation of the CTest_6View class
//

#include "stdafx.h"
#include "test_6.h"

#include "test_6Doc.h"
#include "test_6View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest_6View

IMPLEMENT_DYNCREATE(CTest_6View, CView)

BEGIN_MESSAGE_MAP(CTest_6View, CView)
	//{{AFX_MSG_MAP(CTest_6View)
	ON_COMMAND(IDM_BEGIN, OnBegin)
	ON_COMMAND(IDM_STOP, OnStop)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest_6View construction/destruction

CTest_6View::CTest_6View()
{
	// TODO: add construction code here
	numpts=0;
	isDrawing = false;
}

CTest_6View::~CTest_6View()
{
	
}

BOOL CTest_6View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTest_6View drawing

void CTest_6View::OnDraw(CDC* pDC)
{
	CTest_6Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	DrawRect(pDC);
	DrawBezierLine(pDC);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTest_6View diagnostics

#ifdef _DEBUG
void CTest_6View::AssertValid() const
{
	CView::AssertValid();
}

void CTest_6View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTest_6Doc* CTest_6View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest_6Doc)));
	return (CTest_6Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTest_6View message handlers


void CTest_6View::OnBegin() 
{
	// TODO: Add your command handler code here
	for(int i=0;i<50;i++)
		de[i] = 3;
	this->SetTimer(1,50,NULL);
}

void CTest_6View::OnStop() 
{
	// TODO: Add your command handler code here
	this->KillTimer(1);
}

void CTest_6View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC = this->GetDC();

	if(isDrawing==false)
	{
		isDrawing = true;
		numpts = 0;
		Invalidate(true);
		pts[numpts] = point;
		tpoint = point;
	}
	else
	{
		pts[numpts] = point;
		pDC->MoveTo(pts[numpts-1]);
		pDC->LineTo(pts[numpts]);
		tpoint = point;
	}
	numpts++;
	ReleaseDC(pDC);

	CView::OnLButtonDown(nFlags, point);
}

void CTest_6View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC = this->GetDC();
	if(isDrawing)
	{
		isDrawing = false;
		pts[numpts]=point;
		pDC->MoveTo(point);
		pDC->LineTo(pts[0]);
		numpts++;
	}
	DrawBezierLine(pDC);
	ReleaseDC(pDC);

	CView::OnRButtonDown(nFlags, point);
}

void CTest_6View::DrawRect(CDC *pDC)
{
	if(numpts==0)
		return;
	for(int i=0;i<numpts;i++)
	{
		pDC->MoveTo(pts[i]);
		pDC->LineTo(pts[(i+1)%numpts]);
	}
}

void CTest_6View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC* pDC = this->GetDC();
	if(isDrawing)
	{
		pDC->SetROP2(R2_NOT);
		pDC->MoveTo(pts[numpts-1]);
		pDC->LineTo(tpoint);
		pDC->MoveTo(pts[numpts-1]);
		pDC->LineTo(point);
		tpoint = point;
	}
	ReleaseDC(pDC);
	CView::OnMouseMove(nFlags, point);
}

/**********************************************************************************************/

void CTest_6View::BezierLine(CDC *pDC, CPoint* cpts, int n, int npoints)
{
	double t, delt;
	delt = 1.0/(double)npoints;
	t=0.0;
	CPoint *p = new CPoint[npoints+1];
	for(int i=0;i<=npoints;i++)
	{
		p[i]=decas(cpts,n,t);
		t+=delt;
	}

	CPen *mypen = new CPen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen *oldpen = pDC->SelectObject(mypen);
	for(int j=0;j<npoints;j++)
	{
		pDC->MoveTo(p[j]);
		pDC->LineTo(p[j+1]);
	}
	pDC->SelectObject(oldpen);
	delete mypen;
	delete p;
}

CPoint CTest_6View::decas(CPoint P[], int n, double t)
{
	int m,i;
	CPoint *R,*Q,P0;
	R=new CPoint[n+1];
	Q=new CPoint[n+1];
	for(i=0;i<=n;i++)
		R[i]=P[i];
	for(m=n;m>0;m--)
	{
		for(i=0;i<m-1;i++)
		{
			Q[i].x=R[i].x+t*(R[i+1].x-R[i].x);
			Q[i].y=R[i].y+t*(R[i+1].y-R[i].y);
		}
		for(i=0;i<m-1;i++)
			R[i]=Q[i];
	}
	P0=R[0];
	delete R;
	delete Q;

	return P0;
}

/**********************************************************************************************/

void CTest_6View::DrawBezierLine(CDC *pDC)
{
	if(numpts==0)
		return;
	for(int i=0;i<numpts;i++)
	{
		CPoint p[3];
		p[0].x = (pts[i].x + pts[(i+1)%numpts].x)/2;
		p[0].y = (pts[i].y + pts[(i+1)%numpts].y)/2;
		p[1] = pts[(i+1)%numpts];
		p[2].x = (pts[(i+1)%numpts].x + pts[(i+2)%numpts].x)/2;
		p[2].y = (pts[(i+1)%numpts].y + pts[(i+2)%numpts].y)/2;

		BezierLine(pDC,p,3,10);
	}

}

void CTest_6View::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC = this->GetDC();
	RECT rect;
	this->GetClientRect(&rect);
	if(nIDEvent==1)
	{
		
		for(int i=0;i<numpts;i++)
		{
			if((i+1)%2==0)//ˮƽ
			{
				if(de[i]==3 && pts[i].x+(i+1)*de[i]>rect.right)
					de[i] = -3;
				else if(de[i]==-3 && pts[i].x+(i+1)*de[i]<rect.left)
					de[i] = 3;
				pts[i].x+=de[i]*(i+1);
			}
			else
			{
				if(de[i] ==3 && pts[i].y+(i+1)*de[i]>rect.bottom)
					de[i] = -3;
				else if(de[i] ==-3 && pts[i].y+(i+1)*de[i]<rect.top)
					de[i] = 3;
				pts[i].y+=de[i]*(i+1);
			}
		}
		Invalidate(true);
	}
	ReleaseDC(pDC);
	CView::OnTimer(nIDEvent);
}
