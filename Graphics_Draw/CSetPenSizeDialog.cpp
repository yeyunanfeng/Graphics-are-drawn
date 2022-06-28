// CSetPenSizeDialog.cpp: 实现文件
//

#include "pch.h"
#include "Graphics_Draw.h"
#include "afxdialogex.h"
#include "CSetPenSizeDialog.h"


// CSetPenSizeDialog 对话框

IMPLEMENT_DYNAMIC(CSetPenSizeDialog, CDialogEx)

CSetPenSizeDialog::CSetPenSizeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CSetPenSizeDialog::~CSetPenSizeDialog()
{
}

void CSetPenSizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);

	CString str;
	m_Edit.GetWindowTextW(str);
	m_PenSize = _ttoi(str);
}


BEGIN_MESSAGE_MAP(CSetPenSizeDialog, CDialogEx)
END_MESSAGE_MAP()


// CSetPenSizeDialog 消息处理程序
