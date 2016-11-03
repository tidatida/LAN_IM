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

    void insertChatRoomMap(const QString &, IMChatWidget *);
    void insertFlockRoomMap(const QString &, IMFlockChatWidget *);
    void insertDiscussionRoomMap(const QString &, IMDiscussionChatWidget*);
    void getFriendInformation(const QString &id);
    void changeMyInformation(const UserInformation &);
    void changeFriendRemark(const QString &, const QString &);
    void deleteFriend(const QString &);
    void removeInformationWidget(const QString &);
    void removeFlockInformationWidget(const QString &);
    void removeDiscussionInformationWidget(const QString &);

    void changeFlockInformation(const FlockInformation &);
    void changeDiscussionInformation(const DiscussionInformation &);

    void removeChatWidget(const QString &);
    void removeFlockChatWidget(const QString &);
    void removeDiscussionChatWidget(const QString &);
    void dropFlock(const QString &);
    void dropDiscussion(const QString &);

    void leaveFlock(const QString & memberID, const QString &flockID);
    void leaveDiscussion(const QString & memberID, const QString &discussionID);

    void addFriend(const QString friendID);
    void changeFlockMemberRemark(const TempStrings & tmpStr);

    void moveFriendToBox(const QString & friendID, const QString & groupName, const QString &title);
    void setOnlineCounter(int num);


    //  get  all  box 
    QStringList getGroupList() const
    {
        return m_friendsGroupList;
    }

    //  get  all  box 
    QStringList getGroupFriendList(const QString & groupName);

    /*********************local database *******************/
    void getLocalHistoryMessage(const int index, const QDate &date);

    void exportLocalMessage(const int index);
    void exportLocalMessageAll();
    void deleteLocalMessage(const int index);
    void deleteLocalMessageAll();

    /*********************network database *******************/
    void getNetWorkHistoryMessage(const int index, const QDate &date);

signals:
    void exportHistoryMessageOneFriendSuccess(const QString &, const QString &,
                                              const QString &);
    void exportHistoryMessageAllSuccess(const QString &, const QString &);
public slots:

    void getFriendsInformation();
    void getFlocksInformation();
    void getDiscussionsInformation();
    void getLatestMessage();

    void setNetworkMessageWidget(const QString & friendID, const QDate & date,
                                 const QVector<TalkMessage> & mesVec);

    void setFriendListWidget(const QVector<FriendInformation> &);
    void setFlockListWidget(const QVector<FlockInformation> &);
    void setDiscussionListWidget(const QVector<DiscussionInformation> &);

    bool addFriendButton(const FriendInformation &);
    bool addFlockButton(const FlockInformation & flcokInfo);
    bool addDiscussionButton(const DiscussionInformation & disInfo);

    void receiveFriendTalkMessage(const TalkMessage &);
    void setFriendStatus(const QString &, int);
    void setFriendInformation(const FriendInformation &);
    void showFriendInformation(const UserInformation &);
    void showMyInformation(const UserInformation &);
    void setMyInformation(const UserInformation &);

    void showFlockInformation(const FlockInformation &);
    void showDiscussionInformation(const DiscussionInformation &);

    void setFlockInformation(const FlockInformation &);
    void setDiscussionInformation(const DiscussionInformation &);

    void setFlockMemberRemark(const TempStrings &);

    void setFriendRemark(const TempStrings&);
    void deletedFriend(const QString &, const QString &, const QString &);
    void dropedFlock(const QString &);
    void dropedDiscussion(const QString & discussionID);

    void leavedFlock(const QString &, const QString &, const QString &);
    void leavedDiscussion(const QString &, const QString &);

    void createFlockSuccess(const FlockInformation &);
    void createDiscussionSuccess(const DiscussionInformation &);

    void searchFriend(const QString & text);
    void onClickSearchFriend();

    void onClickAddFriend();
    void onClickAddFlock();
    void onClickChangePwd();
    void createFlock();
    void createDiscussion();

    void showMessageWidget();
    void showMailWidget();
    void showMailWriteWidget(const QString & address);
    void showLatestMessageWidget();
    void setTimerStatus(bool isOpen);

    void renameBoxSuccess(const QString & title, const QString & newTitle);
    void moveFriendToBoxSuccess(const QString &, const QString &, const QString &);

    void onClickRightButton();
    void createBox();

    /*****************link button*****************************/
    void removeLinkButton(const QString & id);
    void removeAllLinkButton();
    void showAllChatRoom();

protected:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *);

private slots:

    void closeWindow();
    void closeAllWindows();

    void getMyInformation();

    //void createChatRoom(QListWidgetItem *);

    void receiveMessagesFromChat(TalkMessage &);
    void changeMyStatus(const int index);

    void receiveFriendRequest(const TalkMessage &, const UserInformation &);
    void receiveFlockRequest(const TalkMessage &,
                             const FlockMember &,
                             const FlockInformation &);
    void receiveDiscussionRequest(const TalkMessage & mes,
                                  const DiscussionMember & member,
                                  const DiscussionInformation & discussion);

    void removeBox(const QString &);
    void renameBox(const QString &);


private:
    void initIMMainWidget();
    void linkSignalWithSlot();
    void clearContainers();
    void creatMenu();
    void refreshFriendButtonMenu();
    bool continueToClose();

private:
    IMMainCtrl *m_mainCtrl;
    int m_onlineCounter;
    UserInformation m_myself;

    QMap<QString,IMChatWidget *> m_chatRoomMap;
    QMap<QString,IMFlockChatWidget *> m_flockRoomMap;
    QMap<QString,IMDiscussionChatWidget *> m_discussionRoomMap;

    QMap<QString, IMInformationWidget *> m_informationMap;
    QMap<QString, IMFlockInformationWidget *> m_flockInformationMap;
    QMap<QString, IMDiscussionInformationWidget *> m_discussionInformationMap;

    QStringList m_friendsGroupList;
    QStringList m_friendsMarkList;  
    QStringList m_friendsIDList;  

    QVector<IMToolItem *> m_toolItemsFriendsVec;
    QMap<QString, int> m_indexFriendsGroupMap; 
    QMap<QString, IMFriendButton *> m_friendMap; 
    QMap<QString, IMFlockButton *> m_flockMap; 
    QMap<QString, IMDiscussionButton *> m_discussionMap; 
    QMap<QString, IMLinkButton*> m_linkMap;  


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
};

#endif // IMMAINWIDGET_H
