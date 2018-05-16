#include <windows.h>
#include <math.h>
#include "resource.h"

#define CXWINDOW 300
#define CYWINDOW 300

POINT scrPoint;					//当前全局鼠标位置，左键按下有效
POINT cliPoint;                 //局部坐标
HWND hwnd;						//主窗口句柄
HHOOK myhook;					//钩子句柄
bool isLButtonDown = false;		//判断鼠标状态
HINSTANCE hIns;					//当前实例句柄

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
void OnPaint(HDC hdc, HWND hwnd);

/*--------------------------- Main函数 ---------------------------*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR szCmdLine, int iCmdShow)
{
	hIns = hInstance;
	LPTSTR szAppName = TEXT("MouseHook");
	MSG message;
	WNDCLASS wcl;       
	
	//创建窗口类
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

	//注册窗口类
	if (!RegisterClass(&wcl)) 
	{
		MessageBoxA(NULL, "This program requires Windows NT!", "ERROR", MB_OK | MB_ICONHAND);
		return -1;
	}

	//创建窗口
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

	//显示窗口
	ShowWindow(hwnd, iCmdShow); 
	
	//更新窗口 
	UpdateWindow(hwnd);  

	//消息循环
	while (GetMessage(&message, NULL, 0, 0)) 
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

/*--------------------------- windowProc函数 ---------------------------*/

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

/*--------------------------- 鼠标钩子处理函数 ---------------------------*/

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	LPMSLLHOOKSTRUCT p = (LPMSLLHOOKSTRUCT)lParam;
	if (nCode >= 0)
	{
		if (wParam == WM_MOUSEMOVE)//鼠标移动
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

/*--------------------------- 处理PAINT消息 ---------------------------*/

void OnPaint(HDC hdc, HWND hwnd)
{
	static POINT pts1[3] = { { 80,132 },{ 80,90 },{ 105,125 } }; //左耳朵
	static POINT pts2[3] = { { 200,132 },{ 200,90 },{ 175,125 } };

	//绘制脸部
	SelectObject(hdc, (HBRUSH)GetStockObject(GRAY_BRUSH));
	Ellipse(hdc, 50, 120, 230, 220); //对称轴x=140,y=170
	
	//绘制耳朵
	Polygon(hdc, pts1, 3);
	Polygon(hdc, pts2, 3);
	
	//绘制胡子
	for (int i = 0; i < 3; i++)
	{
		MoveToEx(hdc, 10, 165 + i * 10, NULL);
		LineTo(hdc, 80, 165 + i * 10);
		MoveToEx(hdc, 270, 165 + i * 10, NULL);
		LineTo(hdc, 200, 165 + i * 10);
	}
	
	//醒着的状态
	if (isLButtonDown)
	{
		//输出文本
		SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FIXED_PITCH, NULL));
		TextOut(hdc, 0, 0, TEXT("作者:仲杰 学号:21141122"), 17);
		TCHAR szBuffer[25] = { 0 };
		int len = wsprintf(szBuffer, TEXT("光标位置：x=%d, y=%d  "), scrPoint.x, scrPoint.y);
		TextOut(hdc, 0, 20, szBuffer, len);
		DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));

		//绘制眼眶
		SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		Ellipse(hdc, 100, 145, 120, 165);//外圆心(110,155),R=10
		Ellipse(hdc, 160, 145, 180, 165);//外圆心(170,155),R=10

		//计算坐标差
		int dx1 = cliPoint.x - 110;
		int dx2 = cliPoint.x - 170;
		int dy = cliPoint.y - 155;//两个圆心y一样

		//计算左眼球坐标
		double dist = sqrt(double(dx1*dx1) + double(dy*dy));//计算两点距离
		double delt = 5.0 / dist;//r=5,线段比例
		int ex = 110 + (int)(delt*(double)dx1);//计算眼球的圆心坐标
		int ey = 155 + (int)(delt*(double)dy);
		SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
		Ellipse(hdc, ex - 5, ey - 5, ex + 5, ey + 5);//绘制眼球

		//相同方法处理右眼球
		dist = sqrt(double(dx2*dx2) + double(dy*dy));
		delt = 5.0 / dist;
		ex = 170 + (int)(delt*(double)dx2);
		ey = 155 + (int)(delt*(double)dy);
		Ellipse(hdc, ex - 5, ey - 5, ex + 5, ey + 5);
		
		//绘制嘴巴
		Arc(hdc, 110, 160, 170, 200, 120, 190, 160, 190);
	}
	else//睡着的状态
	{
		MoveToEx(hdc, 100, 150, NULL);//眼睛
		LineTo(hdc, 120, 150);
		MoveToEx(hdc, 180, 150, NULL);
		LineTo(hdc, 160, 150);
		MoveToEx(hdc, 120, 190, NULL);//嘴巴
		LineTo(hdc, 160, 190);
	}
}