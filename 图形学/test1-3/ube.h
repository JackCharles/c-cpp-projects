#if !defined(AFX_UBE_H__1CD3D40B_42B1_465F_A21C_E2F01B5DC013__INCLUDED_)
#define AFX_UBE_H__1CD3D40B_42B1_465F_A21C_E2F01B5DC013__INCLUDED_
#include "math.h"

typedef struct tdpoint
{
	float x;
	float y;
	float z;
	tdpoint(float nx =0 , float ny=0,float nz =0)
	{
		x=nx;y=ny;z=nz;
	}
}CUBEPOINT;


class Cube
{
public:
	Cube(float p[][3]);
	~Cube();
public:
	CUBEPOINT tPoints[8];//立方体顶点
	CPoint ptUp[4],ptDown[4];//设备坐标系中的斜交投影点
	int xoffset,yoffset;//设备坐标原点

	static CUBEPOINT ProjCent;//投影中心(单点透视)
	static float disp;//位移
	static float rate;//缩放比率
	static float angl;//旋转角度
	static float r;//弧度

public:
	void MatrixMult(float in[], float m[][4],float out[]);
	void PerspectiveProjection(CDC *pDC);//透视投影
	void ObliqueProjection(CDC *pDC);//斜交投影--平行

public:
	float TransMatrix[4][4];
	void RotationTrans(float m[][4], Cube* cube);//旋转变换
	void Create_Obli_TM(float a, float l);//斜交投影矩阵
	void Create_Pers_TM(); //单点透视投影矩阵，以z=d为投影平面进行演示
	void DrawCoor(CDC *pDC, int zbx);//绘制坐标系
	void DrawCube(CDC *pDC, CPen* pen);//绘制立体图
	void DrawPoint(CDC *pDC, CUBEPOINT *pt);
};

#endif
