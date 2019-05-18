// 4.5.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "4.5.h"

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
	LoadString(hInstance, IDC_MY45, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY45));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY45));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY45);
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
	double dfRadious0 = 100.0,dfRadious1;	// �ⲿ/ �ڲ�����������Բ�뾶
	POINT lpOuterPoints[5],lpInnerPoints[5];	// ������,��������ε�ṹ����
	POINT lpTriangle[3];	// ���������ε�ṹ����
	dfRadious1 = dfRadious0 * sin(0.1 * Pi)/ sin(126.0/ 180 * Pi); // ������Բ�뾶������Բ�뾶
	// ��������������εĵ�����
	for(int i = 0;i < 5;i++)
	{
		lpOuterPoints[i] .x = (long)(dfRadious0 * cos(i * 72.0/ 180 * Pi));
		lpOuterPoints[i] .y = (long)(dfRadious0 * sin(i * 72.0/ 180 * Pi));
		lpInnerPoints[i] .x = (long)(dfRadious1 * cos(i * 72.0/ 180 * Pi + 36.0/ 180 * Pi));
		lpInnerPoints[i] .y = (long)(dfRadious1 * sin(i * 72.0/ 180 * Pi + 36.0/ 180 * Pi));
	}

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
		hDC = BeginPaint(hWnd,&PtStr);	// �õ��豸�������
		SetMapMode(hDC,MM_ANISOTROPIC);	// ����ӳ��ģʽ
		SetWindowOrgEx(hDC, - 100, - 100,NULL);      // ��������ԭ��
		hPen = CreatePen(PS_SOLID,1,RGB(255,0,0)); // ������ɫ����
		SelectObject(hDC,hPen);	// ������ѡ��
		Polygon(hDC,lpOuterPoints,5);	// ���������
		int i;
		for( i= 0;i < 5;i++ )	// ���������εĲ�ͬ����
		{
			lpTriangle[0] = lpOuterPoints[i % 5];	// ����ͼ���е����������������
			lpTriangle[1] = lpInnerPoints[i % 5]; lpTriangle[2] = lpOuterPoints[(i + 1) % 5];
			hBrush = CreateSolidBrush(RGB(i * 10,i * 20,i * 9));// �����»�ˢ
			SelectObject(hDC,hBrush);	// ѡ���»�ˢ
			Polygon(hDC,lpTriangle,3);	// ������������
			lpTriangle[2] = lpInnerPoints[(i + 4) % 5];	// ����ͼ���е����������������
			hBrush = CreateSolidBrush(RGB(i * 1,i * 30,i * 20));// ������ˢ
			SelectObject(hDC,hBrush);	// ѡ�뻭ˢ
			Polygon(hDC,lpTriangle,3);	// ������������
		}
		hBrush = CreateSolidBrush(RGB(255,255,255));	// �����׻�ˢ
		SelectObject(hDC,hBrush);
		Polygon(hDC,lpInnerPoints,5);	// �����ĵ������
		// �ò�ͬ����ɫ�Ļ��������������
		MoveToEx(hDC,lpOuterPoints[0] .x,lpOuterPoints[0] .y,NULL); 
		for(i = 1;i <= 5;i++)
		{
			hPen = CreatePen(PS_SOLID,1,RGB(0,i * 51,0));
			SelectObject(hDC,hPen);
			LineTo(hDC,lpOuterPoints[(i + 2) % 5].x,lpOuterPoints[(i + 2) % 5].y);
		}
		hPen = (HPEN)(GetStockObject(PS_NULL));
		DeleteObject(hPen);	//ɾ������
		DeleteObject(hBrush);	// ɾ����ˢ
		EndPaint(hWnd,&PtStr);	// ������ͼ

		break;
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
