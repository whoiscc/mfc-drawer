#include "stdafx.h"
#include "Worker.h"


Worker::~Worker()
{
}

namespace {
	int Round(double x) {
		return int(x + (x > 0 ? 0.5 : -0.5));
	}

	template <typename T> T Abs(T x) {
		return x > 0 ? x : -x;
	}
	
	template <typename T> void Swap(T &a, T &b) {
		T tmp = a;
		a = b;
		b = tmp;
	}
}
void Worker::Draw(int x, int y) { return _manager.DrawPixel(x, y); }
void Worker::NextTick() { return _manager.NextTick(); }


// Implematation
void Worker::DrawLineDDA(int x0, int y0, int x1, int y1) {
	int dx = x1 - x0, dy = y1 - y0;
	int steps = Abs(dx) > Abs(dy) ? Abs(dx) : Abs(dy);
	
	float xInc = float(dx) / float(steps), 
		yInc = float(dy) / float(steps);

	Draw(x0, y0);

	float x = float(x0), y = float(y0);
	for (int k = 0; k < steps; k++) {
		x += xInc;
		y += yInc;
		NextTick();
		Draw(Round(x), Round(y));
	}
}

namespace {
	template <typename F1, typename F2>
	void DrawLineBresenhamImpl(int x0, int y0, int x1, int y1,
			F1 Draw, F2 NextTick) {
		int dx = Abs(x1 - x0), dy = Abs(y1 - y0);
		int p = 2 * dy - dx;
		int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
		if (x0 > x1) {
			Swap(x0, x1);
			Swap(y0, y1);
		}
		int yStep = y1 > y0 ? 1 : -1;

		int x = x0, y = y0;
		Draw(x, y);
		while (x < x1) {
			x++;
			if (p < 0) {
				p += twoDy;
			}
			else {
				y += yStep;
				p += twoDyMinusDx;
			}
			NextTick();
			Draw(x, y);
		}
	}
}

void Worker::DrawLineBresenham(int x0, int y0, int x1, int y1)
{
	if (Abs(x1 - x0) > Abs(y1 - y0)) {
		DrawLineBresenhamImpl(x0, y0, x1, y1, [this](int x, int y) {
			Draw(x, y);
		}, [this]() { NextTick(); });
	}
	else {
		DrawLineBresenhamImpl(y0, x0, y1, x1, [this](int x, int y) {
			Draw(y, x);
		}, [this]() { NextTick(); });
	}
}

namespace {
	void Draw8(int x, int y, int xc, int yc, Worker &worker) {
		worker.Draw(xc + x, yc + y);
		worker.Draw(xc + x, yc - y);
		worker.Draw(xc - x, yc + y);
		worker.Draw(xc - x, yc - y);
		worker.Draw(xc + y, yc + x);
		worker.Draw(xc + y, yc - x);
		worker.Draw(xc - y, yc + x);
		worker.Draw(xc - y, yc - x);
		worker.NextTick();
	}
}

void Worker::DrawCircle(int xc, int yc, int r)
{
	int p = 1 - r;
	int x = 0, y = r;
	Draw8(x, y, xc, yc, *this);
	while (x < y) {
		x++;
		if (p < 0) {
			p += 2 * x + 1;
		}
		else {
			y--;
			p += 2 * (x - y) + 1;
		}
		Draw8(x, y, xc, yc, *this);
	}
}

#include <cstdio>

namespace {
	void Draw4(int x, int y, int xc, int yc, Worker &worker) {
		char buffer[100];
		sprintf(buffer, "x: %d y: %d\n", x, y);
		TRACE(buffer);
		worker.Draw(xc + x, yc + y);
		worker.Draw(xc + x, yc - y);
		worker.Draw(xc - x, yc + y);
		worker.Draw(xc - x, yc - y);
		worker.NextTick();
	}
}

void Worker::DrawEllipse(int xc, int yc, int rx, int ry)
{
	int rx2 = rx * rx, ry2 = ry * ry;
	int twoRx2 = 2 * rx2, twoRy2 = 2 * ry2;
	int x = 0, y = ry;
	int px = 0, py = twoRx2 * y;
	Draw4(x, y, xc, yc, *this);

	int p = Round(ry2 - rx2 * ry + 0.25 * rx2);
	while (px < py) {
		x++;
		px += twoRy2;
		if (p < 0) {
			p += ry2 + px;
		}
		else {
			y--;
			py -= twoRx2;
			p += ry2 + px - py;
		}
		Draw4(x, y, xc, yc, *this);
	}

	TRACE("start region 2\n");
	p = Round(
		(double)ry2 * (x + 0.5) * (x + 0.5) + 
		(double)rx2 * (y - 1) * (y - 1) - 
		(double)rx2 * ry2);
	while (y > 0) {
		y--;
		py -= twoRx2;
		if (p > 0) {
			p += rx2 - py;
		}
		else {
			x++;
			px += twoRy2;
			p += rx2 - py + px;
		}
		Draw4(x, y, xc, yc, *this);
	}
}
