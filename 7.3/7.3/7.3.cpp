// 7.3.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "7.3.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HWND hdlg;
TCHAR str[200];
BOOL CALLBACK ModalDlgProc(HWND hdlg,UINT message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK ModalessDlgProc(HWND hdlg,UINT message,WPARAM wParam,LPARAM lParam);

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
	LoadString(hInstance, IDC_MY73, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY73));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY73));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY73);
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
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_OPEN:
			MessageBox(hWnd,L"文件已经打开",L"文件打开",MB_OK);
			break;
			
		case IDM_SAVE:
			MessageBox(hWnd,L"文件已经保存",L"文件保存",MB_OK);
			break;
		
		case IDM_EXIT:
			SendMessage(hWnd,WM_DESTROY,0,0);
			DestroyWindow(hWnd);
			break;
		case IDM_MODAL:  //创建并显示模式对话框
			DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)ModalDlgProc);
		break;
		case IDM_MODALLESS:
			hdlg=CreateDialog(hInst,MAKEINTRESOURCE(IDD_DIALOG1), hWnd,(DLGPROC)ModalessDlgProc);
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//输出对话框返回的信息
		TextOut(hdc,0,0,str,_tcslen(str));
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

BOOL CALLBACK ModalDlgProc(HWND hdlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	TCHAR mystr[200];
	switch(message)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hdlg,IDC_TITLE,L"模式对话框示例");
		return 1;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hdlg,IDC_EDIT1,mystr,200);
			_tcscpy(str,L"这是模式窗口输入的信息:");
			_tcscat(str,mystr);
			InvalidateRect(GetParent(hdlg),NULL,true);
			EndDialog(hdlg,0);
			return 1;
		case IDCANCEL:
			SetDlgItemText(hdlg,IDC_EDIT1,L"");
			return 1;
		}
		break;
	case WM_CLOSE:
		EndDialog(hdlg,0);
		return 1;
	}
	return 0;

}

BOOL CALLBACK ModalessDlgProc(HWND hdlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	TCHAR mystr[200];
	switch(message)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hdlg,IDC_TITLE,L"非模式对话框示例");
		return 1;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hdlg,IDC_EDIT1,mystr,200);
			_tcscpy(str,L"这是非模式窗口输入的信息");
			_tcscat(str,mystr);
			InvalidateRect(GetParent(hdlg),NULL,true);
			DestroyWindow(hdlg);
			return 1;
		case IDCANCEL:
			SetDlgItemText(hdlg,IDC_EDIT1,L"");
			return 1;
		}
		break;
	case WM_CLOSE:
		EndDialog(hdlg,0);
		return 1;
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
