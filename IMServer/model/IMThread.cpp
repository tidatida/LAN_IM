/*********************************************
File Name： IMThread.cpp
Author： jet.F.R
Date： 2014.3.10
Description：
Changes：
********************************************/

#include "IMThread.h"
#include "control/IMClientSocketCtrl.h"

// mark: public--------------------------------------------
IMThread::IMThread(QObject *parent) :
    QThread(parent)
{
}


IMThread::IMThread( QObject * parent, int socketDescriptor):
    QThread(parent)

{
    m_socketDescriptor = socketDescriptor;
}

IMThread::~IMThread()
{
//    if (m_clientSocket != NULL)
//    {
//        delete m_clientSocket;
//        m_clientSocket = NULL;
//    }
}


// mark: public slots:--------------------------------------
//void IMThread::sendTalkMessage(TalkMessage mes)
//{
//    m_clientSocket->sendTalkMessage(mes);
//}

// mark: private------------------------------------------
/*************************************************
Function Name： run()
Description: 
Input： NULL
Output：NULL
Changes： NULL
*************************************************/
void IMThread::run()
{
    m_clientSocket = new IMClientSocketCtrl;
    m_clientSocket->setSocketDescriptor(m_socketDescriptor);

    connect(m_clientSocket, SIGNAL(destroyed()),this, SLOT(quit()));//断开连接时线程退出
    exec();
}
