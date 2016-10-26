/*********************************************
File Name: IMDatabaseCtrl.h
Author: jet.F.R
Date: 2014.3.12
Description: access database
Changes:
********************************************/
#ifndef IMDATABASECTRL_H
#define IMDATABASECTRL_H

#include <QObject>
#include <QMap>
#include "model/IMConstant.h"

class QSqlQuery;
class QSqlDatabase;
class IMUser;
class QDateTime;


/*************************************************
Class Name: IMDatabaseCtrl
Description: database operation class
*************************************************/
class IMDatabaseCtrl : public QObject
{
    Q_OBJECT
public:
    IMDatabaseCtrl(QObject *parent = 0);

    ~IMDatabaseCtrl();

    // create connection 
    bool createConnection();
    // init database  set all user 's statusstatusset to OFFLINE
    bool initDatabase();
    // close database 
    void close();
    // open database 
    bool isOpen();

    // modify passwd
    int updatePassword(TempStrings & tmp);
    // query passwd-protect questionand answer 
    int searchQuestionAndAnswer(const QString &id, TempStrings & tmp);
    // query user 
    int searchUserInUserInformation(const LoginInformation &logInf,
                                       UserInformation &userInf);

    //  through idquery 好友简易信息
    int searchFriendSimpleInformationByID(const QString &id,
                                          FriendInformation &friInf);

    //  through idquery 好友信息
    int searchFriendInformationByID(const QString &id, UserInformation &userInf);
    //  through idquery 自己信息
    int searchMyselfInformationByID(const QString &id, UserInformation &userInf);
    // modifyuser 信息
    int updateMyselfInformation(const UserInformation &user);
    // add user 
    int addUserInUserInformation(const UserInformation &userInf);

    //  get 一段时间Register 数量
    int countRegisteredInPeriod(const QDateTime &datePre,
                                 const QDateTime &dateLater);
    //  get 一段时间群add 数量
    int countFlockInPeriod(const QDateTime &datePre,
                                 const QDateTime &dateLater);
    //  get  all 好友信息
    int searchFriendsInformation(const QString &id,
                                  QVector<FriendInformation> &friendsVec);
    //  get  all 好友ID
    bool searchFriendsID(const QString &id, QVector<QString> &IDVec);
    // 更 new 好友状态
    bool updateStatus(int status, const QString & id);
    // 更 new 好友备注
    int updateRemark(const TempStrings & tempStr);
    // delete  好友
    int deleteFriend(const QString & myID, const QString & friendID,
                       QString & groupName, QString & groupNameF);
    // add 好友
    bool addFriend(const TalkMessage & mes);

    //  get 某user 加入,s  all 群
    int searchFlocksInformation(const QString &, QVector<FlockInformation> &);
    //  get 某个群信息
    bool searchFlockInformation(const QString &, FlockInformation &);
    //  get 某群中 all ,s 成员
    int searchFlockMembers(const QString &, QVector<FlockMember> &);
    //  get 某群,s 某个成员
    bool searchFlockMember(const QString &, const QString &, FlockMember & flockMember);


    //  get  all user 加入,s 讨论 box 
    int searchDiscussionsInformation(const QString &,
                                       QVector<DiscussionInformation> &);
    //  get 某个讨论 box 信息
    bool searchDiscussionInformation(const QString &, DiscussionInformation &);
    //  get 某讨论 box 中 all ,s 成员
    int searchDiscussionMembers(const QString &, QVector<DiscussionMember> &);
    //  get 某讨论 box 中,s 某个成员
    bool searchDiscussionMember(const QString & discussionID,
                               const QString & userID,
                               DiscussionMember & discussionMember);


    //  get 群 main  account  
    bool searchFlockHost(const QString & flockID, QString & hostID);
    // add 群成员
    bool addFlockMember(const QString & flockID, const QString & memberID,
                        const int status = FLOCK_MEMBER);
    //  get  box 长 account  
    bool searchDiscussionHost(const QString & discussionID, QString & hostID);
    // add 讨论 box 成员
    bool addDiscussionMember(const QString & discussionID, const QString & memberID,
                            const int status = DISCUSSION_MEMBER);
    // add 群
    int addFlock(const TempStrings &, QString & flockID);
    // add 讨论 box 
    int addDiscussion(const TempStrings &, QString & discussionID);
    // delete  群
    int deleteFlock(const QString userID, const QString &flockID);
    // delete  讨论 box 
    int deleteDiscussion(const QString userID, const QString &discussionID);
    // delete  群成员
    int deleteFlockMember(const QString & flockID, const QString & memberID);
    // delete  讨论 box 成员
    int deleteDiscussionMember(const QString & discussionID, const QString & memberID);

    // 更 new 群信息
    int updateFlockInformation(const FlockInformation & flock);
    // 更 new 讨论 box 信息
    int updateDiscussionInformation(const DiscussionInformation & discussion);

    // 更 new 群成员 name 片
    int updateFlockMemberRemark(const TempStrings & tmpStr);

    // 更 new 讨论 box 成员 name 片---暂时没用
    // int updateDiscussionMemberRemark(const TempStrings & tmpStr);

    // 检测user ---暂时没用
    // int checkUser(const LoginInformation &logInf);

    //插入DateCounterb table 某日,s 数据项
    bool insertValuesInDateCounter(const QDate &);
    //  get 某日user Register 数量+1
    int getUserTimes(const QDate &);
    //  get 某日 create 群数量+1
    int getFlockTimes(const QDate &);
    //  get 某日 create 讨论 box 数量+1
    int getDiscussionTimes(const QDate &);

    // 增加某日user Register 数量
    bool increaseUserTimes(const QDate &);
    // 增加某日 create 群数量
    bool increaseFlockTimes(const QDate &);
    // 增加某日 create 讨论 box 数量
    bool increaseDiscussionTimes(const QDate &);

    /***********邮件模块*********************/
    //  get 收件箱
    int searchInMails(const QString & id, QVector<MailInformation> & mailsVec);
    //  get 发件箱
    int searchOutMails(const QString & id, QVector<MailInformation> & mailsVec);
    // delete  邮件
    bool deleteMail(const QString & receiverID, const int mailID);
    // delete  收件箱邮件
    int deleteInMail(const QString & receiverID, const int mailID);
    // delete  收件箱邮件
    int deleteOutMail(const QString & senderID, const int mailID);
    // 插入 new 邮件
    int insertMail(MailInformation &);
    // 更 new 邮件，set to  already 读
    bool setMailRead(const QString & receiverID, const int mailID);

    /*************好友 box ********************/
//    // delete   box 
//    int deleteGroup(const QString & id, const QString & title);
//    // create  box 
//    int createGroup(const QString & id, const QString & title);

    //  move 好友至 other  box 
    int moveFriendToGroup(const QString & myID, const QString & friendID,
                          const QString & title, const QString & newTitle);
    // rename group
    int renameGroup(const QString & id, const QString & title,
                    const QString & newTitle);

    /************消息管理*********************/
    // 存储历史记录
    bool addHistoryMessage(const TalkMessage &);
    // 存储 offline 记录
    bool addOfflineMessage(const TalkMessage &);
    //  get user ,s 某日 and 某位好友,s 聊天记录
    int searchHistoryMessageOneFriendOneDate(const QString & myID,
                                             const QString &friendID,
                                             const QDate & date,
                                             QVector<TalkMessage> & mesVec);

signals:

public slots:

private:
    //检查SQL语句,s 正确性
    void errorSQLOrder(QSqlQuery query, QString mark);
    //create database  table 格
    void createTable();

private:
    QSqlDatabase *m_db;
};

#endif // IMDATABASECTRL_H
