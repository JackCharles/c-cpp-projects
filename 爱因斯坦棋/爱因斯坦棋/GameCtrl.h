#pragma once
#include <windows.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include "resource.h"


struct Chessman					//���ӽṹ��
{
	bool flag;					//�����Ƿ���
	int num;					//���ӵ���
	int x, y;					//�������꣨�������ص㣩
	int type;					//0:�з�1:�ҷ���Ŀǰ���ã�
	HBITMAP hChessBitmap;		//λͼ���
};

//��Ϸ������
class GameCtrl					
{
public:
	GameCtrl();
	~GameCtrl();
public:
	//����paint��Ϣ
	void OnPaint();

	//����ʱ����Ϣ
	void OnTimer(UINT nTimerID);

	//��������������
	void OnLButtonDown(POINT pt);

	//��ʼ����Ϸ����
	void InitGameDate();

	//�������ݣ�ͼ�ν�����أ�
	void SetDataValue(HINSTANCE hInst,HWND hwnd);

	//��ʾ����
	void ShowChessMap(HDC hMemDC1);

	//��ʾ����
	void ShowChessMan(HDC hMemDC1);

public://���Խ׶�
	HWND m_hwnd;				//���ھ��
	HINSTANCE m_hInstance;		//����ʵ��������
	HBITMAP hChessMap;			//���̾��
	HBITMAP hBackground;
	HBITMAP hDice[6];
	HBITMAP hCmpuTurn;
	HBITMAP hYourTurn;
	Chessman Red[6];			//�췽����
	Chessman Blue[6];			//��������
	int map[5][5];				//��ͼ�������ʾ	
	std::vector<int> vtr;		//���������ڳ�ʼ�����֣�
	int SelectID;				//��ѡ�����ӱ�ţ�ָ��ң�
	int nRand;					//ģ������
	int turn;					//0�췽��1������-2�����ÿɿ�ʼ,-1��δ����


private:
	//��ȡ�����
	void GetRandom();

	void ShowDice(HDC hMemDC1);
	void ShowTurn(HDC hMemDC1);

	//�ж��Ƿ��ѡ�У������ң�
	bool CanSelect(POINT pt);

	//�Ƿ���Է��ã������ң�
	bool CanPlace(POINT pt);

	//��ʾѡ�б߿�
	void ShowSelected(HDC hMemDC1);

	//�������ӣ������ң�
	void PlaceChessman(POINT pt);
	
	//�Ƿ���һ��ʤ��
	bool WinTheGame();

	//���¿�ʼ
	void ResetGame();

//����Ϊ���Ե����岿��(��ʱ�Ѻ췽Ϊ����������ҵ�������)
private:
	int nRedLeftCount;		//����ʣ��
	int nBlueLeftCount;		//�з�ʣ��
	int nRedOddCount;		//������������
	int nBlueOddCount;		//�з���������
	int nRedEvenCount;		//����ż������
	int nBlueEvenCount;		//�з�ż������
	bool CanFullClip;		//�Ƿ���ȫ��
	void StartGame(int num);//�����߷�
	
	//bool�����Ƿ�ִ�гɹ�
	void IsFullClip();		 //�жϱ����Ƿ����ȫ������
	bool ToDestWithOneStep(int index_x, int index_y,int num);//һ�����յ�
	bool FullClip(int index_x, int index_y,int num);		 //ȫ��
	void KillEnemy(int index_x, int index_y,int num, int type);//�Ե��з�����
	bool CanStartGame(int index_x, int index_y);
	bool NormalMove(int index_x, int index_y, int num);			//һ���߷�
	int ScanEnemy(int index_x, int index_y, int* down, int* right, int* rightDown);//ɨ�����������Χ��kill me�ĵ�����
	void EatRightDown(int index_x, int index_y, int num, int tnum0);
	void EatDown(int index_x, int index_y, int num, int tnum1);
	void EatRight(int index_x, int index_y, int num, int tnum2);
	void RightDownEmpty(int index_x, int index_y, int num);
	void DownEmpty(int index_x, int index_y, int num);
	void RightEmpty(int index_x, int index_y, int num);
	int IsExist(int num);

public:
	//��������
	bool ComputerTurn();

};

