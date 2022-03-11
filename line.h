#ifndef LINE_H
#define LINE_H

#include <cmath>
#include <windows.h>

struct point {
	float x, y;
};

class LINE {
public:
	LINE ();
	~LINE ();
	void move(int asix, float speed);
	void rotate(double angle);
	void scale(float scale);
	POINT getStartPoint();
	POINT getEndPoint();


private:
	point start, end;
};


void showFirstLine(POINT startP, POINT endP, HDC hdc);

void showSecondLine(POINT startP, POINT endP, HDC hdc);

#endif // !LINE_H