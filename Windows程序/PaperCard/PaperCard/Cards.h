#ifndef CARDS_H_INCLUDED
#define CARDS_H_INCLUDED
#include <windows.h>

//��ɫö��
enum{enum_cards_heart,enum_cards_black,enum_cards_square,enum_cards_flower};//0,1,2,3

//���忨Ƭ�ṹ��
struct Cards
{
    int m_nCardsNum;//����
    int m_nCardsColor;//��ɫ
    HBITMAP m_hCardsBitMap;//λͼ���


};


//����ڵ�
struct List
{
	Cards m_Cards;//һ����
	bool bflag;//������
	int m_x;//�Ƶ�����
	int m_y;
	List *m_pNext;//��һ����
	List *m_pPre;//��һ����
};

#endif // CARDS_H_INCLUDED
