
// 10.2View.h : CMy102View 类的接口
//

#pragma once
#include "afxwin.h"


class CMy102View : public CView
{
protected: // 仅从序列化创建
	CMy102View();
	DECLARE_DYNCREATE(CMy102View)

// 特性
public:
	CMy102Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy102View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // 10.2View.cpp 中的调试版本
inline CMy102Doc* CMy102View::GetDocument() const
   { return reinterpret_cast<CMy102Doc*>(m_pDocument); }
#endif

