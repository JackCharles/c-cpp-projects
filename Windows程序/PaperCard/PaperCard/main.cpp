#include <windows.h>
#include "CardCtrl.h"

//�ص�����
LRESULT CALLBACK WindowsProcess (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

//����ֽ�ƶ���
CCardCtrl *g_oCardCtrl=new CCardCtrl();

HINSTANCE g_hIns;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    char* szCmdLine, int iCmdShow)
{
    g_hIns = hInstance;

    LPSTR    szAppName = TEXT ("PaperCard") ;
    HWND           hwnd ;//���ھ������
    MSG			msg ;/*��Ϣ��ṹ��*/
    WNDCLASS       wndclass ;/*������ṹ��*/

    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;//���ڷ��
    wndclass.lpfnWndProc   = WindowsProcess ;//���ڹ���,����ָ��
    wndclass.cbClsExtra    = 0 ;//�趨���������ڴ�(B)
    wndclass.cbWndExtra    = 0 ;//ͬ�ϣ�Ϊ����ʵ���������(B)
    wndclass.hInstance     = hInstance ;//��ʾ�ô��ڵľ��
    wndclass.hIcon         = LoadIcon (hInstance, MAKEINTRESOURCE(IDI_ICON1)) ;//����ͼ�꣨һ����С��ʱ��
    wndclass.hCursor       = LoadCursor (hInstance, MAKEINTRESOURCE(IDC_CURSOR1));//�������ָ��
    wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;//�ͻ����ı�����ɫ����ʽ�����û�ˢ����
    wndclass.lpszMenuName  = NULL ;//���ڲ˵��������Ӷ���˵�
    wndclass.lpszClassName = szAppName ;//����������

    /************************ע�ᴰ����*****************************/

    if (!RegisterClass (&wndclass))//ע�ᴰ���࣬���ú��������봰����ָ��
    {
        MessageBox (NULL, TEXT ("This program requires Windows NT!"),
                    szAppName, MB_ICONERROR) ;
        return 0 ;
    }


    /************************�������ڲ���¼���*********************/


    hwnd = CreateWindow (szAppName,                  // window class name����������һ����ע��Ĵ�����������Ԥ����Ŀ�������
                         TEXT ("ֽ��-���԰�"), // window caption���ڱ���
                         WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU,          // window style���ڷ��
                         (GetSystemMetrics(SM_CXSCREEN)- 750 ) / 2,    // initial x position���ڳ�ʼx����λ��
						 20,					     // initial y position     y
                         750,						 // initial x size��
                         700,						 // initial y size��
                         NULL,                       // parent window handleָ�򸸴��ڻ������ߵľ��
                         LoadMenu(hInstance, MAKEINTRESOURCE(MainMenu)),                       // window menu handle�˵����
                         hInstance,                  // program instance handle�봰�ڹ�����ʾ�����
                         NULL) ;                     // creation parameter��������

    /***********************��ʾ����*******************************/
    ShowWindow (hwnd, iCmdShow) ;

    /**********************���´���*********************************/
    UpdateWindow (hwnd) ;


    /***********************��Ϣѭ��********************************/
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
    case WM_CREATE://���ڴ���
        g_oCardCtrl->SetDataValue(hwnd, g_hIns);

        //��Ϸ��ʼ��
        g_oCardCtrl->InitGameData();
        break;

    case WM_PAINT:
		
        g_oCardCtrl->OnPaint();
        break;

    case WM_LBUTTONDOWN://�������(�������)lParam
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
		
        g_oCardCtrl->OnLButtonDown(pt);
		SetCapture(hwnd);
        break;


    case WM_LBUTTONUP://�������(���̧��)lParam
    {
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        g_oCardCtrl->OnLButtonUP(pt);
		ReleaseCapture();
        break;
    }

    case WM_MOUSEMOVE://����ƶ�lParam
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
				if (MessageBox(hwnd, "ȷ��Ҫ���¿�ʼ?", "��ʾ", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
				{
					//��Ϸ��ʼ��
					delete g_oCardCtrl;
					g_oCardCtrl = new CCardCtrl();

					g_oCardCtrl->InitGameData();
				}
				break;*/

			case Help:
				MessageBox(hwnd, "�Լ���", "����", MB_OK);
				break;

			case About:
				MessageBox(hwnd, "ûɶ˵��", "����", MB_OK);
				break;
		}
		break;
	}


    case WM_CLOSE://���ڹر�
        if(MessageBox(hwnd, "ȷ��Ҫ�˳�?", "��ʾ", MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2) == IDNO)
            return 0;
        break;

    case WM_DESTROY://��������
        PostQuitMessage (0) ;
        break;
    }

    return DefWindowProc (hwnd, message, wParam, lParam) ;
}
