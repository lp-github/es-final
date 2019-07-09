#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QPixmap>
#include <QImage>
#include <QLabel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private slots:
    /*void on_pushButton_clicked();
    void on_exitButton_clicked();*/



    void on_playButton_clicked();

    void on_exit_clicked();

    void on_receive_clicked();

    void dataPending();

private:
    Ui::Widget *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    QImage *image;
    QLabel *label;

    int play=1;
    int exit=0;
    int rev_count = 0;
};

#endif // WIDGET_H
