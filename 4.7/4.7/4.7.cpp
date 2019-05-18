// 4.7.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "4.7.h"

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
	MSG msg;  //定义消息变量
	
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY47, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY47));

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
	WNDCLASSEX wcex;//定义窗口类

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY47));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY47);
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
   HWND hWnd; //定义窗口句柄

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
		hDC = BeginPaint(hWnd, &PtStr);
		// TODO: 在此添加任意绘图代码...
		 SetMapMode(hDC,MM_ANISOTROPIC);	// 设置映像模式
    SetWindowExtEx(hDC,300,300,NULL);	// 设置窗口区域 .逻辑单位
    SetViewportExtEx(hDC,600,600,NULL);	// 设置视口区域 .物理单位
    SetViewportOrgEx(hDC,0,0,NULL);	// 设置视口原点物理单位坐标(0,0)
   // 绘制四个圆形 .(笔的样式不同)
    hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	// 选择空画刷
    SelectObject(hDC,hBrush);
    hPen = CreatePen(PS_DASH,0,RGB(255,0,0));	// 建立虚线样式的红色画笔
    SelectObject(hDC,hPen);	// 选入设备环境
    Ellipse(hDC,0,0,70,70);	// 画圆
    hPen = CreatePen(PS_DASHDOT,0,RGB(0,255,0));	// 建立点划线样式的绿色画笔
    SelectObject(hDC,hPen);
    Ellipse(hDC,25,0,95,70);	// 画圆
    hPen = CreatePen(PS_DASHDOTDOT,0,RGB(0,0,255));	// 建立双点划线样式的蓝色画笔
    SelectObject(hDC,hPen);
    Ellipse(hDC,0,25,70,95);
    hPen = CreatePen(PS_DOT,0,RGB(0,255,255));	// 建立点线样式的天蓝色画笔
    SelectObject(hDC,hPen);
    Ellipse(hDC,25,25,95,95);
   // 画 6 个圆角矩形 .(实画刷样式不同 .)
    hPen = (HPEN)GetStockObject(BLACK_PEN);
    SelectObject(hDC,hPen);
    hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);	// 选择黑色画刷
    SelectObject(hDC,hBrush);	// 选入设备环境
    RoundRect(hDC,120,0,165,45,10,10);	// 画圆角矩形
    hBrush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);	// 选择深灰色画刷
    SelectObject(hDC,hBrush);
    RoundRect(hDC,165,0,210,45,10,10);
    hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);	// 选择灰色画刷
    SelectObject(hDC,hBrush);
    RoundRect(hDC,210,0,255,45,10,10);
    hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);	// 选择虚画刷
	 SelectObject(hDC,hBrush);
    RoundRect(hDC,120,45,165,90,10,10);
    hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);	// 选择亮灰画刷
    SelectObject(hDC,hBrush);
    RoundRect(hDC,165,45,210,90,10,10);
    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 选择白画刷
    SelectObject(hDC,hBrush);
    RoundRect(hDC,210,45,255,90,10,10);
   // 画 6 个矩形 .(画刷阴影样式不同 .)
    hPen = (HPEN)GetStockObject(BLACK_PEN);
    SelectObject(hDC,hPen);
    hBrush = CreateHatchBrush(HS_BDIAGONAL,RGB(200,200,200)); // 创建 45 度左上右下阴影线
    SelectObject(hDC,hBrush);	// 将画刷选入设备环境
    Rectangle(hDC,120,90,165,135);	// 画矩形
    hBrush = CreateHatchBrush(HS_DIAGCROSS,RGB(200,200,200)); // 创建 45 度交叉线
    SelectObject(hDC,hBrush);
    Rectangle(hDC,165,90,210,135);
    hBrush = CreateHatchBrush(HS_FDIAGONAL,RGB(200,200,200)); // 创建 45 度左下右上阴影线
    SelectObject(hDC,hBrush);
    Rectangle(hDC,210,90,255,135);
    hBrush = CreateHatchBrush(HS_CROSS,RGB(200,200,200));	// 创建垂直相交阴影线
    SelectObject(hDC,hBrush);
    Rectangle(hDC,120,135,165,175);
    hBrush = CreateHatchBrush(HS_HORIZONTAL,RGB(200,200,200)); // 创建水平阴影线
    SelectObject(hDC,hBrush);
    Rectangle(hDC,165,135,210,175);
    hBrush = CreateHatchBrush(HS_VERTICAL,RGB(200,200,200));	// 创建垂直阴影线
    SelectObject(hDC,hBrush);
    Rectangle(hDC,210,135,255,175);
   // 画饼图
    hPen = (HPEN)GetStockObject(BLACK_PEN);
    SelectObject(hDC,hPen);
    hBrush = CreateSolidBrush(RGB(255,0,0));	// 创建红色画刷
    SelectObject(hDC,hBrush);	// 选入设备环境
    Pie(hDC,10,100,	// 画饼图
100,190,
(int)(55 + 45 * cos(2 * Pi/ 3)),(int)(145 + 45 * sin(2 * Pi/ 3)), (int)(55 + 45 * cos(0.0)),(int)(145 + 45 * sin(0.0)));
    hBrush = CreateSolidBrush(RGB(0,255,255));	// 创建天蓝色画刷
    SelectObject(hDC,hBrush);	// 选入设备环境
    Pie(hDC,10,100,
100,190,
(int)(55 + 45 * cos(4 * Pi/ 3)),(int)(145 + 45 * sin(4 * Pi/ 3)),
(int)(55 + 45 * cos(2 * Pi/ 3)),(int)(145 + 45 * sin(2 * Pi/ 3)));
    hBrush = CreateSolidBrush(RGB(255,255,0));	// 创建黄色画刷
    SelectObject(hDC,hBrush);	// 选入设备环境
    Pie(hDC,10,100,
100,190,
(int)(55 + 45 * cos(2 * Pi)),(int)(145 + 45 * sin(2 * Pi)), (int)(55 + 45 * cos(4 * Pi/ 3)),(int)(145 + 45 * sin(4 * Pi/ 3)));
		EndPaint(hWnd, &PtStr);
		break;
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
