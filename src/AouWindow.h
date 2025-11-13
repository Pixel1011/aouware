#pragma once
#include <qlabel.h>
#include <qmovie.h>
#include <qelapsedtimer.h>
#include <qtypes.h>
#include <qmetatype.h>
#include <qvectornd.h>
#include <qnamespace.h>
#include <qaudiooutput.h>
#include <qmediaplayer.h>
#include <qwidget.h>
#include <qbuffer.h>
#include <qsoundeffect.h>

class AouWindow : public QLabel
{
public:
	AouWindow(QWidget* parent, Qt::WindowFlags f = Qt::WindowFlags());
private:
	void update();
	bool Collide();
	void Move(float dtime);
	void Draw();
	static void checkSupportedFormats();

	QVector2D* position;
	QVector2D* velocity;

	QSoundEffect* soundEffect;
	QMovie* movie;
	QElapsedTimer timer;
	qint64 lastFrameTime = 0;
	int frameRate = 90;
};