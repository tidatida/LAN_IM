/*********************************************
File Name: IMMainCtrl.h
Author: jet.F.R
Date: 2014.3.26
Description: 
Changes:
********************************************/
#ifndef IMMAINCTRL_H
#define IMMAINCTRL_H

#include <QObject>
#include <QMultiMap>
#include "model/IMConstant.h"
#include <QVector>


class IMTcpSocket;

class IMMainCtrl : public QObject
{
    Q_OBJECT
public:
    IMMainCtrl(const QString myID, QObject *parent = 0);
    
    void closeConnect();

    void getFriendsInformation(const QString &, const int);
    void getFlocksInformation(const QString &);
    void getDiscussionsInformation(const QString &);
    void getLatestMessage(const QString &);

    void getFlockMembers(const QString &);
    void getDiscussionMembers(const QString &);

    void sendTalkMessage(TalkMessage &);

    void getFriendInformation(const QString &id);
    void getMynformation(const QString &id);
    void changeMyInformation(const UserInformation &me);
    void changeMyStatus(const QString id, const int status);
    void changeFriendRemark(const QString & myID,
                            const QString & friendID,
                            const QString &remark);

    void deleteFriend(const QString & myID, const QString & friendID);
    void addFriend(const TalkMessage & mes);//const TempStrings &);
    void addFlock(const TalkMessage & mes);
    void addDiscussion(const TalkMessage & mes);
    void dropFlock(const QString &, const QString &);
    void dropDiscussion(const QString &, const QString &);
    void leaveFlock(const QString &, const QString &);
    void leaveDiscussion(const QString &, const QString & discussionID);
    void createFlock(const TempStrings & tmpStr);
    void createDiscussion(const TempStrings & tmpStr);

    void changeFlockInformation(const FlockInformation &);
    void changeFlockMemberRemark(const TempStrings & tmpStr);

    void changeDiscussionInformation(const DiscussionInformation &);

    void resultOfFriendRequest(const TalkMessage & mes);
    void resultOfFlockRequest(const TalkMessage & mes);
    void removeBox(const QString &);
    void renameBox(const QString &, const QString &);
    void moveFriendToBox(const QString &, const QString &, const QString &);

    /**************** network ****************/

signals:
    void getFriendsSuccess(const QVector<FriendInformation> &);
    void getFlocksSuccess(const QVector<FlockInformation> &);
    void getDiscussionsSuccess(const QVector<DiscussionInformation> &);
    void getFlockMembersSuccess(const QVector<FlockMember> &);
    void getDiscussionMembersSuccess(const QVector<DiscussionMember> &);

    void getFriendTalkMessage(const TalkMessage &);
    void getFriendChangedStatus(const QString &, const int);
    void getFriendChangedInformation(const FriendInformation &);
    void getFriendInformationSuccess(const UserInformation &);
    void getMyInformationSuccess(const UserInformation &);
    void changeMyInformationSuccess(const UserInformation &);
    void changeFriendRemarkSuccess(const TempStrings &);
    void deleteFriendSuccess(const QString &, const QString &, const QString &);
    void getFriendRequest(const TalkMessage &, const UserInformation &);

    void getFlockRequest(const TalkMessage &, const FlockMember &,
                         const FlockInformation &);
    void dropFlockSuccess(const QString &);
    void leaveFlockSuccess(const QString &, const QString &, const QString &);
    void haveMemberleavedFlock(const QString &, const QString &, const QString &);
    void changeFlockSuccess(const FlockInformation &);
    void changeFlockRemarkSuccess(const TempStrings &);
    void createFlockSuccess(const FlockInformation &);

    void getDiscussionRequest(const TalkMessage &, const DiscussionMember &,
                              const DiscussionInformation &);
    void dropDiscussionSuccess(const QString &);
    void leaveDiscussionSuccess(const QString &, const QString &);//, const QString &);
    void changeDiscussionSuccess(const DiscussionInformation &);
    void createDiscussionSuccess(const DiscussionInformation &);
    void renameBoxSuccess(const QString &, const QString &);
    void moveFriendToBoxSuccess(const QString &, const QString &, const QString);

    void getNetworkHistoryMessagesSuccess(const QString & friendID, const QDate & date,
                                   const QVector<TalkMessage> &);
    void closeWindowSignal();

public slots:
    void requestGetFriendsInformation();
    void requestGetFlocksInformation(const QString &);
    void requestGetDiscussionsInformation(const QString &);
    void requestGetFlockMembers(const QString &);
    void requestGetDiscussionMembers(const QString &);

    void requestGetFriendInformation(const QString &);
    void requestGetMyInformation();
    void requestChangeMyInformation(const UserInformation &);
    void requestChangeMyStatus(const QString id, const int status);
    void requestChangeFriendRemark(const QString & myID,
                                   const QString & friendID,
                                   const QString &remark);
    void requestDeleteFriend(const QString & myID, const QString & friendID);
    void requestAddFriend(const TalkMessage & mes);
    void requestAddFlock(const TalkMessage & mes);
    void requestAddDiscussion(const TalkMessage & mes);
    void requestDropFlock(const QString &, const QString &);
    void requestDropDiscussion(const QString &, const QString &);

    void requestLeaveFlock(const QString &, const QString &);

    void requestLeaveDiscussion(const QString &, const QString &);

    void requestCreateFlock(const TempStrings &);
    void requestCreateDiscussion(const TempStrings &);

    void requestSendResultOfFriendRequest(const TalkMessage & mes);
    void requestSendResultOfFlockRequest(const TalkMessage & mes);

    void requestChangeFlockInformation(const FlockInformation &);
    void requestChangeFlockMemberRemark(const TempStrings & tmpStr);

    void requestChangeDiscussionInformation(const DiscussionInformation &);

    void requestSendTalkMessage();

    void requestRemoveBox(const QString &);
    void requestRenameBox(const QString &, const QString &);
    void requestMoveFriendToBox(const QString & friendID, const QString & oldTitle,
                                const QString & newTitle);

    void requestGetNetWorkHistoryMessageOneFriendOneDate(
            const QString &, const QDate &);

    void requestChangePwd(const QString & oldPwd, const QString & newPwd);

    void readMessage();

    void closeWindow();


private:
    QString m_myID;

    IMTcpSocket *m_tcpSocket;
    quint16 m_blockSize;
    QString m_id;
    int m_status;
    int m_peerStatus;

    QVector<TalkMessage> m_messageVector;

    QVector<TalkMessage> m_HistoryMessageVector;
    QVector<TalkMessage> m_OfflineMessageVector;

    QString m_creatorID;
    QString m_flockID;
    QString m_discussionID;
    FlockMember m_flockMember;
    DiscussionMember m_discussionMember;
    FlockInformation m_flockInf;
    DiscussionInformation m_discussionInf;

    QVector<FriendInformation> m_friendsVec;
    QVector<FlockInformation> m_flocksVec;
    QVector<DiscussionInformation> m_discussionsVec;
    QVector<FlockMember> m_flockMembersVec;
    QVector<DiscussionMember> m_discussionMembersVec;

    TalkMessage m_message;
    QString m_peerID;
    QString m_groupName;
    QString m_friendID;
    UserInformation m_myInf;
    UserInformation m_friInf;
    FriendInformation m_friSimInf;
    TempStrings m_tempStr;

    QString m_title;
    QString m_newTitle;
    QDate m_date;

};

#endif // IMMAINCTRL_H
