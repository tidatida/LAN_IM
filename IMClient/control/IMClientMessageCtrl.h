///*********************************************
//File Name： IMClientMessageCtrl.h
//Author： jet.F.R
//Date： 2014.3.10
//Description： 
//Changes：
//********************************************/

//#ifndef IMCLIENTMESSAGECTRL_H
//#define IMCLIENTMESSAGECTRL_H

//#include <QObject>
//#include <QObject>
//#include <QHostAddress>

//class IMTcpSocket;
//class IMUser;

//enum MessageType
//{
//    CONNECT = 0,
//    LOGIN   = 1,
//    REGISTER = 2
//};

//enum LoginStatus
//{
//    ONLINE = 0,
//    INVISIBLE = 1,
//    BUSY = 2,
//    LEAVE = 3,
//    NOTDISTURB = 4
//};

///*************************************************
//Class Name： IMClientMessageCtrl
//Description: 
//*************************************************/
//class IMClientMessageCtrl : public QObject
//{
//    Q_OBJECT
//public:
//    explicit IMClientMessageCtrl(QObject *parent = 0);
//    ~IMClientMessageCtrl();
//    void sendMessage(MessageType, const QString &mes1,
//                     const QString &mes2 = "", LoginStatus status = ONLINE,
//                     const IMUser * user = NULL);

//    static QHostAddress sm_hostAddress;
//    static qint16 sm_hostPort;

//signals:
//    void showLoginStatus(const QString &, bool isLogin = false);

//public slots:

//private slots:
//    //void connectionClosed();
//    void readMessage();
//    //void dispalyError(QAbstractSocket::SocketError);
//    void requestLogin();
//    void requsetRegister(const IMUser *);

//private:
//    void initIMClientMessageCtrl();
//    //void linkSignalWithSlot();
//    void requestConnect();
//    //QString getIP();

//private:
//    IMTcpSocket *m_tcpSocket;
//    quint16 m_blockSize;

//    QString m_id;
//    QString m_pwd;
//    LoginStatus m_status;

//    bool m_isConnected;

//};
//#endif // IMCLIENTMESSAGECTRL_H
