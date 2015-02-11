# include "main.h"

LPCTSTR g_lptszClassName = TEXT("WndClass");
const int g_nScrWidth = GetSystemMetrics(SM_CXSCREEN);
const int g_nScrHeight = GetSystemMetrics(SM_CYSCREEN);
const int g_nTktBorder = 5;
const int g_nCapBorder = 20;
const RECT g_rtInitCliWnd = { 0, 0, 600, 600 };
const POINT g_ptMinWnd = { 300, 300 };

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
		case WM_PAINT:
			return OnPaint_MainWnd(hWnd, wParam, lParam);
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
	wnd.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = WinMainProc;
	wnd.lpszClassName = g_lptszClassName;
	wnd.lpszMenuName = NULL;
	wnd.style = CS_HREDRAW | CS_VREDRAW;//重要！！要不然背景绘制会出问题

	if (! RegisterClass(&wnd))
	{
		return false;
	}

	RECT rtClient = g_rtInitCliWnd;
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

LRESULT WINAPI OnGetMinMaxInfo_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PMINMAXINFO minmax = NULL;
	minmax = (PMINMAXINFO)lParam;
	minmax->ptMinTrackSize.x = g_ptMinWnd.x;
	minmax->ptMinTrackSize.y = g_ptMinWnd.y;

	return 0;
}

LRESULT WINAPI OnLbuttonDown_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	
	POINT point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);
	
	RECT wndRect;
	if (! GetClientRect(hWnd, &wndRect))
	{
		return 0;
	}

	int width = wndRect.right - wndRect.left;
	int height = wndRect.bottom - wndRect.top;
	
	if (//标题栏
		point.x > g_nTktBorder && point.x < (width - g_nTktBorder) &&
		point.y > g_nTktBorder && point.y <= g_nCapBorder + g_nTktBorder
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, lParam);
	}
	else if (//在窗口水平边框的上方
		point.x > g_nTktBorder && point.x < (width - g_nTktBorder) &&
		point.y >= 0 && point.y <= g_nTktBorder
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTTOP, lParam);
	}
	else if (//在窗口的水平边框的底部
		point.x > g_nTktBorder && point.x < (width - g_nTktBorder) &&
		point.y >= (height - g_nTktBorder) && point.y <= height
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTBOTTOM, lParam);
	}
	else if (//在窗口的左边框上 
		point.x >= 0 && point.x <= g_nTktBorder &&
		point.y > g_nTktBorder && point.y < (height - g_nTktBorder)
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTLEFT, lParam);
	}
	else if (// 在窗口的右边框上
		point.x >= (width - g_nTktBorder) && point.x <= width &&
		point.y > g_nTktBorder && point.y < (height - g_nTktBorder)
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTRIGHT, lParam);
	}
	else if (//在窗口边框的左上角
		point.x >= 0 && point.x <= g_nTktBorder &&
		point.y >= 0 && point.y <= g_nTktBorder
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTTOPLEFT, lParam);
	}
	else if (//在窗口边框的左下角
		point.x >= 0 && point.x <= g_nTktBorder &&
		point.y >= (height - g_nTktBorder) && point.y <= height
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTBOTTOMLEFT, lParam);
	}
	else if (//在窗口边框的右上角
		point.x >= (width - g_nTktBorder) && point.x <= width &&
		point.y >= 0 && point.y <= g_nTktBorder
		)
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTTOPRIGHT, lParam);
	}
	else if (//在窗口边框的右下角
		point.x >= (width - g_nTktBorder) && point.x <= width &&
		point.y >= (height - g_nTktBorder) && point.y <= height
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

LRESULT WINAPI OnPaint_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	/*
	PAINTSTRUCT ps;
	HDC hdc = NULL;
	hdc = BeginPaint(hWnd, &ps);

	EndPaint(hWnd, &ps);
	*/
	return DefWindowProc(hWnd, WM_PAINT, wParam, lParam);
}


LRESULT WINAPI OnEraseBkgnd_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = (HDC)wParam;

	RECT wndRect;
	//GetWindowRect(hWnd, &wndRect);//错误，不能获取窗口大小，否则会失败。
	GetClientRect(hWnd, &wndRect);

	RECT bufRect = wndRect;

	//边框
	HBRUSH brush = CreateSolidBrush(RGB(0,0,0));
	FillRect(hdc, &bufRect, brush);
	DeleteObject(brush);

	//标题栏
	bufRect.top += g_nTktBorder;
	bufRect.bottom = g_nCapBorder + g_nTktBorder;
	bufRect.left += g_nTktBorder;
	bufRect.right -= g_nTktBorder;
	FillRect(hdc, &bufRect, (HBRUSH)GetStockObject(GRAY_BRUSH));

	//客户区
	bufRect.top = g_nCapBorder + g_nTktBorder;
	bufRect.bottom = wndRect.bottom - g_nTktBorder;

	//FillRect(hdc, &bufRect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	TRIVERTEX trives[3];
	trives[0].x = bufRect.left;
	trives[0].y = bufRect.top;
	trives[0].Alpha = 0xff00;
	trives[0].Red = 0xff00;
	trives[0].Green = 0 ;
	trives[0].Blue = 0 ;
	trives[1].x = bufRect.right ;
	trives[1].y = bufRect.bottom / 2;
	trives[1].Alpha = 0xff00;
	trives[1].Red = 0 ;
	trives[1].Green = 0xff00;
	trives[1].Blue = 0;
	trives[2].x = bufRect.left;
	trives[2].y = bufRect.bottom;
	trives[2].Alpha = 0xff00;
	trives[2].Red = 0;
	trives[2].Green = 0 ;
	trives[2].Blue =0xff00 ;
	// 定义渐变区为矩形，并确定其点
	GRADIENT_RECT rects[2];
	rects[0].UpperLeft = 0;
	rects[0].LowerRight = 1;
	rects[1].UpperLeft = 1;
	rects[1].LowerRight = 2;
	GradientFill(hdc, trives, 3, rects, 2, GRADIENT_FILL_RECT_V);

	/*
	//创建兼容DC
	HDC bufHdc = NULL;
	bufHdc = CreateCompatibleDC(hdc);

	int nRet = 0;
	//边框
	nRet = FillRect(bufHdc, &wndRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

	//非边框区
	wndRect.left += g_nTktBorder;
	wndRect.top += g_nTktBorder;
	wndRect.right -= g_nTktBorder;
	wndRect.bottom -= g_nTktBorder;
	nRet = FillRect(bufHdc, &wndRect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	//标题栏
	wndRect.bottom = g_nCapBorder + g_nTktBorder;
	nRet = FillRect(bufHdc, &wndRect, (HBRUSH)GetStockObject(GRAY_BRUSH));

	nRet = StretchBlt(hdc, wndRect.left, wndRect.top, wndRect.right, wndRect.bottom,
		bufHdc, wndRect.left, wndRect.top, wndRect.right, wndRect.bottom, SRCCOPY);
	DeleteDC(bufHdc);
	*/
	return  1;// DefWindowProc(hWnd, WM_ERASEBKGND, wParam, lParam);//返回非零表示擦除背景
}