#pragma once
#include "afxwin.h"


// DrawLineDialog 对话框

class DrawLineDialog : public CDialogEx
{
	DECLARE_DYNAMIC(DrawLineDialog)

public:
	DrawLineDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DrawLineDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAWLINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CEdit x0Edit;
	CEdit x1Edit;
	CEdit y0Edit;
	CEdit y1Edit;
	void ValidateText();
	CButton ButtonOK;
public:
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();

	struct Data {
		int x0; int y0; int x1; int y1;
	};
	struct Data Input;
private:
	struct Data GetData();
};
