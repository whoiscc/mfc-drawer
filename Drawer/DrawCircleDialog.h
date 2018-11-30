#pragma once
#include "afxwin.h"


// DrawCircleDialog �Ի���

class DrawCircleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(DrawCircleDialog)

public:
	DrawCircleDialog(bool hasRy, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DrawCircleDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAWCIRCLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
