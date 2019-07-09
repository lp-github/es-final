#include "shapewidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include "v4l2grab.h"
ShapeWidget::ShapeWidget(QWidget *parent)//
    : QWidget(parent)
{
    isPlayed=1;
    pix=new QPixmap();
    pix->load(":/images/p1.png",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither);
    resize(pix->size());
    setMask(QBitmap(pix->mask()));

    count=1;
    timer=new QTimer(this);
    timer->start(30);
    connect(timer,SIGNAL(timeout()),this,SLOT(changePicture()));//

    //network receiver
    receiver = new QUdpSocket(this);
    receiver->bind(45454,QUdpSocket::ShareAddress);
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));

    //network sender
    sender=new QUdpSocket(this);
}

ShapeWidget::~ShapeWidget()
{

}

void ShapeWidget::changePicture()//
{
    if(isPlayed==0){
        return;
    }
    QImage* image=grab();
    sendPicture(image);
    *pix=QPixmap::fromImage(*image);
    //pix->load(picName,0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither);
    //pix->set]
    resize(pix->size());
    setMask(QBitmap(pix->mask()));//
    update();
}
void ShapeWidget::processPendingDatagram(){
    printf("receive message\n");
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(receiver->pendingDatagramSize());
        receiver->readDatagram(datagram.data(),datagram.size());
        char * mess=datagram.data();
        if(strcmp(mess,"play")==0){
            isPlayed=1;
            printf("continue\n");
        }
        else if(strcmp(mess,"pause")==0){
            isPlayed=0;
            printf("paused\n");
        }
        else if(strcmp(mess,"exit")==0){
            close();
            exit(0);
        }
        else if(strcmp(mess,"push")){
            //TODO
        }
        else{
            continue;
        }
        /*printf("none else\n");
        printf("mess:%s",mess);
        exit(0);*/
    }
}
void ShapeWidget::sendPicture(QImage *image){
    for( quint16 y=0; y<image->height(); ++y )
    {
        QByteArray buffer( 6+3*image->width(), 0 );
        QDataStream stream( &buffer, QIODevice::WriteOnly );
        stream.setVersion( QDataStream::Qt_4_0 );

        stream << (quint16)image->width() << (quint16)image->height();
        stream << y;
        for( int x=0; x<image->width(); ++x )
        {
          QRgb rgb = image->pixel( x, y );

          stream << (quint8)qRed( rgb ) << (quint8)qGreen( rgb ) << (quint8)qBlue( rgb );

        }
         sender->writeDatagram( buffer, QHostAddress::Broadcast, 9988 );
    }


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

