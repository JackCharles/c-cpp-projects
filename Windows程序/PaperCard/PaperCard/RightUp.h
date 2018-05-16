#pragma once
#include "Cards.h"
#include "resource.h"
#include "DownCards.h"
#include <windows.h>

//���Ͻǲ��ֵ���
class CRightUp
{
public:
	CRightUp();
	~CRightUp();

private:
	HBITMAP m_hRightUpBackBmp;

private:
	List* m_pRightUpHead[4];//���Ͻ�4��������Ϊ��ֹ��һ����
	List* m_pRightUpRear[4];

	int m_nLinkID;//��¼�ж�����������ڷ���
	int m_nGetCardLinkID;//��¼�ж������Ƶ�����ID�ţ��������ƺͻָ�

public:
	//��ʼ��
	void InitRightUpCards(HINSTANCE hInstance);
	//��ʾ��
	void ShowRightUpCards(HDC hMemDC);
	//���Ͻ��ܲ��ܽ�����
	bool CanRightReceiveCard(POINT pt, List* pMouseLinkHead);
	//������,����һ��DownCards�����Ӧ�����ڷ��·�����
	void RightReceiveCard(List* &pMouseLinkHead, List* &pMouseLinkRear,CDownCards& oDownCards);
	//���Ͻ��Ƿ�������
	bool CanGetCard(POINT pt);
	//����
	void GetRightCard(List* &pMouseLinkHead, List* &pMouseLinkRear);
	//�ָ�
	void RecoverRightUpCard(List* &pMouseLinkHead, List* &pMouseLinkRear);
	//�Ƿ�ʤ��
	bool IsWinTheGame();
};

