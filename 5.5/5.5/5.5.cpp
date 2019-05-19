// 5.5.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "5.5.h"

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
	LoadString(hInstance, IDC_MY55, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY55));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY55));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY55);
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
   char lpsz_1[] ="只有付出才有收获";	// 定义输出的字符串
   //const char* lpsz_1[] ={"只有付出才有收获"};
   TCHAR  chFont[7];
 //  char chFont[7];	// 定义字体种类的字符串
	int X = 0,Y = 0,i;
	int nCharlen = strlen(lpsz_1);	// 定义字符串长度变量
	int iFontSign = 0;// 定义字体标志

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
		hDC = BeginPaint(hWnd,&ps);	// 获得设备环境句柄
		for(i = 0;i < nCharlen;i += 2)	// 采用某种字体和颜色输出字符串
		{
			SetTextColor(hDC,RGB((long)(255.0/nCharlen * i),// 设置字体颜色
				0,
				0));
		/*	if(iFontSign% 5 == 0) strcpy(chFont,"楷体_GB2312"); // 设置包含字体信息的字符串 
			else if(iFontSign% 5 == 1) strcpy(chFont,"宋体"); // 以 5 为周期循环改变字体 
			else if(iFontSign % 5 == 2) strcpy(chFont,"隶书");
			else if(iFontSign % 5 == 3) strcpy(chFont,"黑体");
			else strcpy(chFont,"幼圆");*/
			if(iFontSign% 5 == 0) _tcscpy(chFont,_T("楷体_GB2312")); // 设置包含字体信息的字符串 
			else if(iFontSign% 5 == 1) _tcscpy(chFont,_T("宋体")); // 以 5 为周期循环改变字体 
			else if(iFontSign % 5 == 2) _tcscpy(chFont,_T("隶书"));
			else if(iFontSign % 5 == 3) _tcscpy(chFont,_T("黑体"));
			else _tcscpy(chFont,_T("幼圆"));
			hF = CreateFont(	// 定义字体句柄
				(long)(8 + 32.0 * i/ nCharlen),	// 字体高度
				0,	// 系统定义的宽度值
				0,	// 文本倾斜度为 0,表示水平
				0,	// 字体倾斜度为 0
				400,	// 字体粗度 .400 为正常
				0,	// 非斜体字
				0,	// 无下划线
				0,	// 无删除线
				GB2312_CHARSET,	// 所用的字符集为 ANSI- CHARSET
				OUT_DEFAULT_PRECIS,	// 删除精度为默认值
				CLIP_DEFAULT_PRECIS,	// 裁剪精度为默认值
				DEFAULT_QUALITY,	// 输出质量为默认值
				DEFAULT_PITCH|FF_DONTCARE,	// 字间距和字体系列使用默认值
				chFont);	// 字体名称
			SelectObject(hDC,hF);	// 选入字体
			GetTextMetrics(hDC,&tm);	// 得到包含字体信息的结构体
			X = X + tm .tmAveCharWidth * 2;	// 设置输出字符的 X 坐标
			Y = iFontSign % 5 * 40 + tm .tmExternalLeading;	// 设置输出字符的 Y 坐标

//错误：不能将参数 4 从“char *”转换为“LPCWSTR”
			TextOut(hDC,X,Y,(LPCWSTR)&lpsz_1[i],2);	// 输出第 i 个字符 .产生滚动的效果
			Sleep(400);	// 暂停 0 .4 秒
			DeleteObject(hF);	// 删除字体句柄
		}
		iFontSign++;	// 字体标志增加
		InvalidateRect(hWnd,NULL,1);	// 刷新用户区
		EndPaint(hWnd,&ps);	// 删除设备句柄
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
