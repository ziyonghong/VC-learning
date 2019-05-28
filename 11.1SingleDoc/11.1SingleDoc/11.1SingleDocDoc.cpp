
// 11.1SingleDocDoc.cpp : CMy111SingleDocDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "11.1SingleDoc.h"
#endif
#include "DlgInput.h"                           
#include "11.1SingleDocDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy111SingleDocDoc

IMPLEMENT_DYNCREATE(CMy111SingleDocDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy111SingleDocDoc, CDocument)
	ON_COMMAND(IDR_CHANGETEXT, &CMy111SingleDocDoc::OnChangetext)
END_MESSAGE_MAP()


// CMy111SingleDocDoc 构造/析构

CMy111SingleDocDoc::CMy111SingleDocDoc()
{
	// TODO: 在此添加一次性构造代码

	m_str = _T("您好，但文档界面的例程！");
}

CMy111SingleDocDoc::~CMy111SingleDocDoc()
{
}

BOOL CMy111SingleDocDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	m_str = _T("您好，但文档界面的例程！");
	return TRUE;
}




// CMy111SingleDocDoc 序列化

void CMy111SingleDocDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMy111SingleDocDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMy111SingleDocDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMy111SingleDocDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy111SingleDocDoc 诊断

#ifdef _DEBUG
void CMy111SingleDocDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy111SingleDocDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy111SingleDocDoc 命令


void CMy111SingleDocDoc::OnChangetext()
{
	// TODO: 在此添加命令处理程序代码
	DlgInput inputDlg;				//创建一个CInputDlg类的对象inputDlg
	if(inputDlg.DoModal()==IDOK)	//显示对话框
	{
		m_str=inputDlg.m_input;		//获取输入的字符串
		UpdateAllViews(NULL);		//更新视图
	}
}
