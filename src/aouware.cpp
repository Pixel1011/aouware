// aouware.cpp : Defines the entry point for the application.


#include "aouware.h"
#include "AouWindow.h"
#include <qwidget.h>
#include <qapplication.h>
#include <qmovie.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	srand(static_cast<unsigned int>(time(nullptr)));

	QWidget window;
	window.resize(155, 145);
	window.setWindowTitle("aou");
	window.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	
	AouWindow* aouWindow = new AouWindow(&window);
	
	window.show();

	//AouWindow* aouWindow = new AouWindow();
	//aouWindow->setParent(&window);
	//aouWindow->setStyleSheet("background-color: black;");

	//aouWindow->show();
	return app.exec();
}
