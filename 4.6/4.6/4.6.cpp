// 4.6.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "4.6.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
double dfTheta = 0,dfRange = 100.0;	// �������ߵĽǶȱ���
long i = 0,j = 0;
long lCentreX = 0,lCentreY = 0,lRadious = (long)(0.2 * dfRange); // ����Բ�������Բ����
POINT lpSin[100];	// �����������ߵĵ�����
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
	LoadString(hInstance, IDC_MY46, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY46));

	for(int j = 0;j < 100;j++ )	// �����������ߵĵ�����
	{
		lpSin[j] .x = (long)(j * 2 * Pi/ 100 * 60);
		lpSin[j] .y = (long)(dfRange * sin(j * 2 * Pi/ 100));
	}
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY46));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY46);
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
	HDC hDC;	// �����豸�������
	HBRUSH hBrush;	// ���廭ˢ���
	HPEN hPen;	// ���廭�ʾ��
	PAINTSTRUCT PtStr;	// ���������ͼ��Ϣ�Ľṹ�����

	switch (message)
	{
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
		hDC = BeginPaint(hWnd,&PtStr);	// ����豸����ָ��
		SetWindowOrgEx(hDC, - 200, - 200,NULL);	// ����ԭ������Ϊ(-20 ,-200)
		hPen = CreatePen(PS_DASH,1,RGB(255,0,0));	// �������ʾ��
		SelectObject(hDC,hPen);	// ѡ�뻭��
		Polyline(hDC,lpSin,100);	// ������������
		if(i <= 25)	// ��һ�� 1/ 4 ����
		{
			hPen = CreatePen(PS_DASH,1,RGB(255,0,0));	// ������ɫ����
			hBrush = CreateHatchBrush(HS_BDIAGONAL,RGB(255,0,0)); // ������ɫ��ˢ
			lRadious = (long)(dfRange * 0.2 + i% 25 * dfRange * 0.4/ 25); // ����뾶
		}
		else if(i <= 50)	// �ڶ��� 1/ 4 ����
		{
			hPen = CreatePen(PS_DASH,1,RGB(0,255,0));	// ������ɫ����
			hBrush = CreateHatchBrush(HS_DIAGCROSS,RGB(0,255,0)); // ������ˢ
			lRadious = (long)(dfRange * 0.2 + i% 25 * dfRange * 0.4/ 25); // ����뾶
		}
		else if(i <= 75)	// ����������
		{
			hPen = CreatePen(PS_DASH,1,RGB(0,0,255));	// ������ɫ����
			hBrush = CreateHatchBrush(HS_CROSS,RGB(0,0,255)); // ������ɫ��ˢ
			lRadious = (long)(dfRange * 0.2 + i% 25 * dfRange * 0.4/ 25); // ����뾶
		}
		else	// ���ĸ�����
		{
			hPen = CreatePen(PS_DASH,1,RGB(255,255,0)); // �� �� �� ɫ �� ��
			hBrush = CreateHatchBrush(HS_VERTICAL,RGB(255,255,0));// ������ɫ��ˢ
			lRadious = (long)(dfRange * 0.2 + i% 25 * dfRange * 0.4/ 25); // ����뾶
		}
		SelectObject(hDC,hBrush);	// ѡ�뻭ˢ
		SelectObject(hDC,hPen);	// ѡ�뻭��
		lCentreX = lpSin[i] .x;	// Բ�� x ����
		lCentreY = lpSin[i] .y;	// Բ�� y ����
		Ellipse(hDC,lCentreX - lRadious,lCentreY - lRadious,
			lCentreX + lRadious,lCentreY + lRadious);	// ��Բ
		i++;
		DeleteObject(hPen);	// ɾ������
		DeleteObject(hBrush);	// ɾ����ˢ
		EndPaint(hWnd,&PtStr);	// ɾ���豸�������
		Sleep(100);	// ͣ 0 .1 ��
		if(i < 100) InvalidateRect(hWnd,NULL,1);	// ˢ���û���
		return 0;

	case WM_DESTROY:
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
