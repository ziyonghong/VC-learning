// DlgInput.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "11.1SingleDoc.h"
#include "DlgInput.h"
#include "afxdialogex.h"


// DlgInput �Ի���

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


// DlgInput ��Ϣ�������





void DlgInput::OnEnChangeChangetext()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
