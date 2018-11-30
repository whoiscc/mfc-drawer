
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once

#include "Manager.h"
#include "Worker.h"

// CChildView ����

class Manager;
class Worker;

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

private:
	Manager *_manager;
	Worker *_worker;

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT, int, int);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDDADrawline();
	afx_msg void OnBresenhamDrawline();
	afx_msg void OnDrawcircle();
	afx_msg void OnDrawEllipse();
};

