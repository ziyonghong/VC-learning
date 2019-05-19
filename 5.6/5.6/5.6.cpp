// 5.6.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "5.6.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HFONT CreateMyFont(TCHAR* chFont);
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
	LoadString(hInstance, IDC_MY56, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY56));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY56));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY56);
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
	HFONT hF;	// ����������
	PAINTSTRUCT ps;	// ���������ͼ��Ϣ�Ľṹ�����
	TEXTMETRIC tm;	// �������������Ϣ�Ľṹ�����
	LPWSTR lpsz_1 = L"����ǧ��Ŀ ����һ��¥";	// ��������ַ���
	//char lpsz_1[] = "����ǧ��Ŀ ����һ��¥";
	char chFont[7];	// �������������ַ���
	int X = 0,Y = 0,nCharlen = 11;
	//int nCharlen=strlen(lpsz_1);
	int iFontFlag = 0;	// ���������־
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd,1,200,NULL);	// ÿ 0 .2 �뷢�� WM- TIMER ��Ϣ
		break;
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
		hDC = BeginPaint(hWnd,&ps);	// ��ȡ�豸�������
		if(iFontFlag/nCharlen == 0)	// ����������ɫ
		{
			SetTextColor(hDC,RGB(255,0,0));
			hF=CreateMyFont(L"����");
		}
		else if(iFontFlag/ nCharlen == 1)
		{
			SetTextColor(hDC,RGB(0,255,0));hF=CreateMyFont(L"����");
		}
		else if(iFontFlag/ nCharlen == 2)
		{
			SetTextColor(hDC,RGB(255,255,0));hF=CreateMyFont(L"������");
		}
		else if(iFontFlag/ nCharlen == 3)
		{
			SetTextColor(hDC,RGB(0,0,255)); hF=CreateMyFont(L"����");
		}
		else
		{
			iFontFlag = 0; SetTextColor(hDC,RGB(255,0,0));
		}
		
		SelectObject(hDC,hF);	// ѡ������
		GetTextMetrics(hDC,&tm);	// �õ��������Ϣ
		TextOut(hDC,X,Y,&lpsz_1[iFontFlag % nCharlen],nCharlen - iFontFlag % nCharlen);
		iFontFlag += 2;	// �����־����
		DeleteObject(hF);	// ɾ������
		EndPaint(hWnd,&ps);	// ɾ���豸�������
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
// ��������
		HFONT CreateMyFont(TCHAR* chFont)
		{
		return  CreateFont(	// ���������
			40,	// ����߶�
			0,	// ϵͳ�Զ��������
			0,	// �ı�ˮƽ
			0,	// ������б��Ϊ 0
			400,	// ����ֶ� .400 Ϊ����
			0,	// ���岻��б
			0,	// ���»���
			0,	// ��ɾ����
			GB2312_CHARSET,	// �ַ���
			OUT_DEFAULT_PRECIS,	// Ĭ���������
			CLIP_DEFAULT_PRECIS,	// Ĭ�ϲü�����
			DEFAULT_QUALITY,	// Ĭ���������
			DEFAULT_PITCH|FF_DONTCARE,	// Ĭ�ϼ��
			chFont);	// ��������
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
