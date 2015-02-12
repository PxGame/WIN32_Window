# ifndef _MAIN_H_
# define _MAIN_H_

# include <Windows.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInstance,
	LPSTR lpCmdLine,
	int nCmdShow);

LRESULT CALLBACK WinMainProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);

bool InitApplication(
	HINSTANCE hInstance);

bool InitControl(
	HWND hWnd);

//MainWnd Message
LRESULT WINAPI OnClose_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnCreate_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnDestroy_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnEraseBkgnd_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnGetMinMaxInfo_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnLbuttonDown_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnPaint_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnSize_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnDrawItem_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnMoveMouse_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI OnCommand_MainWnd(HWND hWnd, WPARAM wParam, LPARAM lParam);


# endif