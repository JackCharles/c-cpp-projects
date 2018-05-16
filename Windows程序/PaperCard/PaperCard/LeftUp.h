#pragma once
#include "Cards.h"
#include "DownCards.h"


//左上角发牌区
class CLeftUp
{
public:
	CLeftUp();
	~CLeftUp();

private:
	List* m_pCloseCardsHead;//发牌区正面朝下的牌的链表头
	List* m_pCloseCardsRear;
	List* m_pOpenCardsHead;//发牌区正面朝上的牌的链表头
	List* m_pOpenCardsRear;
	HBITMAP m_hBackCardsBitmap;

public:
	bool m_bCanRecycle;//是否能回收牌
	

public:
	//加载牌
	void InitLeftUpCards(Cards cardsArr[], vector<int>& vtr, HINSTANCE hInstance);
	//显示牌
	void ShowLeftUpCards(HDC hMemDC);
	//能否打开牌
	bool CanOpenLeftUpCards(POINT pt);
	//打开牌
	void OpenLeftUpCards();
	//收起牌
	void CloseLeftUpCards();
	//左上方拿牌
	bool CanGetLeftUpCards(POINT pt);
	//拿牌
	void GetLeftUpCards(List* &pMouseLinkHead, List* &pMouseLinkRear);
	//归位
	void RecoverLeftUpCard(List* &pMouseLinkHead, List* &pMouseLinkRear);
};

