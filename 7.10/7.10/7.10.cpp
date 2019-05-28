// 7.10.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "7.10.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HWND hWndMain;	// 定义全局窗口句柄
RECT rect1 = {100,100,100,100};	// 定义矩形结构体
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
	LoadString(hInstance, IDC_MY710, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY710));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY710));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY710);
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

	HMENU hMenu1,hMenu2;	// 定义菜单句柄
	HDC hDC;	// 定义设备环境句柄
	static BOOL bCircle = FALSE,bRect = FALSE;	// 设置绘制圆和矩形的标志变量
	static BOOL bMove = FALSE;	// 设置移动标志
	PAINTSTRUCT ps;	// 定义绘图结构体变量
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_CIRCLE:	// 单击圆形菜单
			hMenu1 = GetMenu(hWnd);	// 得到菜单句柄
			CheckMenuItem(hMenu1,IDM_CIRCLE,MF_CHECKED);	// 设置选中标志
			CheckMenuItem(hMenu1,IDM_RECTANGLE,MF_UNCHECKED); // 删除标志
			DeleteMenu(hMenu1,1,MF_BYPOSITION);	// 删除“矩形”弹出菜单
			hMenu2 = CreateMenu();	// 动态创建菜单
			// 添加菜单项
			AppendMenu(hMenu2,MF_ENABLED,IDM_DRAWCIRCLE,L"绘制圆形(&d)"); 
			AppendMenu(hMenu2,MF_ENABLED,IDM_MOVECIRCLE,L"移动圆形(&m)"); 
			AppendMenu(hMenu2,MF_ENABLED,IDM_ZOOMIN,L"放大(&i)");
			AppendMenu(hMenu2,MF_ENABLED,IDM_ZOOMOUT,L"缩小(&o)"); 
			AppendMenu(hMenu2,MF_ENABLED,IDM_REDRAW,L"重绘(&r)");
			// 插入菜单。
			InsertMenu(hMenu1,1,MF_POPUP|MF_BYPOSITION,(UINT)hMenu2,L"圆形(&c)"); 
			DrawMenuBar(hWndMain);	// 刷新菜单
			bCircle = FALSE;	// 绘圆标志为″假″
			bRect = FALSE;	// 绘矩形标志为″假″
			bMove = FALSE;	// 移动标志为″假″
			rect1 .left = 100;	// 恢复矩形的初始状态
			rect1 .right = 100;
			rect1 .bottom = 100;
			rect1 .top = 100;
			InvalidateRect(hWnd,NULL,TRUE);	// 发出刷新信息
			break;
		case IDM_RECTANGLE:	// 单击矩形菜单
			hMenu1 = GetMenu(hWnd);	// 得到菜单句柄
			CheckMenuItem(hMenu1,IDM_CIRCLE,MF_UNCHECKED);	// 删除选中标志
			CheckMenuItem(hMenu1,IDM_RECTANGLE,MF_CHECKED);	// 设置选中标志
			DeleteMenu(hMenu1,1,MF_BYPOSITION);	// 删除″圆形″弹出菜单
			hMenu2 = LoadMenu(hInst,L"menuRect");	// 得到菜单句柄
			// 插入菜单
			InsertMenu(hMenu1,1,MF_POPUP|MF_BYPOSITION,(UINT)hMenu2,L"矩形(&r)");
			DrawMenuBar(hWndMain);	// 刷新菜单
			bCircle = FALSE;	// 绘圆标志为″假″
			bRect = FALSE;	// 绘矩形标志为″假″
			bMove = FALSE;	// 移动标志为″假″
			rect1 .left = 100;	// 恢复矩形的初始状态
			rect1 .right = 100;
			rect1 .bottom = 100;
			rect1 .top = 100;
			InvalidateRect(hWnd,NULL,TRUE);	// 发出刷新信息
			break; 
		case IDM_EXIT:
			SendMessage(hWnd,WM_DESTROY,0,0);	// 发出关闭窗口信息
			break;
		case IDM_DRAWCIRCLE:	// 绘制圆形
			bCircle = TRUE;	// 绘圆标志为″真″
			bRect = FALSE;	// 绘矩形标志为″假″
			bMove = FALSE;	// 移动标志为″假″
			break;
		case IDM_DRAWRECT:	// 绘制矩形
			bCircle = FALSE;	// 绘圆标志为″假″
			bRect = TRUE;	// 绘矩形标志为″真″
			bMove = FALSE;	// 移动标志为″假″
			break;
		case IDM_MOVECIRCLE:	// 移动圆形
			bMove = TRUE;	// 移动标志为″真″
			break;
		case IDM_MOVERECT:	// 移动矩形
			bMove = TRUE;	// 移动标志为″真″
			break;
		case IDM_ZOOMIN:	// 放大
			if(bCircle == TRUE|bRect == TRUE)
			{
				int nLength,nWidth;
				nLength = abs(rect1 .right - rect1 .left);	// 计算长度
				nWidth = abs(rect1 .top - rect1 .bottom);	// 计算宽度
				rect1 .right = (int)(rect1 .left+ nLength * 1.2); // 放大
				rect1 .bottom = (int)(rect1 .top + nWidth * 1.2);
				InvalidateRect(hWnd,NULL,TRUE);	// 发出刷新信息
			}
			break;
		case IDM_ZOOMOUT:	// 缩小
			if(bCircle == TRUE | bRect == TRUE)
			{
				int nLength,nWidth;
				nLength = abs(rect1 .right - rect1 .left);	// 计算长度
				nWidth = abs(rect1 .top - rect1 .bottom);	// 计算宽度
				rect1 .right = (int)(rect1 .left + nLength/ 1.2);// 缩小
				rect1 .bottom = (int)(rect1 .top + nWidth/ 1.2);
				InvalidateRect(hWnd,NULL,TRUE);	// 发出刷新信息
			}
			break;
		case IDM_REDRAW:	// 重新绘图
			bMove = FALSE;	// 移动标志为″假″
			rect1 .left = 100;	// 恢复矩形的初始状态
			rect1 .right = 100;
			rect1 .top = 100;
			rect1 .bottom = 100;
			InvalidateRect(hWnd,NULL,TRUE);	// 发出刷新信息
			break;
		}
		break; case WM_KEYDOWN:
		if(bMove == TRUE)
		{
			if(wParam == VK_LEFT)
			{	// 按″左箭头″键,向左移动
				rect1 .left -= 10;
				rect1 .right -= 10;
				InvalidateRect(hWnd,NULL,TRUE);	// 发出刷新信息
			}
			else if(wParam == VK_RIGHT)
			{	// 按″右箭头″键,向右移动
				rect1 .left += 10;
				rect1 .right += 10;
				InvalidateRect(hWnd,NULL,TRUE);	// 发出刷新信息
			}
			else if(wParam == VK_UP)
			{	// 按″上箭头″键时,向上移动
				rect1 .top -= 10;
				rect1 .bottom -= 10;
				InvalidateRect(hWnd,NULL,TRUE);	// 发出刷新信息
			}
			else if(wParam == VK_DOWN)
			{	// 按″下箭头″键,向下移动
				rect1 .top += 10;
				rect1 .bottom += 10;
				InvalidateRect(hWnd,NULL,TRUE);	// 发出刷新信息
			}
		}
		else if(bCircle == TRUE | bRect == TRUE)
		{
			if(wParam == VK_RIGHT)
			{
				rect1 .right += 10;	// 按下″右箭头″矩形框长度 + 10
				InvalidateRect(hWnd,NULL,TRUE);	// 发出刷新信息
			}
			else if(wParam == VK_DOWN)
			{
				rect1 .bottom += 10;	// 按下″下箭头″矩形框高度 + 10
				InvalidateRect(hWnd,NULL,TRUE);	// 发出刷新信息
			}
			else if(wParam == VK_UP)
			{
				rect1 .bottom -= 10;	// 按下″上箭头″矩形框高度 - 10
				InvalidateRect(hWnd,NULL,TRUE);	// 发出刷新信息
			}
			else if(wParam == VK_LEFT)
			{
				rect1 .right -= 10;	// 按下″左箭头″矩形框高度 - 10
				InvalidateRect(hWnd,NULL,TRUE);	// 发出刷新信息
			}
		}
		break; 
		case WM_PAINT:
			hDC = BeginPaint(hWnd,&ps);
			if(bCircle == TRUE)
			{	// 绘制圆形
				Ellipse(hDC,rect1 .left,rect1 .top,rect1 .right,rect1 .bottom);
			}

			if(bRect == TRUE)
			{Rectangle(hDC,rect1 .left,rect1 .top,rect1 .right,rect1 .bottom);
			}

			EndPaint(hWnd, &ps);
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
