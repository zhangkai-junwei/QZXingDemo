#include "videiosurface.h"

videiosurface::videiosurface(QObject *parent):QAbstractVideoSurface(parent)
{

}

QList<QVideoFrame::PixelFormat> videiosurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    return QList<QVideoFrame::PixelFormat>()<<QVideoFrame::Format_RGB32;
}

bool videiosurface::present(const QVideoFrame &frame)
{
    emit vedioChanged(frame);
    return true;
}
