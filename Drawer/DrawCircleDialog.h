#pragma once
#include "afxwin.h"


// DrawCircleDialog 对话框

class DrawCircleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(DrawCircleDialog)

public:
	DrawCircleDialog(bool hasRy, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DrawCircleDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAWCIRCLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit xcEdit;
	CEdit ycEdit;
	CEdit rxEdit;
	CEdit ryEdit;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnShowWindow(BOOL, UINT);

	void ValidateText();
	CButton ButtonOK;

	struct Data {
		int xc; int yc; int rx; int ry;
	};
	struct Data Input;
private:
	struct Data GetData();
	bool _hasRy;
};
