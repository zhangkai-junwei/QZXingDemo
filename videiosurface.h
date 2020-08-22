#ifndef VIDEIOSURFACE_H
#define VIDEIOSURFACE_H

#include <QAbstractVideoSurface>
#include <QList>
#include <QVideoFrame>

class videiosurface: public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit videiosurface(QObject *parent = 0);
    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType) const;
    bool present(const QVideoFrame &frame);

signals:
    void vedioChanged(QVideoFrame);
public slots:
};

#endif // VIDEIOSURFACE_H
