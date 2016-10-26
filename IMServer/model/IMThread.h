/*********************************************
File Name: IMThread.h
Author: jet.F.R
Date: 2014.3.10
Description: server used to   process   socketIO thread class
Changes:
********************************************/
#ifndef IMTHREAD_H
#define IMTHREAD_H

#include <QThread>
#include "model/IMConstant.h"

class IMClientSocketCtrl;


/*************************************************
Class Name: IMThread
Description: process   socketIO thread class
*************************************************/
class IMThread : public QThread
{
    Q_OBJECT
public:
    explicit IMThread(QObject *parent = 0);
    explicit IMThread( QObject * parent, int socketDescriptor);
    ~IMThread();

signals:

public slots:
//    void sendTalkMessage(TalkMessage mes);

private:
    void run(); // threadrunning ，will call this func

private:
    int m_socketDescriptor;
    IMClientSocketCtrl * m_clientSocket;

};

#endif // IMTHREAD_H
