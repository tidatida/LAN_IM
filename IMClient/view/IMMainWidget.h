/*********************************************
File Name: IMMainWidget.h
Author: jet.F.R
Date: 2014.3.14
Description: clientmainframe
Changes:
********************************************/

#ifndef IMMAINWIDGET_H
#define IMMAINWIDGET_H

#include <QWidget>
#include <QMap>
#include "model/IMConstant.h"
#include "control/IMDatabaseCtrl.h"
//#include "model/IMEncryption.h"

class IMMainCtrl;
class QListWidget;
class IMChatWidget;
class IMFlockChatWidget;
class IMDiscussionChatWidget;
class QListWidgetItem;
class QGroupBox;
class QVBoxLayout;
class QToolBox;
class IMFriendButton;
class IMFlockButton;
class IMDiscussionButton;
class IMToolBox;
class IMToolItem;
class QFrame;
class QLabel;
class QComboBox;
class QToolButton;
class QLineEdit;
class QTabWidget;
class IMFriendListWidget;
class IMFlockListWidget;
class IMDiscussionListWidget;
class IMLatestMessageListWidget;
class IMInformationWidget;
class IMClickLabel;
class IMFlockInformationWidget;
class IMDiscussionInformationWidget;
class IMMailWidget;
class QMenu;
class IMMessageManageWidget;
class IMLinkButton;
class IMSearchListWidget;

//class QList;

/*************************************************
Class Name: IMMainWidget
Description: clientmainframe
*************************************************/
class IMMainWidget : public QWidget
{
    Q_OBJECT
public:
    IMMainWidget( const UserInformation me, QWidget *parent = 0);
    ~IMMainWidget();

    IMMainCtrl * getMainCtrl() const
    {
        return m_mainCtrl;
    }

    UserInformation getLocalMyInformation() const;

    bool isMyFriend(const QString &id) const;

//    void setNickname(const QString &nickname);
//    void setUserID(const QString &id);
//    void setLoginStatus(const LoginStatus status);

    // 插入好友聊天 room 
    void insertChatRoomMap(const QString &, IMChatWidget *);
    // 插入群聊
    void insertFlockRoomMap(const QString &, IMFlockChatWidget *);
    // 插入 box 聊
    void insertDiscussionRoomMap(const QString &, IMDiscussionChatWidget*);
    //  get 好友信息（发送至server ）
    void getFriendInformation(const QString &id);
    // 改变自己信息（发送至server ）
    void changeMyInformation(const UserInformation &);
    // 改变好友备注（发送至server ）
    void changeFriendRemark(const QString &, const QString &);
    // delete  好友（发送至server ）
    void deleteFriend(const QString &);
    // delete  存储于m_informationMap中,s 信息窗口
    void removeInformationWidget(const QString &);
    // delete  存储 and m_flockInformationMap中,s 信息窗口
    void removeFlockInformationWidget(const QString &);
    // delete  存储 and m_discussionInformationMap中,s 信息窗口
    void removeDiscussionInformationWidget(const QString &);

    // modify群信息（发送至server ）
    void changeFlockInformation(const FlockInformation &);
    // modify讨论 box 信息 （发送至server ）
    void changeDiscussionInformation(const DiscussionInformation &);

    // delete  存储于m_chatRoomMap中,s 聊天窗口
    void removeChatWidget(const QString &);
    // delete  存储于m_flockRoomMap中,s 群聊窗口
    void removeFlockChatWidget(const QString &);
    // delete  存储于m_discussionChatWidget中,s 讨论 box 窗口
    void removeDiscussionChatWidget(const QString &);
    // 解散群 (发送至server )
    void dropFlock(const QString &);
    // 解散讨论 box （发送至server ）
    void dropDiscussion(const QString &);

    // 退出群（发送至server ）
    void leaveFlock(const QString & memberID, const QString &flockID);

    // 退出讨论 box  （发送至server ）
    void leaveDiscussion(const QString & memberID, const QString &discussionID);

    // add 好友（发送至server ）
    void addFriend(const QString friendID);
    // modify群成员 name 片（发送至server ）
    void changeFlockMemberRemark(const TempStrings & tmpStr);

    //  move 好友至 other  box 
    void moveFriendToBox(const QString & friendID, const QString & groupName, const QString &title);

    // 设置在线人数
    void setOnlineCounter(int num);


    //  get  all  box 
    QStringList getGroupList() const
    {
        return m_friendsGroupList;
    }

    //  get  all  box 
    QStringList getGroupFriendList(const QString & groupName);

    /*********************local database *******************/
    //  get 本地某日某好友,s 消息记录
    void getLocalHistoryMessage(const int index, const QDate &date);

    // 导出单个好友消息记录
    void exportLocalMessage(const int index);
    // 导出 all 消息记录
    void exportLocalMessageAll();
    // delete  单个好友消息记录
    void deleteLocalMessage(const int index);
    // delete   all 消息记录
    void deleteLocalMessageAll();

    /*********************network database *******************/
    //  get 网络某日某好友,s 消息记录
    void getNetWorkHistoryMessage(const int index, const QDate &date);

//    // 导出单个好友消息记录
//    void exportNetWorkMessage(const int index);
//    // 导出 all 消息记录
//    void exportNetWorkMessageAll();
//    // delete  单个好友消息记录
//    void deleteNetWorkMessage(const int index);
//    // delete   all 消息记录
//    void deleteNetWorkMessageAll();

signals:
    void exportHistoryMessageOneFriendSuccess(const QString &, const QString &,
                                              const QString &);
    void exportHistoryMessageAllSuccess(const QString &, const QString &);
public slots:

    //  get 好友信息列 table （发送至server ）
    void getFriendsInformation();
    //  get 群信息列 table （发送至server ）
    void getFlocksInformation();
    //  get 讨论 box 信息列 table （发送至.server ）
    void getDiscussionsInformation();
    //  get 本地最近消息（访问本地database ）
    void getLatestMessage();

    // 设置消息界面
    void setNetworkMessageWidget(const QString & friendID, const QDate & date,
                                 const QVector<TalkMessage> & mesVec);

    // 设置好友列 table 
    void setFriendListWidget(const QVector<FriendInformation> &);
    // 设置群列 table 
    void setFlockListWidget(const QVector<FlockInformation> &);
    // 设置讨论 box 列 table 
    void setDiscussionListWidget(const QVector<DiscussionInformation> &);

    // add 好友 button 
    bool addFriendButton(const FriendInformation &);
    // add 群 button 
    bool addFlockButton(const FlockInformation & flcokInfo);
    // add 讨论 box  button 
    bool addDiscussionButton(const DiscussionInformation & disInfo);

    //  get 好友发来,s 消息
    void receiveFriendTalkMessage(const TalkMessage &);
    // 设置好友状态
    void setFriendStatus(const QString &, int);
    // 设置好友信息
    void setFriendInformation(const FriendInformation &);
    // 显示好友信息
    void showFriendInformation(const UserInformation &);
    // 显示自己,s 信息
    void showMyInformation(const UserInformation &);
    // 设置个人信息
    void setMyInformation(const UserInformation &);

    // 显示群信息
    void showFlockInformation(const FlockInformation &);
    // 显示讨论 box 信息
    void showDiscussionInformation(const DiscussionInformation &);

    // 设置群信息
    void setFlockInformation(const FlockInformation &);
    // 设置讨论 box 信息
    void setDiscussionInformation(const DiscussionInformation &);

    // 设置群成员 name 片
    void setFlockMemberRemark(const TempStrings &);

    // 设置好友备注
    void setFriendRemark(const TempStrings&);
    //  already delete  好友
    void deletedFriend(const QString &, const QString &, const QString &);

    //  already delete  群
    void dropedFlock(const QString &);
    //  already delete  讨论 box 
    void dropedDiscussion(const QString & discussionID);

    //  already 退出群
    void leavedFlock(const QString &, const QString &, const QString &);
    //  already 退出讨论 box 
    void leavedDiscussion(const QString &, const QString &);

    // create 群成功
    void createFlockSuccess(const FlockInformation &);
    // create 讨论 box 成功
    void createDiscussionSuccess(const DiscussionInformation &);

    // 搜索友好
    void searchFriend(const QString & text);
    //   click “搜索” button 
    void onClickSearchFriend();

    //  click “add 好友” button 
    void onClickAddFriend();
    // add 群
    void onClickAddFlock();
    // modify passwd
    void onClickChangePwd();
    // create 群
    void createFlock();
    // create 讨论 box 
    void createDiscussion();
    // add 讨论 box 
//    void addDiscussion();

    // 显示消息管理窗口
    void showMessageWidget();
    // 显示邮箱
    void showMailWidget();
    // 显示邮箱 write mail 窗口
    void showMailWriteWidget(const QString & address);
    // 显示最 new 消息窗口
    void showLatestMessageWidget();
    // 设置显示 Got  new 消息,s  timer 器
    void setTimerStatus(bool isOpen);

    // rename group成功
    void renameBoxSuccess(const QString & title, const QString & newTitle);
    //  move 好友至 other  box 
    void moveFriendToBoxSuccess(const QString &, const QString &, const QString &);

    void onClickRightButton();
    // create  box 
    void createBox();

    /*****************link button*****************************/
    // delete   new 消息connection  button 
    void removeLinkButton(const QString & id);
    // delete   all 消息connection  button 
    void removeAllLinkButton();
    // 显示 all 聊天窗口
    void showAllChatRoom();

protected:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *);

private slots:

    // close  main 窗口
    void closeWindow();
    // close  all  other ,s 窗口
    void closeAllWindows();

    //  get 自己信息（发送至server ）
    void getMyInformation();

    //void createChatRoom(QListWidgetItem *);

    //  get 好友聊天 room  send ,s 消息
    void receiveMessagesFromChat(TalkMessage &);
    //  get 群 send ,s 消息
    // void receiveMessagesFromFlockChat(TalkMessage &);
    //  get 讨论 box  send ,s 消息
    // void receiveMessagesFromDiscussionChat(TalkMessage &);


    // 改变个人状态（发送至server ）
    void changeMyStatus(const int index);

    // 接收并and  process   好友,s request 
    void receiveFriendRequest(const TalkMessage &, const UserInformation &);

    // 接收并and  process   群,s request 
    void receiveFlockRequest(const TalkMessage &,
                             const FlockMember &,
                             const FlockInformation &);
    // 接收并process   讨论 box request 
    void receiveDiscussionRequest(const TalkMessage & mes,
                                  const DiscussionMember & member,
                                  const DiscussionInformation & discussion);

    // delete   box 
    void removeBox(const QString &);
    // rename group
    void renameBox(const QString &);


private:
    void initIMMainWidget();
    void linkSignalWithSlot();
    void clearContainers();
    void creatMenu();
    void refreshFriendButtonMenu();
    //询问user 是否真,s 要退出
    bool continueToClose();
private:
    IMMainCtrl *m_mainCtrl;
    int m_onlineCounter;
    //IMUser *m_myself;
    UserInformation m_myself;

//    QListWidget * m_friendsList;

    //IMChatWidget *m_chatRoom;
    QMap<QString,IMChatWidget *> m_chatRoomMap; // 好友ID  and  聊天 room   map  table 
    QMap<QString,IMFlockChatWidget *> m_flockRoomMap; // 群ID  and  群聊  map  table 
    QMap<QString,IMDiscussionChatWidget *> m_discussionRoomMap; // 讨论 box ID  and  讨论 room   map  table 

    QMap<QString, IMInformationWidget *> m_informationMap;
    QMap<QString, IMFlockInformationWidget *> m_flockInformationMap;
    QMap<QString, IMDiscussionInformationWidget *> m_discussionInformationMap;

    QStringList m_friendsGroupList;  //  box  name  列 table 
    QStringList m_friendsMarkList; // 某 box 中好友 备注 name  列 table 
    QStringList m_friendsIDList; // 某 box 中好友 ID  列 table 

    QVector<IMToolItem *> m_toolItemsFriendsVec;  // 存储 each  box ,s  array 

    QMap<QString, int> m_indexFriendsGroupMap; //  box  name   and   subscribe index   map  table 

    QMap<QString, IMFriendButton *> m_friendMap; // 好友帐 number   and  好友 button   map  table 

    QMap<QString, IMFlockButton *> m_flockMap; // 群ID  and  群 button   map  table 

    QMap<QString, IMDiscussionButton *> m_discussionMap; // 讨论 box ID  and  讨论 box  button   map  table 

    QMap<QString, IMLinkButton*> m_linkMap; //ID 链接 button   map  table 


//    QFrame *m_frameHead;
    IMClickLabel *m_labelHead;
    QLabel *m_labelNickname;
    QComboBox *m_cbStatus;
    QLabel *m_labelMark;
    QToolButton *m_toolBtnSpace;
    QToolButton *m_toolBtnMail;
    QToolButton *m_toolBtnMesBox;
    QToolButton *m_toolBtnNewMes;

    QLineEdit *m_leSearch;
    QToolButton *m_toolBtnSearch;
//    QLabel *m_labelSearch;

    QLabel *m_labelOnlineNum;
    QToolButton *m_toolBtnAddFlock;
//    QToolButton *m_toolBtnAddDiscussion;
    QToolButton *m_toolBtnAddFriend;
//    QToolButton *m_toolBtnSearchAdd;
    QToolButton *m_toolBtnConfig;

    QTabWidget *m_tabWidget;
    IMFriendListWidget *m_friendListWidget;
    IMFlockListWidget *m_flockListWidget;
    IMDiscussionListWidget *m_discussionListWidget;
    IMLatestMessageListWidget *m_messageListWidget;
    IMSearchListWidget *m_searchListWidget;
    int m_timerId; //ID of timer


    IMMailWidget *m_mailWidget;
    IMMessageManageWidget *m_messageManWidget;
    QMenu *m_menu;

    int m_flag;

    // access database
    IMDatabaseCtrl m_database;
    QVector<TalkMessage> m_localHistoryMessageVec;
    QVector<TalkMessage> m_networkHistoryMessageVec;
//    QMap<QString, QVector<TalkMessage> > m_local
};

#endif // IMMAINWIDGET_H
