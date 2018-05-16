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
	//������������
	List* m_pCardsHead[7];//7��ͷ
	List* m_pCardsRear[7];//7��β

	//������
	HBITMAP m_hBackCardsBitmap;
public:
	//�����·�����
	void LoadDownCards(Cards cardsArr[],vector<int>& vtr,HINSTANCE hInstance);
	//��ʾ�·�����
	void ShowDownCards(HDC hMemDC);

	//�ӿ�
	List* GetDownCardsRear(int nLinkID)
	{
		return m_pCardsRear[nLinkID];
	}
public:
	//
	List* m_pTemp;//��¼ԭʼ�����������λ�ö�Ӧ�Ľ�㣬����Ͽ���βָ��Ļָ�
	int m_nLinkID;//��¼�����ѡ������ţ��������λ����Чʱԭʼ����Ļָ�����Чʱԭʼ����ĸ���

	int m_nReceiveLinkID;//��¼���������,�������
public:
	//����Ƿ�������
	bool CanMouseGetCard(POINT pt);
	//�������
	void MouseGetCard(List* &pMouseLinkHead, List* &pMouseLinkRear);
	//�ж��������λ���Ƿ��ܽ�����
	bool CanReceiveCards(POINT pt,List* pMouseLinkHead);
	//Ŀ�����������
	void ReceiveCards(List* &pMouseLinkHead, List* &pMouseLinkRear);
	//��ԭ��
	void RecoverCards(List* &pMouseLinkHead, List* &pMouseLinkRear);
};

