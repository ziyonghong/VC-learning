
// 11.1SingleDocView.cpp : CMy111SingleDocView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "11.1SingleDoc.h"
#endif

#include "11.1SingleDocDoc.h"
#include "11.1SingleDocView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy111SingleDocView

IMPLEMENT_DYNCREATE(CMy111SingleDocView, CView)

BEGIN_MESSAGE_MAP(CMy111SingleDocView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy111SingleDocView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_COMMAND(IDR_CHANGETEXT, &CMy111SingleDocView::OnChangetext)
END_MESSAGE_MAP()

// CMy111SingleDocView ����/����

CMy111SingleDocView::CMy111SingleDocView()
{
	// TODO: �ڴ˴���ӹ������

	//  m_str = _T("");
}

CMy111SingleDocView::~CMy111SingleDocView()
{
}

BOOL CMy111SingleDocView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy111SingleDocView ����

void CMy111SingleDocView::OnDraw(CDC* pDC)
{
	CMy111SingleDocDoc* pDoc = GetDocument();  //����ı������
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CRect rectClient;	
	GetClientRect(rectClient);		// ��ȡ��ǰ�ͻ�����ָ��
	CSize sizeClient=rectClient.Size();	// ��ȡ��ǰ�ͻ����Ĵ�С
	CString str=pDoc->m_str;		// ���ļ��ж�ȡ����
	CSize sizeTextExtent=pDC->GetTextExtent(str);	// ����ѡ������������ַ���
	pDC->TextOut((sizeClient.cx-sizeTextExtent.cx)/2,(sizeClient.cy-sizeTextExtent.cy)/2,str);
}


// CMy111SingleDocView ��ӡ


void CMy111SingleDocView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy111SingleDocView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy111SingleDocView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy111SingleDocView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMy111SingleDocView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy111SingleDocView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy111SingleDocView ���

#ifdef _DEBUG
void CMy111SingleDocView::AssertValid() const
{
	CView::AssertValid();
}

void CMy111SingleDocView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy111SingleDocDoc* CMy111SingleDocView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy111SingleDocDoc)));
	return (CMy111SingleDocDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy111SingleDocView ��Ϣ�������


