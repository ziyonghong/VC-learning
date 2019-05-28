// DlgInput.cpp : 实现文件
//

#include "stdafx.h"
#include "11.1SingleDoc.h"
#include "DlgInput.h"
#include "afxdialogex.h"


// DlgInput 对话框

IMPLEMENT_DYNAMIC(DlgInput, CDialogEx)

DlgInput::DlgInput(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgInput::IDD, pParent)
	, m_input(_T(""))
{

	m_input = _T("");
}

DlgInput::~DlgInput()
{
}

void DlgInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX,IDR_CHANGETEXT, m_input);
}


BEGIN_MESSAGE_MAP(DlgInput, CDialogEx)
	//ON_EN_CHANGE(IDC_EDIT1, &DlgInput::OnEnChangeEdit1)
	ON_EN_CHANGE(IDR_CHANGETEXT, &DlgInput::OnEnChangeChangetext)
END_MESSAGE_MAP()


// DlgInput 消息处理程序





void DlgInput::OnEnChangeChangetext()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
