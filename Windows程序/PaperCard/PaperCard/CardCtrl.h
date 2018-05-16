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

//Crtl��
class CCardCtrl
{
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;

	CDownCards m_oDownCards;//�·��Ƶ�ʵ������
	CRightUp m_oRightUpCards;//���Ͻ��ƵĶ���
	CLeftUp m_oLeftUpCars;//���Ͻ��ƵĶ���

public:
    Cards m_cardsArr[52];//һ����	
	vector<int> m_vtr;//STL�е��������൱�ڶ�̬���飨һ��������	
	HBITMAP m_hBackGroundBit;//����ͼ���
	List* m_pMouseLinkHead;//�������ͷ��β
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
	//�������ݳ�Ա
	void SetDataValue(HWND hwnd,HINSTANCE hInstance);

	HWND GetHWnd(){return m_hWnd;}

	HINSTANCE GethInstance(){return m_hInstance;}

private:
    //������
    void LoadCards();
	//��ʾ����ϵ���
	void ShowMouseCards(HDC hMenDC);
	
	POINT m_LeftButtonDownPos;//��¼��갴��λ��
	POINT m_MouseMovePos;//��¼����ƶ�λ��

public:
	//��ʼ����Ϸ����
	void InitGameData();

	//����paint��Ϣ
	void OnPaint();

	//����ʱ����Ϣ
	void OnTimer(UINT nTimerID);

	//���������Ϣ
	void OnKeyDown(UINT nKeyID);

	//��������������
	void OnLButtonDown(POINT pt);

	//��������Ҽ�����
	void OnRButtonDown(POINT pt);

	//����������̧��
	void OnLButtonUP(POINT pt);

	//��������Ҽ�̧��
	void OnRButtonUP(POINT pt);

	//��������ƶ�
	void OnMouseMOve(POINT pt);
};




#endif
