#pragma once
#include "Cards.h"
#include "resource.h"
#include "DownCards.h"
#include <windows.h>

//右上角部分的类
class CRightUp
{
public:
	CRightUp();
	~CRightUp();

private:
	HBITMAP m_hRightUpBackBmp;

private:
	List* m_pRightUpHead[4];//右上角4个链表，因为不止存一张牌
	List* m_pRightUpRear[4];

	int m_nLinkID;//记录判定的链表号用于放牌
	int m_nGetCardLinkID;//记录判定可拿牌的链表ID号，用于拿牌和恢复

public:
	//初始化
	void InitRightUpCards(HINSTANCE hInstance);
	//显示牌
	void ShowRightUpCards(HDC hMemDC);
	//右上角能不能接收牌
	bool CanRightReceiveCard(POINT pt, List* pMouseLinkHead);
	//接收牌,传入一个DownCards对象的应用用于翻下方的牌
	void RightReceiveCard(List* &pMouseLinkHead, List* &pMouseLinkRear,CDownCards& oDownCards);
	//左上角是否能拿牌
	bool CanGetCard(POINT pt);
	//拿牌
	void GetRightCard(List* &pMouseLinkHead, List* &pMouseLinkRear);
	//恢复
	void RecoverRightUpCard(List* &pMouseLinkHead, List* &pMouseLinkRear);
	//是否胜利
	bool IsWinTheGame();
};

