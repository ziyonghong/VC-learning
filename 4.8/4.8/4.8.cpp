// 4.8.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "4.8.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

int nNum=0,nMaxNum=20;// nMaxNum ΪҶƬѭ��һ���л�ͼ�Ĵ���
// nNum ��¼�˵�ǰ������

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
	LoadString(hInstance, IDC_MY48, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY48));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY48));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY48);
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
	PAINTSTRUCT PtStr;
	HDC hDC;
	HBRUSH hBrush;	// ���廭ˢ���
HPEN hPen;	// ���廭�ʾ��
int nCentreX,nCentreY;	// ���� 3 ��ҶƬ��Բ�ĵ�����
double fAngle; 
	
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
    SetMapMode(hDC,MM_ANISOTROPIC);	// ����ӳ��ģʽ
    SetWindowExtEx(hDC,400,300,NULL);	// ���ô������� .�߼���λ
    SetViewportExtEx(hDC,600,450,NULL);	// �����ӿ����� .����λ
    SetViewportOrgEx(hDC,300,200,NULL);	// �����ӿ�ԭ������Ϊ(300,200)
   // ������Բ
    hPen = (HPEN)GetStockObject(BLACK_PEN);
    SelectObject(hDC,hPen);
    Ellipse(hDC, - 100, - 100,100,100);
   // ���Ʒ糵��ҶƬ��
    hBrush = CreateSolidBrush(RGB(255,0,0));	// ����ɫ��ҶƬ
    SelectObject(hDC,hBrush);
    fAngle = 2 * Pi/ nMaxNum * nNum;
    nCentreX = (int)(50 * cos(fAngle));
    nCentreY = (int)(50 * sin(fAngle));
    Pie( hDC,nCentreX - 50,nCentreY - 50, nCentreX + 50,nCentreY + 50,
(int)(nCentreX + 50 * cos(fAngle)),(int)(nCentreY + 50 * sin(fAngle)),
(int)(nCentreX + 50 * cos(fAngle + Pi)),(int)(nCentreY + 50 * sin(fAngle + Pi)));
    hBrush = CreateSolidBrush(RGB(255,255,0));	// ������ɫ��ҶƬ
    SelectObject(hDC,hBrush);
    nCentreX = (int)(50 * cos(fAngle + 2 * Pi/ 3));
    nCentreY = (int)(50 * sin(fAngle + 2 * Pi/ 3));
    Pie( hDC,nCentreX - 50,nCentreY - 50, nCentreX + 50,nCentreY + 50,
(int)(nCentreX + 50 * cos(fAngle + 2 * Pi/ 3)),(int)(nCentreY + 50 * sin(fAngle + 2 *
Pi/ 3)),
(int)(nCentreX + 50 * cos(fAngle + Pi + 2 * Pi/ 3)),(int)(nCentreY + 50 * sin(fAngle + Pi + 2 * Pi/ 3)));
    hBrush = CreateSolidBrush(RGB(0,255,255));	// ����ɫ��ҶƬ
    SelectObject(hDC,hBrush);
    nCentreX = (int)(50 * cos(fAngle + 4 * Pi/ 3));
    nCentreY = (int)(50 * sin(fAngle + 4 * Pi/ 3));
    Pie( hDC,nCentreX - 50,nCentreY - 50, nCentreX + 50,nCentreY + 50,
(int)(nCentreX + 50 * cos(fAngle + 4 * Pi/ 3)),(int)(nCentreY + 50 * sin(fAngle + 4 *
Pi/ 3)),
(int)(nCentreX + 50 * cos(fAngle + Pi + 4 * Pi/ 3)),(int)(nCentreY + 50 * sin(fAngle + Pi + 4 * Pi/ 3)));
	  nNum++;	// ��ǰ������ 1
    Sleep(100);	// �ȴ� 0 .1 ��
    InvalidateRect(hWnd,NULL,1);	// �ػ洰������
		EndPaint(hWnd, &PtStr);
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
