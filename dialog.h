#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "videiosurface.h"
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void vedeioChangedSlot(QVideoFrame curFrame);

    void timeoutSlot();

private:
    Ui::Dialog *ui;

    QCamera *camera;
    //QCameraViewfinder *viewfinder;
    QCameraImageCapture *imageCapture;
    videiosurface *vf;


};

#endif // DIALOG_H
