#ifndef CARDS_H_INCLUDED
#define CARDS_H_INCLUDED
#include <windows.h>

//花色枚举
enum{enum_cards_heart,enum_cards_black,enum_cards_square,enum_cards_flower};//0,1,2,3

//定义卡片结构体
struct Cards
{
    int m_nCardsNum;//点数
    int m_nCardsColor;//花色
    HBITMAP m_hCardsBitMap;//位图句柄


};


//链表节点
struct List
{
	Cards m_Cards;//一张牌
	bool bflag;//正反面
	int m_x;//牌的坐标
	int m_y;
	List *m_pNext;//下一张牌
	List *m_pPre;//上一张牌
};

#endif // CARDS_H_INCLUDED
