
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "Drawer.h"
#include "ChildView.h"
#include "DrawLineDialog.h"
#include "DrawCircleDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView() : _manager(nullptr)
{
}

CChildView::~CChildView()
{
	if (_manager != nullptr) {
		delete _manager;
		delete _worker;
	}
}

void CChildView::OnSize(UINT _x, int width, int height) {
	if (_manager == nullptr) {
		_manager = new Manager(*this, width, height);
		_worker = new Worker(*_manager);
		// _worker->DrawLineDDA(-100, -100, 300, 200);
	}
	else {
		_manager->ResetCanvas(width, height);
	}
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_COMMAND(ID_DDA_DRAWLINE, &CChildView::OnDDADrawline)
	ON_COMMAND(ID_BRESENHAM_DRAWLINE, &CChildView::OnBresenhamDrawline)
	ON_COMMAND(ID_DRAWCIRCLE, &CChildView::OnDrawcircle)
	ON_COMMAND(ID_DRAWELLIPSE, &CChildView::OnDrawEllipse)
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	/*
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
	*/
	return _manager->OnPaint();
}

void CChildView::OnTimer(UINT_PTR timer_id)
{
	return _manager->OnTimer(timer_id);
}



void CChildView::OnDDADrawline()
{
	TRACE("DDA Draw Line\n");

	DrawLineDialog dialog;
	if (dialog.DoModal() == IDOK) {
		TRACE("Start drawing\n");
		struct DrawLineDialog::Data data = dialog.Input;
		_manager->ResetCanvas();
		_worker->DrawLineDDA(data.x0, data.y0, data.x1, data.y1);
	}
}


void CChildView::OnBresenhamDrawline()
{
	DrawLineDialog dialog;
	if (dialog.DoModal() == IDOK) {
		struct DrawLineDialog::Data data = dialog.Input;
		_manager->ResetCanvas();
		_worker->DrawLineBresenham(data.x0, data.y0, data.x1, data.y1);
	}
}


void CChildView::OnDrawcircle()
{
	DrawCircleDialog dialog(false);
	if (dialog.DoModal() == IDOK) {
		struct DrawCircleDialog::Data data = dialog.Input;
		_manager->ResetCanvas();
		_worker->DrawCircle(data.xc, data.yc, data.rx);
	}
}


void CChildView::OnDrawEllipse()
{
	DrawCircleDialog dialog(true);
	if (dialog.DoModal() == IDOK) {
		struct DrawCircleDialog::Data data = dialog.Input;
		_manager->ResetCanvas();
		_worker->DrawEllipse(data.xc, data.yc, data.rx, data.ry);
	}
}
