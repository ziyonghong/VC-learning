#pragma once


// DlgInput 对话框

class DlgInput : public CDialogEx
{
	DECLARE_DYNAMIC(DlgInput)

public:
	DlgInput(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgInput();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString m_input;
	CString m_input;
	afx_msg void OnEnChangeChangetext();
};
