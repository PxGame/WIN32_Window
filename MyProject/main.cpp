# include "main.h"

LPCTSTR g_lptszClassName = TEXT("WndClass");
const int g_nScrWidth = GetSystemMetrics(SM_CXSCREEN);
const int g_nScrHeight = GetSystemMetrics(SM_CYSCREEN);

HWND g_hMainWnd = NULL;



int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	BOOL bRet = FALSE;
	bRet = InitApplication(hInstance);
	if (bRet == false)
	{
		return -1;
	}

	UpdateWindow(g_hMainWnd);
	ShowWindow(g_hMainWnd, SW_SHOW);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WinMainProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	if (hWnd == g_hMainWnd)
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			return OnClose_MainWnd(hWnd, wParam, lParam);
		case WM_DESTROY:
			return OnDestroy_MainWnd(hWnd, wParam, lParam);
		case WM_ERASEBKGND:
			return OnEraseBkgnd_MainWnd(hWnd, wParam, lParam);
		case WM_GETMINMAXINFO:
			return OnGetMinMaxInfo_MainWnd(hWnd, wParam, lParam);
		case WM_LBUTTONDOWN:
			return OnLbuttonDown_MainWnd(hWnd, wParam, lParam);
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool InitApplication(
	HINSTANCE hInstance)
{
	WNDCLASS wnd;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = CreateSolidBrush(RGB(200, 200, 200));
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = WinMainProc;
	wnd.lpszClassName = g_lptszClassName;
	wnd.lpszMenuName = NULL;
	wnd.style = 0;

	if (! RegisterClass(&wnd))
	{
		return false;
	}

	RECT rtClient = { 0, 0, 400, 400 };
	DWORD wStyle = WS_POPUP;
		//WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME;
	if (! AdjustWindowRect(&rtClient, wStyle, FALSE))
	{
		return false;
	}

	int wndWidth = rtClient.right - rtClient.left;
	int wndHeight = rtClient.bottom - rtClient.top;
	POINT point;
	point.x = (g_nScrWidth - wndWidth) / 2;
	point.y = (g_nScrHeight - wndHeight) / 2;

	g_hMainWnd = CreateWindow(
		g_lptszClassName,
		TEXT("MyProject"),
		wStyle,
		point.x, point.y,
		wndWidth, wndHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (g_hMainWnd == NULL)
	{
		return false;
	}

	return true;
}


//MainWnd Message
LRESULT WINAPI OnClose_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	DestroyWindow(hWnd);
	return 0;
}

LRESULT WINAPI OnDestroy_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;
}

LRESULT WINAPI OnEraseBkgnd_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

	RECT wndRect;
	if (!GetWindowRect(hWnd, &wndRect))
	{
		return 0;
	}

	HDC hDev = (HDC)wParam;


	return DefWindowProc(hWnd, WM_ERASEBKGND, wParam, lParam);
}

LRESULT WINAPI OnGetMinMaxInfo_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PMINMAXINFO minmax = NULL;
	minmax = (PMINMAXINFO)lParam;
	minmax->ptMinTrackSize.x = 400;
	minmax->ptMinTrackSize.y = 400;

	return 0;
}

LRESULT WINAPI OnLbuttonDown_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	
	POINT point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);
	
	RECT wndRect;
	if (! GetWindowRect(hWnd, &wndRect))
	{
		return 0;
	}

	int width = wndRect.right - wndRect.left;
	int height = wndRect.bottom - wndRect.top;

	int borderWidth = 10;
	int  captionHeight = 50;

	if (//标题栏
		point.x > borderWidth && point.x < (width - borderWidth) &&
		point.y > borderWidth && point.y <= captionHeight
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, lParam);
	}
	else if (//在窗口水平边框的上方
		point.x > borderWidth && point.x < (width - borderWidth) &&
		point.y >= 0 && point.y <= borderWidth
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTTOP, lParam);
	}
	else if (//在窗口的水平边框的底部
		point.x > borderWidth && point.x < (width - borderWidth) &&
		point.y >= (height - borderWidth) && point.y <= height
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTBOTTOM, lParam);
	}
	else if (//在窗口的左边框上 
		point.x >= 0 && point.x <= borderWidth &&
		point.y > borderWidth && point.y < (height - borderWidth)
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTLEFT, lParam);
	}
	else if (// 在窗口的右边框上
		point.x >= (width - borderWidth) && point.x <= width &&
		point.y > borderWidth && point.y < (height - borderWidth)
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTRIGHT, lParam);
	}
	else if (//在窗口边框的左上角
		point.x >= 0 && point.x <= borderWidth &&
		point.y >= 0 && point.y <= borderWidth
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTTOPLEFT, lParam);
	}
	else if (//在窗口边框的左下角
		point.x >= 0 && point.x <= borderWidth &&
		point.y >= (height - borderWidth) && point.y <= height
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTBOTTOMLEFT, lParam);
	}
	else if (//在窗口边框的右上角
		point.x >= (width - borderWidth) && point.x <= width &&
		point.y >= 0 && point.y <= borderWidth
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTTOPRIGHT, lParam);
	}
	else if (//在窗口边框的右下角
		point.x >= (width - borderWidth) && point.x <= width &&
		point.y >= (height - borderWidth) && point.y <= height
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTBOTTOMRIGHT, lParam);
	}
	else
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCLIENT, lParam);		
	}


	return 0;
}
