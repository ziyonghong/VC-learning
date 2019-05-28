
// 11.1SingleDocView.cpp : CMy111SingleDocView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy111SingleDocView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_COMMAND(IDR_CHANGETEXT, &CMy111SingleDocView::OnChangetext)
END_MESSAGE_MAP()

// CMy111SingleDocView 构造/析构

CMy111SingleDocView::CMy111SingleDocView()
{
	// TODO: 在此处添加构造代码

	//  m_str = _T("");
}

CMy111SingleDocView::~CMy111SingleDocView()
{
}

BOOL CMy111SingleDocView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy111SingleDocView 绘制

void CMy111SingleDocView::OnDraw(CDC* pDC)
{
	CMy111SingleDocDoc* pDoc = GetDocument();  //获得文本类对象
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect rectClient;	
	GetClientRect(rectClient);		// 获取当前客户区的指针
	CSize sizeClient=rectClient.Size();	// 获取当前客户区的大小
	CString str=pDoc->m_str;		// 从文件中读取数据
	CSize sizeTextExtent=pDC->GetTextExtent(str);	// 用新选定的字体绘制字符串
	pDC->TextOut((sizeClient.cx-sizeTextExtent.cx)/2,(sizeClient.cy-sizeTextExtent.cy)/2,str);
}


// CMy111SingleDocView 打印


void CMy111SingleDocView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy111SingleDocView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy111SingleDocView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy111SingleDocView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CMy111SingleDocView 诊断

#ifdef _DEBUG
void CMy111SingleDocView::AssertValid() const
{
	CView::AssertValid();
}

void CMy111SingleDocView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy111SingleDocDoc* CMy111SingleDocView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy111SingleDocDoc)));
	return (CMy111SingleDocDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy111SingleDocView 消息处理程序


