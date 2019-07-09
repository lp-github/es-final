#include <QtGui/QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    printf("a");
    QApplication a(argc, argv);
    Widget w;
    w.show();
    
    return a.exec();
}
