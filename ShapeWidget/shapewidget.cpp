#include "shapewidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include "v4l2grab.h"
ShapeWidget::ShapeWidget(QWidget *parent)//
    : QWidget(parent)
{
    pix=new QPixmap();
    pix->load(":/images/p1.png",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither);
    resize(pix->size());
    setMask(QBitmap(pix->mask()));

    count=1;
    timer=new QTimer(this);
    timer->start(100);
    connect(timer,SIGNAL(timeout()),this,SLOT(changePicture()));//

}

ShapeWidget::~ShapeWidget()
{

}

void ShapeWidget::changePicture()//
{
    QString picName;
    count=count+1;
    if(count>5) count=1;
    switch(count)
    {
    case 1:picName=":/images/p1.png";break;
    case 2:picName=":/images/p2.png";break;
    case 3:picName=":/images/p3.png";break;
    case 4:picName=":/images/p4.png";break;
    case 5:picName=":/images/p5.png";break;
    default:break;
    }
    grab();
    picName="./image_bmp.bmp";
    //QImage *image = new QImage();
    QImage* image=grab();

    image->load(picName);
    *pix=QPixmap::fromImage(*image);
    //pix->load(picName,0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither);
    //pix->set]
    resize(pix->size());
    setMask(QBitmap(pix->mask()));//
    update();
}

void ShapeWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        dragPosition =event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
    if(event->button()==Qt::RightButton)
    {
       close();
    }
}

void ShapeWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        move(event->globalPos()-dragPosition);
        event->accept();
    }
}

void ShapeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,*pix);
}

