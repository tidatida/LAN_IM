/*********************************************
File Name： IMTcpServer.h
Author： jet.F.R
Date： 2014.3.10
Description：
Changes：
********************************************/

#ifndef IMTCPSERVER_H
#define IMTCPSERVER_H

#include <QTcpServer>
#include "control/IMClientSocketCtrl.h"
#include "IMConstant.h"
#include "control/IMDatabaseCtrl.h"

/*************************************************
Class Name： IMTcpServer
Description: 
*************************************************/
class IMTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    IMTcpServer(QObject *parent = 0);
    ~IMTcpServer();

public slots:
    void clientDisconnected(const QString &id);
    void sendMessage(const SaveTmpInformation &temp);

signals:
    void haveNewID(const QString & id);
    void haveNewAddress(const QString & address);
    void haveLeftID(const QString & id);
    void haveLeftAddress(const QString & address);

private:
    void incomingConnection(int socketDescriptor);

    void friendRequest(const SaveTmpInformation & save);
    void flockRequest(const SaveTmpInformation & save);
    void discussionRequest(const SaveTmpInformation & saves);
    void talkRequest(const SaveTmpInformation & save);


    void tellFriendsStatusChanged(const QString &id, int status);
    void tellFriendsInformationChanged(const QString & id);//, const FriendInformation &fri);
    void tellMembersFlockDroped(const QString & flockID);
    void tellMembersDiscussionDroped(const QString & discussionID);
    void tellMembersFlockChanged(const FlockInformation &);
    void tellMembersDiscussionChanged(const DiscussionInformation &);

    void tellFlockMemberHaveNewMember(const QString &flockID);
    void tellFlockMemberHaveLeavedMember(const QString & flockID);

    void tellDiscussionMemberHaveNewMember(const QString & discussionID);
    void tellDiscussionMemberHaveLeavedMember(const QString & discussionID);

private:
    SaveTmpInformation m_save;
    IMDatabaseCtrl m_database;
    QMap<QString, IMClientSocketCtrl*> m_userMap;
    QMap<QString, int> m_userStatus;

    QMap<QString, IMClientSocketCtrl*> m_userMailMap;
};

#endif // IMTCPSERVER_H

