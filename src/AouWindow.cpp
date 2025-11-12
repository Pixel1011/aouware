#include "AouWindow.h"
#include <qtimer.h>
#include <qtypes.h>
#include <qmovie.h>
#include <qlabel.h>
#include <qlogging.h>
#include <qlist.h>
#include <qbytearray.h>
#include <qimagereader.h>
#include <qfile.h>
#include <qnamespace.h>
#include <qwidget.h>

AouWindow::AouWindow(QWidget* parent, Qt::WindowFlags f = Qt::WindowFlags()) : QLabel(parent, f)
{
    QMovie* movie = new QMovie(":/aou2.gif");
    setMovie(movie);
    movie->setScaledSize(parent->size());
    movie->start();

    if (!movie->isValid()) {
        setText("Failed to load GIF!");
        qDebug() << "Failed to load GIF!" << movie->lastErrorString();
        return;
    }
}

void AouWindow::update()
{
    qint64 now = timer.elapsed();
    float delta = (now - lastFrameTime) / 1000.0f; // seconds
    lastFrameTime = now;
}

void AouWindow::checkSupportedFormats() {
    QList<QByteArray> formats = QImageReader::supportedImageFormats();
    qDebug() << "Supported formats:" << formats;
}