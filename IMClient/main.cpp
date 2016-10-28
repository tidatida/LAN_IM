#include <QtWidgets/QApplication>
#include "view/IMLoginWidget.h"
#include <QTextCodec>
#include <QDebug>

#include "view/IMInformationWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << " start ... ";

    IMLoginWidget w;
    w.show();

    qDebug() << " after w.show(), ... ";


    if (true == w.getIsAutoLogin())
    {
        qDebug() << "click";
        w.onClickBtnLogin();
    }

//    IMInformationWidget w;
//    w.setReadOnly(true, true);
//    w.show();

    qDebug() << "hello, ... ";

    return a.exec();
}

//192.168.50.133
