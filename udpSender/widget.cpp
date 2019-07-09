#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QBitmap>
#include <QLabel>
#include <QtNetwork>
#include <QDataStream>
#include <QObject>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    label = this->findChild<QLabel*>("picture");
    image = 0;
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    receiver->bind(9988);
    connect(receiver, SIGNAL(readyRead()), this, SLOT(dataPending()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_receive_clicked()
{
    image = 0;
    QByteArray datagram="push";
    rev_count++;
    char str[5];
    sprintf(str, "%d", rev_count);
    ui->count->setText(str);
    sender->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,45454);
}

void Widget::on_playButton_clicked()
{
    play=1-play;
    printf("play button clicked\n");
    QByteArray datagram="Hello World!";
    if(play==0){
        printf("play state change to 0: paused\n");
        datagram="pause";
        ui->playButton->setText("play");
    }
    else{
        printf("play state change to 1: played\n");
        datagram="play";
        ui->playButton->setText("pause");
    }
    sender->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,45454);
}

void Widget::on_exit_clicked()
{
    printf("exit button clicked\n");
    exit=1-exit;
    QByteArray datagram="exit";
    /*
    if(exit==0){
        printf("exit state change to 0: \n");
        datagram="exit";
    }
    else{
        printf("exit state change to 1: \n");
        datagram="pl";
    }*/
    sender->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,45454);
}


void Widget::dataPending(){

    while( receiver->hasPendingDatagrams() )
    {
        QByteArray buffer( receiver->pendingDatagramSize(), 0 );
        receiver->readDatagram( buffer.data(), buffer.size() );

        QDataStream stream( buffer );
        stream.setVersion( QDataStream::Qt_4_0 );

        quint16 width, height, y;
        stream >> width >> height >> y;

        if( !image )
          image = new QImage( width, height, QImage::Format_RGB32 );
        else if( image->width() != width || image->height() != height )
        {
          delete image;
          image = new QImage( width, height, QImage::Format_RGB32 );
        }

        for( int x=0; x<width; ++x )
        {
          quint8 red, green, blue;
          stream >> red >> green >> blue;

          image->setPixel( x, y, qRgb( red, green, blue ) );
        }
    }

    QPixmap pixmap = QPixmap::fromImage(*image);
     pixmap.scaled(label->size(), Qt::KeepAspectRatio);
     label->setScaledContents(true);
     label->setPixmap(pixmap);
     //label->resize( image->size() );


}

