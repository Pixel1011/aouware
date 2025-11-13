#include "AouWindow.h"
#include <qtimer.h>
#include <qtypes.h>
#include <qmovie.h>
#include <qlabel.h>
#include <qlogging.h>
#include <qlist.h>
#include <qbytearray.h>
#include <qimagereader.h>
#include <qnamespace.h>
#include <qwidget.h>
#include <qguiapplication.h>
#include <qscreen.h>
#include <qsize.h>
#include <qurl.h>
#include <cstdlib>

AouWindow::AouWindow(QWidget* parent, Qt::WindowFlags f) : QLabel(parent, f)
{  
	soundEffect = new QSoundEffect(this);
	soundEffect->setSource(QUrl("qrc:/aou2.wav"));
	soundEffect->setVolume(0.5f);

	movie = new QMovie(":/aou2.gif");
	setMovie(movie);
	movie->setScaledSize(parent->size());

	if (!movie->isValid()) {
		setText("Failed to load GIF!");
		qDebug() << "Failed to load GIF!" << movie->lastErrorString();
		return;
	}
	movie->start();
	timer.start();

	QScreen* screen = QGuiApplication::primaryScreen();
	if (screen) {
		QSize screenSize = screen->size();
		int sw = screenSize.width();
		int sh = screenSize.height();
		frameRate = screen->refreshRate() + 2;
		position = new QVector2D(static_cast<float>(rand() % (sw - this->width())), static_cast<float>(rand() % (sh - this->height())));
	}
	else {
		position = new QVector2D(this->pos().x(), this->pos().y());
	}
	// random velocity
	velocity = new QVector2D(static_cast<float>(rand() % 700) + 100.0f, static_cast<float>(rand() % 700) + 100.0f);
	*velocity *= 2.0f;
	lastFrameTime = timer.elapsed();
	QTimer* frameTimer = new QTimer(this);
	connect(frameTimer, &QTimer::timeout, this, &AouWindow::update);
	frameTimer->start(1000.0 / frameRate);
}

void AouWindow::update()
{
	qint64 now = timer.elapsed();
	float delta = (now - lastFrameTime) / 1000.0f; // seconds
	lastFrameTime = now;
	Move(delta);
	if (Collide()) {
		soundEffect->play();
	}
	Draw();
}

bool AouWindow::Collide()
{
	// get screen size
	QScreen* screen = QGuiApplication::primaryScreen();
	if (!screen) return false; // dont expect this to occur but :p
	QSize screenSize = screen->size();
	int sw = screenSize.width();
	int sh = screenSize.height();
	
	bool hit = false;
	// 0, 0, sw, sh
	// top, left, right, bottom
	float x, y;
	x = position->x();
	y = position->y();

	// hits left
	if (x <= 0) {
		x = 0;
		velocity->setX(-velocity->x());
		hit = true;
	}
	// hits right
	if (x + this->width() >= sw) {
		x = sw - this->width() - 1; // same up here for catwtf reasons
		velocity->setX(-velocity->x());
		hit = true;
	}
	// hits top
	if (y <= 0) {
		y = 0;
		velocity->setY(-velocity->y());
		hit = true;
	}
	// hits bottom
	if (y + this->height() >= sh) {
		y = sh - this->height() - 1; // -1 for catwtf reasons
		velocity->setY(-velocity->y());
		hit = true;
	}

	// stop catexplode
	position->setX(x);
	position->setY(y);
	return hit;
}

void AouWindow::Move(float dtime)
{
	position->setX(position->x() + velocity->x() * dtime);
	position->setY(position->y() + velocity->y() * dtime);
}

void AouWindow::Draw()
{
	parentWidget()->move(position->x(), position->y());
}

void AouWindow::checkSupportedFormats() {
	QList<QByteArray> formats = QImageReader::supportedImageFormats();
	qDebug() << "Supported formats:" << formats;
}