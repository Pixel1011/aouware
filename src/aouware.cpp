// aouware.cpp : Defines the entry point for the application.


#include "aouware.h"
#include "AouWindow.h"
#include <qwidget.h>
#include <qapplication.h>
#include <qmovie.h>
#include <qlabel.h>
#include <qnamespace.h>

using namespace std;

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QWidget window;
	window.resize(250, 250);
	window.setWindowTitle("aou");
	window.setWindowFlags(Qt::FramelessWindowHint);
	

	
	
	window.show();

	//AouWindow* aouWindow = new AouWindow();
	//aouWindow->setParent(&window);
	//aouWindow->setStyleSheet("background-color: black;");

	//aouWindow->show();

	window.setStyleSheet("background-color: black;");

	return app.exec();
}
