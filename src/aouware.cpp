// aouware.cpp : Defines the entry point for the application.

#include "aouware.h"
#include "AouWindow.h"
#include <qwidget.h>
#include <qapplication.h>
#include <qmovie.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <cstdlib>
#include <windows.h>

using namespace std;

static void createAouWindow(int px = 0, int py = 0, float vx = 0, float vy = 0, int fr = 0) {
	QWidget* window = new QWidget();
	window->resize(155, 145);
	window->setWindowTitle("aou");
	window->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);

	AouWindow* aouWindow = new AouWindow(window);
	window->setFocusPolicy(Qt::NoFocus);
	window->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	window->setAttribute(Qt::WA_TranslucentBackground, true);

	if (px != 0 && py != 0) aouWindow->setPosition(static_cast<float>(px), static_cast<float>(py));
	if (vx != 0 && vy != 0) aouWindow->setVelocity(vx, vy);
	if (fr != 0) aouWindow->setFrameRate(fr);

	window->show();

	HWND aouwin = (HWND)window->winId();
	LONG exStyle = GetWindowLong(aouwin, GWL_EXSTYLE);
	SetWindowLong(aouwin, GWL_EXSTYLE, exStyle | WS_EX_TRANSPARENT | WS_EX_LAYERED);
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	srand(static_cast<unsigned int>(time(nullptr)));
	createAouWindow(0, 0, 0, 0);
	return app.exec();
}