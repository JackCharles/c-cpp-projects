#include <windows.h>
#include "CardCtrl.h"

//回调函数
LRESULT CALLBACK WindowsProcess (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

//定义纸牌对象
CCardCtrl *g_oCardCtrl=new CCardCtrl();

HINSTANCE g_hIns;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    char* szCmdLine, int iCmdShow)
{
    g_hIns = hInstance;

    LPSTR    szAppName = TEXT ("PaperCard") ;
    HWND           hwnd ;//窗口句柄变量
    MSG			msg ;/*消息类结构体*/
    WNDCLASS       wndclass ;/*窗口类结构体*/

    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;//窗口风格
    wndclass.lpfnWndProc   = WindowsProcess ;//窗口过程,函数指针
    wndclass.cbClsExtra    = 0 ;//设定额外分配的内存(B)
    wndclass.cbWndExtra    = 0 ;//同上，为窗口实例额外分配(B)
    wndclass.hInstance     = hInstance ;//标示该窗口的句柄
    wndclass.hIcon         = LoadIcon (hInstance, MAKEINTRESOURCE(IDI_ICON1)) ;//窗口图标（一般最小化时）
    wndclass.hCursor       = LoadCursor (hInstance, MAKEINTRESOURCE(IDC_CURSOR1));//加载鼠标指针
    wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;//客户区的背景颜色和样式，调用画刷工具
    wndclass.lpszMenuName  = NULL ;//窗口菜单句柄，添加额外菜单
    wndclass.lpszClassName = szAppName ;//窗口类名称

    /************************注册窗口类*****************************/

    if (!RegisterClass (&wndclass))//注册窗口类，调用函数，传入窗口类指针
    {
        MessageBox (NULL, TEXT ("This program requires Windows NT!"),
                    szAppName, MB_ICONERROR) ;
        return 0 ;
    }


    /************************创建窗口并记录句柄*********************/


    hwnd = CreateWindow (szAppName,                  // window class name窗口类名，一般用注册的窗口类名或者预定义的控制类名
                         TEXT ("纸牌-测试版"), // window caption窗口标题
                         WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU,          // window style窗口风格
                         (GetSystemMetrics(SM_CXSCREEN)- 750 ) / 2,    // initial x position窗口初始x坐标位置
						 20,					     // initial y position     y
                         750,						 // initial x size宽
                         700,						 // initial y size高
                         NULL,                       // parent window handle指向父窗口或所有者的句柄
                         LoadMenu(hInstance, MAKEINTRESOURCE(MainMenu)),                       // window menu handle菜单句柄
                         hInstance,                  // program instance handle与窗口关联的示例句柄
                         NULL) ;                     // creation parameter创建参数

    /***********************显示窗口*******************************/
    ShowWindow (hwnd, iCmdShow) ;

    /**********************更新窗口*********************************/
    UpdateWindow (hwnd) ;


    /***********************消息循环********************************/
    while (GetMessage (&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }

    return msg.wParam ;
}

LRESULT CALLBACK WindowsProcess (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE://窗口创建
        g_oCardCtrl->SetDataValue(hwnd, g_hIns);

        //游戏初始化
        g_oCardCtrl->InitGameData();
        break;

    case WM_PAINT:
		
        g_oCardCtrl->OnPaint();
        break;

    case WM_LBUTTONDOWN://鼠标坐标(左键按下)lParam
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
		
        g_oCardCtrl->OnLButtonDown(pt);
		SetCapture(hwnd);
        break;


    case WM_LBUTTONUP://鼠标坐标(左键抬起)lParam
    {
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        g_oCardCtrl->OnLButtonUP(pt);
		ReleaseCapture();
        break;
    }

    case WM_MOUSEMOVE://鼠标移动lParam
    {
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        g_oCardCtrl->OnMouseMOve(pt);
        break;
    }

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			/*case Restart:
				if (MessageBox(hwnd, "确定要重新开始?", "提示", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
				{
					//游戏初始化
					delete g_oCardCtrl;
					g_oCardCtrl = new CCardCtrl();

					g_oCardCtrl->InitGameData();
				}
				break;*/

			case Help:
				MessageBox(hwnd, "自己想", "帮助", MB_OK);
				break;

			case About:
				MessageBox(hwnd, "没啥说的", "关于", MB_OK);
				break;
		}
		break;
	}


    case WM_CLOSE://窗口关闭
        if(MessageBox(hwnd, "确定要退出?", "提示", MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2) == IDNO)
            return 0;
        break;

    case WM_DESTROY://窗口销毁
        PostQuitMessage (0) ;
        break;
    }

    return DefWindowProc (hwnd, message, wParam, lParam) ;
}
