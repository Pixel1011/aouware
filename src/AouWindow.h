#pragma once
#include <qlabel.h>
#include <qmovie.h>
#include <qelapsedtimer.h>
#include <qtypes.h>


class AouWindow : public QLabel
{
public:
	AouWindow(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
private:
	void update();
	static void checkSupportedFormats();
	QMovie* movie;
	QElapsedTimer timer;
	qint64 lastFrameTime = 0;
	const int frameRate = 60;
};