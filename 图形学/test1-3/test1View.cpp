// test1View.cpp : implementation of the CTest1View class
//

#include "stdafx.h"
#include "test1.h"

#include "test1Doc.h"
#include "test1View.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest1View

IMPLEMENT_DYNCREATE(CTest1View, CView)

BEGIN_MESSAGE_MAP(CTest1View, CView)
	//{{AFX_MSG_MAP(CTest1View)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_CIRCLE, OnDrawCircle)
	ON_COMMAND(ID_DRAW_ELLIPSE, OnDrawEllipse)
	ON_COMMAND(ID_DRAW_LINE, OnDrawLine)
	ON_COMMAND(ID_DRAW_MultEdge, OnDRAWMultEdge)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_3D_DRAW, On3dDraw)
	ON_COMMAND(IDM_XJTY, OnXjty)
	ON_COMMAND(IDM_TSTY, OnTsty)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(IDM_SETDATA, OnSetdata)
	ON_COMMAND(ID_CUT, OnCut)
	ON_WM_RBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest1View construction/destruction

bool find(int *p,int n,int x)
{
	for(int i=0;i<n;i++)
	{
		if(x==p[i])
			return true;
	}
	return false;
}

CTest1View::CTest1View()
{
	// TODO: add construction code here
	isLButtonDown = false;
	drawType = 1;
	isDraw = true;
	m_Cursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	points = new CPoint[100];
	numPoints = 0;
	cube = NULL;
	ProjectionType = 1;
	canCut=false;
}

CTest1View::~CTest1View()
{
	delete []points;
	delete cube;
}

BOOL CTest1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTest1View drawing

void CTest1View::OnDraw(CDC* pDC)
{
	CTest1Doc* pDoc = GetDocument();
	if(drawType == 5)
	{
		if(ProjectionType==1)
			cube->ObliqueProjection(pDC);
		else if(ProjectionType == 2)
		{
			cube->PerspectiveProjection(pDC);
		}
	}
	ReleaseDC(pDC);
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTest1View printing

BOOL CTest1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTest1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTest1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTest1View diagnostics

#ifdef _DEBUG
void CTest1View::AssertValid() const
{
	CView::AssertValid();
}

void CTest1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTest1Doc* CTest1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest1Doc)));
	return (CTest1Doc*)m_pDocument;
}
#endif //_DEBUG







/*==============================================================================================================================*/






// 左键按下

void CTest1View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCursor(m_Cursor);
	this->isLButtonDown = true;
	this->begPoint = point;
	this->endPoint = point;
	this->SetCapture();
	
	if(this->drawType==4)
	{
		if(this->isDraw == true)
		{                                                                                                                                             
			this->isDraw = false;
			numPoints = 0;
			points[numPoints]=point;
		}
		else
		{	
			CDC *pDC = this->GetDC();
			pDC->MoveTo(this->points[numPoints-1]);
			pDC->LineTo(point);
			points[numPoints]=point;
			ReleaseDC(pDC);
		}
		this->numPoints++;
	}
	else if(drawType==5)
	{
		cube->xoffset = point.x;
		cube->yoffset = point.y;
		Invalidate(true);
	}
	
	else if(drawType == 6)
	{
		rectPointLU = point;
		rectPointRD = point;
	}

	CView::OnLButtonDown(nFlags, point);
}

//左键弹起
void CTest1View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCursor(m_Cursor);
	this->isLButtonDown = false;
	ReleaseCapture();

	CDC* pDC = this->GetDC();
	if(this->drawType==1)
	{
		//画直线
		pDC->MoveTo(this->begPoint);
		pDC->LineTo(this->endPoint);
	}
	else if(this->drawType==2)
	{
		//画圆
		MidpointCircle(pDC, this->begPoint,this->endPoint);
	}
	else if(this->drawType==3)
	{
		//画椭圆
		MidpointEllipse(pDC,this->begPoint,this->endPoint);
	}

	else if(drawType == 6)
	{
		rectPointRD = point;
		canCut = true;
		DrawRect(1,pDC, rectPointLU, rectPointRD);
	}

	this->ReleaseDC(pDC);
	CView::OnLButtonUp(nFlags, point);
}

//右键按下

void CTest1View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(this->drawType==4&&isDraw==false)
	{
		CDC *pDC = this->GetDC();
		points[numPoints]=point;
		numPoints++;
		
		pDC->MoveTo(points[numPoints-1]);
		pDC->LineTo(points[0]);
		EdgeMarkFill(pDC, this->points, this->numPoints, RGB(255,0,0));
			
		this->isDraw = true;
		ReleaseDC(pDC);
	}

	if(this->drawType==6)
	{
		if(this->isDraw == true)
		{                                                                                                                                             
			this->isDraw = false;
			numPoints = 0;
			points[numPoints]=point;
		}
		else
		{	
			CDC *pDC = this->GetDC();
			pDC->MoveTo(this->points[numPoints-1]);
			pDC->LineTo(point);
			points[numPoints]=point;
			ReleaseDC(pDC);
		}
		this->numPoints++;
	}

	CView::OnRButtonDown(nFlags, point);
}

//左键双击
void CTest1View::OnLButtonDblClk(UINT nFlags, CPoint point) {}

//R button dk
void CTest1View::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(this->drawType==6 && isDraw==false)
	{
		CDC *pDC = this->GetDC();
		points[numPoints]=point;
		//numPoints++;
		
		pDC->MoveTo(points[numPoints-1]);
		pDC->LineTo(points[0]);
		
		for(int i=0;i<numPoints;i++)
			L_Barsky(pDC,points[i].x,points[i].y,points[(i+1)%numPoints].x,points[(i+1)%numPoints].y);

		this->isDraw = true;
		ReleaseDC(pDC);
	}
	CView::OnRButtonDblClk(nFlags, point);
}



//鼠标移动
void CTest1View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCursor(m_Cursor);
	CDC *pDC = this->GetDC();
	
	if(isLButtonDown == true)
	{
		pDC->SetROP2(R2_NOT);
		if(this->drawType==1)
		{
			//直线
			pDC->MoveTo(this->begPoint);
			pDC->LineTo(this->endPoint);
			pDC->MoveTo(this->begPoint);
			pDC->LineTo(point);			
		}
		else if(this->drawType==2)
		{
			//画圆
			MidpointCircle(pDC,this->begPoint,this->endPoint);
			MidpointCircle(pDC,this->begPoint,point);
		}
		else if(this->drawType==3)
		{
			//画椭圆
			MidpointEllipse(pDC,this->begPoint,this->endPoint);
			MidpointEllipse(pDC,this->begPoint,point);
		}
		else if(drawType == 6)
		{
			DrawRect(0,pDC,rectPointLU,rectPointRD);
			DrawRect(1,pDC,rectPointLU,point);	
			rectPointRD = point;
		}

	}
	if((this->drawType==4 ||this->drawType==6) && this->isDraw==false)
	{
		pDC->SetROP2(R2_NOT);
		pDC->MoveTo(this->points[this->numPoints-1]);
		pDC->LineTo(this->endPoint);
		pDC->MoveTo(this->points[this->numPoints-1]);
		pDC->LineTo(point);
	}



	if(drawType==5&&isLButtonDown == true)
	{
		cube->xoffset = point.x;
		cube->yoffset = point.y;
		Invalidate(true);
	}
	

	this->endPoint = point;
	this->ReleaseDC(pDC);
	CView::OnMouseMove(nFlags, point);
}


//中点画圆算法
void CTest1View::MidpointCircle(CDC *pDC, CPoint P, CPoint Q)
{
	int dx = Q.x - P.x;
	int dy = Q.y - P.y;
	int R = (int)sqrt((dx*dx) + (dy*dy));

	int x,y,del1,del2,d;
	x = 0;
	y = R;
	d = 1 - R;
	del1 = 3;
	del2 = 5 - R - R;
	pDC->SetPixel(x+P.x, y+P.y, RGB(0,0,255));
	while(x<y)
	{
		if(d<0)
		{
			d+=del1;
			del1+=2;
			del2+=2;
			x++;
		}
		else
		{
			d+=del2;
			del1+=2;
			del2+=4;
			x++;
			y--;
		}
		pDC->SetPixel(x+P.x, y+P.y, RGB(255,0,0));
		pDC->SetPixel(-x+P.x, y+P.y, RGB(255,0,0));
		pDC->SetPixel(x+P.x, -y+P.y, RGB(255,0,0));
		pDC->SetPixel(-x+P.x, -y+P.y, RGB(255,0,0));

		pDC->SetPixel(y+P.x, x+P.y, RGB(255,0,0));
		pDC->SetPixel(y+P.x, -x+P.y, RGB(255,0,0));
		pDC->SetPixel(-y+P.x, x+P.y, RGB(255,0,0));
		pDC->SetPixel(-y+P.x, -x+P.y, RGB(255,0,0));
	    
	}
}



//中点椭圆算法
void CTest1View::MidpointEllipse(CDC *pDC, CPoint P, CPoint Q)
{
	int a = abs(Q.x - P.x);
	int b = abs(Q.y - P.y);

	int x,y;
	double d1,d2;
	x = 0;
	y = b;
	d1 = b * b + a * a * ( -b + 0.25);
	pDC->SetPixel(x+P.x, y+P.y, RGB(0,0,255));
	while(b * b * (x+1)<a*a*(y-0.5))
	{
		if(d1<0)
		{
			d1+=b*b*(2*x+3);
			x++;
		}
		else
		{
			d1+=(b*b*(2*x+3)+a*a*(-2*y+2));
			x++;
			y--;
		}
		pDC->SetPixel(x+P.x, y+P.y, RGB(0,0,255));
		pDC->SetPixel(-x+P.x, y+P.y, RGB(0,0,255));
		pDC->SetPixel(x+P.x, -y+P.y, RGB(0,0,255));
		pDC->SetPixel(-x+P.x, -y+P.y, RGB(0,0,255));
	}

	d2 = b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
	while(y>0)
	{
		if(d2<0)
		{
			d2+=b*b*(2*x+2)+a*a*(-2*y+3);
			x++;
			y--;
		}
		else
		{
			d2+=a*a*(-2*y+3);
			y--;
		}
		pDC->SetPixel(x+P.x, y+P.y, RGB(0,0,255));
		pDC->SetPixel(-x+P.x, y+P.y, RGB(0,0,255));
		pDC->SetPixel(x+P.x, -y+P.y, RGB(0,0,255));
		pDC->SetPixel(-x+P.x, -y+P.y, RGB(0,0,255));
	}
}


/*==================================================================================================================*/

void CTest1View::EdgeMarkFill(CDC *pDC, CPoint *pt, int n, COLORREF color)
{
	//计算边界
	int x1=pt[0].x, y1=pt[0].y;
	int x2=x1, y2=y1;
	for(int i=0;i<n;i++)
	{
		if(y1>pt[i].y)
			y1=pt[i].y;
		if(y2<pt[i].y)
			y2=pt[i].y;
		if(x1>pt[i].x)
			x1=pt[i].x;
		if(x2<pt[i].x)
			x2=pt[i].x;
	}
	x1=x1-5>0?x1-5:x1;
	x2+=5;
	y1=y1-5>0?y1-5:y1;
	y2+=5;
	//绘制边框
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y1);
	pDC->MoveTo(x2,y1);
	pDC->LineTo(x2,y2);
	pDC->MoveTo(x2,y2);
	pDC->LineTo(x1,y2);
	pDC->MoveTo(x1,y2);
	pDC->LineTo(x1,y1);


	bool **MASK = new bool*[y2];
	for(int j=0;j<y2;j++)
		MASK[j] = new bool[x2];
	
	for(int y=y1;y<y2;y++) 
		for(int x=x1;x<x2;x++)
			MASK[y-y1][x-x1]=false;

	if( (pt[0].y-pt[n-1].y) * (pt[0].y-pt[1].y) > 0)
			MASK[pt[0].y-y1][pt[0].x-x1]=!MASK[pt[0].y-y1][pt[0].x-x1];
	
	for(int t=1;t<n;t++)
	{

		if( (pt[t].y-pt[t-1].y) * (pt[t].y-pt[(t+1)%n].y) > 0)
			MASK[pt[t].y-y1][pt[t].x-x1]=true;
	}

	for(int k=y1+1;k<y2;k++)
	{
		bool isInside = false;
	
		for(int l=x1+1;l<x2;l++)
		{
			COLORREF color = pDC->GetPixel(l,k);

			if(color == RGB(0,0,0))
			{
				if(isInside)
				{
					MASK[k-y1][l-x1]=!MASK[k-y1][l-x1];	
					for( ;pDC->GetPixel(l,k)==RGB(0,0,0); l++);
					isInside = false;
				}
				else
				{
					isInside = true;
					for( ;pDC->GetPixel(l,k)==RGB(0,0,0); l++);
					MASK[k-y1][l-x1]=!MASK[k-y1][l-x1];	
				}
			}

		}
	}

	bool inside;
	for(int yy = y1; yy<y2; yy++)
	{
		inside = false;
		for(int xx=x1;xx<x2;xx++)
		{
			if(MASK[yy-y1][xx-x1])
				inside=!inside;
			if(inside)
				//pDC->SetPixel(xx,yy,color);
				PatternFill(pDC,xx,yy,pic,48,48);

		}
	}

}


/*==================================================================================================================*/
void CTest1View::OnDrawCircle() 
{
	// TODO: Add your command handler code here
	drawType = 2;//1表示绘制直线段
	isDraw = true;//初始状态为绘图状态
}

void CTest1View::OnDrawEllipse() 
{
	// TODO: Add your command handler code here
	drawType = 3;//1表示绘制直线段
	isDraw = true;//初始状态为绘图状态
}

void CTest1View::OnDrawLine() 
{
	// TODO: Add your command handler code here
	drawType = 1;//1表示绘制直线段
	isDraw = true;//初始状态为绘图状态
}


/*----------------------------------------------------------------------------------------------------------------------------*/



void CTest1View::OnDRAWMultEdge() 
{
	// TODO: Add your command handler code here
	drawType = 4;//1表示绘制直线段
	isDraw = true;//初始状态为绘图状态
		int i,j;
	int white[14]={0,1,7,8,9,10,16,17,18,31,32,33,46,47};//2 的头部
	int redup[18]={2,3,4,5,6,11,12,13,14,15,27,28,29,30,42,43,44,45};//2的背部
	int reddown[18]={2,3,4,5,6,11,12,13,14,15,19,20,21,22,34,35,36,37};
	for(i=0;i<4;i++)
	{
		for(j=0;j<48;j++)
			pic[i][j] = RGB(255,255,255);
	}
	for(i=4;i<8;i++)
	{
		for(j=0;j<48;j++)
			if(find(white,14,j))
				pic[i][j]=RGB(255,255,255);
			else
				pic[i][j]=RGB(255,0,0);
	}
	for(i=8;i<22;i++)
	{
		for(j=0;j<48;j++)
			if(find(redup,18,j))
				pic[i][j]=RGB(255,0,0);
			else
				pic[i][j]=RGB(255,255,255);
	}
	for(i=22;i<26;i++)
	{
		for(j=0;j<48;j++)
			if(find(white,14,j))
				pic[i][j]=RGB(255,255,255);
			else
				pic[i][j]=RGB(255,0,0);
	}
	for(i=26;i<40;i++)
	{
		for(j=0;j<48;j++)
			if(find(reddown,18,j))
				pic[i][j]=RGB(255,0,0);
			else
				pic[i][j]=RGB(255,255,255);
	}
	for(i=40;i<44;i++)
	{
		for(j=0;j<48;j++)
			if(find(white,14,j))
				pic[i][j]=RGB(255,255,255);
			else
				pic[i][j]=RGB(255,0,0);
	}

	for(i=44;i<48;i++)
	{
		for(j=0;j<48;j++)
			pic[i][j] = RGB(255,255,255);
	}
}

void CTest1View::PatternFill(CDC *pDC, int x, int y, COLORREF pattern[][48], int m, int n)
{
	pDC->SetPixel(x,y,pattern[y%m][x%n]);
}

void CTest1View::On3dDraw() 
{
	drawType = 5;//1表示绘制直线段
	isDraw = true;//初始状态为绘图状态

	//////////////初始化立方体//////////////
	int a = 100;//正方体边长
	//float p1[8][3]={{0,0,50},{50,0,50},{50,0,0},{0,0,0},{0,50,50},{50,50,50},{50,50,0},{0,50,0}};
	float p2[8][3]={{0,0,a},{a,0,a},{a,0,0},{0,0,0},{0,a,a},{a,a,a},{a,a,0},{0,a,0}};

	cube = new Cube(p2);
	Invalidate(true);
}
 


void CTest1View::OnXjty() //斜交
{
	// TODO: Add your command handler code here	
	if(drawType!=5)
	{
		MessageBox("请先切换到立体图模式！","错误",MB_OK|MB_ICONHAND);
		return;
	}
	ProjectionType = 1;
	Invalidate(true);
}


void CTest1View::OnTsty() //透视
{
	// TODO: Add your command handler code here
	if(drawType!=5)
	{
		MessageBox("请先切换到立体图模式！","错误",MB_OK|MB_ICONHAND);
		return;
	}
	ProjectionType = 2;
	Invalidate(true);
}

void CTest1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(drawType!=5)
		return;
	switch(nChar)
	{
		int i;
		case VK_UP:
			for(i=0;i<8;i++)
				cube->tPoints[i].y+=cube->disp;
			break;
		case VK_DOWN:
			for(i=0;i<8;i++)
				cube->tPoints[i].y-=cube->disp;
			break;
		case VK_LEFT:
			for(i=0;i<8;i++)
				cube->tPoints[i].x-=cube->disp;
			break;
		case VK_RIGHT:
			for(i=0;i<8;i++)
				cube->tPoints[i].x+=cube->disp;
			break;
		case VK_PRIOR:
			for(i=0;i<8;i++)
				cube->tPoints[i].z+=cube->disp;
			break;
		case VK_NEXT:
			for(i=0;i<8;i++)
				cube->tPoints[i].z-=cube->disp;
			break;
		case 'X':
			{	
				float mx[4][4]={{1,0,0,0},{0,cos(cube->r),sin(cube->r),0},{0,-sin(cube->r),cos(cube->r),0},{0,0,0,1}};
				cube->RotationTrans(mx,cube);
				break;
			}
		case 'Y':
			{
				float my[4][4]={{cos(cube->r),0,-sin(cube->r),0},{0,1,0,0},{sin(cube->r),0,cos(cube->r),0},{0,0,0,1}};
				cube->RotationTrans(my,cube);
				break;
			}
		case 'Z':
			{
				float mz[4][4]={{cos(cube->r),sin(cube->r),0,0},{-sin(cube->r),cos(cube->r),0,0},{0,0,1,0},{0,0,0,1}};
				cube->RotationTrans(mz,cube);
				break;
			}
	}

	Invalidate(true);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}



BOOL CTest1View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if(drawType==5)
	{	
		float t = cube->rate;
		if(zDelta == -120)
			t = 1.0/cube->rate;
		for(int i=0;i<8;i++)
		{	
			cube->tPoints[i].x*=t;
			cube->tPoints[i].y*=t;
			cube->tPoints[i].z*=t;
		}
		Invalidate(true);
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CTest1View::OnSetdata() 
{
	if(drawType!=5)
	{
		MessageBox("请先切换到立体图模式！","错误",MB_OK|MB_ICONHAND);
		return;
	}
	SettingsDlg dlg;
	dlg.DoModal();

	Invalidate(true);
	
}

void CTest1View::OnCut() 
{
	// TODO: Add your command handler code here
	drawType = 6;//1表示绘制直线段
	isDraw = true;//初始状态为绘图状
	Invalidate();
}


void CTest1View::DrawRect(int type, CDC *pDC, CPoint p1, CPoint p2)
{
	CPen *mypen;
	if(type==1)
		mypen = new CPen(PS_SOLID, 2, RGB(0, 0, 255));
	else
		mypen = new CPen(PS_SOLID, 2, RGB(255, 255, 255));
	CPen *oldpen = pDC->SelectObject(mypen);

	pDC->MoveTo(p1);
	pDC->LineTo(p2.x,p1.y);
	pDC->MoveTo(p1);
	pDC->LineTo(p1.x,p2.y);

	pDC->MoveTo(p2);
	pDC->LineTo(p2.x,p1.y);
	pDC->MoveTo(p2);
	pDC->LineTo(p1.x,p2.y);
	
	pDC->SelectObject(oldpen);
	delete mypen;
}

/*------------------------------------------------------------------------------------------------------------------------*/


bool cansee(double q,double d, double *t0, double *t1)
{
	double r;
	if(q<0)
	{
		r=d/q;
		if(r>*t1)
			return false;
		else if(r>*t0)
			*t0=r;
	}
	else if(q>0)
	{
		r=d/q;
		if(r<*t0)
			return false;
		else if(r<*t1)
			*t1=r;
	}
	else if(d<0)
		return false;
	return true;
}


void ShowLine(CDC *pDC, double x0, double y0, double x2, double y2)
{
	CPen *mypen = new CPen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen *oldpen = pDC->SelectObject(mypen);

	pDC->MoveTo(x0,y0);
	pDC->LineTo(x2,y2);

	pDC->SelectObject(oldpen);
	delete mypen;
}

void CTest1View::L_Barsky(CDC *pDC, double x0, double y0, double x2, double y2) //梁友栋裁剪算法
{
	double xl = rectPointLU.x;
	double xr = rectPointRD.x;
	double yt = rectPointRD.y;
	double yb = rectPointLU.y;

	double t0,t1,dx,dy;
	t0=0.0;
	t1=1.0;
	dx=x2-x0;
	if(!cansee(-dx,x0-xl,&t0,&t1))
		return;
	if(!cansee(dx,xr-x0,&t0,&t1))
		return;
	dy=y2-y0;
	if(!cansee(-dy,y0-yb,&t0,&t1))
		return;
	if(!cansee(dy,yt-y0,&t0,&t1))
		return;

	x2=x0+t1*dx;
	y2=y0+t1*dy;
	x0=x0+t0*dx;
	y0=y0+t0*dy;

	ShowLine(pDC,x0,y0,x2,y2);
}



void CTest1View::FillColor(CDC *pDC)//填充裁剪后的可视区域
{
	bool MASK_RECT[rectPointRD.y-rectPointLU.y][rectPointRD.x-rectPointLU.x];
	for
}
