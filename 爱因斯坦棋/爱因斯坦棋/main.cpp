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
		MessageBox(NULL, "��Ҫ Windows NT!", "����", MB_OK);
		return 0;
	}
	
	RECT rect;//���ڴ�������ָ���ĳ���Ϊ�������ڶ��ǿͻ����Ĵ�С��Ҫ��ȷ��λ�ͻ�����С��Ҫ����һ�����νṹ
	SetRect(&rect, 0, 0, 700, 500);//ͨ���趨���β���������AdjustWindowRect�Զ���������Ӧ��ͬ��ʾ�豸
	AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, NULL);
	
	hwnd = CreateWindow(szAppName, 
		"����˹̹��", 
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
			int x = MessageBox(hwnd, "��ȷ��Ҫ�˳�?", "��ʾ", MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2);
			if(x==IDCANCEL)//Ĭ��WM_CLOSE����WM_DESTROY,���ȡ���رմ�����ضϴ���Ϣ
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