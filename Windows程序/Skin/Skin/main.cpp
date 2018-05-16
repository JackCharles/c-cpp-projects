#include <windows.h>
#include <WindowsX.h>
#include "resource.h"

TCHAR szClassName[] = TEXT("MainClassName");
int cxWindow = 500;
int cyWindow = 300;
HINSTANCE hIns;
bool isLButtonDown = false;
LRESULT CALLBACK WindProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HRGN BitmapToRegion(HBITMAP hBmp, COLORREF cTransparentColor = 0, COLORREF cTolerance = 0x101010);

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	hIns = hThisInstance;
	HWND hwnd;
	MSG messages;
	WNDCLASSEX wincl;

	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindProc;
	wincl.style = CS_HREDRAW | CS_VREDRAW;
	wincl.cbSize = sizeof(WNDCLASSEX);
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	if (!RegisterClassEx(&wincl))
		return 0;

	hwnd = CreateWindowEx(0, szClassName, TEXT("Skin-Test"), WS_POPUP,
		(GetSystemMetrics(SM_CXSCREEN) - cxWindow) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - cyWindow) / 2,
		cxWindow, cyWindow, HWND_DESKTOP, NULL, hThisInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&messages, NULL, 0, 0))
	{
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}
	return messages.wParam;
}

LRESULT CALLBACK WindProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HBITMAP hBmp;
	static BITMAP bm;
	static HRGN hrgn;
	PAINTSTRUCT ps;
	HDC hdc, memDC;
	POINT pt;
	TCHAR str[50] = { 0 };
	int len;
	switch (message)
	{
		case WM_CREATE:
			hBmp = (HBITMAP)LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP1));
			GetObject(hBmp, sizeof(bm), &bm);
			SetWindowPos(hwnd, 0, 0, 0, bm.bmWidth, bm.bmHeight, SWP_NOMOVE | SWP_NOZORDER);
			hrgn = BitmapToRegion(hBmp, RGB(255, 255, 255),RGB(0,0,0));
			SetWindowRgn(hwnd, hrgn, TRUE);
			DeleteObject(hBmp);
			//到此为止只是选定了窗口区域，并没有显示图案
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			hBmp = (HBITMAP)LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP1));
			memDC = CreateCompatibleDC(hdc);
			SelectObject(memDC, hBmp);
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);
			DeleteObject(hBmp);
			ReleaseDC(hwnd, memDC);
			EndPaint(hwnd, &ps);
			return 0;

		case WM_LBUTTONDOWN:
			SetCursor(LoadCursor(NULL, IDC_HAND));
			//向操作系统发送消息模拟此时鼠标点击在标题栏上，由此实现移动
			SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
			UpdateWindow(hwnd);
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			return 0;

		case WM_CONTEXTMENU:
		{

			HMENU hroot = LoadMenu(hIns, MAKEINTRESOURCE(IDR_MENU1));//加载菜单资源
			HMENU hpop = GetSubMenu(hroot, 0);// 获取第一个弹出菜单   
			int px = GET_X_LPARAM(lParam);// 获取鼠标右击是的坐标
			int py = GET_Y_LPARAM(lParam);
			TrackPopupMenu(hpop, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON,
				px, py, 0, (HWND)wParam, NULL);//显示快捷菜单  
			DestroyMenu(hroot);// 用完后要销毁菜单资源  
		}
		return 0;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDM_MIN:
					SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
					break;
				case IDM_EXIT:
					SendMessage(hwnd, WM_CLOSE, NULL, NULL);
					break;
			}
		}
		return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}
}





// BitmapToRegion : Create a region from the "non-transparent" pixels of a bitma
// Author : Jean-Edouard Lachand-Robert, June 1998

// hBmp : Source bitma
// cTransparentColor : Color base for the "transparent" pixels (default is black
// cTolerance : Color tolerance for the "transparent" pixels

// A pixel is assumed to be transparent if the value of each of its 3 components (blue, green and red) is
// greater or equal to the corresponding value in cTransparentColor and is lower or equal to the
// corresponding value in cTransparentColor + cTolerance

HRGN BitmapToRegion(HBITMAP hBmp, COLORREF cTransparentColor, COLORREF cTolerance)
{
	HRGN hRgn = NULL;
	if (hBmp)
	{
		// Create a memory DC inside which we will scan the bitmap conten
		HDC hMemDC = CreateCompatibleDC(NULL);
		if (hMemDC)
		{
			// Get bitmap siz
			BITMAP bm;
			GetObject(hBmp, sizeof(bm), &bm);

			// Create a 32 bits depth bitmap and select it into the memory DC
			BITMAPINFOHEADER RGB32BITSBITMAPINFO = {
				sizeof(BITMAPINFOHEADER), // biSize
				bm.bmWidth, // biWidth;
				bm.bmHeight, // biHeight;
				1, // biPlanes;
				32, // biBitCount
				BI_RGB, // biCompression;
				0, // biSizeImage;
				0, // biXPelsPerMeter;
				0, // biYPelsPerMeter;
				0, // biClrUsed;
				0 // biClrImportant;
			};
			VOID * pbits32;
			HBITMAP hbm32 = CreateDIBSection(hMemDC, (BITMAPINFO *)&RGB32BITSBITMAPINFO, DIB_RGB_COLORS, &pbits32, NULL, 0);
			if (hbm32)
			{
				HBITMAP holdBmp = (HBITMAP)SelectObject(hMemDC, hbm32);

				// Create a DC just to copy the bitmap into the memory D
				HDC hDC = CreateCompatibleDC(hMemDC);
				if (hDC)
				{
					// Get how many bytes per row we have for the bitmap bits (rounded up to 32 bits
					BITMAP bm32;
					GetObject(hbm32, sizeof(bm32), &bm32);
					while (bm32.bmWidthBytes % 4)
						bm32.bmWidthBytes++;

					// Copy the bitmap into the memory D
					HBITMAP holdBmp = (HBITMAP)SelectObject(hDC, hBmp);
					BitBlt(hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hDC, 0, 0, SRCCOPY);

					// For better performances, we will use the ExtCreateRegion() function to create th
					// region. This function take a RGNDATA structure on entry. We will add rectangles b
					// amount of ALLOC_UNIT number in this structure
#define ALLOC_UNIT 100
					DWORD maxRects = ALLOC_UNIT;
					HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects));
					RGNDATA *pData = (RGNDATA *)GlobalLock(hData);
					pData->rdh.dwSize = sizeof(RGNDATAHEADER);
					pData->rdh.iType = RDH_RECTANGLES;
					pData->rdh.nCount = pData->rdh.nRgnSize = 0;
					SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);

					// Keep on hand highest and lowest values for the "transparent" pixel
					BYTE lr = GetRValue(cTransparentColor);
					BYTE lg = GetGValue(cTransparentColor);
					BYTE lb = GetBValue(cTransparentColor);
					BYTE hr = min(0xff, lr + GetRValue(cTolerance));
					BYTE hg = min(0xff, lg + GetGValue(cTolerance));
					BYTE hb = min(0xff, lb + GetBValue(cTolerance));

					// Scan each bitmap row from bottom to top (the bitmap is inverted vertically
					BYTE *p32 = (BYTE *)bm32.bmBits + (bm32.bmHeight - 1) * bm32.bmWidthBytes;
					for (int y = 0; y < bm.bmHeight; y++)
					{
						// Scan each bitmap pixel from left to righ
						for (int x = 0; x < bm.bmWidth; x++)
						{
							// Search for a continuous range of "non transparent pixels"
							int x0 = x;
							LONG *p = (LONG *)p32 + x;
							while (x < bm.bmWidth)
							{
								BYTE b = GetRValue(*p);
								if (b >= lr && b <= hr)
								{
									b = GetGValue(*p);
									if (b >= lg && b <= hg)
									{
										b = GetBValue(*p);
										if (b >= lb && b <= hb)
											// This pixel is "transparent"
											break;
									}
								}
								p++;
								x++;
							}

							if (x > x0)
							{
								// Add the pixels (x0, y) to (x, y+1) as a new rectangle in the regio
								if (pData->rdh.nCount >= maxRects)
								{
									GlobalUnlock(hData);
									maxRects += ALLOC_UNIT;
									hData = GlobalReAlloc(hData, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), GMEM_MOVEABLE);
									pData = (RGNDATA *)GlobalLock(hData);
								}
								RECT *pr = (RECT *)&pData->Buffer;
								SetRect(&pr[pData->rdh.nCount], x0, y, x, y + 1);
								if (x0 < pData->rdh.rcBound.left)
									pData->rdh.rcBound.left = x0;
								if (y < pData->rdh.rcBound.top)
									pData->rdh.rcBound.top = y;
								if (x > pData->rdh.rcBound.right)
									pData->rdh.rcBound.right = x;
								if (y + 1 > pData->rdh.rcBound.bottom)
									pData->rdh.rcBound.bottom = y + 1;
								pData->rdh.nCount++;

								// On Windows98, ExtCreateRegion() may fail if the number of rectangles is to
								// large (ie: > 4000). Therefore, we have to create the region by multiple steps
								if (pData->rdh.nCount == 2000)
								{
									HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
									if (hRgn)
									{
										CombineRgn(hRgn, hRgn, h, RGN_OR);
										DeleteObject(h);
									}
									else
										hRgn = h;
									pData->rdh.nCount = 0;
									SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);
								}
							}
						}

						// Go to next row (remember, the bitmap is inverted vertically
						p32 -= bm32.bmWidthBytes;
					}

					// Create or extend the region with the remaining rectangle
					HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
					if (hRgn)
					{
						CombineRgn(hRgn, hRgn, h, RGN_OR);
						DeleteObject(h);
					}
					else
						hRgn = h;

					// Clean u
					SelectObject(hDC, holdBmp);
					DeleteDC(hDC);
				}

				DeleteObject(SelectObject(hMemDC, holdBmp));
			}
			DeleteDC(hMemDC);
		}
	}
	return hRgn;
}