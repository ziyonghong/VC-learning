// 5.6.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "5.6.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HFONT CreateMyFont(TCHAR* chFont);
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
	LoadString(hInstance, IDC_MY56, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY56));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY56));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY56);
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
	HFONT hF;	// 定义字体句柄
	PAINTSTRUCT ps;	// 定义包含绘图信息的结构体变量
	TEXTMETRIC tm;	// 定义包含字体信息的结构体变量
	LPWSTR lpsz_1 = L"欲穷千里目 更上一层楼";	// 定义输出字符串
	//char lpsz_1[] = "欲穷千里目 更上一层楼";
	char chFont[7];	// 定义包含字体的字符串
	int X = 0,Y = 0,nCharlen = 11;
	//int nCharlen=strlen(lpsz_1);
	int iFontFlag = 0;	// 定义字体标志
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd,1,200,NULL);	// 每 0 .2 秒发出 WM- TIMER 消息
		break;
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
		hDC = BeginPaint(hWnd,&ps);	// 获取设备环境句柄
		if(iFontFlag/nCharlen == 0)	// 设置字体颜色
		{
			SetTextColor(hDC,RGB(255,0,0));
			hF=CreateMyFont(L"楷体");
		}
		else if(iFontFlag/ nCharlen == 1)
		{
			SetTextColor(hDC,RGB(0,255,0));hF=CreateMyFont(L"宋体");
		}
		else if(iFontFlag/ nCharlen == 2)
		{
			SetTextColor(hDC,RGB(255,255,0));hF=CreateMyFont(L"仿宋体");
		}
		else if(iFontFlag/ nCharlen == 3)
		{
			SetTextColor(hDC,RGB(0,0,255)); hF=CreateMyFont(L"黑体");
		}
		else
		{
			iFontFlag = 0; SetTextColor(hDC,RGB(255,0,0));
		}
		
		SelectObject(hDC,hF);	// 选入字体
		GetTextMetrics(hDC,&tm);	// 得到字体的信息
		TextOut(hDC,X,Y,&lpsz_1[iFontFlag % nCharlen],nCharlen - iFontFlag % nCharlen);
		iFontFlag += 2;	// 字体标志自增
		DeleteObject(hF);	// 删除字体
		EndPaint(hWnd,&ps);	// 删除设备环境句柄
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
// 设置字体
		HFONT CreateMyFont(TCHAR* chFont)
		{
		return  CreateFont(	// 获得字体句柄
			40,	// 字体高度
			0,	// 系统自动调整宽度
			0,	// 文本水平
			0,	// 字体倾斜度为 0
			400,	// 字体粗度 .400 为正常
			0,	// 字体不倾斜
			0,	// 无下划线
			0,	// 无删除线
			GB2312_CHARSET,	// 字符集
			OUT_DEFAULT_PRECIS,	// 默认输出精度
			CLIP_DEFAULT_PRECIS,	// 默认裁剪精度
			DEFAULT_QUALITY,	// 默认输出质量
			DEFAULT_PITCH|FF_DONTCARE,	// 默认间距
			chFont);	// 字体名称
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
