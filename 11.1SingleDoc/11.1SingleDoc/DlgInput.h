#pragma once


// DlgInput �Ի���

class DlgInput : public CDialogEx
{
	DECLARE_DYNAMIC(DlgInput)

public:
	DlgInput(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgInput();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CString m_input;
	CString m_input;
	afx_msg void OnEnChangeChangetext();
};
