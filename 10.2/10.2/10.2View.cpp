
// 10.2View.cpp : CMy102View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "10.2.h"
#endif

#include "10.2Doc.h"
#include "10.2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy102View

IMPLEMENT_DYNCREATE(CMy102View, CView)

BEGIN_MESSAGE_MAP(CMy102View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy102View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_OPER_SHOW, &CMy102View::OnOperShow)  //���ؼ���OnOperShow��������һ��  ��Ϣӳ��
    ON_COMMAND_RANGE(ID_OPER_RED,ID_OPER_BLUE,&CMy102View::OnOperColorChange)

	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMy102View ����/����

CMy102View::CMy102View()
	: m_nColorIndex(0)
	, m_strShow(_T(""))
	, m_bShow(FALSE)
	, m_pPop(NULL)
{
	// TODO: �ڴ˴���ӹ������
	m_nColors[0] = RGB(255,0,0);
	m_nColors[1] = RGB(0,255,0);
	m_nColors[2] = RGB(0,0,255);
	m_nColorIndex = 0;
	m_strShow = "Hello World!";
	m_bShow = TRUE;
	m_PopMenu.LoadMenu(IDR_MENU_POP);    // ���������ز˵���Դ
}

CMy102View::~CMy102View()
{
}

BOOL CMy102View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy102View ����

void CMy102View::OnDraw(CDC* pDC)
{
	CMy102Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if(m_bShow)
	{		
		pDC->SetTextColor(m_nColors[m_nColorIndex]);	// ��������ַ�����ɫ	
		pDC->TextOut(100,100,m_strShow);// ����ַ���
	}
	
}


// CMy102View ��ӡ


void CMy102View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy102View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy102View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy102View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMy102View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy102View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy102View ���

#ifdef _DEBUG
void CMy102View::AssertValid() const
{
	CView::AssertValid();
}

void CMy102View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy102Doc* CMy102View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy102Doc)));
	return (CMy102Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy102View ��Ϣ�������


void CMy102View::OnOperShow()
{
	// TODO: �ڴ���������������
		m_bShow=!m_bShow;
	Invalidate();  //ǿ�Ƴ������´���
}


void CMy102View::OnOperColorChange(UINT nID)
{
		m_nColorIndex=nID-ID_OPER_RED;
	Invalidate();
}


void CMy102View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_pPop = m_PopMenu.GetSubMenu(0);    // ��õ�һ���Ӳ˵�
	UINT nCheck = m_bShow?MF_CHECKED:MF_UNCHECKED; // ���¡�Show����check״̬
	m_pPop->CheckMenuItem(ID_OPER_SHOW,MF_BYCOMMAND|nCheck);  //��־ѡ�л�ûѡ�в˵�
	m_pPop->CheckMenuRadioItem(ID_OPER_RED,ID_OPER_BLUE,ID_OPER_RED+m_nColorIndex,MF_BYCOMMAND);
	ClientToScreen(&point);    // �������ɿͻ�����ת��Ϊ��Ļ����
	m_pPop->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);// �������������ʾPop-up�˵�
	CView::OnRButtonDown(nFlags, point);
	CView::OnRButtonDown(nFlags, point);
}
