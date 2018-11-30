#include "stdafx.h"
#include "Manager.h"
#include <string>


Manager::Manager(CChildView &view, int width, int height)
	: _view(view), _width(width), _height(height), 
	_has_timer(false), _will_draw_coord(true)
{
	_view.Invalidate();
}


Manager::~Manager()
{
}

void Manager::ResetCanvas(int width, int height)
{
	_width = width;
	_height = height;
	_buffer.clear();
	if (_has_timer) {
		_view.KillTimer(_timer_id);
	}
	_view.Invalidate();
	_will_draw_coord = true;
}

void Manager::DrawPixel(int x, int y)
{
	bool newShape = false;
	if (_buffer.size() == 0) {
		_buffer.push_back(std::vector<struct _Point> {});
		newShape = true;
	}
	struct _Point point { x, y };
	_buffer.at(_buffer.size() - 1).push_back(point);

	if (newShape) {
		ASSERT(!_has_timer);
		_timer_id = SetTimer(_view.m_hWnd, 0, 10, nullptr);
//		_timer_id = _view.SetTimer(42, 10, nullptr);
		_has_timer = true;
	}
}

void Manager::NextTick()
{
	_buffer.push_back(std::vector<struct _Point> {});
}

void Manager::OnPaint()
{
	if (_will_draw_coord) {
		_DrawCoord();
	}
	
	CPaintDC dc(&_view);
	for (auto &point : _will_paint_buffer) {
		dc.SetPixel(point.x, point.y, RGB(255, 0, 0));
	}
}

void Manager::OnTimer(UINT_PTR timer_id)
{
	/*
	if (!_has_timer || timer_id != _timer_id) {
		return;
	}
	*/

	TRACE("Timer triggered\n");

	std::vector<struct _Point> points = _buffer.front();
	_buffer.pop_front();

	_will_paint_buffer.clear();
	for (auto &point : points) {
		struct _Point screenPoint = {
			point.x + (_width / 2),
			-point.y + (_height / 2),
		};
		_will_paint_buffer.push_back(screenPoint);
		CRect rect;
		rect.TopLeft().x = screenPoint.x;
		rect.TopLeft().y = screenPoint.y;
		rect.BottomRight().x = screenPoint.x + 1;
		rect.BottomRight().y = screenPoint.y + 1;
		_view.InvalidateRect(&rect);
	}

	if (_buffer.empty() || _buffer.front().empty()) {
		_view.KillTimer(timer_id);
		_has_timer = false;
	}
}

void Manager::_DrawCoord()
{
	TRACE("Draw coord here.\n");

	CPaintDC dc(&_view);

	int y0 = _height / 2, x0 = _width / 2;
	dc.MoveTo(0, y0);
	dc.LineTo(_width, y0);
	for (int x = x0 - (x0 - 1) / 100 * 100; x < _width; x += 100) {
		dc.MoveTo(x, y0);
		dc.LineTo(x, y0 - 10);
		dc.TextOutW(x - 10, y0 + 5, 
			CStringW(std::to_string(x - x0).c_str()));
	}

	dc.MoveTo(x0, 0);
	dc.LineTo(x0, _height);
	for (int y = y0 - (y0 - 1) / 100 * 100; y < _height; y += 100) {
		if (y == y0) {
			continue;
		}
		dc.MoveTo(x0, y);
		dc.LineTo(x0 + 10, y);
		dc.TextOutW(x0 - 30, y - 7,
			CStringW(std::to_string(y0 - y).c_str()));
	}
	_will_draw_coord = false;
}