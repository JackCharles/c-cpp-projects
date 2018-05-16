#include <windows.h>
#include "GameCtrl.h"

HINSTANCE g_hIns;
GameCtrl* g_oGameCtrl = new GameCtrl();

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR szCmdLine, int nCmdShow)
{
	LPSTR szAppName = TEXT("WTN");
	g_hIns = hInstance;
	HWND hwnd;
	MSG msg;
	WNDCLASS wcl;
	
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcl.hInstance = hInstance;
	wcl.lpfnWndProc = WinProc;
	wcl.lpszClassName = szAppName;
	wcl.lpszMenuName = NULL;
	wcl.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wcl))
	{
		MessageBox(NULL, "需要 Windows NT!", "错误", MB_OK);
		return 0;
	}
	
	RECT rect;//由于创建窗口指定的长宽为整个窗口而非客户区的大小，要精确定位客户区大小需要创建一个矩形结构
	SetRect(&rect, 0, 0, 700, 500);//通过设定矩形参数并调用AdjustWindowRect自动调整以适应不同显示设备
	AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, NULL);
	
	hwnd = CreateWindow(szAppName, 
		"爱恩斯坦棋", 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 
		(GetSystemMetrics(SM_CXSCREEN) - 700) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - 500) / 2,
		rect.right-rect.left, 
		rect.bottom-rect.top, 
		NULL, 
		NULL, 
		hInstance, 
		NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
		{
			g_oGameCtrl->SetDataValue(g_hIns, hwnd);
			g_oGameCtrl->InitGameDate();
			break;
		}

		case WM_CLOSE:
		{
			int x = MessageBox(hwnd, "你确定要退出?", "提示", MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2);
			if(x==IDCANCEL)//默认WM_CLOSE发送WM_DESTROY,如果取消关闭窗口则截断此消息
			{
				return 0;
			}
			break;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_PAINT:
			g_oGameCtrl->OnPaint();
			break;

		case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			g_oGameCtrl->OnLButtonDown(pt);
			break;
		}

		case WM_TIMER:
			//g_oGameCtrl->OnTimer(timerID);
			break;

	}

	return DefWindowProc(hwnd,message,wParam,lParam);
}