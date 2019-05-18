// 4.6.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "4.6.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
double dfTheta = 0,dfRange = 100.0;	// 正弦曲线的角度变量
long i = 0,j = 0;
long lCentreX = 0,lCentreY = 0,lRadious = (long)(0.2 * dfRange); // 定义圆心坐标和圆坐标
POINT lpSin[100];	// 定义正弦曲线的点坐标
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
	LoadString(hInstance, IDC_MY46, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY46));

	for(int j = 0;j < 100;j++ )	// 生成正弦曲线的点坐标
	{
		lpSin[j] .x = (long)(j * 2 * Pi/ 100 * 60);
		lpSin[j] .y = (long)(dfRange * sin(j * 2 * Pi/ 100));
	}
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY46));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY46);
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
	HDC hDC;	// 定义设备环境句柄
	HBRUSH hBrush;	// 定义画刷句柄
	HPEN hPen;	// 定义画笔句柄
	PAINTSTRUCT PtStr;	// 定义包含绘图信息的结构体变量

	switch (message)
	{
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
		hDC = BeginPaint(hWnd,&PtStr);	// 获得设备环境指针
		SetWindowOrgEx(hDC, - 200, - 200,NULL);	// 设置原点坐标为(-20 ,-200)
		hPen = CreatePen(PS_DASH,1,RGB(255,0,0));	// 创建画笔句柄
		SelectObject(hDC,hPen);	// 选入画笔
		Polyline(hDC,lpSin,100);	// 绘制正弦曲线
		if(i <= 25)	// 第一个 1/ 4 周期
		{
			hPen = CreatePen(PS_DASH,1,RGB(255,0,0));	// 创建红色画笔
			hBrush = CreateHatchBrush(HS_BDIAGONAL,RGB(255,0,0)); // 创建红色画刷
			lRadious = (long)(dfRange * 0.2 + i% 25 * dfRange * 0.4/ 25); // 计算半径
		}
		else if(i <= 50)	// 第二个 1/ 4 周期
		{
			hPen = CreatePen(PS_DASH,1,RGB(0,255,0));	// 创建绿色画笔
			hBrush = CreateHatchBrush(HS_DIAGCROSS,RGB(0,255,0)); // 创新绿刷
			lRadious = (long)(dfRange * 0.2 + i% 25 * dfRange * 0.4/ 25); // 计算半径
		}
		else if(i <= 75)	// 第三个周期
		{
			hPen = CreatePen(PS_DASH,1,RGB(0,0,255));	// 创建蓝色画笔
			hBrush = CreateHatchBrush(HS_CROSS,RGB(0,0,255)); // 创建蓝色画刷
			lRadious = (long)(dfRange * 0.2 + i% 25 * dfRange * 0.4/ 25); // 计算半径
		}
		else	// 第四个周期
		{
			hPen = CreatePen(PS_DASH,1,RGB(255,255,0)); // 创 建 黄 色 画 笔
			hBrush = CreateHatchBrush(HS_VERTICAL,RGB(255,255,0));// 创建黄色画刷
			lRadious = (long)(dfRange * 0.2 + i% 25 * dfRange * 0.4/ 25); // 计算半径
		}
		SelectObject(hDC,hBrush);	// 选入画刷
		SelectObject(hDC,hPen);	// 选入画笔
		lCentreX = lpSin[i] .x;	// 圆心 x 坐标
		lCentreY = lpSin[i] .y;	// 圆心 y 坐标
		Ellipse(hDC,lCentreX - lRadious,lCentreY - lRadious,
			lCentreX + lRadious,lCentreY + lRadious);	// 画圆
		i++;
		DeleteObject(hPen);	// 删除画笔
		DeleteObject(hBrush);	// 删除画刷
		EndPaint(hWnd,&PtStr);	// 删除设备环境句柄
		Sleep(100);	// 停 0 .1 秒
		if(i < 100) InvalidateRect(hWnd,NULL,1);	// 刷新用户区
		return 0;

	case WM_DESTROY:
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
