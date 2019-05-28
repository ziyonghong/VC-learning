// 7.10.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "7.10.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HWND hWndMain;	// ����ȫ�ִ��ھ��
RECT rect1 = {100,100,100,100};	// ������νṹ��
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
	LoadString(hInstance, IDC_MY710, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY710));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY710));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY710);
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

	HMENU hMenu1,hMenu2;	// ����˵����
	HDC hDC;	// �����豸�������
	static BOOL bCircle = FALSE,bRect = FALSE;	// ���û���Բ�;��εı�־����
	static BOOL bMove = FALSE;	// �����ƶ���־
	PAINTSTRUCT ps;	// �����ͼ�ṹ�����
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_CIRCLE:	// ����Բ�β˵�
			hMenu1 = GetMenu(hWnd);	// �õ��˵����
			CheckMenuItem(hMenu1,IDM_CIRCLE,MF_CHECKED);	// ����ѡ�б�־
			CheckMenuItem(hMenu1,IDM_RECTANGLE,MF_UNCHECKED); // ɾ����־
			DeleteMenu(hMenu1,1,MF_BYPOSITION);	// ɾ�������Ρ������˵�
			hMenu2 = CreateMenu();	// ��̬�����˵�
			// ��Ӳ˵���
			AppendMenu(hMenu2,MF_ENABLED,IDM_DRAWCIRCLE,L"����Բ��(&d)"); 
			AppendMenu(hMenu2,MF_ENABLED,IDM_MOVECIRCLE,L"�ƶ�Բ��(&m)"); 
			AppendMenu(hMenu2,MF_ENABLED,IDM_ZOOMIN,L"�Ŵ�(&i)");
			AppendMenu(hMenu2,MF_ENABLED,IDM_ZOOMOUT,L"��С(&o)"); 
			AppendMenu(hMenu2,MF_ENABLED,IDM_REDRAW,L"�ػ�(&r)");
			// ����˵���
			InsertMenu(hMenu1,1,MF_POPUP|MF_BYPOSITION,(UINT)hMenu2,L"Բ��(&c)"); 
			DrawMenuBar(hWndMain);	// ˢ�²˵�
			bCircle = FALSE;	// ��Բ��־Ϊ��١�
			bRect = FALSE;	// ����α�־Ϊ��١�
			bMove = FALSE;	// �ƶ���־Ϊ��١�
			rect1 .left = 100;	// �ָ����εĳ�ʼ״̬
			rect1 .right = 100;
			rect1 .bottom = 100;
			rect1 .top = 100;
			InvalidateRect(hWnd,NULL,TRUE);	// ����ˢ����Ϣ
			break;
		case IDM_RECTANGLE:	// �������β˵�
			hMenu1 = GetMenu(hWnd);	// �õ��˵����
			CheckMenuItem(hMenu1,IDM_CIRCLE,MF_UNCHECKED);	// ɾ��ѡ�б�־
			CheckMenuItem(hMenu1,IDM_RECTANGLE,MF_CHECKED);	// ����ѡ�б�־
			DeleteMenu(hMenu1,1,MF_BYPOSITION);	// ɾ����Բ�Ρ嵯���˵�
			hMenu2 = LoadMenu(hInst,L"menuRect");	// �õ��˵����
			// ����˵�
			InsertMenu(hMenu1,1,MF_POPUP|MF_BYPOSITION,(UINT)hMenu2,L"����(&r)");
			DrawMenuBar(hWndMain);	// ˢ�²˵�
			bCircle = FALSE;	// ��Բ��־Ϊ��١�
			bRect = FALSE;	// ����α�־Ϊ��١�
			bMove = FALSE;	// �ƶ���־Ϊ��١�
			rect1 .left = 100;	// �ָ����εĳ�ʼ״̬
			rect1 .right = 100;
			rect1 .bottom = 100;
			rect1 .top = 100;
			InvalidateRect(hWnd,NULL,TRUE);	// ����ˢ����Ϣ
			break; 
		case IDM_EXIT:
			SendMessage(hWnd,WM_DESTROY,0,0);	// �����رմ�����Ϣ
			break;
		case IDM_DRAWCIRCLE:	// ����Բ��
			bCircle = TRUE;	// ��Բ��־Ϊ�����
			bRect = FALSE;	// ����α�־Ϊ��١�
			bMove = FALSE;	// �ƶ���־Ϊ��١�
			break;
		case IDM_DRAWRECT:	// ���ƾ���
			bCircle = FALSE;	// ��Բ��־Ϊ��١�
			bRect = TRUE;	// ����α�־Ϊ�����
			bMove = FALSE;	// �ƶ���־Ϊ��١�
			break;
		case IDM_MOVECIRCLE:	// �ƶ�Բ��
			bMove = TRUE;	// �ƶ���־Ϊ�����
			break;
		case IDM_MOVERECT:	// �ƶ�����
			bMove = TRUE;	// �ƶ���־Ϊ�����
			break;
		case IDM_ZOOMIN:	// �Ŵ�
			if(bCircle == TRUE|bRect == TRUE)
			{
				int nLength,nWidth;
				nLength = abs(rect1 .right - rect1 .left);	// ���㳤��
				nWidth = abs(rect1 .top - rect1 .bottom);	// ������
				rect1 .right = (int)(rect1 .left+ nLength * 1.2); // �Ŵ�
				rect1 .bottom = (int)(rect1 .top + nWidth * 1.2);
				InvalidateRect(hWnd,NULL,TRUE);	// ����ˢ����Ϣ
			}
			break;
		case IDM_ZOOMOUT:	// ��С
			if(bCircle == TRUE | bRect == TRUE)
			{
				int nLength,nWidth;
				nLength = abs(rect1 .right - rect1 .left);	// ���㳤��
				nWidth = abs(rect1 .top - rect1 .bottom);	// ������
				rect1 .right = (int)(rect1 .left + nLength/ 1.2);// ��С
				rect1 .bottom = (int)(rect1 .top + nWidth/ 1.2);
				InvalidateRect(hWnd,NULL,TRUE);	// ����ˢ����Ϣ
			}
			break;
		case IDM_REDRAW:	// ���»�ͼ
			bMove = FALSE;	// �ƶ���־Ϊ��١�
			rect1 .left = 100;	// �ָ����εĳ�ʼ״̬
			rect1 .right = 100;
			rect1 .top = 100;
			rect1 .bottom = 100;
			InvalidateRect(hWnd,NULL,TRUE);	// ����ˢ����Ϣ
			break;
		}
		break; case WM_KEYDOWN:
		if(bMove == TRUE)
		{
			if(wParam == VK_LEFT)
			{	// �������ͷ���,�����ƶ�
				rect1 .left -= 10;
				rect1 .right -= 10;
				InvalidateRect(hWnd,NULL,TRUE);	// ����ˢ����Ϣ
			}
			else if(wParam == VK_RIGHT)
			{	// �����Ҽ�ͷ���,�����ƶ�
				rect1 .left += 10;
				rect1 .right += 10;
				InvalidateRect(hWnd,NULL,TRUE);	// ����ˢ����Ϣ
			}
			else if(wParam == VK_UP)
			{	// �����ϼ�ͷ���ʱ,�����ƶ�
				rect1 .top -= 10;
				rect1 .bottom -= 10;
				InvalidateRect(hWnd,NULL,TRUE);	// ����ˢ����Ϣ
			}
			else if(wParam == VK_DOWN)
			{	// �����¼�ͷ���,�����ƶ�
				rect1 .top += 10;
				rect1 .bottom += 10;
				InvalidateRect(hWnd,NULL,TRUE);	// ����ˢ����Ϣ
			}
		}
		else if(bCircle == TRUE | bRect == TRUE)
		{
			if(wParam == VK_RIGHT)
			{
				rect1 .right += 10;	// ���¡��Ҽ�ͷ����ο򳤶� + 10
				InvalidateRect(hWnd,NULL,TRUE);	// ����ˢ����Ϣ
			}
			else if(wParam == VK_DOWN)
			{
				rect1 .bottom += 10;	// ���¡��¼�ͷ����ο�߶� + 10
				InvalidateRect(hWnd,NULL,TRUE);	// ����ˢ����Ϣ
			}
			else if(wParam == VK_UP)
			{
				rect1 .bottom -= 10;	// ���¡��ϼ�ͷ����ο�߶� - 10
				InvalidateRect(hWnd,NULL,TRUE);	// ����ˢ����Ϣ
			}
			else if(wParam == VK_LEFT)
			{
				rect1 .right -= 10;	// ���¡����ͷ����ο�߶� - 10
				InvalidateRect(hWnd,NULL,TRUE);	// ����ˢ����Ϣ
			}
		}
		break; 
		case WM_PAINT:
			hDC = BeginPaint(hWnd,&ps);
			if(bCircle == TRUE)
			{	// ����Բ��
				Ellipse(hDC,rect1 .left,rect1 .top,rect1 .right,rect1 .bottom);
			}

			if(bRect == TRUE)
			{Rectangle(hDC,rect1 .left,rect1 .top,rect1 .right,rect1 .bottom);
			}

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
