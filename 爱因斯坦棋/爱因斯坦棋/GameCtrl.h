#pragma once
#include <windows.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include "resource.h"


struct Chessman					//棋子结构体
{
	bool flag;					//棋子是否存活
	int num;					//棋子点数
	int x, y;					//棋子坐标（基于像素点）
	int type;					//0:敌方1:我方（目前无用）
	HBITMAP hChessBitmap;		//位图句柄
};

//游戏控制类
class GameCtrl					
{
public:
	GameCtrl();
	~GameCtrl();
public:
	//处理paint消息
	void OnPaint();

	//处理定时器消息
	void OnTimer(UINT nTimerID);

	//处理鼠标左键按下
	void OnLButtonDown(POINT pt);

	//初始化游戏数据
	void InitGameDate();

	//设置数据（图形界面相关）
	void SetDataValue(HINSTANCE hInst,HWND hwnd);

	//显示棋盘
	void ShowChessMap(HDC hMemDC1);

	//显示棋子
	void ShowChessMan(HDC hMemDC1);

public://调试阶段
	HWND m_hwnd;				//窗口句柄
	HINSTANCE m_hInstance;		//程序实例对象句柄
	HBITMAP hChessMap;			//棋盘句柄
	HBITMAP hBackground;
	HBITMAP hDice[6];
	HBITMAP hCmpuTurn;
	HBITMAP hYourTurn;
	Chessman Red[6];			//红方棋子
	Chessman Blue[6];			//蓝方棋子
	int map[5][5];				//地图的数组表示	
	std::vector<int> vtr;		//向量（用于初始化开局）
	int SelectID;				//已选中棋子编号（指玩家）
	int nRand;					//模拟骰子
	int turn;					//0红方，1蓝方，-2已重置可开始,-1尚未重置


private:
	//获取随机数
	void GetRandom();

	void ShowDice(HDC hMemDC1);
	void ShowTurn(HDC hMemDC1);

	//判断是否可选中（针对玩家）
	bool CanSelect(POINT pt);

	//是否可以放置（针对玩家）
	bool CanPlace(POINT pt);

	//显示选中边框
	void ShowSelected(HDC hMemDC1);

	//放置棋子（针对玩家）
	void PlaceChessman(POINT pt);
	
	//是否有一方胜利
	bool WinTheGame();

	//重新开始
	void ResetGame();

//以下为电脑的走棋部分(此时已红方为己方，把玩家当做敌人)
private:
	int nRedLeftCount;		//己方剩余
	int nBlueLeftCount;		//敌方剩余
	int nRedOddCount;		//己方奇数个数
	int nBlueOddCount;		//敌方奇数个数
	int nRedEvenCount;		//己方偶数个数
	int nBlueEvenCount;		//敌方偶数个数
	bool CanFullClip;		//是否能全歼
	void StartGame(int num);//开局走法
	
	//bool返回是否执行成功
	void IsFullClip();		 //判断本次是否具有全歼能力
	bool ToDestWithOneStep(int index_x, int index_y,int num);//一步到终点
	bool FullClip(int index_x, int index_y,int num);		 //全歼
	void KillEnemy(int index_x, int index_y,int num, int type);//吃掉敌方棋子
	bool CanStartGame(int index_x, int index_y);
	bool NormalMove(int index_x, int index_y, int num);			//一般走法
	int ScanEnemy(int index_x, int index_y, int* down, int* right, int* rightDown);//扫描给定坐标周围能kill me的敌人数
	void EatRightDown(int index_x, int index_y, int num, int tnum0);
	void EatDown(int index_x, int index_y, int num, int tnum1);
	void EatRight(int index_x, int index_y, int num, int tnum2);
	void RightDownEmpty(int index_x, int index_y, int num);
	void DownEmpty(int index_x, int index_y, int num);
	void RightEmpty(int index_x, int index_y, int num);
	int IsExist(int num);

public:
	//电脑走棋
	bool ComputerTurn();

};

