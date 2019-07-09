#ifndef SHAPEWIDGET_H
#define SHAPEWIDGET_H

#include <QtGui/QWidget>
#include<QTimer>
#include<QPixmap>
#include<QtNetwork>
class ShapeWidget : public QWidget
{
    Q_OBJECT

public:
    ShapeWidget(QWidget *parent = 0);
    ~ShapeWidget();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    QPoint dragPosition;
    QTimer *timer;
    QPixmap *pix;
    int count;
    QUdpSocket *receiver;
    QUdpSocket *sender;
    int isPlayed;
private slots:
    void changePicture();
    void processPendingDatagram();
    void sendPicture(QImage* image);
};

#endif // SHAPEWIDGET_H
