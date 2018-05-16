#include <windows.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*somthing user defined*/
#define SHADOWWIDTH 5

int cxWindow = 500;
int cyWindow = 300;
HINSTANCE hIns;
HWND hShadowWnd;
HWND hParentWnd;
LPTSTR szShadowClassName = TEXT("ShadowClass");
bool myRegisterClass();
bool CreateShadow(int bAlpha);
bool UpdateShadow();

/*  Make the class name into a global variable  */
TCHAR szClassName[] = TEXT("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszArgument,
	int nCmdShow)
{
	hIns = hThisInstance;
	HWND hwnd;               /* This is the handle for our window */
	MSG messages;            /* Here messages to the application are saved */
	WNDCLASSEX wincl;        /* Data structure for the windowclass */

	/* The Window structure */
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof(WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
	/* Use Windows's default colour as the background of the window */
	wincl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassEx(&wincl))
		return 0;

	/* The class is registered, let's create the program*/
	hParentWnd=hwnd = CreateWindowEx(
		0,                   /* Extended possibilites for variation */
		szClassName,         /* Classname */
		TEXT("Shadow"),       /* Title Text */
		WS_OVERLAPPEDWINDOW, /* default window */
		(GetSystemMetrics(SM_CXSCREEN) - cxWindow) / 2,       /* Windows decides the position */
		(GetSystemMetrics(SM_CYSCREEN) - cyWindow) / 2,       /* where the window ends up on the screen */
		cxWindow,                 /* The programs width */
		cyWindow,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		hThisInstance,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
	);

	/* Make the window visible on the screen */
	ShowWindow(hwnd, nCmdShow);

	/* Run the message loop. It will run until GetMessage() returns 0 */
	while (GetMessage(&messages, NULL, 0, 0))
	{
		/* Translate virtual-key messages into character messages */
		TranslateMessage(&messages);
		/* Send message to WindowProcedure */
		DispatchMessage(&messages);
	}

	/* The program return-value is 0 - The value that PostQuitMessage() gave */
	return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rt;
	switch (message)                   /* handle the messages */
	{
		case WM_CREATE:
			if (!myRegisterClass())
			{
				MessageBox(NULL, TEXT("Register shadow window class failed!"), TEXT("ERROR"), MB_OK);
				return 0;
			}
			CreateShadow(128);
			UpdateShadow();
			break;

		case WM_MOVE:
			GetWindowRect(hwnd, &rt);
			//当SWP_NOSIZE存在时0,0无效，阴影窗口根据主窗口位置决定
			SetWindowPos(hShadowWnd, NULL, rt.left-SHADOWWIDTH, rt.top-SHADOWWIDTH, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
			UpdateShadow();
			return 0;

		case WM_SIZE:
			GetWindowRect(hwnd, &rt);
			SetWindowPos(hShadowWnd, NULL, rt.left-SHADOWWIDTH, rt.top - SHADOWWIDTH,
				rt.right-rt.left+2*SHADOWWIDTH, rt.bottom - rt.top+ 2 * SHADOWWIDTH, SWP_NOACTIVATE);
			UpdateShadow();
			return 0;
	
		case WM_DESTROY:
			PostQuitMessage(0);        /* send a WM_QUIT to the message queue */
			break;
		default:                      /* for messages that we don't deal with */
			return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}


bool myRegisterClass()
{
	WNDCLASSEX wcl;
	wcl.cbClsExtra = 0;
	wcl.cbSize = sizeof(wcl);
	wcl.cbWndExtra = 0;
	wcl.hbrBackground = (HBRUSH)COLOR_WINDOW + 1; //black
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hIcon = NULL;
	wcl.hIconSm = NULL;
	wcl.hInstance = hIns;
	wcl.lpfnWndProc = DefWindowProc;
	wcl.lpszClassName = szShadowClassName;
	wcl.lpszMenuName = NULL;
	wcl.style = CS_HREDRAW | CS_VREDRAW;

	return RegisterClassEx(&wcl);
}

bool CreateShadow(int bAlpha)
{
	hShadowWnd = CreateWindowEx(WS_EX_LAYERED | WS_EX_TRANSPARENT,
		szShadowClassName, NULL, WS_POPUPWINDOW,
		(GetSystemMetrics(SM_CXSCREEN) - cxWindow) / 2 - SHADOWWIDTH,
		(GetSystemMetrics(SM_CYSCREEN) - cyWindow) / 2 - SHADOWWIDTH,
		cxWindow + 2*SHADOWWIDTH, cyWindow + 2*SHADOWWIDTH,
		hParentWnd, NULL, hIns, NULL);
	if (hShadowWnd == NULL)
		return false;
	//窗口句柄,掩码颜色,不透明度,透明方式
	SetLayeredWindowAttributes(hShadowWnd, RGB(255, 255, 255),
		bAlpha, LWA_ALPHA | LWA_COLORKEY);
	ShowWindow(hShadowWnd, SW_SHOW);
	return true;
}


bool UpdateShadow()
{
	//注意：这里采用阴影窗口左上角为原点，主窗口随之而变，但阴影窗口大小需通过主窗口计算
	//如果以主窗口左上角为原点，则阴影窗口矩形区域会产生负值，不采用此方法
	RECT rt;
	GetWindowRect(hParentWnd, &rt);
	HRGN hrPartentRgn = CreateRectRgn(SHADOWWIDTH+7, SHADOWWIDTH, rt.right - rt.left-2, rt.bottom - rt.top-3);//？？？？为什么会有偏差
	HRGN hrShadowRgn = CreateRoundRectRgn(0, 0, rt.right - rt.left + 2 * SHADOWWIDTH, rt.bottom - rt.top + 2 * SHADOWWIDTH, 20, 20);
	CombineRgn(hrShadowRgn, hrShadowRgn ,hrPartentRgn, RGN_DIFF);
	SetWindowRgn(hShadowWnd, hrShadowRgn, true);

	UpdateWindow(hShadowWnd);
	DeleteObject(hrPartentRgn);
	DeleteObject(hrShadowRgn);

	return true;
}
