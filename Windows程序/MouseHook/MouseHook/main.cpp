#include <windows.h>
#include <math.h>
#include "resource.h"

#define CXWINDOW 300
#define CYWINDOW 300

POINT scrPoint;					//��ǰȫ�����λ�ã����������Ч
POINT cliPoint;                 //�ֲ�����
HWND hwnd;						//�����ھ��
HHOOK myhook;					//���Ӿ��
bool isLButtonDown = false;		//�ж����״̬
HINSTANCE hIns;					//��ǰʵ�����

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
void OnPaint(HDC hdc, HWND hwnd);

/*--------------------------- Main���� ---------------------------*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR szCmdLine, int iCmdShow)
{
	hIns = hInstance;
	LPTSTR szAppName = TEXT("MouseHook");
	MSG message;
	WNDCLASS wcl;       
	
	//����������
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wcl.hInstance = hInstance;
	wcl.lpfnWndProc = WinProc;
	wcl.lpszClassName = szAppName;
	wcl.lpszMenuName = NULL;
	wcl.style = CS_HREDRAW | CS_VREDRAW;

	//ע�ᴰ����
	if (!RegisterClass(&wcl)) 
	{
		MessageBoxA(NULL, "This program requires Windows NT!", "ERROR", MB_OK | MB_ICONHAND);
		return -1;
	}

	//��������
	hwnd = CreateWindow(szAppName, 
		TEXT("MouseHook-Test1"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		(GetSystemMetrics(SM_CXSCREEN) - CXWINDOW) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - CYWINDOW) / 2,
		CXWINDOW,
		CYWINDOW,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL);

	//��ʾ����
	ShowWindow(hwnd, iCmdShow); 
	
	//���´��� 
	UpdateWindow(hwnd);  

	//��Ϣѭ��
	while (GetMessage(&message, NULL, 0, 0)) 
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

/*--------------------------- windowProc���� ---------------------------*/

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg)
	{
		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			OnPaint(hdc, hwnd);
			EndPaint(hwnd, &ps);
			return 0;
		}

		case WM_LBUTTONDOWN:
		{
			isLButtonDown = true;
			myhook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hIns, NULL);

			if (myhook == NULL)
			{
				MessageBox(NULL, TEXT("Setting mouse hook failed!"), TEXT("ERROR"), MB_OK);
				return 0;
			}
			InvalidateRect(hwnd, NULL, true);
			return 0;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

/*--------------------------- ��깳�Ӵ����� ---------------------------*/

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	LPMSLLHOOKSTRUCT p = (LPMSLLHOOKSTRUCT)lParam;
	if (nCode >= 0)
	{
		if (wParam == WM_MOUSEMOVE)//����ƶ�
		{
			scrPoint = p->pt;
			cliPoint = p->pt;
			ScreenToClient(hwnd, &cliPoint);
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == WM_LBUTTONUP)
		{
			UnhookWindowsHookEx(myhook);
			isLButtonDown = false;
			InvalidateRect(hwnd, NULL, true);
			return 0;
		}
	}
	return CallNextHookEx(myhook, nCode, wParam, lParam);
}

/*--------------------------- ����PAINT��Ϣ ---------------------------*/

void OnPaint(HDC hdc, HWND hwnd)
{
	static POINT pts1[3] = { { 80,132 },{ 80,90 },{ 105,125 } }; //�����
	static POINT pts2[3] = { { 200,132 },{ 200,90 },{ 175,125 } };

	//��������
	SelectObject(hdc, (HBRUSH)GetStockObject(GRAY_BRUSH));
	Ellipse(hdc, 50, 120, 230, 220); //�Գ���x=140,y=170
	
	//���ƶ���
	Polygon(hdc, pts1, 3);
	Polygon(hdc, pts2, 3);
	
	//���ƺ���
	for (int i = 0; i < 3; i++)
	{
		MoveToEx(hdc, 10, 165 + i * 10, NULL);
		LineTo(hdc, 80, 165 + i * 10);
		MoveToEx(hdc, 270, 165 + i * 10, NULL);
		LineTo(hdc, 200, 165 + i * 10);
	}
	
	//���ŵ�״̬
	if (isLButtonDown)
	{
		//����ı�
		SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FIXED_PITCH, NULL));
		TextOut(hdc, 0, 0, TEXT("����:�ٽ� ѧ��:21141122"), 17);
		TCHAR szBuffer[25] = { 0 };
		int len = wsprintf(szBuffer, TEXT("���λ�ã�x=%d, y=%d  "), scrPoint.x, scrPoint.y);
		TextOut(hdc, 0, 20, szBuffer, len);
		DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));

		//�����ۿ�
		SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		Ellipse(hdc, 100, 145, 120, 165);//��Բ��(110,155),R=10
		Ellipse(hdc, 160, 145, 180, 165);//��Բ��(170,155),R=10

		//���������
		int dx1 = cliPoint.x - 110;
		int dx2 = cliPoint.x - 170;
		int dy = cliPoint.y - 155;//����Բ��yһ��

		//��������������
		double dist = sqrt(double(dx1*dx1) + double(dy*dy));//�����������
		double delt = 5.0 / dist;//r=5,�߶α���
		int ex = 110 + (int)(delt*(double)dx1);//���������Բ������
		int ey = 155 + (int)(delt*(double)dy);
		SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
		Ellipse(hdc, ex - 5, ey - 5, ex + 5, ey + 5);//��������

		//��ͬ��������������
		dist = sqrt(double(dx2*dx2) + double(dy*dy));
		delt = 5.0 / dist;
		ex = 170 + (int)(delt*(double)dx2);
		ey = 155 + (int)(delt*(double)dy);
		Ellipse(hdc, ex - 5, ey - 5, ex + 5, ey + 5);
		
		//�������
		Arc(hdc, 110, 160, 170, 200, 120, 190, 160, 190);
	}
	else//˯�ŵ�״̬
	{
		MoveToEx(hdc, 100, 150, NULL);//�۾�
		LineTo(hdc, 120, 150);
		MoveToEx(hdc, 180, 150, NULL);
		LineTo(hdc, 160, 150);
		MoveToEx(hdc, 120, 190, NULL);//���
		LineTo(hdc, 160, 190);
	}
}