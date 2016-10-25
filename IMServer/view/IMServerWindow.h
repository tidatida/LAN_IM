/*********************************************
File Name： IMServerWindow.h
Author： jet.F.R
Date： 2014.3.10
Description： server mainframe class
Changes：
********************************************/

#ifndef IMSERVERWINDOW_H
#define IMSERVERWINDOW_H

#include <QtWidgets>

class IMServerMessageCtrl;

/*************************************************
Class Name： IMServerWindow
Description: server mainframe class
*************************************************/
class IMServerWindow : public QWidget
{
    Q_OBJECT

public:
    IMServerWindow(QWidget *parent = 0);
    ~IMServerWindow();

private:
        IMServerMessageCtrl *m_serverCtrl;
};

#endif // IMSERVERWINDOW_H
