#pragma once

#include <vector>
#include <deque>
#include "ChildView.h"

class CChildView;

class Manager
{
public:
	Manager(CChildView &view, int width, int height);
	~Manager();

	// interface toward Worker
	void DrawPixel(int x, int y);
	void NextTick();

	// interface toward View
	void ResetCanvas(int width, int height);
	void ResetCanvas() { ResetCanvas(_width, _height); }
	void OnTimer(UINT_PTR nIDEvent);
	void OnPaint();

private:
	CChildView &_view;
	int _width, _height;
	struct _Point { int x; int y; };
	std::deque < std::vector<struct _Point>> _buffer;
	std::vector<struct _Point> _will_paint_buffer;

	bool _has_timer;
	UINT_PTR _timer_id;

	void _DrawCoord();
	bool _will_draw_coord;
};

