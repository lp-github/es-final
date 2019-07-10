/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Wed Jul 10 10:27:06 2019
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *playButton;
    QPushButton *exit;
    QLabel *picture;
    QLabel *count;
    QPushButton *receive;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(591, 494);
        playButton = new QPushButton(Widget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setGeometry(QRect(400, 340, 161, 27));
        exit = new QPushButton(Widget);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setGeometry(QRect(400, 400, 161, 27));
        picture = new QLabel(Widget);
        picture->setObjectName(QString::fromUtf8("picture"));
        picture->setGeometry(QRect(20, 70, 351, 351));
        count = new QLabel(Widget);
        count->setObjectName(QString::fromUtf8("count"));
        count->setGeometry(QRect(520, 30, 31, 21));
        receive = new QPushButton(Widget);
        receive->setObjectName(QString::fromUtf8("receive"));
        receive->setGeometry(QRect(400, 290, 161, 27));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        playButton->setText(QApplication::translate("Widget", "pause", 0, QApplication::UnicodeUTF8));
        exit->setText(QApplication::translate("Widget", "exit", 0, QApplication::UnicodeUTF8));
        picture->setText(QApplication::translate("Widget", "TextLabel", 0, QApplication::UnicodeUTF8));
        count->setText(QApplication::translate("Widget", "0", 0, QApplication::UnicodeUTF8));
        receive->setText(QApplication::translate("Widget", "save", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
