
// ChildView.h : CChildView 类的接口
//


#pragma once

#include "Manager.h"
#include "Worker.h"

// CChildView 窗口

class Manager;
class Worker;

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

private:
	Manager *_manager;
	Worker *_worker;

	// 生成的消息映射函数
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

