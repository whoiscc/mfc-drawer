#pragma once
#include "Manager.h"


class Manager;

class Worker
{
public:
	Worker(Manager &manager) :_manager(manager) {}
	~Worker();

	void Draw(int x, int y);
	void NextTick();

	void DrawLineDDA(int x0, int y0, int x1, int y1);
	void DrawLineBresenham(int x0, int y0, int x1, int y1);
	void DrawCircle(int xc, int yc, int r);
	void DrawEllipse(int xc, int yc, int rx, int ry);
private:
	Manager &_manager;
};

