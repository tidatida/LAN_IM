#include <QtWidgets/QApplication>
#include "view/IMLoginWidget.h"
#include <QTextCodec>
#include <QDebug>

#include "view/IMInformationWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 0
    /* the below lines try to use chinese char */
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    /* the end of use chinese char */
#endif
    IMLoginWidget w;
    w.show();
    if (true == w.getIsAutoLogin())
    {
        qDebug() << "click";
        w.onClickBtnLogin();
    }

//    IMInformationWidget w;
//    w.setReadOnly(true, true);
//    w.show();
    
    return a.exec();
}

//192.168.50.133
