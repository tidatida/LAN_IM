/*********************************************
File Name： IMTcpSocket.h
Author： jet.F.R
Date： 2014.3.10
Description： 
Changes：
********************************************/

#ifndef IMTCPSOCKET_H
#define IMTCPSOCKET_H

#include <QTcpSocket>
#include "IMConstant.h"

/*************************************************
Class Name： IMTcpSocket
Description: 
*************************************************/
class IMTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    IMTcpSocket(QObject *parent = 0);
    // 
    void requestConnect();
    // 
    bool isConnected();

    void setFlag(int);
    int flag();

    // 
    static QString getIP();
    //
    static QString getCurrentDateTime();

    static QHostAddress s_hostAddress;
    static int s_hostPort;

signals:
    void showConnectionStatus(const QString &, bool isLogin = false);

private slots:
    // 
    void connectionClosed();
    // 
    void connectionCreate();
    // 
    void dispalyError(QAbstractSocket::SocketError);

private:
    // 
    void linkSignalWithSlot();


    bool m_isConnected;

    int m_flag;

};

#endif // IMTCPSOCKET_H
