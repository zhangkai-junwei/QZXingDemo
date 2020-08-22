#include "dialog.h"
#include "ui_dialog.h"
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QFileDialog>
#include <QDebug>
#include "qzxing/src/QZXing.h"
#include <QTimer>



Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

    if(cameras.count() > 0) {
        foreach (const QCameraInfo &cameraInfo, cameras) {
            qDebug() << cameraInfo.description();
        }
        camera = new QCamera(cameras.at(0));
    }
    //viewfinder = new QCameraViewfinder(this);
    vf = new videiosurface(this);
    camera->setViewfinder(vf);
   // viewfinder->resize(600, 350);

    imageCapture = new QCameraImageCapture(camera);
    connect(vf, SIGNAL(vedioChanged(QVideoFrame)), this, SLOT(vedeioChangedSlot(QVideoFrame)));

    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->start();

    QTimer *m_timer = new QTimer(this);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));
    m_timer->start(100);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    camera->setCaptureMode(QCamera::CaptureStillImage);
    QString fileName = QFileDialog::getSaveFileName();
    qDebug()<<fileName<<endl;
    camera->searchAndLock();
    // 必须使用绝对路径
    imageCapture->capture(fileName);
    camera->unlock();
}

void Dialog::on_pushButton_2_clicked()
{
    QImage image;
    QZXing decoder;
    QString fileName = QFileDialog::getOpenFileName(this,"open file","./","任何文件(*.*)"";;(*.png)");
    if(!fileName.isEmpty())
    {
        if(image.load(fileName))
        {
            decoder.setDecoder(QZXing::DecoderFormat_QR_CODE|QZXing::DecoderFormat_CODE_128);
            QString result = decoder.decodeImage(image);
            if(!result.isEmpty())
            {
                ui->lineEdit->setText(result);
            }
        }
    }

}

void Dialog::vedeioChangedSlot(QVideoFrame curFrame)
{
    QVideoFrame frame(curFrame);
    QImage image;
    frame.map(QAbstractVideoBuffer::ReadOnly);

    image = QImage(frame.bits(), frame.width(), frame.height(),QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));

    QMatrix matrix;
    matrix.rotate(180);
    image = image.transformed(matrix);

    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap = pixmap.scaled(ui->label->size());
    ui->label->setPixmap(pixmap);

}

void Dialog::timeoutSlot()
{
    QImage image;
    QZXing decoder;
    QString fileName = "E:/qt_project/qCamera/1";

    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->searchAndLock();
    // 必须使用绝对路径
    imageCapture->capture(fileName);
    camera->unlock();

    if(!fileName.isEmpty())
    {
        if(image.load(fileName))
        {
            decoder.setDecoder(QZXing::DecoderFormat_QR_CODE|QZXing::DecoderFormat_CODE_128);
            QString result = decoder.decodeImage(image);
            if(!result.isEmpty())
            {
                ui->lineEdit->setText(result);
            }
        }
    }
}
