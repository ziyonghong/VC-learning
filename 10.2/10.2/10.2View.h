
// 10.2View.h : CMy102View ��Ľӿ�
//

#pragma once
#include "afxwin.h"


class CMy102View : public CView
{
protected: // �������л�����
	CMy102View();
	DECLARE_DYNCREATE(CMy102View)

// ����
public:
	CMy102Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMy102View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	COLORREF m_nColors[3];
	DWORD m_nColorIndex;
	CString m_strShow;
	BOOL m_bShow;
	afx_msg void OnOperShow();
	void OnOperColorChange(UINT nID);
	CMenu m_PopMenu;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	CMenu *m_pPop;
};

#ifndef _DEBUG  // 10.2View.cpp �еĵ��԰汾
inline CMy102Doc* CMy102View::GetDocument() const
   { return reinterpret_cast<CMy102Doc*>(m_pDocument); }
#endif

