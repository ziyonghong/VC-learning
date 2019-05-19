// 5.5.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "5.5.h"

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
	LoadString(hInstance, IDC_MY55, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY55));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY55));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY55);
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
   char lpsz_1[] ="ֻ�и��������ջ�";	// ����������ַ���
   //const char* lpsz_1[] ={"ֻ�и��������ջ�"};
   TCHAR  chFont[7];
 //  char chFont[7];	// ��������������ַ���
	int X = 0,Y = 0,i;
	int nCharlen = strlen(lpsz_1);	// �����ַ������ȱ���
	int iFontSign = 0;// ���������־

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
		hDC = BeginPaint(hWnd,&ps);	// ����豸�������
		for(i = 0;i < nCharlen;i += 2)	// ����ĳ���������ɫ����ַ���
		{
			SetTextColor(hDC,RGB((long)(255.0/nCharlen * i),// ����������ɫ
				0,
				0));
		/*	if(iFontSign% 5 == 0) strcpy(chFont,"����_GB2312"); // ���ð���������Ϣ���ַ��� 
			else if(iFontSign% 5 == 1) strcpy(chFont,"����"); // �� 5 Ϊ����ѭ���ı����� 
			else if(iFontSign % 5 == 2) strcpy(chFont,"����");
			else if(iFontSign % 5 == 3) strcpy(chFont,"����");
			else strcpy(chFont,"��Բ");*/
			if(iFontSign% 5 == 0) _tcscpy(chFont,_T("����_GB2312")); // ���ð���������Ϣ���ַ��� 
			else if(iFontSign% 5 == 1) _tcscpy(chFont,_T("����")); // �� 5 Ϊ����ѭ���ı����� 
			else if(iFontSign % 5 == 2) _tcscpy(chFont,_T("����"));
			else if(iFontSign % 5 == 3) _tcscpy(chFont,_T("����"));
			else _tcscpy(chFont,_T("��Բ"));
			hF = CreateFont(	// ����������
				(long)(8 + 32.0 * i/ nCharlen),	// ����߶�
				0,	// ϵͳ����Ŀ��ֵ
				0,	// �ı���б��Ϊ 0,��ʾˮƽ
				0,	// ������б��Ϊ 0
				400,	// ����ֶ� .400 Ϊ����
				0,	// ��б����
				0,	// ���»���
				0,	// ��ɾ����
				GB2312_CHARSET,	// ���õ��ַ���Ϊ ANSI- CHARSET
				OUT_DEFAULT_PRECIS,	// ɾ������ΪĬ��ֵ
				CLIP_DEFAULT_PRECIS,	// �ü�����ΪĬ��ֵ
				DEFAULT_QUALITY,	// �������ΪĬ��ֵ
				DEFAULT_PITCH|FF_DONTCARE,	// �ּ�������ϵ��ʹ��Ĭ��ֵ
				chFont);	// ��������
			SelectObject(hDC,hF);	// ѡ������
			GetTextMetrics(hDC,&tm);	// �õ�����������Ϣ�Ľṹ��
			X = X + tm .tmAveCharWidth * 2;	// ��������ַ��� X ����
			Y = iFontSign % 5 * 40 + tm .tmExternalLeading;	// ��������ַ��� Y ����

//���󣺲��ܽ����� 4 �ӡ�char *��ת��Ϊ��LPCWSTR��
			TextOut(hDC,X,Y,(LPCWSTR)&lpsz_1[i],2);	// ����� i ���ַ� .����������Ч��
			Sleep(400);	// ��ͣ 0 .4 ��
			DeleteObject(hF);	// ɾ��������
		}
		iFontSign++;	// �����־����
		InvalidateRect(hWnd,NULL,1);	// ˢ���û���
		EndPaint(hWnd,&ps);	// ɾ���豸���
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
