// DrawLineDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Drawer.h"
#include "DrawLineDialog.h"
#include "afxdialogex.h"

#include <string>


// DrawLineDialog 对话框

IMPLEMENT_DYNAMIC(DrawLineDialog, CDialogEx)

DrawLineDialog::DrawLineDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRAWLINE, pParent)
{

}

DrawLineDialog::~DrawLineDialog()
{
}

void DrawLineDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, x0Edit);
	DDX_Control(pDX, IDC_EDIT3, x1Edit);
	DDX_Control(pDX, IDC_EDIT2, y0Edit);
	DDX_Control(pDX, IDC_EDIT4, y1Edit);
	DDX_Control(pDX, IDOK, ButtonOK);
}


BEGIN_MESSAGE_MAP(DrawLineDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT2, &DrawLineDialog::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, &DrawLineDialog::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, &DrawLineDialog::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &DrawLineDialog::OnEnChangeEdit4)
END_MESSAGE_MAP()


// DrawLineDialog 消息处理程序

void DrawLineDialog::OnEnChangeEdit2()
{
	ValidateText();
}


void DrawLineDialog::OnEnChangeEdit1()
{
	ValidateText();
}


void DrawLineDialog::OnEnChangeEdit3()
{
	ValidateText();
}


void DrawLineDialog::OnEnChangeEdit4()
{
	ValidateText();
}

auto DrawLineDialog::GetData() -> struct Data {
	CString x0Str, y0Str, x1Str, y1Str;
	x0Edit.GetWindowTextW(x0Str);
	y0Edit.GetWindowTextW(y0Str);
	x1Edit.GetWindowTextW(x1Str);
	y1Edit.GetWindowTextW(y1Str);
	int x0 = std::stoi(std::wstring(x0Str.GetString()));
	int y0 = std::stoi(std::wstring(y0Str.GetString()));
	int x1 = std::stoi(std::wstring(x1Str.GetString()));
	int y1 = std::stoi(std::wstring(y1Str.GetString()));
	return{ x0, y0, x1, y1 };
}

void DrawLineDialog::ValidateText() {
	try {
		Input = GetData();
	}
	catch (std::invalid_argument) {
		ButtonOK.EnableWindow(false);
		return;
	}
	ButtonOK.EnableWindow(true);
}
