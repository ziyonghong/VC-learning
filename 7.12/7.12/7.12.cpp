// 7.12.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "7.12.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING]=L"ball";			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
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

	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY712, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY712));

	// ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY712));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY712);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}
	if( ! SetTimer(hWnd,1,50,NULL))
	{
		MessageBox(hWnd,L"Too many clocks or timers !", szWindowClass,MB_ICONEXCLAMATION|MB_OK);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC	hdc ,hdcMem;
	HBRUSH	hBrush;
	static HANDLE hBitmap;
	static short cxClient ,cyClient,xCenter,yCenter,cxTotal,cyTotal,
		cxRadius,cyRadius,cxMove,cyMove,xPixel,yPixel; 
	short	nScale;
	switch (message)
	{
	case WM_CREATE:
		hdc = GetDC (hWnd);
		xPixel = GetDeviceCaps(hdc,ASPECTX);// ȡ�ػ�һ�����õ� X �����ص�λ
		yPixel = GetDeviceCaps(hdc,ASPECTY); ReleaseDC (hWnd, hdc);
		return 0;
	case WM_SIZE:	// �յ��ı䴰�ڳߴ������ʱ, 
		xCenter = (cxClient = LOWORD (lParam))/ 2;
		yCenter = (cyClient = HIWORD (lParam))/ 2; // ָ���ͻ����ĸ߶�
		nScale = min(cxClient * xPixel,cyClient * yPixel)/ 16;
		cxRadius = nScale/ xPixel;
		cyRadius = nScale/ yPixel; 
		cxMove = max(1,cxRadius/ 4); 
		cyMove = max(1,cyRadius/ 4); 
		cxTotal = 2 * (cxRadius + cxMove);
		cyTotal = 2 * (cyRadius + cyMove);
		if(hBitmap)
			DeleteObject(hBitmap); 
		hdc = GetDC(hWnd);
		hdcMem = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc,cxTotal,cyTotal);
		ReleaseDC(hWnd,hdc);
		SelectObject(hdcMem,hBitmap);
		Rectangle(hdcMem, - 1, - 1,cxTotal + 1,cyTotal + 1);
		hBrush = CreateHatchBrush(HS_DIAGCROSS,0L); 
		SelectObject(hdcMem,hBrush); 
		SetBkColor(hdcMem,RGB(255,0,0));
		Ellipse(hdcMem,cxMove,cyMove,cxTotal - cxMove,cyTotal - cyMove);
		DeleteDC(hdcMem);
		DeleteObject(hBrush); return 0;
	case WM_TIMER: if( ! hBitmap)
					   break;
		hdc = GetDC(hWnd);
		hdcMem = CreateCompatibleDC(hdc);	// �����豸���
		SelectObject(hdcMem,hBitmap); BitBlt(hdc,xCenter - cxTotal/ 2,
			yCenter - cyTotal/ 2,cxTotal,cyTotal,hdcMem,0,0,SRCCOPY); ReleaseDC(hWnd,hdc);
		DeleteDC(hdcMem); xCenter += cxMove; yCenter += cyMove;
		if(( xCenter + cxRadius >= cxClient) |(xCenter - cxRadius <= 0)) cxMove = - cxMove;
		if((yCenter + cyRadius >= cyClient) |(yCenter - cyRadius <= 0)) cyMove = - cyMove;
		return 0;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
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
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		if(hBitmap)
			DeleteObject(hBitmap);
		KillTimer(hWnd,1);
		PostQuitMessage (0);// ����ϵͳ�˳�����
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);

}

// �����ڡ������Ϣ�������
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
