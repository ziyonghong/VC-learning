// 4.7.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "4.7.h"

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
	MSG msg;  //������Ϣ����
	
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY47, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY47));

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
	WNDCLASSEX wcex;//���崰����

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY47));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY47);
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
   HWND hWnd; //���崰�ھ��

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
		hDC = BeginPaint(hWnd, &PtStr);
		// TODO: �ڴ���������ͼ����...
		 SetMapMode(hDC,MM_ANISOTROPIC);	// ����ӳ��ģʽ
    SetWindowExtEx(hDC,300,300,NULL);	// ���ô������� .�߼���λ
    SetViewportExtEx(hDC,600,600,NULL);	// �����ӿ����� .����λ
    SetViewportOrgEx(hDC,0,0,NULL);	// �����ӿ�ԭ������λ����(0,0)
   // �����ĸ�Բ�� .(�ʵ���ʽ��ͬ)
    hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	// ѡ��ջ�ˢ
    SelectObject(hDC,hBrush);
    hPen = CreatePen(PS_DASH,0,RGB(255,0,0));	// ����������ʽ�ĺ�ɫ����
    SelectObject(hDC,hPen);	// ѡ���豸����
    Ellipse(hDC,0,0,70,70);	// ��Բ
    hPen = CreatePen(PS_DASHDOT,0,RGB(0,255,0));	// �����㻮����ʽ����ɫ����
    SelectObject(hDC,hPen);
    Ellipse(hDC,25,0,95,70);	// ��Բ
    hPen = CreatePen(PS_DASHDOTDOT,0,RGB(0,0,255));	// ����˫�㻮����ʽ����ɫ����
    SelectObject(hDC,hPen);
    Ellipse(hDC,0,25,70,95);
    hPen = CreatePen(PS_DOT,0,RGB(0,255,255));	// ����������ʽ������ɫ����
    SelectObject(hDC,hPen);
    Ellipse(hDC,25,25,95,95);
   // �� 6 ��Բ�Ǿ��� .(ʵ��ˢ��ʽ��ͬ .)
    hPen = (HPEN)GetStockObject(BLACK_PEN);
    SelectObject(hDC,hPen);
    hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);	// ѡ���ɫ��ˢ
    SelectObject(hDC,hBrush);	// ѡ���豸����
    RoundRect(hDC,120,0,165,45,10,10);	// ��Բ�Ǿ���
    hBrush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);	// ѡ�����ɫ��ˢ
    SelectObject(hDC,hBrush);
    RoundRect(hDC,165,0,210,45,10,10);
    hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);	// ѡ���ɫ��ˢ
    SelectObject(hDC,hBrush);
    RoundRect(hDC,210,0,255,45,10,10);
    hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);	// ѡ���黭ˢ
	 SelectObject(hDC,hBrush);
    RoundRect(hDC,120,45,165,90,10,10);
    hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);	// ѡ�����һ�ˢ
    SelectObject(hDC,hBrush);
    RoundRect(hDC,165,45,210,90,10,10);
    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);	// ѡ��׻�ˢ
    SelectObject(hDC,hBrush);
    RoundRect(hDC,210,45,255,90,10,10);
   // �� 6 ������ .(��ˢ��Ӱ��ʽ��ͬ .)
    hPen = (HPEN)GetStockObject(BLACK_PEN);
    SelectObject(hDC,hPen);
    hBrush = CreateHatchBrush(HS_BDIAGONAL,RGB(200,200,200)); // ���� 45 ������������Ӱ��
    SelectObject(hDC,hBrush);	// ����ˢѡ���豸����
    Rectangle(hDC,120,90,165,135);	// ������
    hBrush = CreateHatchBrush(HS_DIAGCROSS,RGB(200,200,200)); // ���� 45 �Ƚ�����
    SelectObject(hDC,hBrush);
    Rectangle(hDC,165,90,210,135);
    hBrush = CreateHatchBrush(HS_FDIAGONAL,RGB(200,200,200)); // ���� 45 ������������Ӱ��
    SelectObject(hDC,hBrush);
    Rectangle(hDC,210,90,255,135);
    hBrush = CreateHatchBrush(HS_CROSS,RGB(200,200,200));	// ������ֱ�ཻ��Ӱ��
    SelectObject(hDC,hBrush);
    Rectangle(hDC,120,135,165,175);
    hBrush = CreateHatchBrush(HS_HORIZONTAL,RGB(200,200,200)); // ����ˮƽ��Ӱ��
    SelectObject(hDC,hBrush);
    Rectangle(hDC,165,135,210,175);
    hBrush = CreateHatchBrush(HS_VERTICAL,RGB(200,200,200));	// ������ֱ��Ӱ��
    SelectObject(hDC,hBrush);
    Rectangle(hDC,210,135,255,175);
   // ����ͼ
    hPen = (HPEN)GetStockObject(BLACK_PEN);
    SelectObject(hDC,hPen);
    hBrush = CreateSolidBrush(RGB(255,0,0));	// ������ɫ��ˢ
    SelectObject(hDC,hBrush);	// ѡ���豸����
    Pie(hDC,10,100,	// ����ͼ
100,190,
(int)(55 + 45 * cos(2 * Pi/ 3)),(int)(145 + 45 * sin(2 * Pi/ 3)), (int)(55 + 45 * cos(0.0)),(int)(145 + 45 * sin(0.0)));
    hBrush = CreateSolidBrush(RGB(0,255,255));	// ��������ɫ��ˢ
    SelectObject(hDC,hBrush);	// ѡ���豸����
    Pie(hDC,10,100,
100,190,
(int)(55 + 45 * cos(4 * Pi/ 3)),(int)(145 + 45 * sin(4 * Pi/ 3)),
(int)(55 + 45 * cos(2 * Pi/ 3)),(int)(145 + 45 * sin(2 * Pi/ 3)));
    hBrush = CreateSolidBrush(RGB(255,255,0));	// ������ɫ��ˢ
    SelectObject(hDC,hBrush);	// ѡ���豸����
    Pie(hDC,10,100,
100,190,
(int)(55 + 45 * cos(2 * Pi)),(int)(145 + 45 * sin(2 * Pi)), (int)(55 + 45 * cos(4 * Pi/ 3)),(int)(145 + 45 * sin(4 * Pi/ 3)));
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
