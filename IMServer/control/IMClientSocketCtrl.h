/*********************************************
File Name: IMClientSocketCtrl.h
Author: jet.F.R
Date: 2014.3.10
Description: used to   control  clientsocket的 class
Changes:
********************************************/

#ifndef IMCLIENTSOCKETCTRL_H
#define IMCLIENTSOCKETCTRL_H

#include <QTcpSocket>
#include "IMDatabaseCtrl.h"
#include "model/IMConstant.h"

class QDateTime;
class IMUser;


/*************************************************
Class Name: IMClientSocketCtrl
Description: from clientsocket，used to   process   requests 
*************************************************/
class IMClientSocketCtrl : public QTcpSocket
{
    Q_OBJECT
public:
    IMClientSocketCtrl(QObject *parent = 0);
    ~IMClientSocketCtrl();

signals:
//    void havaNewClientSocket(IMClientSocket *);
    // request serverprocess   
    void sendSignal(const SaveTmpInformation &temp);
    // user 登录
    void userLoginSignal(const UserInformation &user);
    //user 断开connection 了
    void deleteSignal(const QString &acc);

public slots:
    // 接收信息
    void receiveMessage();
    // 发送信息
    void sendMessage(const SaveTmpInformation &temp);
    // delete  socket
    void deleteScoket();

private:
    quint16 m_blockSize;
    SaveTmpInformation m_save;

    /****************************************/
//public slots:
//    // 发送user 的信息至另一个user 
//    void sendTalkMessage(TalkMessage);

//private slots:
//    // 读取信息
//    void readMessage();

private:
//    // 检测登录信息
//    bool checkUser(const QString & id,const QString & pwd,
//                   const QDateTime &);

//    // add user 
//    bool addUser(IMUser &);

//    // 获取所有好友
//    bool getFriends(const QString &);

//    // 发送信息
//    void sendMessage(MessageType type,bool is = false,
//                     const IMUser *user = NULL,
//                     const QString &mes1 = "",
//                     const QString &mes2 = "");

//    // 发送检测结果
//    void sendCheckResult(bool isSuccess, const QString &id = "",
//                         const QString &nick = "");

//    // 发送Register 结果
//    void sendRegisterResult(bool isSuccess, const IMUser * user = NULL);

//    // 发送所有好友信息
//    void sendFriends(bool isSuccess,
//                     const QMultiMap<QString, FriendInformation> * map = NULL);

private:
    IMDatabaseCtrl m_database;

};

#endif // IMCLIENTSOCKETCTRL_H
