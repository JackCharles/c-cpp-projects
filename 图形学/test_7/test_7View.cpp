// test_7View.cpp : implementation of the CTest_7View class
//

#include "stdafx.h"
#include "test_7.h"

#include "test_7Doc.h"
#include "test_7View.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest_7View

IMPLEMENT_DYNCREATE(CTest_7View, CView)

BEGIN_MESSAGE_MAP(CTest_7View, CView)
	//{{AFX_MSG_MAP(CTest_7View)
	ON_COMMAND(IDM_DrawBLine, OnDrawBLine)
	ON_COMMAND(IDM_DUICHEN, OnDuichen)
	ON_COMMAND(IDM_XUANZHAUN, OnXuanzhaun)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest_7View construction/destruction

CTest_7View::CTest_7View()
{
	// TODO: add construction code here
	numpts = 0;
	isDraw = false;
	color[0] = RGB(255,0,0);
	color[1] = RGB(0,255,0);
	color[2] = RGB(0,0,255);
}

CTest_7View::~CTest_7View()
{
}

BOOL CTest_7View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTest_7View drawing

void CTest_7View::OnDraw(CDC* pDC)
{
	CTest_7Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTest_7View printing

BOOL CTest_7View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTest_7View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTest_7View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTest_7View diagnostics

#ifdef _DEBUG
void CTest_7View::AssertValid() const
{
	CView::AssertValid();
}

void CTest_7View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTest_7Doc* CTest_7View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest_7Doc)));
	return (CTest_7Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTest_7View message handlers

void CTest_7View::OnDrawBLine() 
{
	// TODO: Add your command handler code here
	Invalidate(true);
	UpdateWindow();
	CDC *pDC = this->GetDC();
	int i,j;
	numseg = 0;
	for(i=0;i<numpts-1;i++)
	{
		pDC->MoveTo(pts[i]);
		pDC->LineTo(pts[i+1]);
	}	
	double knot[8]={0,1,2,3,4,5,6,7};//节点向量
	npoints = 30;
	CPoint temp[4];
	for(j=0;j<numpts-3;j++)	
	{
		numseg++;
		for(i=0;i<4;i++)
		temp[i] = pts[j+i];
		DrawBLine(pDC, 4, knot, npoints, temp);
	}
	ReleaseDC(pDC);
}

void CTest_7View::OnDuichen() 
{
	// TODO: Add your command handler code here
	Invalidate(true);
	UpdateWindow();
	CDC *pDC = this->GetDC();
	numseg = 0;
	for(int i=0;i<numpts-3;i++)
	{
		numseg++;
		CPoint temp[50];
		for(int j=0;j<npoints;j++)
		{
			temp[j].x = results[numseg-1][j].x;
			temp[j].y = results[numseg-1][j].y;
		}
		DrawResults(pDC,temp,npoints);
		DuiChen(pDC, pts[0].x);
	}
	ReleaseDC(pDC);
}

void CTest_7View::OnXuanzhaun() 
{
	// TODO: Add your command handler code here
	Invalidate(true);
	UpdateWindow();
	CDC *pDC = this->GetDC();
	numseg=0;
	for(int i=0;i<numpts-3;i++)
	{
		numseg++;
		XunZhuan(pDC,pts[0].x);
	}
	ReleaseDC(pDC);
}

void CTest_7View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC = this->GetDC();

	if(isDraw == false)
	{
		Invalidate(true);
		isDraw = true;
		numpts = 0;
		pts[0] = point;
		pts[1] = point;
		pts[2] = point;
		numpts = 2;
	}
	else
	{
		pts[numpts] = point;
		pDC->MoveTo(pts[numpts-1]);
		pDC->LineTo(point);
	}
	oldPoint = point;
	numpts++;
	ReleaseDC(pDC);

	CView::OnLButtonDown(nFlags, point);
}

void CTest_7View::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC = this->GetDC();
	pts[numpts] = point;	
	pDC->MoveTo(pts[numpts-1]);
	pDC->LineTo(point);
	numpts++;
	pts[numpts] = point;
	numpts++;
	pts[numpts] = point;
	numpts++;
	isDraw = false;
	ReleaseDC(pDC);
	CView::OnLButtonDblClk(nFlags, point);
}

void CTest_7View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC = this->GetDC();
	if(isDraw == true)
	{
		pDC->SetROP2(R2_NOT);
		pDC->MoveTo(pts[numpts-1]);
		pDC->LineTo(oldPoint);

		pDC->MoveTo(pts[numpts-1]);
		pDC->LineTo(point);

		oldPoint = point;
	}


	CView::OnMouseMove(nFlags, point);
}

/******************************************B样条曲线***********************************************/

void CTest_7View::DrawBLine(CDC *pDC, int k, double knot[], int npoints, CPoint ctrlPoint[])
{
	double u,delt;
	int i,j;
	int n = 3;

	delt = (knot[n+1]-knot[k-1])/(double)npoints;
	i=k-1;
	u=knot[k-1];
	for(j=0;j<=npoints;j++)
	{
		while((i<n)&&(u>knot[i+1]))
		i++;
		CPoint t=deboor(ctrlPoint,i,k,knot,u);
		tyd[j].x = results[numseg-1][j].x = t.x;
		tyd[j].y = results[numseg-1][j].y = t.y;
		results[numseg-1][j].z = 0;
		u+=delt;
	}
	DrawResults(pDC,tyd,npoints);
}


CPoint CTest_7View::deboor(CPoint CP[], int i, int k, double knot[], double u)
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

/*******************************************************************************************************/

void CTest_7View::DrawResults(CDC *pDC, CPoint in[], int n)
{
	CPen *mypen = new CPen(PS_SOLID, 1, color[numseg%3]);
	CPen *oldpen = pDC->SelectObject(mypen);
	for(int i=0;i<n;i++)
	{
		pDC->MoveTo(in[i]);
		pDC->LineTo(in[i+1]);
	}
	pDC->SelectObject(oldpen);
}

void CTest_7View::DuiChen(CDC *pDC, int x)
{
	int i;
	for(i = 0;i<npoints+1;i++)
	{
		tyd[i].x =results[numseg-1][i].x + 2*(x - results[numseg-1][i].x);
		tyd[i].y = results[numseg-1][i].y;
	}
	DrawResults(pDC,tyd, npoints);
}



void MatrixMult(float in[], float m[][4], float out[])//矩阵乘法
{
	for(int i=0;i<4;i++)
	{
		out[i] = 0.0;
		for(int j=0;j<4;j++)
		{
			out[i]+= in[j]*m[j][i];
		}
	}
}


void CTest_7View::XunZhuan(CDC *pDC, int x)
{
	int i,j;

	float r = 3.14159/18.0;
	float a = (3.14159*45)/180.0;
	float l = 0.5;
	float m1[4][4] = {{cos(r),0,-sin(r),0},{0,1,0,0},{sin(r),0,cos(r),0},{0,0,0,1}};
	float m2[4][4] = {{1.0,0.0,0.0,0.0},{0.0,1.0,0.0,0.0},{l*cos(a),l*sin(a),0.0,0.0},{0.0,0.0,0.0,1.0}};
	float in[4] = {0,0,0,1},out[4];
	float in2[4]={0,0,0,1},out2[4];

	for(j = 0;j<36;j++)
	{
		for(i = 0; i< npoints+1 ; i++)
		{
			in[0] = results[numseg-1][i].x - x;//移到原点
			in[1] = results[numseg-1][i].y;
			in[2] = results[numseg-1][i].z;

			MatrixMult(in,m1,out);//旋转
			
			out[0]+=x;            //移回原来位置   
			results[numseg-1][i].x = out[0];//旋转后备份
			results[numseg-1][i].y = out[1];
			results[numseg-1][i].z = out[2];

		    
			out[3]=1;             //投影规范化

			MatrixMult(out,m2,out2);//投影

			tyd[i].x = out2[0];   //保存投影结果
			tyd[i].y = out2[1];
		}

		DrawResults(pDC, tyd, npoints);
	}
}
