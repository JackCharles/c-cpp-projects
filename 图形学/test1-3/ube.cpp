// ube.cpp : implementation file

#include "stdafx.h"
#include "test1.h"
#include "ube.h"


CUBEPOINT Cube::ProjCent(300.1,300.1,300.1);
float Cube::disp = 2.1;
float Cube::rate = 1.1;
float Cube::angl = 30.1 ;
float Cube::r = angl/180.0*3.1416;


/********************************************************************************/

Cube::Cube(float p[][3])//构造函数
{
	int j = 0;
	for(int i=0;i<8;i++)
	{
		tPoints[i].x=p[i][j];
		j++;
		tPoints[i].y=p[i][j];
		j++;
		tPoints[i].z=p[i][j];
		j=0;
	}
	xoffset = 400; //默认坐标原点
	yoffset = 300;//默认投影中心

}

/********************************************************************************/

Cube::~Cube()//析构函数
{
}

/********************************************************************************/

void Cube::PerspectiveProjection(CDC *pDC)// 透视投影
{
	float tempIn[4],tempOut[4];
	DrawPoint(pDC,&ProjCent);
	Create_Pers_TM();

	for(int i=0;i<8;i++)
	{
		tempIn[0] = tPoints[i].x;
		tempIn[1] = tPoints[i].y;
		tempIn[2] = tPoints[i].z;
		tempIn[3] = 1;
		MatrixMult(tempIn,TransMatrix,tempOut);
		if(i<4)
		{
			ptUp[i].x = (long)(tempOut[0]/(tPoints[i].z/ProjCent.z+1))+xoffset;
			ptUp[i].y = yoffset-(long)(tempOut[1]/(tPoints[i].z/ProjCent.z+1));
		}
		else
		{
			ptDown[i-4].x = (long)(tempOut[0]/(tPoints[i].z/ProjCent.z+1))+xoffset;
			ptDown[i-4].y = yoffset-(long)(tempOut[1]/(tPoints[i].z/ProjCent.z+1));
		}
	}

	DrawCoor(pDC,400);

	CPen *mypen = new CPen(PS_SOLID, 2, RGB(0, 0, 255));
	DrawCube(pDC,mypen);
	delete mypen;

}

/********************************************************************************/

void Cube::ObliqueProjection(CDC *pDC)//斜交投影
{
	Create_Obli_TM(0.7854,0.5);
	float tempIn[4];
	float tempOut[4];

	for(int i=0;i<8;i++)
	{
		tempIn[0] = tPoints[i].x;
		tempIn[1] = tPoints[i].y;
		tempIn[2] = tPoints[i].z;
		tempIn[3] = 1;
		MatrixMult(tempIn,TransMatrix,tempOut);
		if(i<4)
		{
			ptUp[i].x = (long)tempOut[0]+xoffset;
			ptUp[i].y = yoffset-(long)tempOut[1];
		}
		else
		{
			ptDown[i-4].x = (long)tempOut[0]+xoffset;
			ptDown[i-4].y = yoffset-(long)tempOut[1];
		}
	}

	DrawCoor(pDC,400);//绘制坐标系	
	CPen *mypen = new CPen(PS_SOLID, 2, RGB(0, 0, 255));
	DrawCube(pDC,mypen);
	delete mypen;
}

/********************************************************************************/

void Cube::Create_Obli_TM(float a,float l)//创建斜交投影变换矩阵
{
	float temp[4][4] = {{1.0,0.0,0.0,0.0},{0.0,1.0,0.0,0.0},
	{l*cos(a),l*sin(a),0.0,0.0},{0.0,0.0,0.0,1.0}};
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			TransMatrix[i][j] = temp[i][j];
}

/********************************************************************************/

void Cube::MatrixMult(float in[], float m[][4], float out[])//矩阵乘法
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

/********************************************************************************/

void Cube::Create_Pers_TM()//生成透视投影矩阵(任意投影中心点)
{
	int temp[4][4] ={{1,0,0,0},{0,1,0,0},{ProjCent.x/ProjCent.z,ProjCent.y/ProjCent.z,0,1.0/ProjCent.z},{0,0,0,1}};
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			TransMatrix[i][j] = temp[i][j];
}

/********************************************************************************/

void Cube::DrawCoor(CDC *pDC, int zbx)//绘制坐标系
{
	CPen *mypen = new CPen(PS_DASHDOT, 1, RGB(128, 128, 128));
	CPen *oldPen = pDC->SelectObject(mypen);

	pDC->MoveTo(xoffset,yoffset);
	pDC->LineTo(xoffset+zbx,yoffset);
	pDC->MoveTo(xoffset,yoffset);
	pDC->LineTo(xoffset-zbx,yoffset);
	pDC->MoveTo(xoffset,yoffset);
	pDC->LineTo(xoffset,yoffset-zbx);
	pDC->MoveTo(xoffset,yoffset);
	pDC->LineTo(xoffset,yoffset+zbx);
	pDC->MoveTo(xoffset,yoffset);
	pDC->LineTo(xoffset-zbx,yoffset+zbx);
	pDC->MoveTo(xoffset,yoffset);
	pDC->LineTo(xoffset+zbx,yoffset-zbx);

	pDC->SelectObject(oldPen);
}

/********************************************************************************/

void Cube::DrawCube(CDC *pDC, CPen* pen)//绘制立体图
{
	CPen *oldPen = pDC->SelectObject(pen);
	for(int j=0;j<4;j++)//绘制投影图
	{
		//顶部四边形
		pDC->MoveTo(ptUp[j]);
		pDC->LineTo(ptUp[(j+1)%4]);
		//底部四边形
		pDC->MoveTo(ptDown[j]);
		pDC->LineTo(ptDown[(j+1)%4]);
		//上下相连
		pDC->MoveTo(ptDown[j]);
		pDC->LineTo(ptUp[j]);
	}
	pDC->SelectObject(oldPen);
}

void Cube::RotationTrans(float m[][4], Cube* cube)//旋转变换
{
	float in[4]={0,0,0,1},out[4];
	for(int i=0;i<8;i++)
	{
		in[0]=cube->tPoints[i].x;
		in[1]=cube->tPoints[i].y;
		in[2]=cube->tPoints[i].z;
		cube->MatrixMult(in,m,out);
		cube->tPoints[i].x=out[0];
		cube->tPoints[i].y=out[1];
		cube->tPoints[i].z=out[2];
	}
}

void Cube::DrawPoint(CDC *pDC, CUBEPOINT *pt)
{
	Create_Obli_TM(0.7854,0.5);
	float tempIn[4],tempOut[4];

	tempIn[0] = pt->x;
	tempIn[1] = pt->y;
	tempIn[2] = pt->z;
	tempIn[3] = 1;
	MatrixMult(tempIn,TransMatrix,tempOut);

	int x = (int)tempOut[0]+xoffset;
	int y = yoffset-(int)tempOut[1];

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
