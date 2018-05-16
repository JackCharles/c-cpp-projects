#ifndef  CARDCTRL_H
#define  CARDCTRL_H
#include <windows.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include "Cards.h"
#include "DownCards.h"
#include "resource.h"
#include "RightUp.h"
#include "LeftUp.h"
using namespace std;

//Crtl类
class CCardCtrl
{
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;

	CDownCards m_oDownCards;//下方牌的实例对象
	CRightUp m_oRightUpCards;//右上角牌的对象
	CLeftUp m_oLeftUpCars;//左上角牌的对象

public:
    Cards m_cardsArr[52];//一副牌	
	vector<int> m_vtr;//STL中的向量，相当于动态数组（一个容器）	
	HBITMAP m_hBackGroundBit;//背景图句柄
	List* m_pMouseLinkHead;//鼠标链表头和尾
	List* m_pMouseLinkRear;

public:
	CCardCtrl();
	~CCardCtrl()
	{
		m_oDownCards.~CDownCards();
		m_oLeftUpCars.~CLeftUp();
		m_oRightUpCards.~CRightUp();
		delete m_pMouseLinkHead;
		delete m_pMouseLinkRear;
		delete[] m_cardsArr;
		m_vtr.~vector();
	}

public:
	//设置数据成员
	void SetDataValue(HWND hwnd,HINSTANCE hInstance);

	HWND GetHWnd(){return m_hWnd;}

	HINSTANCE GethInstance(){return m_hInstance;}

private:
    //加载牌
    void LoadCards();
	//显示鼠标上的牌
	void ShowMouseCards(HDC hMenDC);
	
	POINT m_LeftButtonDownPos;//记录鼠标按下位置
	POINT m_MouseMovePos;//记录鼠标移动位置

public:
	//初始化游戏数据
	void InitGameData();

	//处理paint消息
	void OnPaint();

	//处理定时器消息
	void OnTimer(UINT nTimerID);

	//处理键盘消息
	void OnKeyDown(UINT nKeyID);

	//处理鼠标左键按下
	void OnLButtonDown(POINT pt);

	//处理鼠标右键按下
	void OnRButtonDown(POINT pt);

	//处理鼠标左键抬起
	void OnLButtonUP(POINT pt);

	//处理鼠标右键抬起
	void OnRButtonUP(POINT pt);

	//处理鼠标移动
	void OnMouseMOve(POINT pt);
};




#endif
