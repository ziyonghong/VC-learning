
// 10.2View.cpp : CMy102View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy102View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_OPER_SHOW, &CMy102View::OnOperShow)  //将控件和OnOperShow函数绑定在一定  消息映射
    ON_COMMAND_RANGE(ID_OPER_RED,ID_OPER_BLUE,&CMy102View::OnOperColorChange)

	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMy102View 构造/析构

CMy102View::CMy102View()
	: m_nColorIndex(0)
	, m_strShow(_T(""))
	, m_bShow(FALSE)
	, m_pPop(NULL)
{
	// TODO: 在此处添加构造代码
	m_nColors[0] = RGB(255,0,0);
	m_nColors[1] = RGB(0,255,0);
	m_nColors[2] = RGB(0,0,255);
	m_nColorIndex = 0;
	m_strShow = "Hello World!";
	m_bShow = TRUE;
	m_PopMenu.LoadMenu(IDR_MENU_POP);    // 创建并加载菜单资源
}

CMy102View::~CMy102View()
{
}

BOOL CMy102View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy102View 绘制

void CMy102View::OnDraw(CDC* pDC)
{
	CMy102Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if(m_bShow)
	{		
		pDC->SetTextColor(m_nColors[m_nColorIndex]);	// 设置输出字符串颜色	
		pDC->TextOut(100,100,m_strShow);// 输出字符串
	}
	
}


// CMy102View 打印


void CMy102View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy102View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy102View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy102View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CMy102View 诊断

#ifdef _DEBUG
void CMy102View::AssertValid() const
{
	CView::AssertValid();
}

void CMy102View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy102Doc* CMy102View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy102Doc)));
	return (CMy102Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy102View 消息处理程序


void CMy102View::OnOperShow()
{
	// TODO: 在此添加命令处理程序代码
		m_bShow=!m_bShow;
	Invalidate();  //强制程序重新窗口
}


void CMy102View::OnOperColorChange(UINT nID)
{
		m_nColorIndex=nID-ID_OPER_RED;
	Invalidate();
}


void CMy102View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pPop = m_PopMenu.GetSubMenu(0);    // 获得第一个子菜单
	UINT nCheck = m_bShow?MF_CHECKED:MF_UNCHECKED; // 更新【Show】的check状态
	m_pPop->CheckMenuItem(ID_OPER_SHOW,MF_BYCOMMAND|nCheck);  //标志选中或没选中菜单
	m_pPop->CheckMenuRadioItem(ID_OPER_RED,ID_OPER_BLUE,ID_OPER_RED+m_nColorIndex,MF_BYCOMMAND);
	ClientToScreen(&point);    // 将坐标由客户坐标转化为屏幕坐标
	m_pPop->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);// 跟踪鼠标坐标显示Pop-up菜单
	CView::OnRButtonDown(nFlags, point);
	CView::OnRButtonDown(nFlags, point);
}
