#include "IMMainCtrl.h"
#include "model/IMTcpSocket.h"
#include "view/IMLoginWidget.h"
#include <QMessageBox>

// mark: public -----------------------------------------------------
IMMainCtrl::IMMainCtrl(const QString myID, QObject *parent) :
    m_myID(myID), QObject(parent)
{
    m_tcpSocket = new IMTcpSocket(this);
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(requestGetFriendsInformation()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(closeWindow()));
}

void IMMainCtrl::closeConnect()
{
    m_tcpSocket->close();
}

/*************************************************
Function Name: getFriendsInformation
Description: 
*************************************************/
void IMMainCtrl::getFriendsInformation(const QString &id, const int status)
{
    m_myID = id;
    m_status = status;
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestGetFriendsInformation();
    }
    else
    {
        m_blockSize = 0;
        m_tcpSocket->requestConnect();
    }
}


/*************************************************
Function Name: getFlocksInformation
Description: 
*************************************************/
void IMMainCtrl::getFlocksInformation(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestGetFlocksInformation(id);
}

/*************************************************
Function Name: getDiscussionsInformation
Description: 
*************************************************/
void IMMainCtrl::getDiscussionsInformation(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestGetDiscussionsInformation(id);
}

/*************************************************
Function Name: getLatestMessage
Description: 
*************************************************/
void IMMainCtrl::getLatestMessage(const QString & id)
{
}

/*************************************************
Function Name: getFlockMembers
Description: 
*************************************************/
void IMMainCtrl::getFlockMembers(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestGetFlockMembers(id);
}

/*************************************************
Function Name: getDiscussionMembers
Description: 
*************************************************/
void IMMainCtrl::getDiscussionMembers(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestGetDiscussionMembers(id);
}

/*************************************************
Function Name: sendTalkMessage
Description: 
*************************************************/
void IMMainCtrl::sendTalkMessage(TalkMessage &mes)
{
//    if (mes.m_type == TALK_MESSAGE)
    mes.m_senderID = m_myID;
    mes.m_senderIP = IMTcpSocket::getIP();
    m_messageVector.push_back(mes);
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestSendTalkMessage();
    }
//    else
//    {
//        m_blockSize = 0;
//        m_tcpSocket->requestConnect();
//    }
}


//// 
//void IMMainCtrl::sendFlockTalkMessage(TalkMessage & mes)
//{
//    if (NULL == m_tcpSocket)
//        return;
//    if (m_tcpSocket->isConnected())
//    {
//        requestSendFlockTalkMessage(mes);
//    }
//}

//// 
//void IMMainCtrl::sendDiscussionTalkMessage(TalkMessage & mes)
//{
//    if (NULL == m_tcpSocket)
//        return;
//    if (m_tcpSocket->isConnected())
//    {
//        requestSendFlockTalkMessage(mes);
//    }
//}

/*************************************************
Function Name: getFriendInformation
Description: 
*************************************************/
void IMMainCtrl::getFriendInformation(const QString &id)
{
//    m_friendID = id;
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestGetFriendInformation(id);
    }
//    else
//    {
//        m_blockSize = 0;
//        m_tcpSocket->requestConnect();
//    }
}


/*************************************************
Function Name: getMynformation
Description: 
*************************************************/
void IMMainCtrl::getMynformation(const QString &id)
{
    m_myID = id;
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestGetMyInformation();
    }
    else
    {
        m_blockSize = 0;
        m_tcpSocket->requestConnect();
    }
}

/*************************************************
Function Name: changeMyInformation
Description: 
*************************************************/
void IMMainCtrl::changeMyInformation(const UserInformation &me)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestChangeMyInformation(me);
    }
//    else
//    {
//        m_blockSize = 0;
//        m_tcpSocket->requestConnect();
//    }
}


/*************************************************
Function Name: changeMyStatus
Description: 
*************************************************/
void IMMainCtrl::changeMyStatus(const QString id, const int status)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestChangeMyStatus(id, status);
}

/*************************************************
Function Name: changeFriendRemark
Description: 
*************************************************/
void IMMainCtrl::changeFriendRemark(const QString & myID,
                                    const QString & friendID,
                                    const QString & remark)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestChangeFriendRemark(myID, friendID, remark);
}

/*************************************************
Function Name: deleteFriend
Description: 
*************************************************/
void IMMainCtrl::deleteFriend(const QString & myID, const QString & friendID)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestDeleteFriend(myID, friendID);
}

/*************************************************
Function Name: addFriend
Description: 
*************************************************/
void IMMainCtrl::addFriend(const TalkMessage & mes)//const TempStrings & temp)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestAddFriend(mes);
}

/*************************************************
Function Name: addFlock
Description: 
*************************************************/
void IMMainCtrl::addFlock(const TalkMessage & mes)//const TempStrings & temp)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestAddFlock(mes);
}


/*************************************************
Function Name: addDiscussion
Description: 
*************************************************/
void IMMainCtrl::addDiscussion(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestAddDiscussion(mes);
}


/*************************************************
Function Name: dropFlock
Description: 
*************************************************/
void IMMainCtrl::dropFlock(const QString & userID, const QString & flockID)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestDropFlock(userID, flockID);
}

/*************************************************
Function Name: dropFlock
Description: 
*************************************************/
void IMMainCtrl::dropDiscussion(const QString & userID, const QString & discussionID)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestDropDiscussion(userID, discussionID);
}

/*************************************************
Function Name: leaveFlock
Description: 
*************************************************/
void IMMainCtrl::leaveFlock(const QString & userID, const QString & flockID)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestLeaveFlock(userID, flockID);
}

/*************************************************
Function Name: leaveDiscussion
Description: 
*************************************************/
void IMMainCtrl::leaveDiscussion(const QString & userID, const QString & discussionID)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestLeaveDiscussion(userID, discussionID);
}

/*************************************************
Function Name: createFlock
Description: 
*************************************************/
void IMMainCtrl::createFlock(const TempStrings & tmpStr)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestCreateFlock(tmpStr);
}


/*************************************************
Function Name: createDiscussion
Description: 
*************************************************/
void IMMainCtrl::createDiscussion(const TempStrings & tmpStr)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestCreateDiscussion(tmpStr);
}

/*************************************************
Function Name: changeFlockInformation
Description: 
*************************************************/
void IMMainCtrl::changeFlockInformation(const FlockInformation & flock)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestChangeFlockInformation(flock);
}

/*************************************************
Function Name: changeFlockMemberRemark
Description: 
*************************************************/
void IMMainCtrl::changeFlockMemberRemark(const TempStrings & tmpStr)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestChangeFlockMemberRemark(tmpStr);
}



/*************************************************
Function Name: changeDiscussionInformation
Description: 
*************************************************/
void IMMainCtrl::changeDiscussionInformation(const DiscussionInformation & discussion)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestChangeDiscussionInformation(discussion);
}


/*************************************************
Function Name: resultOfFriendRequest
Description: 
*************************************************/
void IMMainCtrl::resultOfFriendRequest(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestSendResultOfFriendRequest(mes);
}


/*************************************************
Function Name: resultOfFlockRequest
Description: 
*************************************************/
void IMMainCtrl::resultOfFlockRequest(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestSendResultOfFlockRequest(mes);
}


/*************************************************
Function Name: removeBox
Description: 
*************************************************/
void IMMainCtrl::removeBox(const QString & title)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestRemoveBox(title);
}


/*************************************************
Function Name: renameBox
Description: 
*************************************************/
void IMMainCtrl::renameBox(const QString & oldTitle, const QString & newTitle)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestRenameBox(oldTitle, newTitle);
}

/*************************************************
Function Name: moveFriendToBox
Description:  
*************************************************/
void IMMainCtrl::moveFriendToBox(const QString &friendID, const QString &oldTitle,
                                 const QString & newTitle)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestMoveFriendToBox(friendID, oldTitle, newTitle);
}



// mark: public slots:---------------------------------------------------
/*************************************************
Function Name: requestGetFriendsInformation()
Description: 
*************************************************/
void IMMainCtrl::requestGetFriendsInformation()
{
    if (NULL == m_tcpSocket)
        return;
    qDebug() << "request friends: " << m_myID;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_ALL_FRIENDS) << m_myID << m_status;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestGetFlocksInformation()
Description: 
*************************************************/
void IMMainCtrl::requestGetFlocksInformation(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    qDebug() << "request Flocks: " << id;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_ALL_FLOCKS) << id;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: requestGetDiscussionsInformation()
Description: 
*************************************************/
void IMMainCtrl::requestGetDiscussionsInformation(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    qDebug() << "request Discussions: " << id;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_ALL_DISCUSSIONS) << id;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestGetFlockMembers()
Description: 
*************************************************/
void IMMainCtrl::requestGetFlockMembers(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    qDebug() << "request flock members: " << id;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_FLOCK_MEMBERS) << id;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestGetDiscussionMembers()
Description: 
*************************************************/
void IMMainCtrl::requestGetDiscussionMembers(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    qDebug() << "request Discussion members: " << id;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_DISCUSSIONS_MEMBERS) << id;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: requestGetFriendInformation()
Description: 
*************************************************/
void IMMainCtrl::requestGetFriendInformation(const QString &id)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_FRIEND_INFORMATION) << id;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: requestGetMyInformation()
Description: 
*************************************************/
void IMMainCtrl::requestGetMyInformation()
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_MYSELF_INFORMATION) << m_myID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: requestChangeMyInformation()
Description: 
*************************************************/
void IMMainCtrl::requestChangeMyInformation(const UserInformation &me)
{
    if (NULL == m_tcpSocket)
        return;

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_INFORMATION) << me;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: requestChangeMyStatus()
Description: 
*************************************************/
void IMMainCtrl::requestChangeMyStatus(const QString id, const int status)
{
    if (NULL == m_tcpSocket)
        return;

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_STATUE) << id << status;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: requestChangeFriendRemark()
Description: 
*************************************************/
void IMMainCtrl::requestChangeFriendRemark(const QString & myID,
                                           const QString & friendID,
                                           const QString &remark)
{
    if (NULL == m_tcpSocket)
        return;

    TempStrings tempStr;
    tempStr.m_one = myID;
    tempStr.m_two = friendID;
    tempStr.m_three = remark;

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_REMARK) << tempStr;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestDeleteFriend()
Description: 
*************************************************/
void IMMainCtrl::requestDeleteFriend(const QString & myID,
                                     const QString & friendID)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(DELETE_FRIEND) << myID << friendID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: requestAddFriend()
Description: 
*************************************************/
void IMMainCtrl::requestAddFriend(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(ADD_FRIEND) << mes;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: requestAddFlock()
Description: 
*************************************************/
void IMMainCtrl::requestAddFlock(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(ADD_FLOCK) << mes;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestAddDiscussion()
Description: 
*************************************************/
void IMMainCtrl::requestAddDiscussion(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(ADD_DISCUSSION) << mes;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: requestDropFlock()
Description: 
*************************************************/
void IMMainCtrl::requestDropFlock(const QString & userID, const QString & flockID)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(DROP_FLOCK) << userID << flockID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestDropDiscussion()
Description: 
*************************************************/
void IMMainCtrl::requestDropDiscussion(const QString & userID, const QString & discussionID)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(DROP_DISCUSSION) << userID << discussionID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: requestLeaveFlock()
Description: 
*************************************************/
void IMMainCtrl::requestLeaveFlock(const QString & userID, const QString & flockID)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(LEAVE_FLOCK) << userID << flockID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestLeaveDiscussion()
Description: 
*************************************************/
void IMMainCtrl::requestLeaveDiscussion(const QString & userID,
                                        const QString & discussionID)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(LEAVE_DISCUSSION) << userID << discussionID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: requestCreateFlock()
Description: 
*************************************************/
void IMMainCtrl::requestCreateFlock(const TempStrings & tmpStr)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CREATE_FLOCK) << tmpStr;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestCreateDiscussion()
Description: 
*************************************************/
void IMMainCtrl::requestCreateDiscussion(const TempStrings & tmpStr)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CREATE_DISCUSSION) << tmpStr;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestSendResultOfFriendRequest
Description: 
*************************************************/
void IMMainCtrl::requestSendResultOfFriendRequest(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(ADD_FRIEND) << mes;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestSendResultOfFriendRequest
Description: 
*************************************************/
void IMMainCtrl::requestSendResultOfFlockRequest(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(ADD_FLOCK) << mes;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}



/*************************************************
Function Name: requestChangeFlockInformation
Description: 
*************************************************/
void IMMainCtrl::requestChangeFlockInformation(const FlockInformation &flock)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_FLOCK) << flock;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestChangeFlockMemberRemark
Description: 
*************************************************/
void IMMainCtrl::requestChangeFlockMemberRemark(const TempStrings & tmpStr)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_FLOCK_REMARK) << tmpStr;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}



/*************************************************
Function Name: requestChangeDiscussionInformation
Description: 
*************************************************/
void IMMainCtrl::requestChangeDiscussionInformation(
        const DiscussionInformation & discussion)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_DISCUSSION) << discussion;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: requestSendTalkMessage
Description: 
*************************************************/
void IMMainCtrl::requestSendTalkMessage()
{
    if (NULL == m_tcpSocket)
        return;

    while (m_messageVector.size() > 0)
    {
        m_blockSize = 0;
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);
        out << quint16(0) << int(TALK)
            << m_messageVector.front();
        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));
        m_tcpSocket->write(block);

        m_messageVector.pop_front();
    }
}


/*************************************************
Function Name: requestRemoveBox
Description: 
*************************************************/
void IMMainCtrl::requestRemoveBox(const QString & title)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(REMOVE_BOX) << m_myID << title;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: requestRenameBox
Description: 
*************************************************/
void IMMainCtrl::requestRenameBox(const QString & oldTitle, const QString & newTitle)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(RENAME_BOX) << m_myID << oldTitle << newTitle;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestMoveFriendToBox
Description:  
*************************************************/
void IMMainCtrl::requestMoveFriendToBox(const QString & friendID,
                                        const QString & oldTitle,
                                        const QString & newTitle)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(MOVE_FRIEND_BOX) << m_myID << friendID << oldTitle << newTitle;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestGetNetWorkHistoryMessageOneFriendOneDate
Description:  
*************************************************/
void IMMainCtrl::requestGetNetWorkHistoryMessageOneFriendOneDate(
        const QString & friendID, const QDate & date)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_HISTORY_MESSAGE) << m_myID << friendID << date;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name: requestChangePwd
Description:  
*************************************************/
void IMMainCtrl::requestChangePwd(const QString & oldPwd, const QString & newPwd)
{
    if (NULL == m_tcpSocket)
        return;

    TempStrings tmpStr;
    tmpStr.m_one = m_myID;
    tmpStr.m_two = oldPwd;
    tmpStr.m_three = newPwd;

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_PASSWORD) << tmpStr;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: readMessage
Description: 
*************************************************/
void IMMainCtrl::readMessage()
{
    if (NULL == m_tcpSocket)
        return;

    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_4_8);
    if (m_blockSize == 0)
    {
        if (m_tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> m_blockSize;
    }

    if (m_tcpSocket->bytesAvailable() < m_blockSize)
        return;
    int type;

    in >> type;
    int len;

    switch (type)
    {
    case NO_FRIEND:
    {
        requestGetFlocksInformation(m_myID);
        break;
    }
    case GET_ALL_FRIENDS_FAIL:
        break;
    case GET_ALL_FRIENDS_SUCCESS:
    {
        in >> len;
        m_friendsVec.clear();
        m_friendsVec.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_friendsVec[i];
        }
        qDebug() << "friends len: " << len;
        emit getFriendsSuccess(m_friendsVec);
        break;
    }
    case NO_FLOCK:
    {
        requestGetDiscussionsInformation(m_myID);
        break;
    }
    case GET_ALL_FLOCKS_FAIL:
    {
        break;
    }
    case GET_ALL_FLOCKS_SUCCESS:
    {
        in >> len;
        m_flocksVec.clear();
        m_flocksVec.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_flocksVec[i];
        }
        qDebug() << "flocks len: " << len;
        emit getFlocksSuccess(m_flocksVec);
        break;
    }
    case NO_DISCUSSION:
    {
        break;
    }
    case GET_ALL_DISCUSSIONS_FAIL:
    {
        break;
    }
    case GET_ALL_DISCUSSIONS_SUCCESS:
    {
        in >> len;
        m_discussionsVec.clear();
        m_discussionsVec.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_discussionsVec[i];
        }
        qDebug() << "discussions len: " << len;
        emit getDiscussionsSuccess(m_discussionsVec);
        break;
    }
    case GET_FLOCK_MEMBERS_SUCCESS:
    {
        in >> len;
        m_flockMembersVec.clear();
        m_flockMembersVec.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_flockMembersVec[i];
        }
        qDebug() << "flock-members len: " << len;
        emit getFlockMembersSuccess(m_flockMembersVec);
        break;
    }
    case GET_DISCUSSION_MEMBERS_SUCCESS:
    {
        in >> len;
        m_discussionMembersVec.clear();
        m_discussionMembersVec.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_discussionMembersVec[i];
        }
        qDebug() << "discussion-members len: " << len;
        emit getDiscussionMembersSuccess(m_discussionMembersVec);
        break;
    }
    case GET_FRIEND_FAIL:
        break;
    case GET_FRIEND_SUCCESS:
    {
        in >> m_friInf;
        emit getFriendInformationSuccess(m_friInf);
        break;
    }
    case GET_MYSELF_FAIL:
    {
        break;
    }
    case GET_MYSELF_SUCCESS:
    {
        in >> m_myInf;
        emit getMyInformationSuccess(m_myInf);
        break;
    }
    case CHANGE_INFORMATION_FAIL:
    {
        QMessageBox::critical(NULL, tr("change self info "), tr("change self info  failed"));
        break;
    }
    case CHANGE_INFORMATION_SUCCESS:
    {
        in >> m_myInf;
        emit changeMyInformationSuccess(m_myInf);
        QMessageBox::information(NULL, tr("change self info "), tr("change self info  successfully"));
        break;
    }
    case TALK:
    {
        in >> m_message;
        emit getFriendTalkMessage(m_message);
        break;
    }
    case CHANGE_STATUE:
    {
        in >> m_peerID >> m_peerStatus;
        emit getFriendChangedStatus(m_peerID, m_peerStatus);
        break;
    }
    case CHANGE_INFORMATION:
    {
        in >> m_friSimInf;
        emit getFriendChangedInformation(m_friSimInf);
        break;
    }
    case CHANGE_REMARK_SUCCESS:
    {
        in >> m_tempStr;
        emit changeFriendRemarkSuccess(m_tempStr);
        break;
    }
    case DELETE_FRIEND_SUCCESS:
    {
        in >> m_id >> m_peerID >> m_groupName;
        emit deleteFriendSuccess(m_id, m_peerID, m_groupName);
        break;
    }
    case DELETE_FRIEND_FAIL:
    {
        break;
    }
    case BE_DELETED:
    {
        in >> m_id >> m_peerID >> m_groupName;

        QString temp = QString(tr("你被好友(%1)delete  了")).arg(m_peerID);
        QMessageBox::information(NULL, tr("消息"), temp);
        emit deleteFriendSuccess(m_id, m_peerID, m_groupName);
        break;
    }
    case ADD_FRIEND:
    {
        in >> m_message >> m_friInf;
        emit getFriendRequest(m_message, m_friInf);
        break;
    }
    case ADD_FLOCK:
    {
        in >> m_message >> m_flockMember >> m_flockInf;
        emit getFlockRequest(m_message, m_flockMember, m_flockInf);
        break;
    }
    case DROP_FLOCK_SUCCESS:
    {
        in >> m_flockID;
        emit dropFlockSuccess(m_flockID);
        break;
    }
    case LEAVE_FLOCK_SUCCESS:
    {
        in >> m_id >> m_flockID >> m_creatorID;
        emit leaveFlockSuccess(m_id, m_flockID, m_creatorID);
        break;
    }
    case LEAVE_FLOCK_MEMBER:
    {
        in >> m_id >> m_flockID >> m_creatorID;
        emit haveMemberleavedFlock(m_id, m_flockID, m_creatorID);
        break;
    }
    case CHANGE_FLOCK_SUCCESS:
    {
        in >> m_flockInf;
        emit changeFlockSuccess(m_flockInf);
        break;
    }
    case CHANGE_FLOCK_REMARK_SUCCESS:
    {
        in >> m_tempStr;
        emit changeFlockRemarkSuccess(m_tempStr);
        break;
    }
    case CREATE_FLOCK_SUCCESS:
    {
        in >> m_flockInf;
        emit createFlockSuccess(m_flockInf);
        break;
    }


    case ADD_DISCUSSION:
    {
        in >> m_message;
        if (ADD_DISCUSSION_SUCCESS == m_message.m_type)
            in >> m_discussionInf;
        else if (NEW_DISCUSSION_MEMBER == m_message.m_type)
            in >> m_discussionMember;

        emit getDiscussionRequest(m_message, m_discussionMember, m_discussionInf);
        break;
    }
    case DROP_DISCUSSION_SUCCESS:
    {
        in >> m_discussionID;
        emit dropDiscussionSuccess(m_discussionID);
        break;
    }
//    case LEAVE_DISCUSSION_SUCCESS:
//    {
//        in >> m_id >> m_discussionID >> m_creatorID;
//        emit leaveDiscussionSuccess(m_id, m_discussionID, m_creatorID);
//        break;
//    }
    case LEAVE_DISCUSSION_MEMBER:
    {
        in >> m_id >> m_discussionID;// >> m_creatorID;
        emit leaveDiscussionSuccess(m_id, m_discussionID);//, m_creatorID);
        break;
    }
    case CHANGE_DISCUSSION_SUCCESS:
    {
        in >> m_discussionInf;
        emit changeDiscussionSuccess(m_discussionInf);
        break;
    }

    case CREATE_DISCUSSION_SUCCESS:
    {
        in >> m_discussionInf;
        emit createDiscussionSuccess(m_discussionInf);
        break;
    }

    case RENAME_BOX_SUCCESS:
    {
        in >> m_id >> m_title >> m_newTitle;
        if (m_id == m_myID)
        {
            emit renameBoxSuccess(m_title, m_newTitle);
        }
        break;
    }

    case MOVE_FRIEND_BOX_SUCCESS:
    {
        in >> m_id >> m_peerID >> m_title >> m_newTitle;
        if (m_id == m_myID)
        {
            emit moveFriendToBoxSuccess(m_peerID, m_title, m_newTitle);
        }
        break;
    }

    case GET_HISTORY_MESSAGE_SUCCESS:
    {
        in >> m_id >> m_peerID >> m_date >> len;
        m_HistoryMessageVector.clear();
        m_HistoryMessageVector.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_HistoryMessageVector[i];
        }
        qDebug() << "history message len: " << len;
        if (m_id == m_myID)
        {
            emit getNetworkHistoryMessagesSuccess(m_peerID, m_date,
                                           m_HistoryMessageVector);
        }
        break;
    }
    case CHANGE_PWD_FAIL:
    {
        QMessageBox::information(NULL, tr("change password"), tr("change password failed！"));
        break;
    }
    case CHANGE_PWD_SUCCESS:
    {
        m_tcpSocket->setFlag(1);
//        if (m_tcpSocket != NULL)
//        {
//            m_tcpSocket->close();
//            m_tcpSocket->deleteLater();
//        }

        QMessageBox::information(NULL, tr("change password"), tr("changed successfully.！please relogin"));
        emit closeWindowSignal();
        IMLoginWidget *loginWidget = new IMLoginWidget;
        loginWidget->show();

//        closeWindow();
        break;
    }

    default:
        break;
    }
//    qDebug() << "size of quint16: " << sizeof(quint16);
//    qDebug() << "m_blockSize: " << m_blockSize;

    m_blockSize = 0;
    QByteArray data = m_tcpSocket->readAll();
    qDebug() << "leaved in socket: " << data.size();
}


/*************************************************
Function Name: closeWindow
Description: close  main 程序
*************************************************/
void IMMainCtrl::closeWindow()
{
    if (m_tcpSocket->flag() == 0)
    {

        QMessageBox::information(NULL, tr("system notify"),
                              tr("please relogin."));
        emit closeWindowSignal();
        IMLoginWidget *loginWidget = new IMLoginWidget;
        loginWidget->show();


    }
}
