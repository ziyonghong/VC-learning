// 6.4.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "6.4.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

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
	LoadString(hInstance, IDC_MY64, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY64));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY64));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY64);
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
	HDC hDC;	// �����豸�������
	WORD x,y;	// ��������λ������
	HCURSOR hCursor;	// ��������
	HBRUSH hBrush;
	LPSIZE lpSize;	// ���ڳߴ�ṹ
	static char cLeftBtn[] = "LEFT BUTTON";	// ���嵥�����ʱ������ַ�
	static char cRightBtn[] = "RIGHT BUTTON";	// ���嵥���Ҽ�ʱ������ַ�
	RECT ClientRect;

	switch (message)
	{
	case WM_MOUSEMOVE:	// ��������ƶ���Ϣ
		x = LOWORD(lParam);	// ������� X ����
		y = HIWORD(lParam);	// ������� Y ����
		GetClientRect(hWnd,&ClientRect);	// �õ����ڴ�С
		if(y >= 0&&y <= ClientRect .bottom)
		{
			if(y >= 0&&y <= ClientRect .bottom/ 5)	// �ڴ�����,�Ǽ�ͷ
			{
				hCursor = LoadCursor(NULL,IDC_ARROW); SetCursor(hCursor);
			}
			else if(y >= ClientRect .bottom/ 5&&y <= ClientRect .bottom/ 5 * 2)// �ڴ�����Ϊʮ��ͼ��
			{
				hCursor = LoadCursor(NULL,IDC_CROSS); SetCursor(hCursor);
			}
			
			else if(y>= ClientRect.bottom/ 5 * 2&&y<= ClientRect.bottom/ 5 * 3)//������ - ���ϡ�����
			{
				hCursor = LoadCursor(NULL,IDC_SIZENESW); SetCursor(hCursor);
			}
			else if(y>= ClientRect.bottom/ 5 * 3&&y<= ClientRect.bottom/ 5 * 4)//���� - ��������
			{
				hCursor = LoadCursor(NULL,IDC_SIZENS); SetCursor(hCursor);
			}
			else	// �ڴ�����Ϊ�ȴ����
			{
				hCursor = LoadCursor(NULL,IDC_WAIT); SetCursor(hCursor);
			}
			}
			return 0;
	case WM_LBUTTONDOWN:	// ������
		hDC = GetDC(hWnd);	// �õ��豸�������
		SetBkColor(hDC,RGB(255,255,0));	// ���ñ���ɫ
		TextOut(hDC,0,0,(LPCWSTR)cLeftBtn,strlen(cLeftBtn));	// ���
		ReleaseDC(hWnd,hDC);	// �ͷ��豸�������
		break;
	case WM_RBUTTONDOWN:	// �����ҽ�
		hDC = GetDC(hWnd);	// �õ��豸�������
		SetBkColor(hDC,RGB(255,255,0));	// ���ñ���ɫΪ��ɫ
		TextOut(hDC,0,0,cRightBtn,strlen(cRightBtn));	// ���
		ReleaseDC(hWnd,hDC);	// �ͷ��豸�������break;
	case WM_SIZE:
		hDC = GetDC(hWnd);	// �õ��豸�������
		SetMapMode(hDC,MM_ANISOTROPIC);	// ����ӳ��ģʽ
		SetViewportExtEx(hDC,LOWORD(lParam),HIWORD(lParam),lpSize);// �����Կ�����
		SetWindowExtEx(hDC,100,50,lpSize);	//  ���ô�������
		hBrush = CreateSolidBrush(RGB(255,255,255));	// �����ɫ��ˢ
		SelectObject(hDC,hBrush);	// ѡ���ɫ��ˢ
		Rectangle(hDC,0,0,100,10);	// ������
		DeleteObject(hBrush);	// ɾ����ˢ
		hBrush = CreateSolidBrush(RGB(0,255,0));	// ������ɫ��ˢ
		SelectObject(hDC,hBrush);	// ѡ����ɫ��ˢ
		Rectangle(hDC,0,10,100,20);	// ������
		DeleteObject(hBrush);	// ɾ����ˢ
		hBrush = CreateSolidBrush(RGB(0,0,255));	// ������ɫ��ˢ
		SelectObject(hDC,hBrush);	// ѡ����ɫ��ˢ
		Rectangle(hDC,0,20,100,30);	// ������
		DeleteObject(hBrush);	// ɾ����ˢ
		hBrush = CreateSolidBrush(RGB(255,255,0));	// �����ɫ��ˢ
		SelectObject(hDC,hBrush);	// ѡ���ɫ��ˢ
		Rectangle(hDC,0,30,100,40);	// ������
		DeleteObject(hBrush);	// ɾ����ɫ��ˢ
		hBrush = CreateSolidBrush(RGB(255,0,0));	// �����ɫ��ˢ
		SelectObject(hDC,hBrush);	// ѡ�뻭ˢ
		Rectangle(hDC,0,40,100,50);	// ������
		DeleteObject(hBrush);	// ɾ����ˢ
		ReleaseDC(hWnd,hDC);	// ɾ���豸�������
		break;
	case WM_DESTROY:	// �����˳�������Ϣ
		PostQuitMessage(0); return 0;
	default:
		return(DefWindowProc(hWnd,message,wParam,lParam));
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
