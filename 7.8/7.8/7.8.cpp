// 7.8.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "7.8.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HWND hWndMain;	// 定义窗口句柄
HDC hDC;	// 定义设备环境句柄
HDC hdcmem;	// 定义内存句柄
HBITMAP hBm;	// 定义位图句柄
BITMAP bm;	// 定义位图结构变量
int iY = 80;	// 位图左上角初始 y 坐标
int iWindowWidth,iWindowHeight;	// 窗口的宽度和高度
char cUpWarn[] = "不能再向上移动了";	// 向上警告字符串
char cDownWarn[] = "不能再向下移动了";	// 向下警告字符串

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此放置代码。
	MSG msg;// 定义消息变量
	HACCEL hAccelTable;

	hBm = LoadBitmap(hInstance,L"forest");	// 加载位图
	GetObject(hBm,sizeof(BITMAP),(LPVOID)&bm);	// 获得位图信息
	iWindowWidth = 2 * bm .bmWidth;	// 得到窗口的宽度
	iWindowHeight = 2 * bm .bmHeight;	// 得到窗口的高度
	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY78, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY78));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY78));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY78);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // 将实例句柄存储在全局变量中

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;


	switch (message)
	{
	case WM_LBUTTONDOWN:	// 点击鼠标左键
		iY = iY - 10;	// 位图高度 - 10
		InvalidateRect(hWnd,NULL,1);	// 刷新用户区
		break;
	case WM_RBUTTONDOWN:	// 点击鼠标右键
		iY = iY + 10;	// 位图高度 + 10
		InvalidateRect(hWnd,NULL,1);	// 刷新用户区
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_UP:	// 按上箭头时,位置 - 10
			iY = iY - 10;
			break;
		case VK_DOWN:	// 按下箭头时,位置 + 10
			iY = iY + 10;
			break;
		}
		InvalidateRect(hWnd,NULL,1);	// 刷新用户区
		break;
	case WM_CREATE:	// 初始化窗口消息
		hDC = GetDC(hWnd);	// 得到设备环境指针
		hdcmem = CreateCompatibleDC(hDC);	// 得到内存指针
		ReleaseDC(hWnd,hDC);	// 删除设备环境指针
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd,&ps);	// 得到设备环境指针
		if(iY > 0&&iY < iWindowHeight/ 2)	// 当位图完整的在窗口中时
		{
			SelectObject(hdcmem,hBm);	// 选入内存句柄
			BitBlt(hDC,60,iY,bm .bmWidth,bm .bmHeight,hdcmem,0,0,SRCCOPY);// 输出位图
		}
		else if(iY <= 0)	// 当位图的上边界超出了窗口时
		{
			TextOut(hDC,0,0,(LPCWSTR)cUpWarn,sizeof(cUpWarn));	// 输出警告
		}
		else	// 当位图的下边界超出了窗口时
		{
			TextOut(hDC,0,0,(LPCWSTR)cDownWarn,sizeof(cDownWarn));// 输出警告
		}
		EndPaint(hWnd,&ps);	// 输出环境句柄
		break;
	case WM_DESTROY:
		DeleteObject(hBm);	// 删除内存句柄
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
