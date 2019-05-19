// 6.4.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "6.4.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

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
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY64, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY64));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY64));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY64);
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
	HDC hDC;	// 定义设备环境句柄
	WORD x,y;	// 定义鼠标的位置坐标
	HCURSOR hCursor;	// 定义光标句柄
	HBRUSH hBrush;
	LPSIZE lpSize;	// 窗口尺寸结构
	static char cLeftBtn[] = "LEFT BUTTON";	// 定义单击左键时的输出字符
	static char cRightBtn[] = "RIGHT BUTTON";	// 定义单击右键时的输出字符
	RECT ClientRect;

	switch (message)
	{
	case WM_MOUSEMOVE:	// 处理鼠标移动信息
		x = LOWORD(lParam);	// 获得鼠标的 X 坐标
		y = HIWORD(lParam);	// 获得鼠标的 Y 坐标
		GetClientRect(hWnd,&ClientRect);	// 得到窗口大小
		if(y >= 0&&y <= ClientRect .bottom)
		{
			if(y >= 0&&y <= ClientRect .bottom/ 5)	// 在此区域,是箭头
			{
				hCursor = LoadCursor(NULL,IDC_ARROW); SetCursor(hCursor);
			}
			else if(y >= ClientRect .bottom/ 5&&y <= ClientRect .bottom/ 5 * 2)// 在此区域为十字图标
			{
				hCursor = LoadCursor(NULL,IDC_CROSS); SetCursor(hCursor);
			}
			
			else if(y>= ClientRect.bottom/ 5 * 2&&y<= ClientRect.bottom/ 5 * 3)//“东北 - 西南”方向
			{
				hCursor = LoadCursor(NULL,IDC_SIZENESW); SetCursor(hCursor);
			}
			else if(y>= ClientRect.bottom/ 5 * 3&&y<= ClientRect.bottom/ 5 * 4)//“南 - 北”方向
			{
				hCursor = LoadCursor(NULL,IDC_SIZENS); SetCursor(hCursor);
			}
			else	// 在此区域为等待光标
			{
				hCursor = LoadCursor(NULL,IDC_WAIT); SetCursor(hCursor);
			}
			}
			return 0;
	case WM_LBUTTONDOWN:	// 单击左建
		hDC = GetDC(hWnd);	// 得到设备环境句柄
		SetBkColor(hDC,RGB(255,255,0));	// 设置背景色
		TextOut(hDC,0,0,(LPCWSTR)cLeftBtn,strlen(cLeftBtn));	// 输出
		ReleaseDC(hWnd,hDC);	// 释放设备环境句柄
		break;
	case WM_RBUTTONDOWN:	// 单击右建
		hDC = GetDC(hWnd);	// 得到设备环境句柄
		SetBkColor(hDC,RGB(255,255,0));	// 设置背景色为黄色
		TextOut(hDC,0,0,cRightBtn,strlen(cRightBtn));	// 输出
		ReleaseDC(hWnd,hDC);	// 释放设备环境句柄break;
	case WM_SIZE:
		hDC = GetDC(hWnd);	// 得到设备环境句柄
		SetMapMode(hDC,MM_ANISOTROPIC);	// 设置映像模式
		SetViewportExtEx(hDC,LOWORD(lParam),HIWORD(lParam),lpSize);// 设置试口区域
		SetWindowExtEx(hDC,100,50,lpSize);	//  设置窗口区域
		hBrush = CreateSolidBrush(RGB(255,255,255));	// 定义白色画刷
		SelectObject(hDC,hBrush);	// 选入白色画刷
		Rectangle(hDC,0,0,100,10);	// 填充矩形
		DeleteObject(hBrush);	// 删除画刷
		hBrush = CreateSolidBrush(RGB(0,255,0));	// 定义绿色画刷
		SelectObject(hDC,hBrush);	// 选入绿色画刷
		Rectangle(hDC,0,10,100,20);	// 填充矩形
		DeleteObject(hBrush);	// 删除画刷
		hBrush = CreateSolidBrush(RGB(0,0,255));	// 定义蓝色画刷
		SelectObject(hDC,hBrush);	// 选入蓝色画刷
		Rectangle(hDC,0,20,100,30);	// 填充矩形
		DeleteObject(hBrush);	// 删除画刷
		hBrush = CreateSolidBrush(RGB(255,255,0));	// 定义黄色画刷
		SelectObject(hDC,hBrush);	// 选入黄色画刷
		Rectangle(hDC,0,30,100,40);	// 填充矩形
		DeleteObject(hBrush);	// 删除黄色画刷
		hBrush = CreateSolidBrush(RGB(255,0,0));	// 定义红色画刷
		SelectObject(hDC,hBrush);	// 选入画刷
		Rectangle(hDC,0,40,100,50);	// 填充矩形
		DeleteObject(hBrush);	// 删除画刷
		ReleaseDC(hWnd,hDC);	// 删除设备环境句柄
		break;
	case WM_DESTROY:	// 处理退出窗口信息
		PostQuitMessage(0); return 0;
	default:
		return(DefWindowProc(hWnd,message,wParam,lParam));
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
