
// 11.1SingleDocView.h : CMy111SingleDocView ��Ľӿ�
//

#pragma once


class CMy111SingleDocView : public CView
{
protected: // �������л�����
	CMy111SingleDocView();
	DECLARE_DYNCREATE(CMy111SingleDocView)

// ����
public:
	CMy111SingleDocDoc* GetDocument() const;

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
	virtual ~CMy111SingleDocView();
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
//	CString m_str;
//	afx_msg void OnChangetext();
};

#ifndef _DEBUG  // 11.1SingleDocView.cpp �еĵ��԰汾
inline CMy111SingleDocDoc* CMy111SingleDocView::GetDocument() const
   { return reinterpret_cast<CMy111SingleDocDoc*>(m_pDocument); }
#endif

