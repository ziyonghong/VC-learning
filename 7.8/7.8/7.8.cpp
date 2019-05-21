// 7.8.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "7.8.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HWND hWndMain;	// ���崰�ھ��
HDC hDC;	// �����豸�������
HDC hdcmem;	// �����ڴ���
HBITMAP hBm;	// ����λͼ���
BITMAP bm;	// ����λͼ�ṹ����
int iY = 80;	// λͼ���Ͻǳ�ʼ y ����
int iWindowWidth,iWindowHeight;	// ���ڵĿ�Ⱥ͸߶�
char cUpWarn[] = "�����������ƶ���";	// ���Ͼ����ַ���
char cDownWarn[] = "�����������ƶ���";	// ���¾����ַ���

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
	MSG msg;// ������Ϣ����
	HACCEL hAccelTable;

	hBm = LoadBitmap(hInstance,L"forest");	// ����λͼ
	GetObject(hBm,sizeof(BITMAP),(LPVOID)&bm);	// ���λͼ��Ϣ
	iWindowWidth = 2 * bm .bmWidth;	// �õ����ڵĿ��
	iWindowHeight = 2 * bm .bmHeight;	// �õ����ڵĸ߶�
	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY78, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY78));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY78));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY78);
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


	switch (message)
	{
	case WM_LBUTTONDOWN:	// ���������
		iY = iY - 10;	// λͼ�߶� - 10
		InvalidateRect(hWnd,NULL,1);	// ˢ���û���
		break;
	case WM_RBUTTONDOWN:	// �������Ҽ�
		iY = iY + 10;	// λͼ�߶� + 10
		InvalidateRect(hWnd,NULL,1);	// ˢ���û���
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_UP:	// ���ϼ�ͷʱ,λ�� - 10
			iY = iY - 10;
			break;
		case VK_DOWN:	// ���¼�ͷʱ,λ�� + 10
			iY = iY + 10;
			break;
		}
		InvalidateRect(hWnd,NULL,1);	// ˢ���û���
		break;
	case WM_CREATE:	// ��ʼ��������Ϣ
		hDC = GetDC(hWnd);	// �õ��豸����ָ��
		hdcmem = CreateCompatibleDC(hDC);	// �õ��ڴ�ָ��
		ReleaseDC(hWnd,hDC);	// ɾ���豸����ָ��
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
		hDC = BeginPaint(hWnd,&ps);	// �õ��豸����ָ��
		if(iY > 0&&iY < iWindowHeight/ 2)	// ��λͼ�������ڴ�����ʱ
		{
			SelectObject(hdcmem,hBm);	// ѡ���ڴ���
			BitBlt(hDC,60,iY,bm .bmWidth,bm .bmHeight,hdcmem,0,0,SRCCOPY);// ���λͼ
		}
		else if(iY <= 0)	// ��λͼ���ϱ߽糬���˴���ʱ
		{
			TextOut(hDC,0,0,(LPCWSTR)cUpWarn,sizeof(cUpWarn));	// �������
		}
		else	// ��λͼ���±߽糬���˴���ʱ
		{
			TextOut(hDC,0,0,(LPCWSTR)cDownWarn,sizeof(cDownWarn));// �������
		}
		EndPaint(hWnd,&ps);	// ����������
		break;
	case WM_DESTROY:
		DeleteObject(hBm);	// ɾ���ڴ���
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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
