#include "line.h"


LINE::LINE() {
	start.x = 10;
	start.y = 10;
	end.x = 100;
	end.y = 100;
}

LINE ::~LINE()
{
}

void LINE::move(int axis, float speed) {
	switch (axis)
	{
	case 0:
		start.x += speed;
		end.x   += speed;
		break;
	case 1:
		start.y += speed;
		end.y   += speed;
		break;
	default:
		break;
	}
}

void LINE::rotate(double angle) {
	long tempX = end.x;
	end.x = (end.x - start.x) * cos(angle) - (end.y - start.y) * sin(angle) + start.x;
	end.y = (tempX - start.x) * sin(angle) + (end.y - start.y) * cos(angle) + start.y;
}

void LINE::scale(float scale) {
	if (!(abs(end.x - start.x) < 1 && abs(end.y - start.y) < 1 && scale < 1)){
		end.x = (end.x - start.x) * scale + start.x;
		end.y = (end.y - start.y) * scale + start.y;
	}
}

POINT LINE::getStartPoint() {
	POINT temp;
	temp.x = static_cast<int>(start.x);
	temp.y = static_cast<int>(start.y);
	return temp;
}

POINT LINE::getEndPoint() {
	POINT temp;
	temp.x = static_cast<int>(end.x);
	temp.y = static_cast<int>(end.y);
	return temp;
}

void showFirstLine(POINT start, POINT end, HDC hdc) {
	HPEN hPen;
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	SelectObject(hdc, hPen);
	MoveToEx(hdc, start.x, start.y, NULL);
	LineTo(hdc, end.x, end.y);
}


void showSecondLine(POINT start, POINT end, HDC hdc) {
	int signX = (end.x >= start.x ? 1 : -1);
	int signY = (end.y >= start.y ? 1 : -1);

	int lengthX = abs(end.x - start.x);
	int lengthY = abs(end.y - start.y);

	int length = max(lengthX, lengthY);

	if (length == 0)
	{
		SetPixel(hdc, start.x, start.y, 0);
	}

	if (lengthY <= lengthX)
	{
		// Начальные значения
		int x = start.x;
		int y = start.y;
		int d = -lengthX;

		// Основной цикл
		length++;
		while (length--)
		{
			SetPixel(hdc, x, y, 0);
			x += signX;
			d += 2 * lengthY;
			if (d > 0) {
				d -= 2 * lengthX;
				y += signY;
			}
		}
	}
	else
	{
		// Начальные значения
		int x = start.x;
		int y = start.y;
		int d = -lengthY;

		// Основной цикл
		length++;
		while (length--)
		{
			SetPixel(hdc, x, y, 0);
			y += signY;
			d += 2 * lengthX;
			if (d > 0) {
				d -= 2 * lengthY;
				x += signX;
			}
		}
	}
}
