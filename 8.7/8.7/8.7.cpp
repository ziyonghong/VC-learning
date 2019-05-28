// 8.7.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "8.7.h"

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
	LoadString(hInstance, IDC_MY87, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY87));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY87));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY87);
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
	PAINTSTRUCT ps;	// 定义包含绘图信息的结构体
	static HWND hWndScrollBarHor,hWndScrollBarVer;	// 定义水平和竖直滚动条的句柄
	static SCROLLINFO stScrollInfo;	// 定义包含滚动条信息的结构体
	static int iHorPos = 1,iVerPos = 100;	// 定义滚动条位置
	char cOut[] = "祝您成功 .";	// 输出字符串
	RECT rcRedrawArea = {0,0,380,200};	// 定义刷新区域
	switch (message)
	{
	case WM_CREATE:	// 窗口创建消息
		// 创建竖直滚动条
		hWndScrollBarVer = CreateWindowEx(0L,	// 定义窗口样式
			L"SCROLLBAR",	// 创建滚动条
			NULL,	// 标题
			WS_CHILD|SBS_VERT,	// 样式
			400,	// 左上角 X 坐标
			30-GetSystemMetrics(SM_CYVSCROLL),	// 左上角 Y 坐标
			GetSystemMetrics(SM_CYVSCROLL),	// 滚动条宽度
			100 + 2 * GetSystemMetrics(SM_CYVSCROLL),   // 滚动条长度
			hWnd,	// 父窗口句柄
			NULL,	// 无菜单
			hInst,	// 程序实例句柄
			NULL);	// 不用此参数
		// 创建水平滚动条
		hWndScrollBarHor = CreateWindowEx(0L,	// 定义窗口样式
			L"SCROLLBAR",	// 创建滚动条
			(LPCWSTR)NULL,	// 标题
			WS_CHILD|SBS_HORZ,	// 样式
			50,	// 左上角 X 坐标
			200,	// 左上角 Y 坐标
			100 + 2 * GetSystemMetrics(SM_CYHSCROLL),       // 滚动条宽度
			GetSystemMetrics(SM_CYHSCROLL),	// 滚动条长度
			hWnd,	// 父窗口句柄
			(HMENU)NULL,	// 无菜单
			hInst,	// 程序实例句柄
			(LPVOID)NULL);	// 不用此参数
		stScrollInfo .cbSize = sizeof(SCROLLINFO);	// 定义此结构体的大小
		stScrollInfo .fMask = SIF_POS|SIF_RANGE|SIF_PAGE;	// 定义滚动条特性参数
		stScrollInfo .nMin = 1;	// 定义滚动条的最小位置
		stScrollInfo .nMax = 100;	// 定义滚动条的最大位置
		stScrollInfo .nPos = 1;	// 定义滚动条滚动的增量
		stScrollInfo .nPage = 10;	// 定义滚动条翻页的增量
		// 设置滚动条的特性参数
		SetScrollInfo(hWndScrollBarVer,SB_CTL,&stScrollInfo,FALSE);
		SetScrollInfo(hWndScrollBarHor,SB_CTL,&stScrollInfo,FALSE);
		ShowWindow(hWndScrollBarHor,TRUE);
		ShowWindow(hWndScrollBarVer,TRUE);
		break;
	case WM_VSCROLL:	// 若是竖直滚动条的消息
		if((HWND)lParam != hWndScrollBarVer)
			break; switch(LOWORD(wParam))
		{
			case SB_LINEUP:	// 向上走一行,位置 + 5
				iVerPos += 5;
				break;
			case SB_LINEDOWN:	// 向下走一行,位置 - 5
				iVerPos -= 5;
				break;
			case SB_PAGEUP:	// 向上走一页,位置 + 20
				iVerPos += 20;
				break;
			case SB_PAGEDOWN:	// 向下走一页,位置 - 20
				iVerPos -= 20;
				break;
			case SB_THUMBPOSITION:	// 拖动滚动条
				iVerPos = 101 - HIWORD(wParam);
				break; default:
				return(DefWindowProc(hWnd,message,wParam,lParam));
		}
		if(iVerPos < 1) iVerPos = 1;	// 限制位置的范围
		else if(iVerPos > 100) iVerPos = 100;
		// 设定滚动条的信息 .主要是设定位置 . 
		stScrollInfo .fMask = SIF_POS; 
		stScrollInfo .nPos = 101 - iVerPos;
		SetScrollInfo(hWndScrollBarVer,SB_CTL,&stScrollInfo,TRUE); 
		InvalidateRect(hWnd,&rcRedrawArea,1);	// 刷新自定义的用户区
		break;
	case WM_HSCROLL:	// 水平滚动条的消息
		if((HWND)lParam != hWndScrollBarHor)
			break; switch(LOWORD(wParam))
		{
			case SB_LINELEFT:	// 向左滚动一行,位置 - 5
				iHorPos -= 5;
				break;
			case SB_LINERIGHT:	// 向右滚动一行,位置 + 5
				iHorPos += 5;
				break;
			case SB_PAGELEFT:	// 向左滚动一页,位置 - 20
				iHorPos -= 20;
				break;
			case SB_PAGERIGHT:	// 向右滚动一页,位置 + 20
				iHorPos += 20;
				break;
			case SB_THUMBPOSITION:	// 拖动滚动条
				iHorPos = HIWORD(wParam);
				break; 
			default:
				return(DefWindowProc(hWnd,message,wParam,lParam));
		}
		if(iHorPos < 1) iHorPos = 1;	// 限制位置范围
		else if(iHorPos > 100) iHorPos = 100;
		// 设定滚动条的信息 .主要是设定位置
		stScrollInfo .fMask = SIF_POS; 
		stScrollInfo .nPos = iHorPos;
		SetScrollInfo(hWndScrollBarHor,SB_CTL,&stScrollInfo,TRUE); 
		InvalidateRect(hWnd,&rcRedrawArea,1);	// 刷新用户区
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
		hDC = BeginPaint(hWnd, &ps);
		hF = CreateFont((int)(50 + 50.0 * iHorPos/ 100),	// 字体高度
			0,	// 自动调整宽度
			0,	// 文本水平
			0,	// 字体水平
			400,	// 正常宽度
			0,	// 字体不倾斜
			0,	// 无下划线
			0,	// 无中划线
			ANSI_CHARSET,	// 字符集
			OUT_DEFAULT_PRECIS,	// 默认输出精度
			CLIP_DEFAULT_PRECIS,	// 默认裁剪精度
			DEFAULT_QUALITY,	// 默认输出质量
			DEFAULT_PITCH|FF_DONTCARE,	// 默认字体间距
			L"楷体");	// 字体
		// 设置字体颜色
		SetTextColor(hDC,RGB(0,0,(int)(iVerPos/ 100.0 * 255)));
		SelectObject(hDC,hF);	// 选入字体
		TextOut(hDC,0,0,(LPCWSTR)cOut,strlen(cOut));	// 输出
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
