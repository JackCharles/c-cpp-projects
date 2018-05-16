#pragma once
#include "cards.h"
#include <vector>
using namespace std;

class CDownCards
{
public:
	CDownCards();

public:
	~CDownCards();

private:
	//定义链表数组
	List* m_pCardsHead[7];//7个头
	List* m_pCardsRear[7];//7个尾

	//反面牌
	HBITMAP m_hBackCardsBitmap;
public:
	//加载下方的牌
	void LoadDownCards(Cards cardsArr[],vector<int>& vtr,HINSTANCE hInstance);
	//显示下方的牌
	void ShowDownCards(HDC hMemDC);

	//接口
	List* GetDownCardsRear(int nLinkID)
	{
		return m_pCardsRear[nLinkID];
	}
public:
	//
	List* m_pTemp;//记录原始链表在鼠标点击位置对应的结点，方便断开和尾指针的恢复
	int m_nLinkID;//记录鼠标所选的链表号，方便接收位置无效时原始链表的恢复和有效时原始链表的更新

	int m_nReceiveLinkID;//记录接受链表号,方便放牌
public:
	//鼠标是否能拿牌
	bool CanMouseGetCard(POINT pt);
	//鼠标拿牌
	void MouseGetCard(List* &pMouseLinkHead, List* &pMouseLinkRear);
	//判断鼠标所在位置是否能接受牌
	bool CanReceiveCards(POINT pt,List* pMouseLinkHead);
	//目标链表接受牌
	void ReceiveCards(List* &pMouseLinkHead, List* &pMouseLinkRear);
	//还原牌
	void RecoverCards(List* &pMouseLinkHead, List* &pMouseLinkRear);
};

