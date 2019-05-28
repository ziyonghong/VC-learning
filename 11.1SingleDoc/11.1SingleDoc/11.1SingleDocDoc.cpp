
// 11.1SingleDocDoc.cpp : CMy111SingleDocDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CMy111SingleDocDoc ����/����

CMy111SingleDocDoc::CMy111SingleDocDoc()
{
	// TODO: �ڴ����һ���Թ������

	m_str = _T("���ã����ĵ���������̣�");
}

CMy111SingleDocDoc::~CMy111SingleDocDoc()
{
}

BOOL CMy111SingleDocDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	m_str = _T("���ã����ĵ���������̣�");
	return TRUE;
}




// CMy111SingleDocDoc ���л�

void CMy111SingleDocDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMy111SingleDocDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CMy111SingleDocDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CMy111SingleDocDoc ���

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


// CMy111SingleDocDoc ����


void CMy111SingleDocDoc::OnChangetext()
{
	// TODO: �ڴ���������������
	DlgInput inputDlg;				//����һ��CInputDlg��Ķ���inputDlg
	if(inputDlg.DoModal()==IDOK)	//��ʾ�Ի���
	{
		m_str=inputDlg.m_input;		//��ȡ������ַ���
		UpdateAllViews(NULL);		//������ͼ
	}
}
