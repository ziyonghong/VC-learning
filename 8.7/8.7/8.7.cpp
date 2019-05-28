// 8.7.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "8.7.h"

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
	LoadString(hInstance, IDC_MY87, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY87));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY87));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY87);
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
	PAINTSTRUCT ps;	// ���������ͼ��Ϣ�Ľṹ��
	static HWND hWndScrollBarHor,hWndScrollBarVer;	// ����ˮƽ����ֱ�������ľ��
	static SCROLLINFO stScrollInfo;	// ���������������Ϣ�Ľṹ��
	static int iHorPos = 1,iVerPos = 100;	// ���������λ��
	char cOut[] = "ף���ɹ� .";	// ����ַ���
	RECT rcRedrawArea = {0,0,380,200};	// ����ˢ������
	switch (message)
	{
	case WM_CREATE:	// ���ڴ�����Ϣ
		// ������ֱ������
		hWndScrollBarVer = CreateWindowEx(0L,	// ���崰����ʽ
			L"SCROLLBAR",	// ����������
			NULL,	// ����
			WS_CHILD|SBS_VERT,	// ��ʽ
			400,	// ���Ͻ� X ����
			30-GetSystemMetrics(SM_CYVSCROLL),	// ���Ͻ� Y ����
			GetSystemMetrics(SM_CYVSCROLL),	// ���������
			100 + 2 * GetSystemMetrics(SM_CYVSCROLL),   // ����������
			hWnd,	// �����ھ��
			NULL,	// �޲˵�
			hInst,	// ����ʵ�����
			NULL);	// ���ô˲���
		// ����ˮƽ������
		hWndScrollBarHor = CreateWindowEx(0L,	// ���崰����ʽ
			L"SCROLLBAR",	// ����������
			(LPCWSTR)NULL,	// ����
			WS_CHILD|SBS_HORZ,	// ��ʽ
			50,	// ���Ͻ� X ����
			200,	// ���Ͻ� Y ����
			100 + 2 * GetSystemMetrics(SM_CYHSCROLL),       // ���������
			GetSystemMetrics(SM_CYHSCROLL),	// ����������
			hWnd,	// �����ھ��
			(HMENU)NULL,	// �޲˵�
			hInst,	// ����ʵ�����
			(LPVOID)NULL);	// ���ô˲���
		stScrollInfo .cbSize = sizeof(SCROLLINFO);	// ����˽ṹ��Ĵ�С
		stScrollInfo .fMask = SIF_POS|SIF_RANGE|SIF_PAGE;	// ������������Բ���
		stScrollInfo .nMin = 1;	// �������������Сλ��
		stScrollInfo .nMax = 100;	// ��������������λ��
		stScrollInfo .nPos = 1;	// �������������������
		stScrollInfo .nPage = 10;	// �����������ҳ������
		// ���ù����������Բ���
		SetScrollInfo(hWndScrollBarVer,SB_CTL,&stScrollInfo,FALSE);
		SetScrollInfo(hWndScrollBarHor,SB_CTL,&stScrollInfo,FALSE);
		ShowWindow(hWndScrollBarHor,TRUE);
		ShowWindow(hWndScrollBarVer,TRUE);
		break;
	case WM_VSCROLL:	// ������ֱ����������Ϣ
		if((HWND)lParam != hWndScrollBarVer)
			break; switch(LOWORD(wParam))
		{
			case SB_LINEUP:	// ������һ��,λ�� + 5
				iVerPos += 5;
				break;
			case SB_LINEDOWN:	// ������һ��,λ�� - 5
				iVerPos -= 5;
				break;
			case SB_PAGEUP:	// ������һҳ,λ�� + 20
				iVerPos += 20;
				break;
			case SB_PAGEDOWN:	// ������һҳ,λ�� - 20
				iVerPos -= 20;
				break;
			case SB_THUMBPOSITION:	// �϶�������
				iVerPos = 101 - HIWORD(wParam);
				break; default:
				return(DefWindowProc(hWnd,message,wParam,lParam));
		}
		if(iVerPos < 1) iVerPos = 1;	// ����λ�õķ�Χ
		else if(iVerPos > 100) iVerPos = 100;
		// �趨����������Ϣ .��Ҫ���趨λ�� . 
		stScrollInfo .fMask = SIF_POS; 
		stScrollInfo .nPos = 101 - iVerPos;
		SetScrollInfo(hWndScrollBarVer,SB_CTL,&stScrollInfo,TRUE); 
		InvalidateRect(hWnd,&rcRedrawArea,1);	// ˢ���Զ�����û���
		break;
	case WM_HSCROLL:	// ˮƽ����������Ϣ
		if((HWND)lParam != hWndScrollBarHor)
			break; switch(LOWORD(wParam))
		{
			case SB_LINELEFT:	// �������һ��,λ�� - 5
				iHorPos -= 5;
				break;
			case SB_LINERIGHT:	// ���ҹ���һ��,λ�� + 5
				iHorPos += 5;
				break;
			case SB_PAGELEFT:	// �������һҳ,λ�� - 20
				iHorPos -= 20;
				break;
			case SB_PAGERIGHT:	// ���ҹ���һҳ,λ�� + 20
				iHorPos += 20;
				break;
			case SB_THUMBPOSITION:	// �϶�������
				iHorPos = HIWORD(wParam);
				break; 
			default:
				return(DefWindowProc(hWnd,message,wParam,lParam));
		}
		if(iHorPos < 1) iHorPos = 1;	// ����λ�÷�Χ
		else if(iHorPos > 100) iHorPos = 100;
		// �趨����������Ϣ .��Ҫ���趨λ��
		stScrollInfo .fMask = SIF_POS; 
		stScrollInfo .nPos = iHorPos;
		SetScrollInfo(hWndScrollBarHor,SB_CTL,&stScrollInfo,TRUE); 
		InvalidateRect(hWnd,&rcRedrawArea,1);	// ˢ���û���
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
		hDC = BeginPaint(hWnd, &ps);
		hF = CreateFont((int)(50 + 50.0 * iHorPos/ 100),	// ����߶�
			0,	// �Զ��������
			0,	// �ı�ˮƽ
			0,	// ����ˮƽ
			400,	// �������
			0,	// ���岻��б
			0,	// ���»���
			0,	// ���л���
			ANSI_CHARSET,	// �ַ���
			OUT_DEFAULT_PRECIS,	// Ĭ���������
			CLIP_DEFAULT_PRECIS,	// Ĭ�ϲü�����
			DEFAULT_QUALITY,	// Ĭ���������
			DEFAULT_PITCH|FF_DONTCARE,	// Ĭ��������
			L"����");	// ����
		// ����������ɫ
		SetTextColor(hDC,RGB(0,0,(int)(iVerPos/ 100.0 * 255)));
		SelectObject(hDC,hF);	// ѡ������
		TextOut(hDC,0,0,(LPCWSTR)cOut,strlen(cOut));	// ���
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
