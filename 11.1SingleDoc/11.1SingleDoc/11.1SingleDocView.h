
// 11.1SingleDocView.h : CMy111SingleDocView 类的接口
//

#pragma once


class CMy111SingleDocView : public CView
{
protected: // 仅从序列化创建
	CMy111SingleDocView();
	DECLARE_DYNCREATE(CMy111SingleDocView)

// 特性
public:
	CMy111SingleDocDoc* GetDocument() const;

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
	virtual ~CMy111SingleDocView();
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
//	CString m_str;
//	afx_msg void OnChangetext();
};

#ifndef _DEBUG  // 11.1SingleDocView.cpp 中的调试版本
inline CMy111SingleDocDoc* CMy111SingleDocView::GetDocument() const
   { return reinterpret_cast<CMy111SingleDocDoc*>(m_pDocument); }
#endif

