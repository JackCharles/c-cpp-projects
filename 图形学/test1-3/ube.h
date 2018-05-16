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
	CUBEPOINT tPoints[8];//�����嶥��
	CPoint ptUp[4],ptDown[4];//�豸����ϵ�е�б��ͶӰ��
	int xoffset,yoffset;//�豸����ԭ��

	static CUBEPOINT ProjCent;//ͶӰ����(����͸��)
	static float disp;//λ��
	static float rate;//���ű���
	static float angl;//��ת�Ƕ�
	static float r;//����

public:
	void MatrixMult(float in[], float m[][4],float out[]);
	void PerspectiveProjection(CDC *pDC);//͸��ͶӰ
	void ObliqueProjection(CDC *pDC);//б��ͶӰ--ƽ��

public:
	float TransMatrix[4][4];
	void RotationTrans(float m[][4], Cube* cube);//��ת�任
	void Create_Obli_TM(float a, float l);//б��ͶӰ����
	void Create_Pers_TM(); //����͸��ͶӰ������z=dΪͶӰƽ�������ʾ
	void DrawCoor(CDC *pDC, int zbx);//��������ϵ
	void DrawCube(CDC *pDC, CPen* pen);//��������ͼ
	void DrawPoint(CDC *pDC, CUBEPOINT *pt);
};

#endif
