// DrawCircleDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Drawer.h"
#include "DrawCircleDialog.h"
#include "afxdialogex.h"

#include <string>


// DrawCircleDialog 对话框

IMPLEMENT_DYNAMIC(DrawCircleDialog, CDialogEx)

DrawCircleDialog::DrawCircleDialog(bool hasRy, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRAWCIRCLE, pParent), _hasRy(hasRy)
{
}

DrawCircleDialog::~DrawCircleDialog()
{
}

void DrawCircleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, xcEdit);
	DDX_Control(pDX, IDC_EDIT2, ycEdit);
	DDX_Control(pDX, IDC_EDIT3, rxEdit);
	DDX_Control(pDX, IDC_EDIT4, ryEdit);
	DDX_Control(pDX, IDOK, ButtonOK);
}


BEGIN_MESSAGE_MAP(DrawCircleDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &DrawCircleDialog::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &DrawCircleDialog::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &DrawCircleDialog::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &DrawCircleDialog::OnEnChangeEdit4)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

void DrawCircleDialog::OnShowWindow(BOOL _b, UINT _u) {
	if (!_hasRy) {
		ryEdit.EnableWindow(false);
	}
}

void DrawCircleDialog::OnEnChangeEdit1()
{
	ValidateText();
}


void DrawCircleDialog::OnEnChangeEdit2()
{
	ValidateText();
}


void DrawCircleDialog::OnEnChangeEdit3()
{
	ValidateText();
}


void DrawCircleDialog::OnEnChangeEdit4()
{
	ValidateText();
}

auto DrawCircleDialog::GetData() -> struct Data {
	CString x0Str, y0Str, x1Str, y1Str;
	xcEdit.GetWindowTextW(x0Str);
	ycEdit.GetWindowTextW(y0Str);
	rxEdit.GetWindowTextW(x1Str);
	ryEdit.GetWindowTextW(y1Str);
	int x0 = std::stoi(std::wstring(x0Str.GetString()));
	int y0 = std::stoi(std::wstring(y0Str.GetString()));
	int x1 = std::stoi(std::wstring(x1Str.GetString()));
	int y1 = 0;
	if (ryEdit.IsWindowEnabled()) {
		y1 = std::stoi(std::wstring(y1Str.GetString()));
	}
	return{ x0, y0, x1, y1 };
}

void DrawCircleDialog::ValidateText() {
	try {
		Input = GetData();
	}
	catch (std::invalid_argument) {
		ButtonOK.EnableWindow(false);
		return;
	}
	ButtonOK.EnableWindow(true);
}
