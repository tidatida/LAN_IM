/*********************************************
File Name:IMMainWidget.cpp
Author:jet.F.R
Date:2014.3.10
<<<<<<< HEAD
Description:clientmainframe
=======
Description:main frame of client
>>>>>>> 20a9555c1984893a09c6f694bdca5c9b4687c5b8
Changes:
********************************************/

#include "IMMainWidget.h"
#include <QLabel>
#include <qdebug.h>
#include <QListWidget>
#include <QHBoxLayout>
#include <QToolBox>
#include <QGroupBox>
#include <QComboBox>
#include <QFrame>
#include <QLabel>
#include <QToolButton>
#include <QLineEdit>
#include <QMap>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QMenu>
#include <QMouseEvent>
#include <QDir>
#include <QFile>
#include <QTime>
#include <QTimerEvent>

#include "IMFriendListWidget.h"
#include "IMFlockListWidget.h"
#include "IMDiscussionListWidget.h"
#include "IMLatestMessageListWidget.h"
#include "IMToolBox.h"
#include "control/IMMainCtrl.h"
#include "model/IMUser.h"
#include "view/IMChatWidget.h"
#include "view/IMFriendButton.h"
#include "view/IMFlockButton.h"
#include "view/IMDiscussionButton.h"
#include "view/IMInformationWidget.h"
#include "view/IMClickLabel.h"
#include "view/IMFlockChatWidget.h"
#include "view/IMFlockInformationWidget.h"
#include "view/IMDiscussionChatWidget.h"
#include "view/IMDiscussionInformationWidget.h"
#include "view/IMMailWidget.h"
#include "view/IMMessageManageWidget.h"
#include "view/IMLinkButton.h"
#include "view/IMLinkFriendButton.h"
#include "view/IMLinkFlockButton.h"
#include "view/IMLinkDiscussionButton.h"
#include "view/IMSearchListWidget.h"
#include "model/IMEncryption.h"
//#include <iostream>
//using namespace std;

static const QString TMP_LOCAL_HISTORY_PARH = "/tmp/local_history_message";
// mark public:--------------------------------------------------------------


// file copy:
bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

IMMainWidget::IMMainWidget(const UserInformation me, QWidget *parent) :
    QWidget(parent), m_database(me.m_userID)
{
    m_flag = 0;
    m_timerId = 0;
    m_myself = me;
    m_onlineCounter = 0;
    m_mailWidget = NULL;
    m_messageManWidget = NULL;
    initIMMainWidget();
    linkSignalWithSlot();
    creatMenu();
    setWindowTitle(tr("IM"));
}

IMMainWidget::~IMMainWidget()
{
    // close timer
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = 0;
    }

    if (m_database.isOpen())
    {
        m_database.close();
    }
    if (m_mailWidget != NULL)
    {
        m_mailWidget->close();
        delete m_mailWidget;
        m_mailWidget = 0;
    }
    if (m_messageManWidget != NULL)
    {
        m_messageManWidget->close();
        delete m_messageManWidget;
        m_messageManWidget = 0;
    }
    // clear containers
    clearContainers();
    qDeleteAll(m_chatRoomMap.begin(), m_chatRoomMap.end());
    m_chatRoomMap.clear();

    qDeleteAll(m_flockRoomMap.begin(), m_flockRoomMap.end());
    m_flockRoomMap.clear();

    qDeleteAll(m_discussionRoomMap.begin(), m_discussionRoomMap.end());
    m_discussionRoomMap.clear();

    qDeleteAll(m_informationMap.begin(), m_informationMap.end());
    m_informationMap.clear();

    qDeleteAll(m_flockInformationMap.begin(), m_flockInformationMap.end());
    m_flockInformationMap.clear();

    qDeleteAll(m_discussionInformationMap.begin(), m_discussionInformationMap.end());
    m_discussionInformationMap.clear();
}

/*************************************************
Function Name:getLocalMyInformation()
Description:
*************************************************/
UserInformation IMMainWidget::getLocalMyInformation() const
{
    return m_myself;
}

/*************************************************
Function Name:isMyFriend()
Description:
*************************************************/
bool IMMainWidget::isMyFriend(const QString & id) const
{
    if (m_friendMap.contains(id))
        return true;
    return false;
}


/*************************************************
Function Name:setNickname()
Description:
Input:const QString &nickname:
Output:NULL
Changes:NULL
*************************************************/
//void IMMainWidget::setNickname(const QString &nickname)
//{
//    m_myself->setNickname(nickname);
//}

/*************************************************
Function Name:setUserID()
Description: set id
*************************************************/
//void IMMainWidget::setUserID(const QString &id)
//{
//    m_myself->setUserID(id);

//    m_mainCtrl->getFriendsInfo(m_myself->getUserID());
//}

/*************************************************
Function Name:setLoginStatus()
Description: set
Input:const QString &nickname:    nickname
Output:NULL
Changes:NULL
*************************************************/
//void IMMainWidget::setLoginStatus(const LoginStatus status)
//{
//    m_myself->setStatus(status);
//}



/*************************************************
Function Name:insertChatRoomMap()
Description:
*************************************************/
void IMMainWidget::insertChatRoomMap(const QString &id, IMChatWidget *chatRoom)
{
    m_chatRoomMap.insert(id, chatRoom);
}

/*************************************************
Function Name:insertFlockRoomMap()
Description:
*************************************************/
void IMMainWidget::insertFlockRoomMap(const QString & id,
                                      IMFlockChatWidget *chatRoom)
{
    m_flockRoomMap.insert(id, chatRoom);
}


/*************************************************
Function Name:insertDiscussionRoomMap()
Description:
*************************************************/
void IMMainWidget::insertDiscussionRoomMap(const QString & id,
                                           IMDiscussionChatWidget *chatRoom)
{
    m_discussionRoomMap.insert(id, chatRoom);
}


/*************************************************
Function Name:getFriendInformation
Description:
*************************************************/
void IMMainWidget::getFriendInformation(const QString &id)
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->getFriendInformation(id);
}

/*************************************************
Function Name:changeMyInformation
Description:
*************************************************/
void IMMainWidget::changeMyInformation(const UserInformation &me)
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->changeMyInformation(me);
}


/*************************************************
Function Name:changeFriendRemark
Description:
*************************************************/
void IMMainWidget::changeFriendRemark(const QString & friendID,
                                      const QString & remark)
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->changeFriendRemark(m_myself.m_userID, friendID, remark);
}

/*************************************************
Function Name:deleteFriend
Description:
*************************************************/
void IMMainWidget::deleteFriend(const QString & friendID)
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->deleteFriend(m_myself.m_userID, friendID);
}

/*************************************************
Function Name:removeInformationWidget
Description:
*************************************************/
void IMMainWidget::removeInformationWidget(const QString & userID)
{
    // mark
    m_informationMap[userID]->deleteLater();
    m_informationMap.remove(userID);
}

/*************************************************
Function Name:removeFlockInformationWidget
Description:
*************************************************/
void IMMainWidget::removeFlockInformationWidget(const QString & flockID)
{
    // mark
    m_flockInformationMap[flockID]->deleteLater();
    m_flockInformationMap.remove(flockID);
}

/*************************************************
Function Name:removeDiscussionInformationWidget
Description:
*************************************************/
void IMMainWidget::removeDiscussionInformationWidget(const QString & discussionID)
{
    // mark
    m_discussionInformationMap[discussionID]->deleteLater();
    m_discussionInformationMap.remove(discussionID);
}

/*************************************************
Function Name:changeFlockInformation
Description:
*************************************************/
void IMMainWidget::changeFlockInformation(const FlockInformation & flock)
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->changeFlockInformation(flock);
}


/*************************************************
Function Name:changeDiscussionInformation
Description:
*************************************************/
void IMMainWidget::changeDiscussionInformation(const DiscussionInformation & discussion)
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->changeDiscussionInformation(discussion);
}

/*************************************************
Function Name:removeChatWidget
Description:
*************************************************/
void IMMainWidget::removeChatWidget(const QString &friendID)
{
    // mark
    m_chatRoomMap[friendID]->deleteLater();
    m_chatRoomMap.remove(friendID);
}

/*************************************************
Function Name:removeFlockChatWidget
Description:
*************************************************/
void IMMainWidget::removeFlockChatWidget(const QString & flockID)
{
    // mark
    qDebug() << "size-font:" << m_flockRoomMap.size();
    m_flockRoomMap[flockID]->deleteLater();
    m_flockRoomMap.remove(flockID);
    qDebug() << "size-behind:" << m_flockRoomMap.size();
}

/*************************************************
Function Name:removeDiscussionChatWidget
Description:
*************************************************/
void IMMainWidget::removeDiscussionChatWidget(const QString & discussionID)
{
    // mark
    m_discussionRoomMap[discussionID]->deleteLater();
    m_discussionRoomMap.remove(discussionID);
}

/*************************************************
Function Name:dropFlock
Description:
*************************************************/
void IMMainWidget::dropFlock(const QString & flockID)
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->dropFlock(m_myself.m_userID, flockID);
}

/*************************************************
Function Name:dropDiscussion
Description:
*************************************************/
void IMMainWidget::dropDiscussion(const QString & discussionID)
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->dropDiscussion(m_myself.m_userID, discussionID);
}

/*************************************************
Function Name:leaveFlock
Description:
*************************************************/
void IMMainWidget::leaveFlock(const QString &memberID, const QString & flockID)
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->leaveFlock(memberID, flockID);
}

/*************************************************
Function Name:leaveFlock
Description:
*************************************************/
void IMMainWidget::leaveDiscussion(const QString & memberID, const QString & discussionID)
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->leaveDiscussion(memberID, discussionID);
}
/*************************************************
Function Name:leaveFlock
Description:
*************************************************/
void IMMainWidget::addFriend(const QString friendID)
{
    if (0 == friendID.compare(m_myself.m_userID))
    {
        QMessageBox::critical(NULL, tr("add failed"), tr("can not add self"));
        return;
    }
    if (m_friendMap.contains(friendID))
    {
        QMessageBox::critical(NULL, tr("add failed"), tr("this is already friend"));
        return;
    }

    bool isOkMes = false;
    QString checkMes = QInputDialog::getText(NULL, "add friend",
                                             "please input verify info",
                                             QLineEdit::Normal,
                                             QString(tr("hello,I am: %1")).
                                             arg(m_myself.m_nickname),
                                             &isOkMes);
    if (!isOkMes)
        return;

    //    TempStrings temp;
    //    temp.m_one = m_myself.m_userID;
    //    temp.m_two = friendID;
    //    temp.m_three = checkMes;

    TalkMessage mes;
    mes.m_senderID = m_myself.m_userID;
    mes.m_receiverID = friendID;
    mes.m_text = checkMes;
    mes.m_type = REQUEST_FRIEND;

    if (NULL != m_mainCtrl)
        m_mainCtrl->addFriend(mes);
}


/*************************************************
Function Name:changeFlockMemberRemark
Description:
*************************************************/
void IMMainWidget::changeFlockMemberRemark(const TempStrings & tmpStr)
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->changeFlockMemberRemark(tmpStr);
}

void IMMainWidget::moveFriendToBox(const QString & friendID,
                                   const QString & groupName,
                                   const QString & title)
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->moveFriendToBox(friendID, groupName, title);
}

/*************************************************
Function Name:setOnlineCounter
Description:
*************************************************/
void IMMainWidget::setOnlineCounter(int num)
{
    m_onlineCounter = num;
    m_labelOnlineNum->setText(QString(tr("online number: %1"))
                              .arg(QString::number(num)));

}


QStringList IMMainWidget::getGroupFriendList(const QString & groupName)
{
    m_friendsMarkList.clear();
    m_friendsIDList.clear();
    if (!m_indexFriendsGroupMap.contains(groupName))
    {
        return m_friendsMarkList;
    }

    int groupIndex = m_indexFriendsGroupMap[groupName];
    IMToolItem * group = m_toolItemsFriendsVec[groupIndex];
    const QList<QWidget *>* friendList = group->getWidgetList();

    QString mark;
    FriendInformation friendInfor;

    for (int i=0; i<friendList->size(); i++)
    {
        IMFriendButton *friendBtn = (IMFriendButton *)friendList->value(i);
        friendInfor = friendBtn->getInformation();

        if(friendInfor.m_remarkName.isEmpty())
            mark = friendInfor.m_nickname;
        else
            mark = friendInfor.m_remarkName;
        m_friendsMarkList.append(mark);
        m_friendsIDList.append(friendInfor.m_userID);
    }
    return m_friendsMarkList;
}


/*************************************************
Function Name:getLocalHistoryMessage()
Description:
*************************************************/
void IMMainWidget::getLocalHistoryMessage(const int index, const QDate & date)
{
    m_localHistoryMessageVec.clear();
    if (index < 0 || index >= m_friendsIDList.size())
        return;
    bool isOk = m_database.searchHistoryMessage(m_myself.m_userID,
                                                m_friendsIDList[index],
                                                date,
                                                m_localHistoryMessageVec);
    qDebug() << "m_localHistoryMessageVec:" << isOk << m_localHistoryMessageVec.size();
    m_messageManWidget->setLocalMessageWidget(m_localHistoryMessageVec);
}


/*************************************************
Function Name:exportLocalMessage()
Description:
*************************************************/
void IMMainWidget::exportLocalMessage(const int index)
{
    QString csv = tr("CSV  file  (*.csv)");
    QString excel = tr("EXCEL  file  (*.xls)");
    QString txt = tr("TXT (*.txt)");
    QString history = "resource/history";
    qDebug() << "export: id: " << index << m_friendsIDList.size();
    QString id = m_friendsIDList[index];
    QString selFilter="All files (*.*)";
    QDir dir = QDir::current();
    if (!dir.exists(history))
        dir.mkpath(history);
    QString path = QString("%1/%2_%3").arg(history, m_myself.m_userID, id);
    QString filter = QString(tr("%1;;%2;;%3").arg(csv, excel, txt));
    QString name = QFileDialog::getSaveFileName(this,tr("  save  file "), path,
                                                filter, &selFilter);
    if(name.isEmpty())
    {
        return;
    }
    qDebug() << "export-path" << name << selFilter;
    if (selFilter == csv)
    {
        if (!name.endsWith(".csv", Qt::CaseInsensitive))
            name.append(".csv");
    }
    else if (selFilter == excel)
    {
        if (!name.endsWith(".xls", Qt::CaseInsensitive))
            name.append(".xls");
    }
    else if (selFilter == txt)
    {
        if (!name.endsWith(".txt", Qt::CaseInsensitive))
            name.append(".txt");
    }

    QString tmpPath = TMP_LOCAL_HISTORY_PARH;
    QString newPath = tmpPath;
    static int i = 0;
    while(1)
    {

        QFile file(newPath.append(".csv"));
        if (file.exists())
        {
            newPath = tmpPath.append("_").append(QString::number(++i));
            tmpPath = TMP_LOCAL_HISTORY_PARH;
        }
        else
            break;
    }

    qDebug() << "newpath:" << newPath;

    int type =  m_database.exportHistoryMessageOneFriend(m_myself.m_userID,
                                                         id, newPath);
    QString temp;
    if (type < 0)
    {
        temp = QString(tr("  chat record export failed.！"));

    }
    else if (type == 0)
    {
        temp = QString(tr("  chat recordis empty！"));
    }
    else
    {
        temp = QString(tr("  chat record export success:%1.")).arg(name);
        copyFileToPath(newPath, name, true);
        emit exportHistoryMessageOneFriendSuccess(m_myself.m_userID, id, newPath);
    }

    QMessageBox::information(NULL, tr(" export   chat record"), temp);
    m_messageManWidget->raise();
    //    m_messageManWidget->activateWindow();
    //    m_messageManWidget->show();
}


/*************************************************
Function Name:exportLocalMessageAll()
Description:  export
*************************************************/
void IMMainWidget::exportLocalMessageAll()
{
    QString csv = tr("CSV  file  (*.csv)");
    QString excel = tr("EXCEL  file  (*.xls)");
    QString txt = tr("TXT  file  (*.txt)");
    QString history = "resource/history";
    QString selFilter="All files (*.*)";
    QDir dir = QDir::current();
    if (!dir.exists(history))
        dir.mkpath(history);
    QString path = QString("%1/%2").arg(history, m_myself.m_userID);
    QString filter = QString(tr("%1;;%2;;%3").arg(csv, excel, txt));
    QString name = QFileDialog::getSaveFileName(this,tr("  save  file "), path,
                                                filter, &selFilter);
    if(name.isEmpty())
    {
        return;
    }
    qDebug() << "export-path" << name << selFilter;
    if (selFilter == csv)
    {
        if (!name.endsWith(".csv", Qt::CaseInsensitive))
            name.append(".csv");
    }
    else if (selFilter == excel)
    {
        if (!name.endsWith(".xls", Qt::CaseInsensitive))
            name.append(".xls");
    }
    else if (selFilter == txt)
    {
        if (!name.endsWith(".txt", Qt::CaseInsensitive))
            name.append(".txt");
    }

    //    TMP_LOCAL_HISTORY_PARH.append(QTime::currentTime().toString("hh-mm-ss"));
    QString tmpPath = TMP_LOCAL_HISTORY_PARH;
    QString newPath = tmpPath;
    static int i = 0;
    while(1)
    {

        QFile file(newPath.append(".csv"));
        if (file.exists())
        {
            newPath = tmpPath.append("_").append(QString::number(++i));
            tmpPath = TMP_LOCAL_HISTORY_PARH;
        }
        else
            break;
    }

    qDebug() << "newpath:" << newPath;

    int type =  m_database.exportHistoryMessageAll(m_myself.m_userID, newPath);

    QString temp;
    if (type < 0)
    {
        temp = QString(tr("  chat record export failed.！"));

    }
    else if (type == 0)
    {
        temp = QString(tr("  chat recordis empty！"));
    }
    else
    {
        temp = QString(tr("  chat record export success:%1.")).arg(name);
        copyFileToPath(newPath, name, true);
        emit exportHistoryMessageAllSuccess(m_myself.m_userID, newPath);
    }

    QMessageBox::information(NULL, tr(" export   chat record"), temp);
    m_messageManWidget->raise();
}

/*************************************************
Function Name:deleteLocalMessage()
Description:
*************************************************/
void IMMainWidget::deleteLocalMessage(const int index)
{
    QString id = m_friendsIDList[index];
    int type =  m_database.deleteHistoryMessageOneFriend(m_myself.m_userID, id);
    QString temp;
    if (type < 0)
    {
        temp = QString(tr("delete  chat recordfailed.！"));
    }
    else if (type == 0)
    {
        temp = QString(tr("  chat recordis empty！"));
    }
    else
    {
        temp = QString(tr("delete  chat recordsuccess！"));
    }
    QMessageBox::information(NULL, tr("delete  chat record"), temp);
    m_messageManWidget->raise();
    return;
}

/*************************************************
Function Name:deleteLocalMessageAll()
Description: delete
*************************************************/
void IMMainWidget::deleteLocalMessageAll()
{
    int type =  m_database.deleteHistoryMessageAll(m_myself.m_userID);
    QString temp;
    if (type < 0)
    {
        temp = QString(tr("delete  chat recordfailed.！"));
    }
    else if (type == 0)
    {
        temp = QString(tr("  chat recordis empty！"));
    }
    else
    {
        temp = QString(tr("delete  chat recordsuccess！"));
    }
    QMessageBox::information(NULL, tr("delete  chat record"), temp);
    m_messageManWidget->raise();
    return;
}



#if 0
//void IMMainWidget::exportLocalMessage(const int &index)
//{
////    QString history = "resource/history";
//    QString history = "/tmp";
//    QString id = m_friendsIDList[index];
////    QString selFilter="All files (*.*)";
////    QDir dir = QDir::current();
////    if (!dir.exists(history))
////        dir.mkpath(history);
//    QString fileName = QString("%1/%2_%3").arg(history, m_myself.m_userID, id);
////    QString filter = QString(
////                tr("CSV  file  (*.xls);;EXCEL  file  (*.xls);; TXT  file  (*.txt)"));
////    QString name = QFileDialog::getSaveFileName(this,tr("  save  file "), path,
////                                                filter, &selFilter);
////    if(name.isEmpty())
////    {
////        return;
////    }
////    qDebug() << "export-path" << name << selFilter;

////    QFile file(dir.filePath(TMP_LOCAL_HISTORY_PARH));
////    QString tmpPath = TMP_LOCAL_HISTORY_PARH;
//    QString tmpPath = fileName;
//    QString newPath = tmpPath;
//    static int i = 0;
//    while(1)
//    {

//        QFile file(newPath.append(".csv"));
//        if (file.exists())
//        {
//            newPath = tmpPath.append("_").append(QString::number(++i));
//            tmpPath = fileName;
//        }
//        else
//            break;
//    }

//    qDebug() << "newpath:" << newPath;

//    int type =  m_database.exportHistoryMessageOneFriend(m_myself.m_userID,
//                                                        id, newPath);
//    if (type < 0)
//    {
//        QString temp = QString(tr("  chat record export failed.！"));
//        QMessageBox::information(NULL, tr("  chat record"), temp);
//        return;
//    }
////    qDebug() << "type: "<< type;
////    if (type >=0)
////    {
////        QFile file(newPath);
////        file.open( QIODevice::WriteOnly );
////        file.copy("/tmp/nimei.xls");
////        file.close();
////    }
//    QString temp = QString(tr("  chat record export success:%1。\n please 选择  save路径。")).arg(newPath);
//    QMessageBox::information(NULL, tr("  chat record"), temp);

//    emit exportHistoryMessageOneFriendSuccess(m_myself.m_userID, id, newPath);

////    QFile file("/tmp/2014050703_2014050701_3.csv");
////    file.open( QIODevice::WriteOnly | QIODevice::Text );
////    file.copy("/tmp/nimei.csv");
////    file.close();

////    copyFileToPath(newPath, "/tmp/nini.csv", true);
//    QFile::copy(newPath, "/tmp/nini.csv");

//}
#endif

/*************************************************
Function Name:getNetWorkHistoryMessage()
Description:
*************************************************/
void IMMainWidget::getNetWorkHistoryMessage(const int index, const QDate &date)
{
    //    m_localHistoryMessageVec.clear();
    if (index < 0 || index >= m_friendsIDList.size())
        return;
    if (NULL != m_mainCtrl)
        m_mainCtrl->requestGetNetWorkHistoryMessageOneFriendOneDate(
                    m_friendsIDList[index], date);
}

// mark: public slots:-------------------------------------------

/*************************************************
Function Name:getFriendsInformation()
Description:
*************************************************/
void IMMainWidget::getFriendsInformation()
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->getFriendsInformation(m_myself.m_userID, m_myself.m_status);
}

/*************************************************
Function Name:getFlocksInformation()
Description:
*************************************************/
void IMMainWidget::getFlocksInformation()
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->getFlocksInformation(m_myself.m_userID);
}

/*************************************************
Function Name:getDiscussionsInformation()
Description:
*************************************************/
void IMMainWidget::getDiscussionsInformation()
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->getDiscussionsInformation(m_myself.m_userID);
}

/*************************************************
Function Name:getLatestMessage()
Description:
*************************************************/
void IMMainWidget::getLatestMessage()
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->getLatestMessage(m_myself.m_userID);
}


/*************************************************
Function Name:setNetworkMessageWidget()
Description: set
*************************************************/
void IMMainWidget::setNetworkMessageWidget(const QString & friendID, const QDate & date,
                                           const QVector<TalkMessage> & mesVec)
{
    //    if (friendID != m_friendsIDList[index])
    //        return;
    m_messageManWidget->setNetworkMessageWidget(mesVec);
}


/*************************************************
Function Name:setFriendListWidget
Description: set
*************************************************/
void IMMainWidget::setFriendListWidget(const QVector<FriendInformation> &friendsVec)
{

    int num = 0;
    int len = friendsVec.size();
    for(int i=0; i<len; i++)
    {
        addFriendButton(friendsVec[i]);
        if (OFFLINE != friendsVec[i].m_status && INVISIBLE != friendsVec[i].m_status)
            num++;
    }

    setOnlineCounter(num);
    //    #endif

    getFlocksInformation();
}

/*************************************************
Function Name:setFlockListWidget
Description: set
*************************************************/
void IMMainWidget::setFlockListWidget(const QVector<FlockInformation> & flocksVec)
{
    //    return;

    qDebug() << "flock-size:" << flocksVec.size();

    int len = flocksVec.size();
    for(int i=0; i<len; i++)
    {
        addFlockButton(flocksVec[i]);
    }
    getDiscussionsInformation();
}

/*************************************************
Function Name:setDiscussionListWidget
Description:
*************************************************/
void IMMainWidget::setDiscussionListWidget(const QVector<DiscussionInformation> & disVec)
{
    //    return;
    qDebug() << "dis-seize:" << disVec.size();

    int len = disVec.size();
    for(int i=0; i<len; i++)
    {
        addDiscussionButton(disVec[i]);
    }
}


/*************************************************
Function Name:addFriendButton
Description:
*************************************************/
bool IMMainWidget::addFriendButton(const FriendInformation & friInfo)
{
    if (m_friendMap.contains(friInfo.m_userID))
        return false;
    QString groupName = friInfo.m_groupName;
    if (!m_friendsGroupList.contains(groupName))
    {
        m_friendsGroupList.append(groupName);

        //        IMToolBox *toolBox = new IMToolBox;
        IMToolItem *toolItem = new IMToolItem(groupName);

        connect(toolItem, SIGNAL(removeBoxSignal(QString)),
                this, SLOT(removeBox(QString)));
        connect(toolItem, SIGNAL(renameBoxSignal(QString)),
                this, SLOT(renameBox(QString)));

        m_toolItemsFriendsVec.push_back(toolItem);
        //        toolBox->addItem(toolItem);
        //        m_friendListWidget->addItem(toolBox);
        m_friendListWidget->addItem(toolItem);

        m_indexFriendsGroupMap.insert(groupName, m_toolItemsFriendsVec.size()-1);
    }

    IMFriendButton *button = new IMFriendButton(friInfo,
                                                &m_friendsGroupList,this, this);
    //    button->setAutoRaise(true);
    m_toolItemsFriendsVec[m_indexFriendsGroupMap.value(groupName)]->addItem(button);
    m_friendMap.insert(friInfo.m_userID, button);
    return true;
}


/*************************************************
Function Name:addFlockButton
Description:
*************************************************/
bool IMMainWidget::addFlockButton(const FlockInformation & flcokInfo)
{
    if (m_flockMap.contains(flcokInfo.m_flockID))
        return false;

    IMFlockButton *button = new IMFlockButton(flcokInfo, this, this);
    //    button->setAutoRaise(true);

    m_flockMap.insert(flcokInfo.m_flockID, button);
    m_flockListWidget->addItem(button);

    return true;
}

/*************************************************
Function Name:addDiscussionButton
Description:
*************************************************/

bool IMMainWidget::addDiscussionButton(const DiscussionInformation & disInfo)
{
    if (m_discussionMap.contains(disInfo.m_discussionID))
        return false;

    IMDiscussionButton *button = new IMDiscussionButton(disInfo, this, this);
    //    button->setAutoRaise(true);

    m_discussionMap.insert(disInfo.m_discussionID, button);
    m_discussionListWidget->addItem(button);

    return true;
}




/*************************************************
Function Name:receiveFriendTalkMessage
Description:
*************************************************/
void IMMainWidget::receiveFriendTalkMessage(const TalkMessage &mes)
{
    if (TALK_FLOCK == mes.m_type)
    {
        if (!m_flockMap.contains(mes.m_receiverID))
            return;
        if (0 == mes.m_senderID.compare(m_myself.m_userID))
            return;

        IMFlockChatWidget *flockRoom = NULL;
        if (m_flockRoomMap.contains(mes.m_receiverID))
        {
            flockRoom = m_flockRoomMap[mes.m_receiverID];
        }
        else
        {
            m_flockMap[mes.m_receiverID]->openChatRoom();
            flockRoom = m_flockMap[mes.m_receiverID]->getRoomPoint();
        }
        flockRoom->appendMessageShow(mes);

        if (!m_flockMap[mes.m_receiverID]->isRoomShow())
        {
            //  IMLinkFlcokButton
            if (!m_linkMap.contains(mes.m_receiverID))
            {
                IMLinkFlockButton * btn = new IMLinkFlockButton(
                            m_flockMap[mes.m_receiverID], this);
                connect(btn, SIGNAL(deleteLinkButton(QString)),
                        this, SLOT(removeLinkButton(QString)));
                m_linkMap.insert(mes.m_receiverID, btn);
                m_messageListWidget->addItem(btn);
                m_tabWidget->setTabText(3, QString(tr("new msg%1"))
                                        .arg(m_messageListWidget->size()));
            }

            m_linkMap[mes.m_receiverID]->setLatestMessage(mes);
        }
        return;
    }
    if (TALK_DISCUSSION == mes.m_type)
    {
        if (!m_discussionMap.contains(mes.m_receiverID))
            return;
        if (0 == mes.m_senderID.compare(m_myself.m_userID))
            return;

        IMDiscussionChatWidget *discussionRoom = NULL;
        if (m_discussionRoomMap.contains(mes.m_receiverID))
        {
            discussionRoom = m_discussionRoomMap[mes.m_receiverID];
        }
        else
        {
            m_discussionMap[mes.m_receiverID]->openChatRoom();
            discussionRoom = m_discussionMap[mes.m_receiverID]->getRoomPoint();
        }
        discussionRoom->appendMessageShow(mes);

        if (!m_discussionMap[mes.m_receiverID]->isRoomShow())
        {
            // IMLinkDiscussionButton
            if (!m_linkMap.contains(mes.m_receiverID))
            {
                IMLinkDiscussionButton * btn = new IMLinkDiscussionButton(
                            m_discussionMap[mes.m_receiverID], this);
                connect(btn, SIGNAL(deleteLinkButton(QString)),
                        this, SLOT(removeLinkButton(QString)));
                m_linkMap.insert(mes.m_receiverID, btn);
                m_messageListWidget->addItem(btn);
                m_tabWidget->setTabText(3, QString(tr("new msg%1"))
                                        .arg(m_messageListWidget->size()));
            }
            m_linkMap[mes.m_receiverID]->setLatestMessage(mes);
        }
        return;
    }


    IMChatWidget *chatRoom = NULL;

    if (!m_friendMap.contains( mes.m_senderID))
    {
        return;
    }

    if (m_chatRoomMap.contains(mes.m_senderID))
    {
        //        qDebug("chat room contains");
        //        m_chatRoomMap[mes.m_senderID]->raise();
        //        m_chatRoomMap[mes.m_senderID]->activateWindow();
        //        m_chatRoomMap[mes.m_senderID]->show();
        chatRoom =  m_chatRoomMap[mes.m_senderID];
    }
    else
    {
        m_friendMap[mes.m_senderID]->openChatRoom();
        chatRoom = m_friendMap[mes.m_senderID]->getRoomPoint();
    }

    switch (mes.m_type)
    {
    case TALK_MESSAGE:
        chatRoom->appendMessageShow(mes);
        // store msg record  to database
        m_database.addHistoryMessage(mes);
        if (!m_friendMap[mes.m_senderID]->isRoomShow())
        {
            // create IMLinkFriendButton
            if (!m_linkMap.contains(mes.m_senderID))
            {
                IMLinkFriendButton * btn = new IMLinkFriendButton(
                            m_friendMap[mes.m_senderID], this);
                connect(btn, SIGNAL(deleteLinkButton(QString)),
                        this, SLOT(removeLinkButton(QString)));
                m_linkMap.insert(mes.m_senderID, btn);
                m_messageListWidget->addItem(btn);
                m_tabWidget->setTabText(3, QString(tr("new msg%1"))
                                        .arg(m_messageListWidget->size()));
            }
            m_linkMap[mes.m_senderID]->setLatestMessage(mes);
        }

        break;
    case REQUEST_VIDEO:
        chatRoom->pendingVideo(mes);
    case AGREE_VOICE:
        //        chatRoom->showCamera(mes);
        // createVideo Window
        // Send  Receive
    case REFUSE_VOICE:
        chatRoom->closeVideoWidget();
        break;

    case REQUEST_FILE:
    {
        chatRoom->pendingFile(mes);
        break;
    }
    case AGREE_FILE:
    {
        break;
    }
    case REFUSE_FILE:
    {
        chatRoom->refusedSendFile();
        break;
    }
    }

}

/*************************************************
Function Name:setFriendStatus
Description: set friend
*************************************************/
void IMMainWidget::setFriendStatus(const QString & id,int status)
{
    QMap<QString, IMFriendButton*>::iterator iter;
    iter = m_friendMap.find(id);
    if(m_friendMap.end() == iter)
        return;

    iter.value()->getInformation().m_status = status;
    iter.value()->setButtonStatus();
}


/*************************************************
Function Name:setFriendInformation
Description: set friendmsg
*************************************************/
void IMMainWidget::setFriendInformation(const FriendInformation &fri)
{
    QMap<QString, IMFriendButton*>::iterator iter;
    iter = m_friendMap.find(fri.m_userID);
    if(m_friendMap.end() == iter)
        return;

    iter.value()->setChangedInformation(fri);
    iter.value()->setButtonStatus();
}

/*************************************************
Function Name:showFriendInformation
Description: show friendmsg
*************************************************/
void IMMainWidget::showFriendInformation(const UserInformation &user)
{
    if (m_informationMap.contains(user.m_userID))
    {
        m_informationMap[user.m_userID]->setUserInformation(user);
        m_informationMap[user.m_userID]->raise();
        m_informationMap[user.m_userID]->activateWindow();
        m_informationMap[user.m_userID]->show();
        return;
    }

    IMInformationWidget *infWidget = new IMInformationWidget(this);
    m_informationMap.insert(user.m_userID, infWidget);
    infWidget->setReadOnly(true, false);
    infWidget->setUserInformation(user);
    infWidget->show();
}

/*************************************************
Function Name:showMyInformation
Description: show self msg
*************************************************/
void IMMainWidget::showMyInformation(const UserInformation &user)
{
    m_myself = user;
    if (m_informationMap.contains(m_myself.m_userID))
    {
        m_informationMap[m_myself.m_userID]->raise();
        m_informationMap[m_myself.m_userID]->activateWindow();
        m_informationMap[m_myself.m_userID]->show();
        return;
    }

    IMInformationWidget *infWidget = new IMInformationWidget(this);
    m_informationMap.insert(m_myself.m_userID, infWidget);
    infWidget->setReadOnly(true, true);
    infWidget->setUserInformation(user);
    infWidget->show();
}

/*************************************************
Function Name:setMyInformation
Description: set self msg
*************************************************/
void IMMainWidget::setMyInformation(const UserInformation &user)
{
    QString str = QString("resource/image/head/%1.bmp").
            arg(QString::number(user.m_headPortrait));
    m_labelHead->setPixmap(QPixmap(str));
    //    m_cbStatus->setCurrentIndex(user.m_status);
    m_labelNickname->setText(QString("%1\n%2").
                             arg(user.m_nickname, user.m_userID));
    //    m_labelMark->setText(user.m_mark); //  sign
}

/*************************************************
Function Name:showFlockInformation
Description: show Groupmsg
*************************************************/
void IMMainWidget::showFlockInformation(const FlockInformation & flock)
{
    if (m_flockInformationMap.contains(flock.m_flockID))
    {
        m_flockInformationMap[flock.m_flockID]->raise();
        m_flockInformationMap[flock.m_flockID]->activateWindow();
        m_flockInformationMap[flock.m_flockID]->show();
        return;
    }

    IMFlockInformationWidget *infWidget = new IMFlockInformationWidget(this);
    m_flockInformationMap.insert(flock.m_flockID, infWidget);
    if (flock.m_creatorID.compare(m_myself.m_userID) == 0)
        infWidget->setReadOnly(true, true);
    else
        infWidget->setReadOnly(true, false);

    infWidget->setFlockInformation(flock);
    infWidget->show();
}


/*************************************************
Function Name:showDiscussionInformation
Description: show discuss groupmsg
*************************************************/
void IMMainWidget::showDiscussionInformation(const DiscussionInformation & discussion)
{
    if (m_discussionInformationMap.contains(discussion.m_discussionID))
    {
        m_discussionInformationMap[discussion.m_discussionID]->raise();
        m_discussionInformationMap[discussion.m_discussionID]->activateWindow();
        m_discussionInformationMap[discussion.m_discussionID]->show();
        return;
    }

    IMDiscussionInformationWidget *infWidget = new IMDiscussionInformationWidget(this);
    m_discussionInformationMap.insert(discussion.m_discussionID, infWidget);
    infWidget->setReadOnly(true, true);

    infWidget->setDiscussionInformation(discussion);
    infWidget->show();
}


/*************************************************
Function Name:setFlockInformation
Description: set Groupmsg
*************************************************/
void IMMainWidget::setFlockInformation(const FlockInformation & flock)
{
    if (m_flockMap.contains(flock.m_flockID))
    {
        m_flockMap[flock.m_flockID]->setChangedInformation(flock);
    }
    if (m_flockRoomMap.contains(flock.m_flockID))
    {
        m_flockRoomMap[flock.m_flockID]->setChatInformation(flock);
    }

}



/*************************************************
Function Name:setDiscussionInformation
Description: set discuss groupmsg
*************************************************/
void IMMainWidget::setDiscussionInformation(const DiscussionInformation & discussion)
{
    if (m_discussionMap.contains(discussion.m_discussionID))
    {
        m_discussionMap[discussion.m_discussionID]->setChangedInformation(discussion);
    }
    if (m_discussionRoomMap.contains(discussion.m_discussionID))
    {
        m_discussionRoomMap[discussion.m_discussionID]->setChatInformation(discussion);
    }
}


/*************************************************
Function Name:setFlockMemberRemark
Description: group name
*************************************************/
void IMMainWidget::setFlockMemberRemark(const TempStrings & tmpStr)
{
    if (m_flockRoomMap.contains(tmpStr.m_one))
    {
        m_flockRoomMap[tmpStr.m_one]->setFlockMemberRemark(tmpStr);
    }

}

/*************************************************
Function Name:setFriendRemark
Description: set friend remark
*************************************************/
void IMMainWidget::setFriendRemark(const TempStrings& tempStr)
{
    if (tempStr.m_one != m_myself.m_userID)
        return;
    QMap<QString, IMFriendButton*>::iterator iter;
    iter = m_friendMap.find(tempStr.m_two);

    if(m_friendMap.end() == iter)
        return;

    iter.value()->getInformation().m_remarkName = tempStr.m_three;
    iter.value()->setButtonStatus();
}


/*************************************************
Function Name:deleteFriend
Description:  already deletefriend
*************************************************/
void IMMainWidget::deletedFriend(const QString & myID, const QString & friendID,
                                 const QString & groupName)
{
    if (myID != m_myself.m_userID)
        return;


    if (!m_friendMap.contains(friendID))
        return;

    m_toolItemsFriendsVec[m_indexFriendsGroupMap.value(groupName)]->removeItem(m_friendMap[friendID]);
    //    removeItem(m_indexFriendsGroupMap[friendID]);
    //    m_indexFriendsGroupMap[friendID]->setVisible(false);
    //    m_indexFriendsGroupMap[friendID]->setEnabled(false);
    //    delete m_indexFriendsGroupMap[friendID];
    //    IMFriendButton *button = m_indexFriendsGroupMap.find();
    m_friendMap[friendID]->deleteLater();
    m_friendMap.remove(friendID);

    if (m_chatRoomMap.contains(friendID))
    {
        m_chatRoomMap[friendID]->close();
        m_chatRoomMap[friendID]->deleteLater();
        m_chatRoomMap.remove(friendID);
    }
    qDebug() << "friend deleted";
    setOnlineCounter(m_onlineCounter - 1);
}


/*************************************************
Function NameQInputDialogption:  already deleteGroup
*************************************************/
void IMMainWidget::dropedFlock(const QString & flockID)
{
    if (!m_flockMap.contains(flockID))
        return;

    QMessageBox::information(NULL, tr("Groupmsg "),
                             QString(tr("Group %1 already destroied by owner")).arg(flockID));

    if (m_flockRoomMap.contains(flockID))
    {
        m_flockRoomMap[flockID]->close();
        m_flockRoomMap[flockID]->deleteLater();
        m_flockRoomMap[flockID] = NULL;
        m_flockRoomMap.remove(flockID);
    }

    m_flockListWidget->removeItem( m_flockMap[flockID] );
    m_flockMap[flockID]->deleteLater();
    m_flockMap.remove(flockID);




    qDebug() << "flock drop";
}



/*************************************************
Function Name:dropedDiscussion
Description:  already deletediscuss group
*************************************************/
void IMMainWidget::dropedDiscussion(const QString & discussionID)

{
    if (!m_discussionMap.contains(discussionID))
        return;

    QMessageBox::information(NULL, tr("discuss groupmsg "),
                             QString(tr("discuss group%1 already been destroyed by ower.")).arg(discussionID));

    if (m_discussionRoomMap.contains(discussionID))
    {
        m_discussionRoomMap[discussionID]->close();
        m_discussionRoomMap[discussionID]->deleteLater();
        m_discussionRoomMap[discussionID] == NULL;
        m_discussionRoomMap.remove(discussionID);
    }


    m_discussionListWidget->removeItem( m_discussionMap[discussionID] );
    m_discussionMap[discussionID]->deleteLater();
    m_discussionMap.remove(discussionID);




    qDebug() << "discussion drop";
}

/*************************************************
Function Name:leavedFlock
Description:  already  quit from  Group
*************************************************/
void IMMainWidget::leavedFlock(const QString & memberID,
                               const QString & flockID,
                               const QString & creatorID)
{
    if (creatorID == m_myself.m_userID)
    {
        QMessageBox::information(NULL, tr("Groupmsg "),
                                 QString(tr("user%1 already 经 quit from  Group%2")).
                                 arg(memberID, flockID));

        if (m_flockRoomMap.contains(flockID))
        {
            m_flockRoomMap[flockID]->removeFlockMemberButton(memberID);
        }
        if (m_flockMap.contains(flockID))
        {
            m_flockMap[flockID]->deleteFlockMember(memberID);
        }
    }
    else if (memberID == m_myself.m_userID)
    {
        QMessageBox::information(NULL, tr("Groupmsg "),
                                 QString(tr("hello,%1, your  already 经 quit from  Group%2")).
                                 arg(memberID, flockID));

        if (m_flockRoomMap.contains(flockID))
        {
            m_flockRoomMap[flockID]->close();
            m_flockRoomMap[flockID]->deleteLater();
            m_flockRoomMap.remove(flockID);
        }

        if (m_flockMap.contains(flockID))
        {
            m_flockListWidget->removeItem( m_flockMap[flockID] );
            m_flockMap[flockID]->deleteLater();
            m_flockMap.remove(flockID);
        }
        qDebug() << "leaved flock";
    }
    else
    {
        if (m_flockRoomMap.contains(flockID))
        {
            m_flockRoomMap[flockID]->removeFlockMemberButton(memberID);
        }
        if (m_flockMap.contains(flockID))
        {
            m_flockMap[flockID]->deleteFlockMember(memberID);
        }
    }


}


/*************************************************
Function Name:leavedDiscussion
Description:  already  quit from  discuss group
*************************************************/
void IMMainWidget::leavedDiscussion(const QString & memberID,
                                    const QString & discussionID)
{
    if (memberID == m_myself.m_userID)
    {
        //        QMessageBox::information(NULL, tr("discuss groupmsg "),
        //                                 QString(tr("hello,%1, your  already 经 quit from  discuss group%2")).
        //                                 arg(memberID, discussionID));

        if (m_discussionRoomMap.contains(discussionID))
        {
            m_discussionRoomMap[discussionID]->close();
            m_discussionRoomMap[discussionID]->deleteLater();
            m_discussionRoomMap.remove(discussionID);
        }

        if (m_discussionMap.contains(discussionID))
        {
            m_discussionListWidget->removeItem( m_discussionMap[discussionID] );
            m_discussionMap[discussionID]->deleteLater();
            m_discussionMap.remove(discussionID);
        }
        qDebug() << "leaved discussion";
    }
    else
    {
        if (m_discussionRoomMap.contains(discussionID))
        {
            m_discussionRoomMap[discussionID]->removeDiscussionMemberButton(memberID);
        }
        if (m_discussionMap.contains(discussionID))
        {
            m_discussionMap[discussionID]->deleteDiscussionMember(memberID);
        }
    }


}


/*************************************************
Function Name:createFlockSuccess
Description: createGroupsuccess
*************************************************/
void IMMainWidget::createFlockSuccess(const FlockInformation & flock)
{
    if (flock.m_creatorID.compare(m_myself.m_userID) != 0)
        return;

    if (m_flockMap.contains(flock.m_flockID))
        return;
    if (!addFlockButton(flock))
        return;
    QString temp =  QString(tr("hello,%1(%2).\n your  already 经successcreateGroup%3(%4).\ncreate date : %5.")).
            arg(m_myself.m_userID, m_myself.m_nickname,
                flock.m_flockID, flock.m_flockName,
                flock.m_createDate.toString("yyyy-MM-dd"));

    QMessageBox::information(NULL, tr("Groupmsg "), temp);
}


/*************************************************
Function Name:createDiscussionSuccess
Description: creatediscuss groupsuccess
*************************************************/
void IMMainWidget::createDiscussionSuccess(const DiscussionInformation & discussion)
{
    if (discussion.m_creatorID.compare(m_myself.m_userID) != 0)
        return;

    if (m_discussionMap.contains(discussion.m_discussionID))

        return;
    if (!addDiscussionButton(discussion))
        return;
    QString temp =  QString(tr("hello,%1(%2).\n your  already 经successcreatediscuss group%3(%4).\ncreate: %5.")).
            arg(m_myself.m_userID, m_myself.m_nickname,
                discussion.m_discussionID, discussion.m_discussionName,
                discussion.m_createDate.toString("yyyy-MM-dd"));

    QMessageBox::information(NULL, tr("discuss groupmsg "), temp);
}


/*************************************************
Function Name:searchFriend
Description: search 友好
*************************************************/
void IMMainWidget::searchFriend(const QString & text)
{
    m_searchListWidget->setVisible(true);
    m_tabWidget->setVisible(false);
    if (text.isEmpty())
    {
        qDebug() << "empty";
        onClickSearchFriend();
        return;
    }
    m_toolBtnSearch->setIcon(QIcon(":/images/cancel.png"));
    m_toolBtnSearch->setEnabled(true);

    m_searchListWidget->clearAll();
    //search 匹配,s friend
    QMapIterator<QString, IMFriendButton *> i(m_friendMap);
    while (i.hasNext()) {
        i.next();
        if(i.key().contains(text)
                || i.value()->getInformation().m_nickname.contains(text)
                || i.value()->getInformation().m_remarkName.contains(text))
        {
            IMLinkFriendButton * btn = new IMLinkFriendButton(
                        m_friendMap[i.key()], this);
            connect(btn, SIGNAL(deleteLinkButton(QString)),
                    this, SLOT(removeLinkButton(QString)));
            m_searchListWidget->addItem(btn);
        }
    }

    //     IMLinkFriendButton * btn = new IMLinkFriendButton(
    //                 m_friendMap[mes.m_senderID], this);
    //     connect(btn, SIGNAL(deleteLinkButton(QString)),
    //             this, SLOT(removeLinkButton(QString)));
    //     m_linkMap.insert(mes.m_senderID, btn);
    //     m_messageListWidget->addItem(btn);
}

/*************************************************
Function Name:onClickSearchFriend
Description:  click “search ” button 
*************************************************/
void IMMainWidget::onClickSearchFriend()
{
    qDebug() << "click search friend.";

    m_toolBtnSearch->setIcon(QIcon(":/images/search.png"));
    m_toolBtnSearch->setEnabled(false);
    m_searchListWidget->setVisible(false);
    m_tabWidget->setVisible(true);
}

/*************************************************
Function Name:onClickAddFriend
Description: Add friend
*************************************************/
void IMMainWidget::onClickAddFriend()
{
    bool isOk = false;
    QString friendID = QInputDialog::getText(NULL, "Add friend",
                                             " please  input 对方帐 number ",
                                             QLineEdit::Normal,
                                             "",
                                             &isOk);
    if (!isOk)
        return;

    // mark

    addFriend(friendID);
}

/*************************************************
Function Name:addFlock
Description: Add Group
*************************************************/
void IMMainWidget::onClickAddFlock()
{
    bool isOk = false;
    QString flockID = QInputDialog::getText(NULL, "Add Group",
                                            " please  input Group帐 number ",
                                            QLineEdit::Normal,
                                            "",
                                            &isOk);
    if (!isOk)
        return;

    // mark

    if (m_flockMap.contains(flockID))
    {
        QMessageBox::critical(NULL, tr("add failed"), tr("you already add in this Group"));
        return;
    }

    bool isOkMes = false;
    QString checkMes = QInputDialog::getText(NULL, "Add Group",
                                             " please  input verify msg",
                                             QLineEdit::Normal,
                                             QString(tr("hello, I am  %1")).
                                             arg(m_myself.m_nickname),
                                             &isOkMes);
    if (!isOkMes)
        return;

    //    TempStrings temp;
    //    temp.m_one = m_myself.m_userID;
    //    temp.m_two = friendID;
    //    temp.m_three = checkMes;

    TalkMessage mes;
    mes.m_senderID = m_myself.m_userID;
    mes.m_receiverID = flockID;
    mes.m_text = checkMes;
    mes.m_type = REQUEST_FLOCK;

    if (NULL != m_mainCtrl)
        m_mainCtrl->addFlock(mes);

}


/*************************************************
Function Name:onClickChangePwd
Description: modify password
*************************************************/
void IMMainWidget::onClickChangePwd()
{
    bool isOkMes = false;
    QString oldPwd = QInputDialog::getText(NULL, "modify password",
                                           " please  input origin password:",
                                           QLineEdit::Password,
                                           NULL,
                                           &isOkMes);
    if (!isOkMes)
        return;

    while(1)
    {
        QString newPwdOne = QInputDialog::getText(NULL, "modify password",
                                                  " please  input  new password:",
                                                  QLineEdit::Password,
                                                  NULL,
                                                  &isOkMes);
        if (!isOkMes)
            return;
        if (newPwdOne.length() < 6)
        {
            QMessageBox::critical(NULL, tr("modify password"),
                                  tr(" new password should be at least 6 charators"));
            continue;
        }
        if (newPwdOne.length() > 14)
        {
            QMessageBox::critical(NULL, tr("modify password"),
                                  tr(" new password can't more than 14 charactors"));
            continue;
        }

        QString newPwdTwo = QInputDialog::getText(NULL, "modify password",
                                                  " please  new password:",
                                                  QLineEdit::Password,
                                                  NULL,
                                                  &isOkMes);
        if (!isOkMes)
            return;
        if (newPwdTwo != newPwdOne)
        {
            QMessageBox::critical(NULL, tr("modify password"), tr("twice new password is different"));
            continue;
        }
        else
        {
            if (NULL != m_mainCtrl)
            {
                QString oldPassword = IMEncryption::getInstace().
                        getXorEncryptDecrypt(oldPwd, 10);
                QString newPassword = IMEncryption::getInstace().
                        getXorEncryptDecrypt(newPwdOne, 10);
                m_mainCtrl->requestChangePwd(oldPassword, newPassword);
                break;
            }
        }

    }
}

/*************************************************
Function Name:createFlock
Description: createGroup
*************************************************/
void IMMainWidget::createFlock()
{
    bool isOk = false;
    QString flockName = QInputDialog::getText(NULL, "createGroup",
                                              " please  input Group name ",
                                              QLineEdit::Normal,
                                              QString("%1,s IMGroup").
                                              arg(m_myself.m_nickname),
                                              &isOk);
    if (!isOk)
        return;

    isOk = false;
    QString flockTheme = QInputDialog::getText(NULL, "createGroup",
                                               " please  input Group  theme ",
                                               QLineEdit::Normal,
                                               tr(" no    theme "),
                                               &isOk);
    if (!isOk)
        return;

    TempStrings tmpStr;
    tmpStr.m_one = m_myself.m_userID;
    tmpStr.m_two = flockName;
    tmpStr.m_three = flockTheme;

    if (NULL != m_mainCtrl)
        m_mainCtrl->createFlock(tmpStr);
}


/*************************************************
Function Name:createDiscussion
Description: creatediscuss group
*************************************************/
void IMMainWidget::createDiscussion()
{
    bool isOk = false;
    QString name = QInputDialog::getText(NULL, "creatediscuss group",
                                         " please  input  box  name ",
                                         QLineEdit::Normal,
                                         QString("%1,s IMdiscuss group").
                                         arg(m_myself.m_nickname),
                                         &isOk);
    if (!isOk)
        return;

    isOk = false;
    QString theme = QInputDialog::getText(NULL, "creatediscuss group",
                                          " please  input   theme ",
                                          QLineEdit::Normal,
                                          tr(" no    theme "),
                                          &isOk);
    if (!isOk)
        return;

    TempStrings tmpStr;
    tmpStr.m_one = m_myself.m_userID;
    tmpStr.m_two = name;
    tmpStr.m_three = theme;

    if (NULL != m_mainCtrl)
        m_mainCtrl->createDiscussion(tmpStr);
}

/*************************************************
Function Name:showMessageWidget
Description: show msg manage Window
*************************************************/
void IMMainWidget::showMessageWidget()
{
    if (m_messageManWidget == NULL)
    {
        m_messageManWidget = new IMMessageManageWidget(this);
    }
    m_messageManWidget->setListModelGroup();

    m_messageManWidget->raise();
    m_messageManWidget->activateWindow();
    m_messageManWidget->show();
}

/*************************************************
Function Name:showMailWidget
Description: show mailbox
*************************************************/
void IMMainWidget::showMailWidget()
{
    if (m_mailWidget == NULL)
    {
        m_mailWidget = new IMMailWidget(m_myself.m_userID);
    }
    m_mailWidget->raise();
    m_mailWidget->activateWindow();
    m_mailWidget->show();
}

/*************************************************
Function Name:showMailWriteWidget
Description: show mailbox  write mail Window
*************************************************/
void IMMainWidget::showMailWriteWidget(const QString & address)
{
    showMailWidget();
    m_mailWidget->showMailWriteWidget(address);
}

/*************************************************
Function Name:showLatestMessageWidget
Description: show new msgWindow
*************************************************/
void IMMainWidget::showLatestMessageWidget()
{
    if (m_messageListWidget == NULL)
    {
        return;
    }
    m_tabWidget->setCurrentWidget(m_messageListWidget);
}

/*************************************************
Function Name:setTimerStatus
Description: set show  Got new msg,s  timer 
*************************************************/
void IMMainWidget::setTimerStatus(bool isOpen)
{
    if (isOpen)
    {
        if (0 == m_timerId)
        {
            m_toolBtnNewMes->setHidden(false);
            m_timerId=startTimer(400);//400ms
            m_toolBtnNewMes->setStatusTip(tr(" read new msg"));
            m_toolBtnNewMes->setToolTip(QString(tr(" Got new msg")));
            //                                        .arg(m_messageListWidget->size()));
        }
    }

    else if (!isOpen && m_timerId != 0)
    {
        killTimer(m_timerId);//kill timer
        m_timerId = 0;
        m_toolBtnNewMes->setToolTip(tr("no new msg"));
        m_toolBtnNewMes->setStatusTip(tr("no new msg"));
        m_toolBtnNewMes->setHidden(true);
    }

}

/*************************************************
Function Name:renameBoxSuccess
Description: rename groupsuccess
*************************************************/
void IMMainWidget::renameBoxSuccess(const QString & title, const QString & newTitle)
{
    //  first modify : box  name   and   subscribe index   map  table 
    int index = m_indexFriendsGroupMap.value(title);
    //    if (index == 0)
    //    {
    //        qDebug("cannot find this group");
    //        return;
    //    }
    m_indexFriendsGroupMap.remove(title);
    m_indexFriendsGroupMap.insert(newTitle, index);

    //  through  store  each  box ,s  array   get  box  item ， then modify  box  name 
    m_toolItemsFriendsVec[index]->setTile(newTitle);

    m_friendsGroupList[m_friendsGroupList.indexOf(title)] = newTitle;

    if (m_messageManWidget != NULL)
        m_messageManWidget->setListModelGroup();
    refreshFriendButtonMenu();
}


/*************************************************
Function Name:moveFriendToBoxSuccess
Description:  move friendto other  box 
*************************************************/
void IMMainWidget::moveFriendToBoxSuccess(const QString & friendID, const QString & title,
                                          const QString & newTitle)
{
    if (!m_friendMap.contains(friendID))
        return;
    m_toolItemsFriendsVec[m_indexFriendsGroupMap.value(title)]->removeItem(m_friendMap[friendID]);

    m_friendMap[friendID]->getInformation().m_groupName = newTitle;
    m_friendMap[friendID]->refreshMoveMenu();
    m_toolItemsFriendsVec[m_indexFriendsGroupMap.value(newTitle)]->addItem(m_friendMap[friendID]);
}


/*************************************************
Function Name:onClickRightButton()
Description:  right button  click  button 
*************************************************/
void IMMainWidget::onClickRightButton()
{
    if (m_menu == NULL)
    {
        //create right button  menu 
        creatMenu();
    }
    m_menu->exec(QCursor::pos() - QPoint(105, 125));
}

/*************************************************
Function Name:createBox
Description:  create  box 
*************************************************/
void IMMainWidget::createBox()
{
    bool isOk = false;
    QString groupName = QInputDialog::getText(NULL, " create  box ",
                                              " please  input  box  name ",
                                              QLineEdit::Normal,
                                              tr("new group"),
                                              &isOk);

    if (isOk)
    {
        if (m_indexFriendsGroupMap.contains(groupName))
        {
            QMessageBox::information(NULL, tr(" create  box "), tr("no create，this name already exists!"));
            return;
        }

        // store   new ,s  box  number 
        m_friendsGroupList.append(groupName);

        //  create and store  box 
        //        IMToolBox *toolBox = new IMToolBox;
        IMToolItem *toolItem = new IMToolItem(groupName);

        connect(toolItem, SIGNAL(removeBoxSignal(QString)),
                this, SLOT(removeBox(QString)));
        connect(toolItem, SIGNAL(renameBoxSignal(QString)),
                this, SLOT(renameBox(QString)));

        m_toolItemsFriendsVec.push_back(toolItem);
        m_friendListWidget->addItem(toolItem);

        // store  map  relation 
        m_indexFriendsGroupMap.insert(groupName, m_toolItemsFriendsVec.size()-1);

        if (m_messageManWidget != NULL)
            m_messageManWidget->setListModelGroup();
        refreshFriendButtonMenu();
    }

}


/*************************************************
Function Name:removeLinkButton
Description: deletenew msg connect  button 
*************************************************/
void IMMainWidget::removeLinkButton(const QString & id)
{
    if (m_linkMap.contains(id))
    {
        m_messageListWidget->removeItem(m_linkMap[id]);
        m_linkMap[id]->deleteLater();
        m_linkMap.remove(id);
        m_tabWidget->setTabText(3, QString(tr("new msg(%1)"))
                                .arg(m_messageListWidget->size()));
    }
    else
    {
        qDebug() << "there is some error in linkButton delete.";
    }
}

/*************************************************
Function Name:deleteAllLinkButton
Description: delete all msg  connect  button 
*************************************************/
void IMMainWidget::removeAllLinkButton()
{
    QMapIterator<QString, IMLinkButton*> i(m_linkMap);
    while (i.hasNext())
    {
        i.next();
        m_messageListWidget->removeItem(i.value());
        m_linkMap[i.key()]->deleteLater();
        m_linkMap.remove(i.key());
    }
    m_tabWidget->setTabText(3, QString(tr("new msg(%1)")).arg(0));
}

/*************************************************
Function Name:showAllChatRoom
Description: show  all  Chat Window
*************************************************/
void IMMainWidget::showAllChatRoom()
{
    QMapIterator<QString, IMLinkButton*> i(m_linkMap);
    while (i.hasNext())
    {
        i.next();
        i.value()->onDoubleClickButton();
    }
    //    removeAllLinkButton();
}

// mark protected:------------------------------------------------------
/*************************************************
Function Name:closeEvent
Description: close  event 
*************************************************/
void IMMainWidget::closeEvent(QCloseEvent *event)
{
    if(continueToClose())
    {
        // close  main Window   before ， first  close  all  Chat Window
        closeAllWindows();
        event->accept();
    }
    else
        event->ignore();
}

/*************************************************
Function Name:mousePressEvent
Description:  mouse  click  event 
*************************************************/
void IMMainWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        //        onClickRightButton();
        return;
    }
    QWidget::mousePressEvent(event);
}

/*************************************************
Function Name:timerEvent
Description:  timer  event 
*************************************************/
void IMMainWidget::timerEvent(QTimerEvent *event)
{
    static bool show = true;
    if (event->timerId() == m_timerId)
    {
        if (show)
            m_toolBtnNewMes->setIcon(QIcon(":/images/newMessage.png"));
        else
            m_toolBtnNewMes->setIcon(QIcon(""));//":/images/noMessage.png"));
        show = !show;
    }
}

// mark: private slots:-------------------------------------------

/*************************************************
Function Name:closeWindow
Description:  close  main Window
*************************************************/
void IMMainWidget::closeWindow()
{
    m_flag = 1;
    closeAllWindows();
    m_mainCtrl->closeConnect();
    close();
}

/*************************************************
Function Name:closeAllWindows
Description:  close  all  other ,s Window
*************************************************/
void IMMainWidget::closeAllWindows()
{
    QMap<QString, IMChatWidget*>::iterator iterFriendChat;
    for(iterFriendChat=m_chatRoomMap.begin();
        iterFriendChat!=m_chatRoomMap.end();
        ++iterFriendChat)
    {
        //        IMChatWidget * widget = iterFriendChat.value();
        //        if ( widget!= NULL)
        //        {
        //            iterFriendChat.value()->close();
        iterFriendChat.value()->deleteLater();

        //            widget->close();
        //            widget->deleteLater();
        //            widget = NULL;
        //        }
    }

    QMap<QString, IMFlockChatWidget*>::iterator iterFlockChat;
    for(iterFlockChat=m_flockRoomMap.begin();
        iterFlockChat!=m_flockRoomMap.end();
        ++iterFlockChat)
    {
        //            iterFlockChat.value()->close();
        iterFlockChat.value()->deleteLater();
    }

    QMap<QString, IMDiscussionChatWidget*>::iterator iterDiscussionChat;
    for(iterDiscussionChat=m_discussionRoomMap.begin();
        iterDiscussionChat!=m_discussionRoomMap.end();
        ++iterDiscussionChat)
    {
        //            iterDiscussionChat.value()->close();
        iterDiscussionChat.value()->deleteLater();
    }

    QMap<QString, IMInformationWidget*>::iterator iterInformation;
    for(iterInformation=m_informationMap.begin();
        iterInformation!=m_informationMap.end();
        ++iterInformation)
    {
        //            iterInformation.value()->close();
        iterInformation.value()->deleteLater();
    }

    QMap<QString, IMFlockInformationWidget*>::iterator iterFlockInformation;
    for(iterFlockInformation=m_flockInformationMap.begin();
        iterFlockInformation!=m_flockInformationMap.end();
        ++iterFlockInformation)
    {
        //            iterFlockInformation.value()->close();
        iterFlockInformation.value()->deleteLater();
    }

    QMap<QString, IMDiscussionInformationWidget*>::iterator iterDiscussionInformation;
    for(iterDiscussionInformation=m_discussionInformationMap.begin();
        iterDiscussionInformation!=m_discussionInformationMap.end();
        ++iterDiscussionInformation)
    {
        //            iterDiscussionInformation.value()->close();
        iterDiscussionInformation.value()->deleteLater();
    }

    //        m_mailWidget->close();
    //        m_messageManWidget->close();
    if (m_mailWidget != NULL)
    {
        m_mailWidget->deleteLater();
    }
    if (m_messageManWidget != NULL)
    {
        m_messageManWidget->deleteLater();
    }

}

/*************************************************
Function Name:createChatRoom
Description: create Chat  room 
*************************************************/
void IMMainWidget::getMyInformation()
{
    if (NULL != m_mainCtrl)
        m_mainCtrl->getMynformation(m_myself.m_userID);
}

//void IMMainWidget::createChatRoom(QListWidgetItem *item)
//{

//    ChatInformation chatInf;
//    chatInf.m_friendID = item->text();
////    chatInf.m_friendMark = "";
////    chatInf.m_friendNickname = "";
////    ChatInformation.m_friendRemark = "";
//    IMChatWidget *chatRoom = new IMChatWidget(chatInf);
//    m_chatRoomMap.insert(chatInf.m_friendID, chatRoom);
//    connect(chatRoom, SIGNAL(sendMessagesFromChat(TalkMessage &)),
//            this, SLOT(receiveMessagesFromChat(TalkMessage &)));
////    connect(room, SIGNAL(roomQuitSignal()),  this, SLOT(chatRoomQuit()));
//    chatRoom->show();
//}

/*************************************************
Function Name:receiveMessagesFromChat
Description:  get friend Chat  room  send ,s msg
*************************************************/
void IMMainWidget::receiveMessagesFromChat(TalkMessage &mes)
{
    mes.m_senderID = m_myself.m_userID;
    if (TALK_MESSAGE == mes.m_type)
        m_database.addHistoryMessage(mes);
    if (NULL != m_mainCtrl)
        m_mainCtrl->sendTalkMessage(mes);
}


/*************************************************
Function Name:receiveMessagesFromFlockChat
Description:
*************************************************/
//void IMMainWidget::receiveMessagesFromFlockChat(TalkMessage &)
//{
//    if (NULL != m_mainCtrl)
//        m_mainCtrl->sendTalkMessage(mes);
//}

/*************************************************
Function Name:receiveMessagesFromDiscussionChat
Description:
*************************************************/
//void IMMainWidget::receiveMessagesFromDiscussionChat(TalkMessage &)
//{
//    if (NULL != m_mainCtrl)
//        m_mainCtrl->sendTalkMessage(mes);
//}

/*************************************************
Function Name:changeStatus
Description:
*************************************************/
void IMMainWidget::changeMyStatus(const int index)
{
    int status = ONLINE;
    switch (index)
    {
    case 0:
        status = ONLINE;
        break;
    case 1:
        status = INVISIBLE;
        break;
    case 2:
        status = BUSY;
        break;
    case 3:
        status = LEAVE;
        break;
    case 4:
        status = NOTDISTURB;
        break;
    default:
        status = ONLINE;
        break;
    }

    if (NULL != m_mainCtrl)
        m_mainCtrl->changeMyStatus(m_myself.m_userID,status);
}



/*************************************************
Function Name:receiveFriendRequest
Description:
*************************************************/
void IMMainWidget::receiveFriendRequest(const TalkMessage & mes,
                                        const UserInformation & friendInf)
{
    if (0 != mes.m_receiverID.compare(m_myself.m_userID))
        return;
    TalkMessage returnMes;

    switch (mes.m_type)
    {
    case REQUEST_FRIEND:
    {
        QMessageBox::StandardButton rb = QMessageBox::question(
                    NULL, tr("friendrequest"),
                    QString(tr("Agree user%1(%2)Add 你为friend?\nverify msg :\n%3")).
                    arg(mes.m_senderID, friendInf.m_nickname, mes.m_text),
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::Yes)
        {
            returnMes.m_type = AGREE_FRIEND;
        }
        else
        {
            returnMes.m_type = REFUSE_FRIEND;
        }
        returnMes.m_senderID = mes.m_receiverID;
        returnMes.m_receiverID = mes.m_senderID;
        if (NULL != m_mainCtrl)
            m_mainCtrl->resultOfFriendRequest(returnMes);
        break;
    }
    case AGREE_FRIEND:
    {
        FriendInformation fri;
        fri.m_headPortrait = friendInf.m_headPortrait;
        fri.m_userID = friendInf.m_userID;
        fri.m_nickname = friendInf.m_nickname;
        //        fri.m_groupName = tr("New Friends");
        fri.m_status = friendInf.m_status;
        if (!addFriendButton(fri))
            return;
        QString temp = QString(tr("successAdd friend%1(%2).")).
                arg(friendInf.m_userID, friendInf.m_nickname);
        QMessageBox::information(NULL, tr("msg "), temp);
        break;
    }
    case REFUSE_FRIEND:
    {
        QString temp = QString(tr("user%1(%2)\nrefuse   your ,s friendAdd request.")).
                arg(friendInf.m_userID, friendInf.m_nickname);
        QMessageBox::information(NULL, tr("msg "), temp);
        break;
    }
    case DELETE_FRIEND:
    {
        break;
    }
    }
}

/*************************************************
Function Name:receiveFlockRequest
Description: Receive and and  processGroup,s request
*************************************************/
void IMMainWidget::receiveFlockRequest(const TalkMessage & mes,
                                       const FlockMember & member,
                                       const FlockInformation &flock)
{
    TalkMessage returnMes;
    switch (mes.m_type)
    {
    case REQUEST_FLOCK:
    {
        QMessageBox::StandardButton rb = QMessageBox::question(
                    NULL, tr("userrequest"),
                    QString(tr("Agree user%1add Group%2?\nverify msg :\n%3")).
                    arg(mes.m_senderID, mes.m_receiverID, mes.m_text),
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        if(rb == QMessageBox::Yes)
        {
            returnMes.m_type = FLOCK_AGREE;
        }
        else
        {
            returnMes.m_type = FLOCK_REFUSE;
        }
        returnMes.m_senderID = mes.m_receiverID; // Group
        returnMes.m_receiverID = mes.m_senderID; // user
        if (NULL != m_mainCtrl)
            m_mainCtrl->resultOfFlockRequest(returnMes);
        break;
    }

    case AGREE_FLOCK:
    {
        if (!m_flockMap.contains(mes.m_receiverID))
            return;
        if (!m_flockRoomMap.contains(mes.m_receiverID))
            return;
        if (!m_flockRoomMap[mes.m_receiverID]->addFlockMemberButton(member))
            return;

        m_flockMap[mes.m_receiverID]->addFlockMember(member.m_userID);

        QString temp = QString(tr("user%1,successadd Group%2(%3).")).
                arg(mes.m_senderID, flock.m_flockID, flock.m_flockName);
        QMessageBox::information(NULL, tr("Groupmsg "), temp);
        //        out << temp.m_message << m_save.m_flockMember;
        break;
    }
    case REFUSE_FLOCK:
    {
        QString temp = QString(tr("hello,%1,user%2,refuse  add Group%3\n,s Group.")).
                arg(m_myself.m_userID, mes.m_senderID, mes.m_receiverID);
        QMessageBox::information(NULL, tr("Groupmsg "), temp);
        break;
    }
    case FLOCK_AGREE:
    {
        if (m_flockMap.contains(flock.m_flockID))
            return;
        if (!addFlockButton(flock))
            return;
        QString temp = QString(tr("successadd Group%1(%2).")).
                arg(flock.m_flockID, flock.m_flockName);
        QMessageBox::information(NULL, tr("Groupmsg "), temp);

        break;
    }
    case FLOCK_REFUSE:
    {
        QString temp = QString(tr("hello,%1,Group%2\n,s Group main refuse   your ,s add request.")).
                arg(m_myself.m_userID, mes.m_senderID);
        QMessageBox::information(NULL, tr("Groupmsg "), temp);
        break;
    }
    case FLOCK_REQUEST:
    {
        QMessageBox::StandardButton rb = QMessageBox::question(
                    NULL, tr("Grouprequest"),
                    QString(tr("Agree add Group%1?\nverify msg :\n%2")).
                    arg(mes.m_senderID, mes.m_text),
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        if(rb == QMessageBox::Yes)
        {
            returnMes.m_type = AGREE_FLOCK;
        }
        else
        {
            returnMes.m_type = REFUSE_FLOCK;
        }
        returnMes.m_senderID = mes.m_receiverID; // user
        returnMes.m_receiverID = mes.m_senderID; // Group
        
	if (NULL != m_mainCtrl)
            m_mainCtrl->resultOfFlockRequest(returnMes);
        break;
    }
    case NEW_FLOCK_MEMBER:
    {
        if (!m_flockMap.contains(flock.m_flockID))
            return;
        if (!m_flockRoomMap.contains(flock.m_flockID))
            return;
        if (!m_flockRoomMap[flock.m_flockID]->addFlockMemberButton(member))
            return;

        m_flockMap[flock.m_flockID]->addFlockMember(member.m_userID);
        break;
    }
    default:
        break;
    }
}


/*************************************************
Function Name:receiveDiscussionRequest
Description: Receive and processdiscuss grouprequest
*************************************************/
void IMMainWidget::receiveDiscussionRequest(const TalkMessage & mes,
                                            const DiscussionMember & member,
                                            const DiscussionInformation & discussion)
{
    switch (mes.m_type)
    {
    case ADD_DISCUSSION_FAIL:
    {
        QString temp = QString(tr("hello,%1,user %2 add discuss group %3 failed..")).
                arg(m_myself.m_userID, mes.m_receiverID, mes.m_senderID);
        QMessageBox::information(NULL, tr("discuss groupmsg "), temp);
        break;
    }

    case NEW_DISCUSSION_MEMBER:
    {
        if (!m_discussionMap.contains(mes.m_senderID))
            return;
        if (!m_discussionRoomMap.contains(mes.m_senderID))
            return;
        if (!m_discussionRoomMap[mes.m_senderID]->addDiscussionMemberButton(member))
            return;

        m_discussionMap[mes.m_senderID]->addDiscussionMember(member.m_userID);

        break;
    }
    case ADD_DISCUSSION_SUCCESS:
    {
        if (m_discussionMap.contains(mes.m_senderID))
            return;
        if (!addDiscussionButton(discussion))
            return;
        break;
    }
    default:
        break;
    }
}


// delete folder
/*************************************************
Function Name:removeBox
Description: folder
*************************************************/
void IMMainWidget::removeBox(const QString & title)
{
    QMessageBox::StandardButton returnBtn;

    returnBtn = QMessageBox::question(NULL, tr("delete folder"),
                                      QString(tr(" Are you sure to delete folder(%1)？")).arg(title),
                                      QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(QMessageBox::No == returnBtn)
        return;

    int index = m_indexFriendsGroupMap[title];

    if (m_toolItemsFriendsVec[index]->getSize() > 0)
    {
        QMessageBox::information(NULL, tr("delete folder"), tr("can't delete，because there is some memebers in it."));
        return;
    }

    m_toolItemsFriendsVec[index]->deleteLater();
    m_toolItemsFriendsVec[index] = NULL;
    m_friendsGroupList.removeAt(m_friendsGroupList.indexOf(title));
    m_indexFriendsGroupMap.remove(title);
    if (m_messageManWidget != NULL)
        m_messageManWidget->setListModelGroup();
    //    if (m_mainWidget == NULL)
    //        return;
    //    m_mainWidget->dropFlock(m_flockInfo.m_flockID);
    //    m_mainCtrl->removeBox(title);
    refreshFriendButtonMenu();
}

/*************************************************
Function Name:renameBox
Description: rename group
*************************************************/
void IMMainWidget::renameBox(const QString & title)
{
    bool isOk = false;
    QString newTitle = QInputDialog::getText(NULL, "rename group",
                                             "please input new name!",
                                             QLineEdit::Normal,
                                             title,
                                             &isOk);


    if (!isOk)
        return;

    if (m_indexFriendsGroupMap.contains(newTitle))
    {
        QMessageBox::information(NULL, tr("rename group"), tr("failed，this name already exists!"));
        return;
    }

    int index = m_indexFriendsGroupMap.value(title);

    if (m_toolItemsFriendsVec[index]->getSize() <= 0)
    {
        renameBoxSuccess(title, newTitle);
        refreshFriendButtonMenu();
        return;
    }

    if (0 != newTitle.compare(title))
    {
        m_mainCtrl->renameBox(title, newTitle);
    }
}


// mark: private:--------------------------------------------------
/*************************************************
Function Name:initIMMainWidget
Description: init
*************************************************/
void IMMainWidget::initIMMainWidget()
{
    m_mainCtrl = new IMMainCtrl(m_myself.m_userID);

    m_labelHead = new IMClickLabel(this);
    /*
border: 2px solid green;
     border-radius: 4px;
     padding: 2px;
     background-image: url(images/welcome.png);
     */
    qDebug() << "m_headPortrait: " << m_myself.m_headPortrait;
    m_labelHead->setFixedSize(HEAD_BIG_SIZE,HEAD_BIG_SIZE);
    //    m_frameHead->setObjectName("headFrame");
    //    QString str = QString("QFrame#headFrame{border-image:url(resource/image/head/%1.bmp);}")
    //            .arg(QString::number(m_myself.m_headPortrait));
    //    m_frameHead->setStyleSheet(str);
    QString str = QString("resource/image/head/%1.bmp").
            arg(QString::number(m_myself.m_headPortrait));
    m_labelHead->setPixmap(QPixmap(str));
    m_cbStatus = new QComboBox(this);
    //    m_cbStatus->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    //    m_cbStatus->setStyleSheet("QComboBox{border: 0;font-size: 16px;}");
    //                              "QComboBox::drop-down{border-style:none;border:0px;width:40px}");

    /*
    ONLINE = 0,    //  online
    INVISIBLE = 1, // invisible
    BUSY = 2,      // busy
    LEAVE = 3,     // away
    NOTDISTURB = 4,// No Disturb
    */
    m_cbStatus->addItem(" online ");
    m_cbStatus->addItem("invisible ");
    m_cbStatus->addItem("busy");
    m_cbStatus->addItem("away");
    m_cbStatus->addItem("No Disturb");
    m_cbStatus->setCurrentIndex(m_myself.m_status);

    // add item
    m_labelNickname = new QLabel(QString("%1\n%2")
                                 .arg(m_myself.m_nickname, m_myself.m_userID));
    m_labelMark = new QLabel(tr("my sign")); //  sign

    m_toolBtnSpace = new QToolButton(this);  // space
    m_toolBtnSpace->setIcon(QIcon(":/images/space.png"));
    m_toolBtnSpace->setAutoRaise(true);
    m_toolBtnSpace->setToolTip(tr("space "));
    m_toolBtnSpace->setStatusTip(tr("openspace "));

    //    m_toolBtnSpace->setAutoFillBackground(true);
    m_toolBtnMail = new QToolButton(this);   // email
    m_toolBtnMail->setIcon(QIcon(":/images/mail.png"));
    m_toolBtnMail->setAutoRaise(true);
    m_toolBtnMail->setToolTip(tr("mailbox "));
    m_toolBtnMail->setStatusTip(tr("openmailbox "));

    m_toolBtnMesBox = new QToolButton(this); // msg box
    m_toolBtnMesBox->setIcon(QIcon(":/images/messageBox.png"));
    m_toolBtnMesBox->setAutoRaise(true);
    m_toolBtnMesBox->setToolTip(tr("msg manage "));
    m_toolBtnMesBox->setStatusTip(tr("openmsg manage "));

    m_toolBtnNewMes = new QToolButton(this);
    m_toolBtnNewMes->setIcon(QIcon(""));//:/images/noMessage.png"));
    m_toolBtnNewMes->setAutoRaise(true);
    m_toolBtnNewMes->setToolTip(tr("no new msg"));
    m_toolBtnNewMes->setStatusTip(tr("no new msg"));
    m_toolBtnNewMes->setHidden(true);

    QLabel *searchLabel = new QLabel(this);
    searchLabel->setStyleSheet("border: 1px;\
                               border-radius:3px;\
            border-style: solid;\
    border-color: gray;\
background: white;");
    searchLabel->setFixedHeight(25);

    m_leSearch = new QLineEdit();
    m_leSearch->setStyleSheet("border: 0px;");
    m_leSearch->setPlaceholderText(tr("search friends"));

    m_toolBtnSearch = new QToolButton();
    m_toolBtnSearch->setIcon(QIcon(":/images/search.png"));
    m_toolBtnSearch->setStyleSheet("border: 0px;");
    m_toolBtnSearch->setEnabled(false);
    //    m_labelSearch = new QLabel(this);
    //    m_labelSearch->setStyleSheet("border: 0px;");

    //    QPixmap pixmap;
    //    QIcon icon(QString(":/images/search.png"));
    //    pixmap = icon.pixmap(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,
    //                               CHAT_WIDGET_TOOL_SMALL_SIZE));
    //    m_labelSearch->setPixmap(pixmap);

    QHBoxLayout *layoutTopSearch = new QHBoxLayout;
    layoutTopSearch->setContentsMargins(0, 0, 0, 0);
    layoutTopSearch->addWidget(m_leSearch);
    layoutTopSearch->addWidget(m_toolBtnSearch);
    //    layoutTopSearch->addWidget(m_labelSearch);
    //    layoutTopSearch->addSpacing(2);
    searchLabel->setLayout(layoutTopSearch);

    //    m_toolBtnSearch = new QToolButton();
    //    m_toolBtnSearch->setIcon(QIcon(":/images/search.png"));
    //    m_toolBtnSearch->setAutoRaise(true);
    //    m_toolBtnSearch->setToolTip(tr("search friend"));
    //    m_toolBtnSearch->setStatusTip(tr("search friend"));

    //    m_toolBtnSearch->adjustSize();
    //    m_toolBtnSearch->setCursor(Qt::ArrowCursor);
    //    m_toolBtnSearch ->setStyleSheet("background:transparent;");

    m_searchListWidget = new IMSearchListWidget;
    m_searchListWidget->setVisible(false);

    m_tabWidget= new QTabWidget;
    //    m_tabWidget->setTabShape(QTabWidget::Triangular);
    m_friendListWidget = new IMFriendListWidget(this, this);
    m_flockListWidget = new IMFlockListWidget(this, this);
    m_discussionListWidget = new IMDiscussionListWidget(this, this);
    m_messageListWidget = new IMLatestMessageListWidget(this, this);
    m_tabWidget->addTab(m_friendListWidget, tr("friends "));
    m_tabWidget->addTab(m_flockListWidget,tr("IMGroup"));
    m_tabWidget->addTab(m_discussionListWidget, tr("discuss group"));
    m_tabWidget->addTab(m_messageListWidget, tr("new msg(0)"));

    m_labelOnlineNum = new QLabel(" online  member count : 0");
    m_labelOnlineNum->setHidden(true);

    m_toolBtnAddFlock = new QToolButton;
    m_toolBtnAddFlock->setIcon(QIcon(":/images/addFlock.png"));
    m_toolBtnAddFlock->setAutoRaise(true);
    m_toolBtnAddFlock->setToolTip(tr("Add Group"));
    m_toolBtnAddFlock->setStatusTip(tr("Add Group"));

    //    m_toolBtnAddDiscussion = new QToolButton;
    //    m_toolBtnAddDiscussion->setIcon(QIcon(":/images/addDiscussion.png"));
    //    m_toolBtnAddDiscussion->setAutoRaise(true);
    //    m_toolBtnAddDiscussion->setToolTip(tr(""));
    //    m_toolBtnAddDiscussion->setStatusTip(tr(""));

    //    m_toolBtnSearchAdd = new QToolButton;
    //    m_toolBtnSearchAdd->setIcon(QIcon(":/images/searchAdd.png"));
    //    m_toolBtnSearchAdd->setAutoRaise(true);
    //    m_toolBtnSearchAdd->setToolTip(tr(""));
    //    m_toolBtnSearchAdd->setStatusTip(tr(""));

    m_toolBtnConfig = new QToolButton;
    m_toolBtnConfig->setIcon(QIcon(":/images/config.png"));
    m_toolBtnConfig->setAutoRaise(true);
    m_toolBtnConfig->setToolTip(tr(" system manage "));
    m_toolBtnConfig->setStatusTip(tr("open system manage "));

    m_toolBtnAddFriend = new QToolButton;
    m_toolBtnAddFriend->setIcon(QIcon(":/images/addFriend.png"));
    m_toolBtnAddFriend->setAutoRaise(true);
    m_toolBtnAddFriend->setToolTip(tr("Add friend"));
    m_toolBtnAddFriend->setStatusTip(tr("Add friend"));

    /****************header*********/
    QVBoxLayout *layoutTopRight = new QVBoxLayout;
    //    layoutTopRight1->addWidget(m_cbStatus);
    layoutTopRight->addWidget(m_labelNickname);
    //    layoutTopRight->addWidget(m_labelMark);

    QHBoxLayout *layoutTop = new QHBoxLayout;
    layoutTop->addWidget(m_labelHead);
    layoutTop->addLayout(layoutTopRight);

    QHBoxLayout *layoutTopTool = new QHBoxLayout;
    layoutTopTool->addWidget(m_cbStatus);
    layoutTopTool->addWidget(m_toolBtnSpace);
    layoutTopTool->addWidget(m_toolBtnMail);
    layoutTopTool->addWidget(m_toolBtnMesBox);
    layoutTopTool->addWidget(m_toolBtnNewMes);
    layoutTopTool->addStretch();

    //    QHBoxLayout *layoutTopSearch = new QHBoxLayout;
    //    layoutTopSearch->addWidget(m_leSearch);
    ////    layoutTopSearch->addWidget(m_toolBtnSearch);

    QVBoxLayout *layoutHead = new QVBoxLayout;
    layoutHead->addLayout(layoutTop);
    layoutHead->addLayout(layoutTopTool);
    layoutHead->addWidget(searchLabel);
    //    layoutHead->addLayout(layoutTopSearch);
    //    layoutTop->addStretch();
    /***********ennd header************/

    QHBoxLayout *layoutBtm = new QHBoxLayout;
    layoutBtm->addWidget(m_labelOnlineNum);
    layoutBtm->addStretch();
    layoutBtm->addWidget(m_toolBtnAddFlock);
    //    layoutBtm->addWidget(m_toolBtnAddDiscussion);
    layoutBtm->addWidget(m_toolBtnAddFriend);
    //    layoutBtm->addWidget(m_toolBtnSearchAdd);
    layoutBtm->addWidget(m_toolBtnConfig);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layoutHead);
    layout->addWidget(m_tabWidget);
    layout->addWidget(m_searchListWidget);
    layout->addLayout(layoutBtm);

    setLayout(layout);

    setMinimumSize(278, 300);
    resize(278,500);

}

/*************************************************
Function Name:linkSignalWithSlot
Description:
*************************************************/
void IMMainWidget::linkSignalWithSlot()
{
    connect(m_mainCtrl, SIGNAL(getFriendsSuccess(QVector<FriendInformation>)),
            this, SLOT(setFriendListWidget(QVector<FriendInformation>)));
    connect(m_mainCtrl, SIGNAL(getFlocksSuccess(QVector<FlockInformation>)),
            this, SLOT(setFlockListWidget(QVector<FlockInformation>)));
    connect(m_mainCtrl, SIGNAL(getDiscussionsSuccess(QVector<DiscussionInformation>)),
            this, SLOT(setDiscussionListWidget(QVector<DiscussionInformation>)));

    connect(m_mainCtrl, SIGNAL(getFriendTalkMessage(TalkMessage)),
            this, SLOT(receiveFriendTalkMessage(TalkMessage)));

    connect(m_mainCtrl, SIGNAL(getFriendChangedStatus(QString,int)),
            this, SLOT(setFriendStatus(QString,int)));
    connect(m_mainCtrl, SIGNAL(getFriendChangedInformation(FriendInformation)),
            this, SLOT(setFriendInformation(FriendInformation)));
    //    connect(m_friendsList, SIGNA.L(itemDoubleClicked(QListWidgetItem *)),
    //            this, SLOT(createChatRoom(QListWidgetItem *)));
    connect(m_mainCtrl, SIGNAL(getFriendInformationSuccess(UserInformation)),
            this, SLOT(showFriendInformation(UserInformation)));

    connect(m_labelHead, SIGNAL(clicked()),
            this, SLOT(getMyInformation()));

    connect(m_mainCtrl, SIGNAL(getMyInformationSuccess(UserInformation)),
            this, SLOT(showMyInformation(UserInformation)));

    connect(m_mainCtrl, SIGNAL(changeMyInformationSuccess(UserInformation)),
            this, SLOT(setMyInformation(UserInformation)));

    connect(m_cbStatus, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeMyStatus(int)));
    connect(m_mainCtrl, SIGNAL(changeFriendRemarkSuccess(TempStrings)),
            this, SLOT(setFriendRemark(TempStrings)));
    connect(m_mainCtrl, SIGNAL(deleteFriendSuccess(QString, QString, QString)),
            this, SLOT(deletedFriend(QString, QString, QString)));

    connect(m_mainCtrl, SIGNAL(getFriendRequest(TalkMessage, UserInformation)),
            this, SLOT(receiveFriendRequest(TalkMessage, UserInformation)));


    connect(m_mainCtrl, SIGNAL(getFlockRequest(TalkMessage, FlockMember, FlockInformation)),
            this, SLOT(receiveFlockRequest(TalkMessage, FlockMember, FlockInformation)));
    connect(m_mainCtrl, SIGNAL(dropFlockSuccess(QString)),
            this, SLOT(dropedFlock(QString)));
    connect(m_mainCtrl, SIGNAL(leaveFlockSuccess(QString,QString,QString)),
            this, SLOT(leavedFlock(QString,QString,QString)));
    connect(m_mainCtrl, SIGNAL(haveMemberleavedFlock(QString,QString,QString)),
            this, SLOT(leavedFlock(QString,QString,QString)));
    connect(m_mainCtrl, SIGNAL(changeFlockSuccess(FlockInformation)),
            this, SLOT(setFlockInformation(FlockInformation)));
    connect(m_mainCtrl, SIGNAL(changeFlockRemarkSuccess(TempStrings)),
            this, SLOT(setFlockMemberRemark(TempStrings)));
    connect(m_mainCtrl, SIGNAL(createFlockSuccess(FlockInformation)),
            this, SLOT(createFlockSuccess(FlockInformation)));


    connect(m_mainCtrl, SIGNAL(getDiscussionRequest(TalkMessage,DiscussionMember,DiscussionInformation)),
            this, SLOT(receiveDiscussionRequest(TalkMessage,DiscussionMember,DiscussionInformation)));
    connect(m_mainCtrl, SIGNAL(dropDiscussionSuccess(QString)),
            this, SLOT(dropedDiscussion(QString)));
    connect(m_mainCtrl, SIGNAL(leaveDiscussionSuccess(QString,QString)),
            this, SLOT(leavedDiscussion(QString,QString)));
    connect(m_mainCtrl, SIGNAL(changeDiscussionSuccess(DiscussionInformation)),
            this, SLOT(setDiscussionInformation(DiscussionInformation)));
    connect(m_mainCtrl, SIGNAL(createDiscussionSuccess(DiscussionInformation)),
            this, SLOT(createDiscussionSuccess(DiscussionInformation)));

    connect(m_mainCtrl, SIGNAL(closeWindowSignal()),
            this, SLOT(closeWindow()));

    connect(m_leSearch, SIGNAL(textChanged(QString)),
            this, SLOT(searchFriend(QString)));
    connect(m_toolBtnSearch, SIGNAL(clicked()),
            this, SLOT(onClickSearchFriend()));

    connect(m_toolBtnAddFriend, SIGNAL(clicked()),
            this, SLOT(onClickAddFriend()));
    connect(m_toolBtnAddFlock, SIGNAL(clicked()),
            this, SLOT(onClickAddFlock()));
    //    connect(m_toolBtnAddDiscussion, SIGNAL(clicked()),
    //            this, SLOT(addDiscussion()));
    connect(m_toolBtnMail, SIGNAL(clicked()),
            this, SLOT(showMailWidget()));
    connect(m_toolBtnMesBox, SIGNAL(clicked()),
            this, SLOT(showMessageWidget()));
    connect(m_toolBtnConfig, SIGNAL(clicked()),
            this, SLOT(onClickRightButton()));
    connect(m_toolBtnNewMes, SIGNAL(clicked()),
            this, SLOT(showLatestMessageWidget()));

    connect(m_mainCtrl, SIGNAL(renameBoxSuccess(QString,QString)),
            this, SLOT(renameBoxSuccess(QString, QString)));
    connect(m_mainCtrl, SIGNAL(moveFriendToBoxSuccess(QString,QString,QString)),
            this, SLOT(moveFriendToBoxSuccess(QString,QString,QString)));

    connect(m_mainCtrl, SIGNAL(getNetworkHistoryMessagesSuccess(QString,QDate,QVector<TalkMessage>)),
            this, SLOT(setNetworkMessageWidget(QString,QDate,QVector<TalkMessage>)));

    connect(m_messageListWidget, SIGNAL(timerStatus(bool)),
            this, SLOT(setTimerStatus(bool)));
}


/*************************************************
Function Name:clearContainers
Description:
*************************************************/
void IMMainWidget::clearContainers()
{
    m_friendsGroupList.clear();

    m_indexFriendsGroupMap.clear();

    qDeleteAll(m_friendMap.begin(), m_friendMap.end());
    m_friendMap.clear();

    qDeleteAll(m_toolItemsFriendsVec.begin(), m_toolItemsFriendsVec.end());
    m_toolItemsFriendsVec.clear();


    qDeleteAll(m_flockMap.begin(), m_flockMap.end());
    m_flockMap.clear();

    qDeleteAll(m_discussionMap.begin(), m_discussionMap.end());
    m_discussionMap.clear();

    qDeleteAll(m_linkMap.begin(), m_linkMap.end());
    m_linkMap.clear();

}

/*************************************************
Function Name:creatMenu
Description: create
*************************************************/
void IMMainWidget:: creatMenu()
{
    m_menu = new QMenu(this);
    QAction *addFriend = new QAction(tr("Add friend"), m_menu);
    QAction *addFlock = new QAction(tr("Add Group"), m_menu);
    QAction *changePwd = new QAction(tr("modify password"), m_menu);
    QAction *information = new QAction(tr("self msg"), m_menu);
    QAction *manMes = new QAction(tr("msg manage "), m_menu);
    QAction *mail = new QAction(tr("email manage "), m_menu);

    connect(addFriend, SIGNAL(triggered()),
            this, SLOT(onClickAddFriend()));
    connect(addFlock, SIGNAL(triggered()),
            this, SLOT(onClickAddFlock()));
    connect(changePwd, SIGNAL(triggered()),
            this, SLOT(onClickChangePwd()));
    connect(information, SIGNAL(triggered()),
            this, SLOT(getMyInformation()));
    connect(manMes, SIGNAL(triggered()),
            this, SLOT(showMessageWidget()));
    connect(mail, SIGNAL(triggered()),
            this, SLOT(showMailWidget()));


    m_menu->addAction(addFlock);
    m_menu->addAction(addFriend);
    m_menu->addAction(changePwd);
    m_menu->addAction(information);
    m_menu->addAction(manMes);
    m_menu->addAction(mail);
}


/*************************************************
Function Name:refreshFriendButtonMenu
Description:
*************************************************/
void IMMainWidget::refreshFriendButtonMenu()
{
    QMapIterator<QString, IMFriendButton *> iter(m_friendMap);
    while (iter.hasNext()) {
        iter.next();
        iter.value()->refreshMoveMenu();
    }
}


/*************************************************
Function Name:refreshFriendButtonMenu
Description:
*************************************************/
bool IMMainWidget::continueToClose()
{
    if (m_flag == 1)
    {
        return true;
    }
    if (m_chatRoomMap.size() != 0
            || m_flockRoomMap.size() != 0
            || m_discussionRoomMap.size() != 0)
    {
        QString temp = tr("There is Chat Window not closed，r u sure to exit？");
        QMessageBox::StandardButton rb;
        rb = QMessageBox::question(this, tr("exit"), temp,
                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::Yes)
            return true;
        else
            return false;
    }
    return true;
}
