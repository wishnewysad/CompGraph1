// CompGraph1.cpp : Определяет точку входа для приложения.

#include "framework.h"
#include "CompGraph1.h"
#include "line.h"

#define _WIN32_WINNT 0x0A00

#define PI 3.14159265358979323846
#define gradToRad(x) x * PI/180 
float speed = 4.0f;
LINE* lines;
LINE first, second;

LRESULT APIENTRY WndProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {

	WNDCLASSEXW wcex;
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = L"My class";
	wcex.lpfnWndProc = WndProc;
	RegisterClassExW(&wcex);

	HWND hwnd = CreateWindowW(L"My class", L"First Lab", WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		0, 0, 1000, 550, NULL, NULL, NULL, NULL);

	ShowWindow(hwnd, SW_SHOWNORMAL);

	lines = new LINE[2];

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	delete[] lines;

	return (int)msg.wParam;
}

unsigned int from = 0, to = 1;
LRESULT APIENTRY WndProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	unsigned int key;
	switch (Msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP memBM = CreateCompatibleBitmap(hdc, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top);

		SelectObject(memDC, memBM);

		//отрисовка:
		// 
		//Заполнение буфера белым цветом
		FillRect(memDC, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		//Отрисовка отрезка AB с помощью встроенных функций (красный отрезок)
		showFirstLine(lines[0].getStartPoint(), lines[0].getEndPoint(), memDC);
		showSecondLine(lines[1].getStartPoint(), lines[1].getEndPoint(), memDC);

		//Загрузка буфера в битмап графического устройства и освобождение памяти выделенной на буфер
		BitBlt(hdc, 0, 0, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top, memDC, 0, 0, SRCCOPY);
		DeleteDC(memDC);
		DeleteObject(memBM);


		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
		key = wParam;
		switch (key)
		{
			// первая линия
		case '1':
			from = 0;
			to = 1;
			break;
			// вторая линия
		case '2':
			from = 1;
			to = 2;
			break;
			// обе линии
		case '3':
			from = 0;
			to = 2;
			break;
			// кручу верчу
		case 'q':
		case 'Q':
			for (size_t i = from; i < to; i++) {
				lines[i].rotate(gradToRad(5));
			}
			//first.rotate(gradToRad(5));
			break;
		case 'e':
		case 'E':
			for (size_t i = from; i < to; i++) {
				lines[i].rotate(gradToRad(-5));
			}
			//first.rotate(gradToRad(-5));
			break;
			// движение по осям X и Y
		case 'w':
		case 'W':
			for (size_t i = from; i < to; i++) {
				lines[i].move(1, -speed);
			}
			//first.move(1, -speed);
			break;
		case 's':
		case 'S':
			for (size_t i = from; i < to; i++) {
				lines[i].move(1, speed);
			}
			//first.move(1, speed);
			break;
		case 'a':
		case 'A':
			for (size_t i = from; i < to; i++) {
				lines[i].move(0, -speed);
			}
			//first.move(0, -speed);
			break;
		case 'd':
		case 'D':
			for (size_t i = from; i < to; i++) {
				lines[i].move(0, speed);
			}
			//first.move(0, speed);
			break;
			// масштабирование		
			// увеличение
		case 'r':
		case 'R':
			for (size_t i = from; i < to; i++) {
				lines[i].scale(1.1f);
			}
			//first.scale(1.1f);
			break;
			// уменьшение
		case 'f':
		case 'F':
			for (size_t i = from; i < to; i++) {
				lines[i].scale(0.9f);
			}
			//first.scale(0.9f);
			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}