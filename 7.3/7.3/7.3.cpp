// 7.3.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "7.3.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HWND hdlg;
TCHAR str[200];
BOOL CALLBACK ModalDlgProc(HWND hdlg,UINT message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK ModalessDlgProc(HWND hdlg,UINT message,WPARAM wParam,LPARAM lParam);

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
	LoadString(hInstance, IDC_MY73, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY73));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY73));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY73);
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
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_OPEN:
			MessageBox(hWnd,L"�ļ��Ѿ���",L"�ļ���",MB_OK);
			break;
			
		case IDM_SAVE:
			MessageBox(hWnd,L"�ļ��Ѿ�����",L"�ļ�����",MB_OK);
			break;
		
		case IDM_EXIT:
			SendMessage(hWnd,WM_DESTROY,0,0);
			DestroyWindow(hWnd);
			break;
		case IDM_MODAL:  //��������ʾģʽ�Ի���
			DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)ModalDlgProc);
		break;
		case IDM_MODALLESS:
			hdlg=CreateDialog(hInst,MAKEINTRESOURCE(IDD_DIALOG1), hWnd,(DLGPROC)ModalessDlgProc);
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//����Ի��򷵻ص���Ϣ
		TextOut(hdc,0,0,str,_tcslen(str));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

BOOL CALLBACK ModalDlgProc(HWND hdlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	TCHAR mystr[200];
	switch(message)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hdlg,IDC_TITLE,L"ģʽ�Ի���ʾ��");
		return 1;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hdlg,IDC_EDIT1,mystr,200);
			_tcscpy(str,L"����ģʽ�����������Ϣ:");
			_tcscat(str,mystr);
			InvalidateRect(GetParent(hdlg),NULL,true);
			EndDialog(hdlg,0);
			return 1;
		case IDCANCEL:
			SetDlgItemText(hdlg,IDC_EDIT1,L"");
			return 1;
		}
		break;
	case WM_CLOSE:
		EndDialog(hdlg,0);
		return 1;
	}
	return 0;

}

BOOL CALLBACK ModalessDlgProc(HWND hdlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	TCHAR mystr[200];
	switch(message)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hdlg,IDC_TITLE,L"��ģʽ�Ի���ʾ��");
		return 1;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hdlg,IDC_EDIT1,mystr,200);
			_tcscpy(str,L"���Ƿ�ģʽ�����������Ϣ");
			_tcscat(str,mystr);
			InvalidateRect(GetParent(hdlg),NULL,true);
			DestroyWindow(hdlg);
			return 1;
		case IDCANCEL:
			SetDlgItemText(hdlg,IDC_EDIT1,L"");
			return 1;
		}
		break;
	case WM_CLOSE:
		EndDialog(hdlg,0);
		return 1;
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
