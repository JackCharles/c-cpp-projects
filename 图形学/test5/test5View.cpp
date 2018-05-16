// test5View.cpp : implementation of the CTest5View class
//

#include "stdafx.h"
#include "test5.h"
#include "math.h"

#include "test5Doc.h"
#include "test5View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest5View

IMPLEMENT_DYNCREATE(CTest5View, CView)

BEGIN_MESSAGE_MAP(CTest5View, CView)
	//{{AFX_MSG_MAP(CTest5View)
	ON_COMMAND(Hermite_MENU, OnHermite)
	ON_COMMAND(Bezier_MENU, OnBezier)
	ON_COMMAND(B_MENU, OnB)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest5View construction/destruction

CTest5View::CTest5View()
{
	// TODO: add construction code here
	flag=false;
	numpts=0;
	type=1;
	HermitePoint=0;//number of Hermite control points
}

CTest5View::~CTest5View()
{
}

BOOL CTest5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTest5View drawing

void CTest5View::OnDraw(CDC* pDC)
{
	CTest5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(type==1)
	{
		pDC->TextOut(0,0,"绘制Hermite曲线");
		pDC->TextOut(0,20,"选择起点和起点切向量（两点确定）:");
	}
	else if(type==2)
		pDC->TextOut(0,0,"绘制Bezier曲线");
	else if(type==3)
			pDC->TextOut(0,0,"绘制B样条曲线");
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTest5View printing

BOOL CTest5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTest5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTest5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTest5View diagnostics

#ifdef _DEBUG
void CTest5View::AssertValid() const
{
	CView::AssertValid();
}

void CTest5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTest5Doc* CTest5View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest5Doc)));
	return (CTest5Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTest5View message handlers

void CTest5View::OnHermite() 
{
	// TODO: Add your command handler code here
	type=1;
	HermitePoint=0;
	Invalidate(true);
}

void CTest5View::OnBezier() 
{
	// TODO: Add your command handler code here
	type=2;
	Invalidate(true);
	
}

void CTest5View::OnB() 
{
	// TODO: Add your command handler code here
	type=3;
	Invalidate(true);
}

void CTest5View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC = this->GetDC();
	if(type==1)//Hermite
	{
		CPen *mypen = new CPen(PS_SOLID, 2, RGB(128, 128, 128));
		CPen *oldpen = pDC->SelectObject(mypen);
		if(HermitePoint==0||HermitePoint==4)//绘制起点
		{
			HermitePoint=0;
			BeginPoint=point;
			HermitePoint++;
			DrawPoint(pDC, point.x, point.y);
		}
		else if(HermitePoint==1)//绘制起点方向
		{
			Beg_directPoint=point;
			pDC->MoveTo(BeginPoint);
			pDC->LineTo(Beg_directPoint);
			HermitePoint++;
			DrawPoint(pDC, point.x, point.y);
			pDC->TextOut(0,20,"终选择点和终点切向量（选完后右键绘制）:");
		}
		else if(HermitePoint==2)//绘制终点
		{	
			EndPoint=point;
			HermitePoint++;
			DrawPoint(pDC, point.x, point.y);
		}
		else if(HermitePoint==3)
		{
			End_directPoint=point;
			pDC->MoveTo(EndPoint);
			pDC->LineTo(End_directPoint);
			HermitePoint++;
			DrawPoint(pDC, point.x, point.y);
		}
		pDC->SelectObject(oldpen);
		delete mypen;
	}

	else//Bizer & B
	{
		if(flag==false)
		{
			numpts=0;
			flag=true;
			pts[numpts]=point;
		}
		else
		{
			pts[numpts]=point;
			CPen *mypen = new CPen(PS_SOLID, 2, RGB(128, 128, 128));
			CPen *oldpen = pDC->SelectObject(mypen);
			pDC->MoveTo(pts[numpts-1]);
			pDC->LineTo(pts[numpts]);
			pDC->SelectObject(oldpen);
			delete mypen;
		}
		DrawPoint(pDC, point.x, point.y);
	}
	
	ReleaseDC(pDC);
	numpts++;
	
	CView::OnLButtonDown(nFlags, point);
}

void CTest5View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if(flag)
		flag=false;
	CDC *pDC = this->GetDC();

	if(type==1)
	{
		if(HermitePoint==4)
			DrawHermiteLine(pDC, 30);
		else
			MessageBox("请选完点再绘图！","错误",MB_OK);
	}
	else if(type==2)
	{
		int n=30;
		DrawBezierLine(pDC,n);
	}
	else if(type==3)
	{
		if(numpts<4)
			MessageBox("请至少选择4个控制点!","错误",MB_OK);
		else
		{
			int i,k=4;//阶	
			double *knot=new double[numpts+k];//节点向量
			for(i=0;i<k;i++)//根据k和控制点数构建节点向量
				knot[i]=0;
			for(i=k;i<numpts;i++)
				knot[i]=i-k+1;
			for(i=numpts;i<numpts+k;i++)
				knot[i]=numpts-k+1;

			//double knot[]={0,0,0,0,1,2,2,2,2};
			DrawBLine(pDC,k,knot,20);
			delete knot;
		}
	}


	ReleaseDC(pDC);
	CView::OnRButtonDown(nFlags, point);
}

void CTest5View::DrawPoint(CDC *pDC,int x,int y)
{
	pDC->SetPixel(x,y,RGB(255,0,0));
	pDC->SetPixel(x-1,y,RGB(255,0,0));
	pDC->SetPixel(x+1,y,RGB(255,0,0));
	pDC->SetPixel(x,y-1,RGB(255,0,0));
	pDC->SetPixel(x,y+1,RGB(255,0,0));
	pDC->SetPixel(x-1,y-1,RGB(255,0,0));
	pDC->SetPixel(x+1,y-1,RGB(255,0,0));
	pDC->SetPixel(x-1,y+1,RGB(255,0,0));
	pDC->SetPixel(x+1,y+1,RGB(255,0,0));
}

/************************************** Hermite曲线 *****************************************/

void CTest5View::DrawHermiteLine(CDC *pDC, int npoints)
{
	double delt = 1.0/(double)npoints;
	double u = 0.0;
	int xb=Beg_directPoint.x-BeginPoint.x;//计算起点和终点切向量
	int yb=Beg_directPoint.y-BeginPoint.y;
	int xe=End_directPoint.x-EndPoint.x;
	int ye=End_directPoint.y-EndPoint.y;
	CPoint *p=new CPoint[npoints];

	for(int i=0;i<npoints;i++)
	{
		double u3=u*u*u;
		double u2=u*u;
		p[i].x=BeginPoint.x*(2*u3-3*u2+1)+EndPoint.x*(-2*u3+3*u2)+xb*(u3-2*u2+u)+xe*(u3-u2);
		p[i].y=BeginPoint.y*(2*u3-3*u2+1)+EndPoint.y*(-2*u3+3*u2)+yb*(u3-2*u2+u)+ye*(u3-u2);
		u+=delt;
	}
	
	CPen *mypen = new CPen(PS_SOLID, 2, RGB(255, 0, 255));
	CPen *oldpen = pDC->SelectObject(mypen);
	for(int j=0;j<npoints-1;j++)
	{
		pDC->MoveTo(p[j]);
		pDC->LineTo(p[j+1]);
	}
	pDC->SelectObject(oldpen);
	delete mypen;
	delete p;
}

/************************************** Bezier曲线 *****************************************/


void CTest5View::DrawBezierLine(CDC *pDC, int npoints)
{
	double t, delt;
	delt = 1.0/(double)npoints;
	t=0.0;
	CPoint *p = new CPoint[npoints+1];
	for(int i=0;i<=npoints;i++)
	{
		p[i]=decas(pts,numpts,t);
		t+=delt;
	}

	CPen *mypen = new CPen(PS_SOLID, 2, RGB(0, 0, 255));
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

CPoint CTest5View::decas(CPoint P[], int n, double t)
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


/************************************** B样条曲线 *****************************************/


void CTest5View::DrawBLine(CDC *pDC, int k, double knot[], int npoints)
{
	double u,delt;
	int i,j;
	int n = numpts-1;
	CPoint *p = new CPoint[npoints+1];

	delt = (knot[n+1]-knot[k-1])/(double)npoints;
	i=k-1;
	u=knot[k-1];
	for(j=0;j<=npoints;j++)
	{
		while((i<n)&&(u>knot[i+1]))
		i++;
		p[j]=deboor(pts,i,k,knot,u);
		u+=delt;
	}

	CPen *mypen = new CPen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen *oldpen = pDC->SelectObject(mypen);
	for(i=0;i<npoints;i++)
	{
		pDC->MoveTo(p[i]);
		pDC->LineTo(p[i+1]);
	}
	pDC->SelectObject(oldpen);
	delete mypen;
	delete p;
		
}


CPoint CTest5View::deboor(CPoint CP[], int i, int k, double knot[], double u)
{
	double denom,alpha;
	CPoint *p = new CPoint[k];
	const double epsilon=0.005;
	for(int j=0;j<k;j++)
	{
		p[j]=CP[i-k+1+j];
	}
	for(int r=1;r<k;r++)
	{
		for(int m=k-1;m>=r;m--)
		{
			int j;
			j=m+i-k+1;
			denom=knot[j+k-r]-knot[j];
			if(fabs(denom)<epsilon)
				alpha=0;
			else
			{
				alpha=(u-knot[j])/denom;
			}
			p[m].x=(1-alpha)*p[m-1].x+alpha*p[m].x;
			p[m].y=(1-alpha)*p[m-1].y+alpha*p[m].y;
		}
	}
	return p[k-1];
}

/*****************************************************************************************/


