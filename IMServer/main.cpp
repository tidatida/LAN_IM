#include "view/IMServerWindow.h"
#include <QtWidgets/QApplication>
#include <QtCore/QTextCodec>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* I am not clear why the author disable the below lines, just translate chinese comments to english */
//    /* make sure only one process is running */
//    QSystemSemaphore sema("IMServerKey",1,QSystemSemaphore::Open);
//    /* use shared-mem in strict protected area */
//    sema.acquire();
//    QSharedMemory mem("IMServerObject");

//    /* if global mem exists, exit. */
//    if (!mem.create(1))
//    {
//        QMessageBox::warning(NULL, "error",
//            "A server has already been running.");
//        sema.release();
//        return 0;
//    }
//    sema.release();


    IMServerWindow w;
    w.show();
    
    return a.exec();
}
