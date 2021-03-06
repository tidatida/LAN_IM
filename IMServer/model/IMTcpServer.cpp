/*********************************************
File Name: IMTcpServer.cpp
Author: jet.F.R
Date: 2014.3.10
Description: server class
Changes:
********************************************/

#include "IMTcpServer.h"
#include "model/IMThread.h"

IMTcpServer::IMTcpServer(QObject *parent) :
    QTcpServer(parent)
{
    /* todo: init database */
}

IMTcpServer::~IMTcpServer()
{
}

// mark: public slots:------------------------------------------
/*************************************************
Function Name: clientDisconnected()
Description: 
*************************************************/
void IMTcpServer::clientDisconnected(const QString &id)
{
    if (id.contains(MAIL_ADDRESS_FORMAT))
    {
        m_userMailMap.remove(id);
        emit haveLeftAddress(id);
    }
    else
    {
        m_userMap.remove(id);
        emit haveLeftID(id);
        if (m_database.updateStatus(OFFLINE, id))
            tellFriendsStatusChanged(id, OFFLINE);
    }

//    qDebug() << "userMap-size:" << m_userMap.size();
//    QMapIterator<QString, IMClientSocketCtrl *> i(m_userMap);
//    while (i.hasNext()) {
//        i.next();
//        qDebug() << i.key();
//    }

//    qDebug() << "userMailMap-size:" << m_userMailMap.size();
//    QMapIterator<QString, IMClientSocketCtrl *> j(m_userMailMap);
//    while (j.hasNext()) {
//        j.next();
//        qDebug() << j.key();
//    }
}

/*************************************************
Function Name: sendMessage()
Description: 
*************************************************/
void IMTcpServer::sendMessage(const SaveTmpInformation &save)
{
    m_save.m_requestKind = save.m_requestKind;
    switch (m_save.m_requestKind)
    {
    case LOGIN:
    {
        m_save.m_loginInf = save.m_loginInf;
        m_save.m_clientSocket = save.m_clientSocket; 

        /* logined or not ? */
        m_save.m_myID = save.m_myID;
        if (m_userMap.contains(m_save.m_myID))
            m_save.m_replyKind = HAVE_LOGINED;
        else
        {
            /* db access */
            m_save.m_replyKind = m_database.searchUserInUserInformation(
                        m_save.m_loginInf, m_save.m_userInf);//, m_save.friendsVec);
//            if(LOGIN_SUCCESS == m_save.m_replyKind)
//                changeStatu(m_save.m_loginInf.m_userID, m_save.m_loginInf.m_status);
//                m_userMap.insert(m_save.m_myID, m_save.m_clientSocket);
        }
        save.m_clientSocket->sendMessage(m_save);
        /* change login status */
        //changeStatu(m_save.m_loginInf.m_userID, m_save.m_loginInf.m_status);
        break;
    }
    case REGISTER:
    {
        m_save.m_userInf = save.m_userInf;
//        QDateTime dateTime;
//        dateTime.setDate(QDate::currentDate());
//        int sum = m_database.countRegisteredInPeriod(dateTime, dateTime.addDays(1));

        int sum = m_database.getUserTimes(QDate::currentDate());
        if (0 == sum)
        {
            m_save.m_replyKind = REGISTER_FAIL;
        }
        else
        {
            QString id = QDate::currentDate().toString("yyyyMMdd");
            id.append(QString::number(0));
            id.append(QString::number(sum));
            m_save.m_userInf.m_userID = id;
//            qDebug() << "regDate:" << m_save.m_userInf.m_regDateTime ;
            m_save.m_userInf.m_regDateTime = QDateTime::currentDateTime();
            /* register */
            m_save.m_replyKind = m_database.addUserInUserInformation(m_save.m_userInf);
        }
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case GET_QUESTION_ANSWER:
    {
        m_save.m_myID = save.m_myID;
//        m_save.m_tempStr.m_one = save.m_myID;
        m_save.m_replyKind = m_database.searchQuestionAndAnswer(m_save.m_myID,
                                                                m_save.m_tempStr);
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case CHECK_MESSAGE:
        break;
    case GET_ALL_FRIENDS:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_status = save.m_status;
        m_save.m_clientSocket = save.m_clientSocket;
        
//        m_save.m_replyKind = m_database.searchUserInUserInformation(
//                    m_save.m_loginInf, m_save.m_userInf);//, m_save.friendsVec);
//        QMultiMap<QString, FriendsInfo> *userMap= new QMultiMap<QString, FriendsInfo>;
        m_save.m_replyKind = m_database.searchFriendsInformation(m_save.m_myID,
                                                                 m_save.m_friendsVec);
        save.m_clientSocket->sendMessage(m_save);
        if (GET_ALL_FRIENDS_FAIL != m_save.m_replyKind)
        {
            if (!m_userMap.contains(m_save.m_myID))
            {
                m_userMap.insert(m_save.m_myID, m_save.m_clientSocket);
                emit haveNewID(m_save.m_myID);
            }

            tellFriendsStatusChanged(m_save.m_myID, m_save.m_status);
        }
        break;
    }
    case GET_ALL_FLOCKS:
    {
        m_save.m_myID = save.m_myID;

        /* get group info */ 
        m_save.m_replyKind = m_database.searchFlocksInformation(
                    m_save.m_myID, m_save.m_flocksVec);
        save.m_clientSocket->sendMessage(m_save);
//        if (GET_ALL_FLOCKS_SUCCESS != m_save.m_replyKind)
//            break;


//        m_save.m_replyKind = m_database.searchFlocksMembers(
//                    m_save.m_myID,m_save.m_flocksMembersVec);
//        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case GET_ALL_DISCUSSIONS:
    {
        m_save.m_myID = save.m_myID;

        m_save.m_replyKind = m_database.searchDiscussionsInformation(
                    m_save.m_myID, m_save.m_discussionsVec);
        save.m_clientSocket->sendMessage(m_save);

//        if (GET_ALL_DISCUSSIONS_SUCCESS != m_save.m_replyKind)
//            break;

//        m_save.m_replyKind = m_database.searchDiscussionsMembers(
//                    m_save.m_myID,m_save.m_discussionsMembersVec);
//        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case GET_FLOCK_MEMBERS:
    {
        m_save.m_flockID = save.m_flockID;

        m_save.m_replyKind = m_database.searchFlockMembers(
                    m_save.m_flockID, m_save.m_flockMembersVec);
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case GET_DISCUSSIONS_MEMBERS:
    {
        m_save.m_discussionID = save.m_discussionID;

        m_save.m_replyKind = m_database.searchDiscussionMembers(
                    m_save.m_discussionID, m_save.m_discussionMembersVec);
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case TALK:
    {
        talkRequest(save);
        break;
    }
    case CHANGE_INFORMATION:
    {
        m_save.m_userInf = save.m_userInf;
        m_save.m_replyKind = m_database.updateMyselfInformation(save.m_userInf);
        save.m_clientSocket->sendMessage(m_save);
        if (m_save.m_replyKind == CHANGE_INFORMATION_SUCCESS)
        {
//            if (m_database.searchFriendSimInformation(save.m_friendInf))
                tellFriendsInformationChanged(m_save.m_userInf.m_userID);
        }
        break;
    }
    case GET_MYSELF_INFORMATION:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_replyKind = m_database.searchMyselfInformationByID(
                    m_save.m_myID,
                    m_save.m_userInf);
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case GET_FRIEND_INFORMATION:
    {
        m_save.m_peerID = save.m_peerID;
        m_save.m_replyKind = m_database.searchFriendInformationByID(
                    m_save.m_peerID,
                    m_save.m_userInf);
        save.m_clientSocket->sendMessage(m_save);
        break;
    }

    case DELETE_FRIEND:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_peerID = save.m_peerID;
        m_save.m_replyKind = m_database.deleteFriend(m_save.m_myID,
                                                     m_save.m_peerID,
                                                     m_save.m_groupName,
                                                     m_save.m_groupNameF);
        save.m_clientSocket->sendMessage(m_save);

        /* if friend online, send msg, else store msg */
        QMap<QString, IMClientSocketCtrl*>::iterator iter;
        iter = m_userMap.find(m_save.m_peerID);
        if(m_userMap.end() == iter)
        {
            TalkMessage mes;
            mes.m_type = BE_DELETED;
            mes.m_senderID = save.m_myID;
            mes.m_receiverID = save.m_peerID;
            mes.m_text = save.m_groupNameF;

            /* store offline msg */
            //m_database.messageRequest(save.message);
        }
        else
        {
            m_save.m_myID = save.m_peerID;
            m_save.m_peerID = save.m_myID;
            m_save.m_replyKind = BE_DELETED;
            m_save.m_groupName = m_save.m_groupNameF;
            iter.value()->sendMessage(m_save);
        }
        break;
    }
    case CHANGE_REMARK:
    {
        m_save.m_tempStr = save.m_tempStr;
        m_save.m_replyKind = m_database.updateRemark(save.m_tempStr);
        save.m_clientSocket->sendMessage(m_save);
//        if (m_save.m_replyKind == CHANGE_INFORMATION_SUCCESS)
//        {
//        }
        break;
    }
    case ADD_FRIEND:
    {
        friendRequest(save);
        break;
    }
    case CHANGE_STATUE:
    {
        if (m_database.updateStatus(save.m_status, save.m_myID))
            tellFriendsStatusChanged(save.m_myID, save.m_status);
        break;
    }
    case ADD_FLOCK:
    {
        flockRequest(save);
        break;
    }
    case DROP_FLOCK:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_flockID = save.m_flockID;

        tellMembersFlockDroped(m_save.m_flockID);

        /*m_save.m_replyKind = */
        m_database.deleteFlock(m_save.m_myID, m_save.m_flockID);
//        if (DROP_FLOCK_SUCCESS == m_save.m_replyKind)
//        {

//        }
        break;
    }
    case LEAVE_FLOCK:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_flockID = save.m_flockID;

      //  tellMembersFlockDroped(m_save.m_flockID);

        m_save.m_replyKind =
                m_database.deleteFlockMember(m_save.m_flockID, m_save.m_myID);

        if ( LEAVE_FLOCK_SUCCESS == m_save.m_replyKind)
        {
            if (m_database.searchFlockHost(m_save.m_flockID, m_save.m_peerID))
            {
//                save.m_clientSocket->sendMessage(m_save);

                /* if owner only ,broadcast msg, else store msg */
                QMap<QString, IMClientSocketCtrl*>::iterator iter;
                iter = m_userMap.find(m_save.m_peerID);
                if(m_userMap.end() == iter)
                {
                    TalkMessage mes;
                    mes.m_type = LEAVE_FLOCK_SUCCESS;
                    mes.m_senderID = save.m_myID;
                    mes.m_receiverID = save.m_peerID;
                    // mes.m_text = save.m_groupNameF;
                    //m_database.messageRequest(save.message);
                }
                else
                {
//                    TalkMessage mes;
//                    mes.m_type = LEAVE_FLOCK_SUCCESS;
//                    mes.m_senderID = save.m_myID;
//                    mes.m_receiverID = save.m_myID;
                    iter.value()->sendMessage(m_save);
                }

//                QMap<QString, IMClientSocketCtrl*>::iterator iter;
                iter = m_userMap.find(m_save.m_myID);
                if(m_userMap.end() == iter)
                {
                    TalkMessage mes;
                    mes.m_type = LEAVE_FLOCK_SUCCESS;
                    mes.m_senderID = save.m_myID;
                    mes.m_receiverID = save.m_peerID;
//                    mes.m_text = save.m_groupNameF;
                    //m_database.messageRequest(save.message);
                }
                else
                {
//                    TalkMessage mes;
//                    mes.m_type = LEAVE_FLOCK_SUCCESS;
//                    mes.m_senderID = save.m_myID;
//                    mes.m_receiverID = save.m_myID;
                    iter.value()->sendMessage(m_save);
                }


            }
//            tellFlockMemberHaveLeavedMember(m_save.m_flockID);

            tellFlockMemberHaveLeavedMember(m_save.m_flockID);
        }
//        save.m_clientSocket->sendMessage(m_save);


        break;
    }

    case CHANGE_FLOCK:
    {
        m_save.m_flockInf = save.m_flockInf;
        m_save.m_replyKind = m_database.updateFlockInformation(m_save.m_flockInf);
        if (CHANGE_FLOCK_SUCCESS == m_save.m_replyKind)
        {
            tellMembersFlockChanged(m_save.m_flockInf);
        }
        break;
    }
    case CHANGE_FLOCK_REMARK:
    {
        m_save.m_tempStr = save.m_tempStr;
        m_save.m_replyKind = m_database.updateFlockMemberRemark(m_save.m_tempStr);
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case CREATE_FLOCK:
    {
        m_save.m_tempStr = save.m_tempStr;
        QString flockID;
        m_save.m_replyKind = m_database.addFlock(m_save.m_tempStr, flockID);
        if (CREATE_FLOCK_SUCCESS == m_save.m_replyKind)
        {
            m_database.searchFlockInformation(flockID, m_save.m_flockInf);
        }
            save.m_clientSocket->sendMessage(m_save);
        break;
    }

    case ADD_DISCUSSION:
    {
        discussionRequest(save);
        break;
    }
    case DROP_DISCUSSION:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_discussionID = save.m_discussionID;

        tellMembersDiscussionDroped(m_save.m_discussionID);

        /*m_save.m_replyKind = */
        m_database.deleteDiscussion(m_save.m_myID, m_save.m_discussionID);
//        if (DROP_FLOCK_SUCCESS == m_save.m_replyKind)
//        {

//        }
        break;
    }
    case LEAVE_DISCUSSION:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_discussionID = save.m_discussionID;

      //  tellMembersFlockDroped(m_save.m_flockID);

        m_save.m_replyKind  =  m_database.deleteDiscussionMember(m_save.m_discussionID,
                                                           m_save.m_myID);

        if ( LEAVE_DISCUSSION_SUCCESS == m_save.m_replyKind)
        {

            {
            #if 0
////                save.m_clientSocket->sendMessage(m_save);

//                QMap<QString, IMClientSocketCtrl*>::iterator iter;
//                iter = m_userMap.find(m_save.m_peerID);
//                if(m_userMap.end() == iter)
//                {
//                    TalkMessage mes;
//                    mes.m_type = LEAVE_DISCUSSION_SUCCESS;
//                    mes.m_senderID = save.m_myID;
//                    mes.m_receiverID = save.m_peerID;
////                    mes.m_text = save.m_groupNameF;
//                    //m_database.messageRequest(save.message);
//                }
//                else
//                {
////                    TalkMessage mes;
////                    mes.m_type = LEAVE_FLOCK_SUCCESS;
////                    mes.m_senderID = save.m_myID;
////                    mes.m_receiverID = save.m_myID;
//                    iter.value()->sendMessage(m_save);
//                }

////                QMap<QString, IMClientSocketCtrl*>::iterator iter;
////                iter = m_userMap.find(m_save.m_myID);
////                if(m_userMap.end() == iter)
////                {
////                    TalkMessage mes;
////                    mes.m_type = LEAVE_DISCUSSION_SUCCESS;
////                    mes.m_senderID = save.m_myID;
////                    mes.m_receiverID = save.m_peerID;
//////                    mes.m_text = save.m_groupNameF;
////                    //m_database.messageRequest(save.message);
////                }
////                else
//                {
////                    TalkMessage mes;
////                    mes.m_type = LEAVE_FLOCK_SUCCESS;
////                    mes.m_senderID = save.m_myID;
////                    mes.m_receiverID = save.m_myID;
//                    iter.value()->sendMessage(m_save);
//                }
//            }
            #endif
            }
            m_save.m_replyKind = LEAVE_DISCUSSION_MEMBER;

//            QMap<QString, IMClientSocketCtrl*>::iterator iter;
//            iter = m_userMap.find(m_save.m_myID);
//            if(m_userMap.end() != iter)
//                iter.value()->sendMessage(m_save);
            tellDiscussionMemberHaveLeavedMember(m_save.m_discussionID);

        }
//        TalkMessage mes;
//        mes.m_type = LEAVE_DISCUSSION_SUCCESS;
//        mes.m_senderID = save.m_myID;
//        mes.m_receiverID = save.m_peerID;
//        save.m_clientSocket->sendMessage(m_save);

        save.m_clientSocket->sendMessage(m_save);

        break;
    }

    case CHANGE_DISCUSSION:
    {
        m_save.m_discussionInf = save.m_discussionInf;
        m_save.m_replyKind = m_database.updateDiscussionInformation(m_save.m_discussionInf);
        if (CHANGE_DISCUSSION_SUCCESS == m_save.m_replyKind)
        {
            tellMembersDiscussionChanged(m_save.m_discussionInf);
        }
        break;
    }
    case CREATE_DISCUSSION:
    {
        m_save.m_tempStr = save.m_tempStr;
        QString discussionID;
        m_save.m_replyKind = m_database.addDiscussion(m_save.m_tempStr, discussionID);
        if (CREATE_DISCUSSION_SUCCESS == m_save.m_replyKind)
        {
            m_database.searchDiscussionInformation(discussionID, m_save.m_discussionInf);
        }
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case GET_IN_MAILS:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_replyKind = m_database.searchInMails(m_save.m_myID, m_save.m_inMailsVec);
        save.m_clientSocket->sendMessage(m_save);
        if (GET_IN_MAILS_SUCCESS == m_save.m_replyKind)
        {
            QString mailAddress =  save.m_myID;
            mailAddress.append(MAIL_ADDRESS_FORMAT);
            if (m_userMailMap.contains(mailAddress))
            {
                qDebug() << "have connected:" << mailAddress;
            }
            else
            {
                m_userMailMap.insert(mailAddress, save.m_clientSocket);
                emit haveNewAddress(mailAddress);
            }
        }
        break;
    }
    case GET_OUT_MAILS:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_replyKind = m_database.searchOutMails(m_save.m_myID, m_save.m_outMailsVec);
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case DELETE_IN_MAIL:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_mailID = save.m_mailID;
        m_save.m_replyKind = m_database.deleteInMail(m_save.m_myID, m_save.m_mailID);
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case DELETE_OUT_MAIL:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_mailID = save.m_mailID;
        m_save.m_replyKind = m_database.deleteOutMail(m_save.m_myID, m_save.m_mailID);
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case SEND_MAIL:
    {
        m_save.m_mail = save.m_mail;
        m_save.m_replyKind = m_database.insertMail(m_save.m_mail);

        save.m_clientSocket->sendMessage(m_save);
//        if (m_database.searchMail(m_save.m_mail.))
//        {
//            return;
//        }
        if (m_save.m_replyKind == SEND_MAIL_SUCCESS)
        {
            QString mailAddress =  m_save.m_mail.m_receiverAddress;
            mailAddress.append(MAIL_ADDRESS_FORMAT);

            QMap<QString, IMClientSocketCtrl*>::iterator iter;
            iter = m_userMailMap.find(mailAddress);
            if(m_userMailMap.end() != iter)
            {
                m_save.m_replyKind = RECEIVE_MAIL;
                iter.value()->sendMessage(m_save);
            }
        }
        break;
    }
    case SET_MAIL_READ:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_mailID = save.m_mailID;
        m_save.m_replyKind = m_database.setMailRead(m_save.m_myID, m_save.m_mailID);
//        save.m_clientSocket->sendMessage(m_save);
        break;
    }

    case REMOVE_BOX:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_title = save.m_title;
        break;
    }
    case CREATE_BOX:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_title = save.m_title;
        break;
    }
    case MOVE_FRIEND_BOX:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_title = save.m_title;
        m_save.m_peerID = save.m_peerID;
        m_save.m_newTitle = save.m_newTitle;
        m_save.m_replyKind = m_database.moveFriendToGroup(
                    m_save.m_myID, m_save.m_peerID,
                    m_save.m_title, m_save.m_newTitle);
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case RENAME_BOX:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_title = save.m_title;
        m_save.m_newTitle = save.m_newTitle;
        m_save.m_replyKind = m_database.renameGroup(
                    m_save.m_myID, m_save.m_title, m_save.m_newTitle);
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case GET_HISTORY_MESSAGE:
    {
        m_save.m_myID = save.m_myID;
        m_save.m_peerID = save.m_peerID;
        m_save.m_date = save.m_date;
        m_save.m_replyKind = m_database.searchHistoryMessageOneFriendOneDate(
                    m_save.m_myID, m_save.m_peerID,
                    m_save.m_date, m_save.m_historyMessageVec);
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    case CHANGE_PASSWORD:
    {
        m_save.m_tempStr = save.m_tempStr;
        m_save.m_replyKind = m_database.updatePassword(m_save.m_tempStr);
        save.m_clientSocket->sendMessage(m_save);
        break;
    }
    default:
        break;
    }
}

// mark: private---------------------------------------------------
/*************************************************
Function Name: incomingConnection()
Description: 
Input: int socketDescriptor:socket
Output:NULL
Changes: NULL
*************************************************/
void IMTcpServer::incomingConnection(qintptr socketDescriptor)
{
//    IMClientSocket *socket = new IMClientSocket(this);
//    socket->setSocketDescriptor(socketDescriptor);
//    connect(this, SIGNAL(readyRead()), this, SLOT(readMessage()));
//    qDebug("new");
//    IMThread *thread = new IMThread(this, socketDescriptor);
//    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

//    //connect(thread, SIGNAL(finished()), this, SLOT(deleteSocketFormMap()));
//    //connect(thread, SIGNAL())
//    thread->start();

    qDebug() << "asdfas";

    IMClientSocketCtrl *clientSocket = new IMClientSocketCtrl(this);
    clientSocket->setSocketDescriptor(socketDescriptor);
    connect(clientSocket, SIGNAL(deleteSignal(const QString &)),
        this, SLOT(clientDisconnected(const QString &)));
    connect(clientSocket, SIGNAL(sendSignal(const SaveTmpInformation &)),
        this, SLOT(sendMessage(const SaveTmpInformation &)));

    qDebug() <<"new client IP:" << clientSocket->peerAddress();

    qDebug() << "userMap-size:" << m_userMap.size();
//    QMapIterator<QString, IMClientSocketCtrl *> i(m_userMap);
//    while (i.hasNext()) {
//        i.next();
//        qDebug() << i.key();
//    }

//    qDebug() << "userMailMap-size:" << m_userMailMap.size();
//    QMapIterator<QString, IMClientSocketCtrl *> j(m_userMailMap);
//    while (j.hasNext()) {
//        j.next();
//        qDebug() << j.key();
//    }
}

/*************************************************
Function Name: friendRequest()
Description:
*************************************************/
void IMTcpServer::friendRequest(const SaveTmpInformation &save)
{
    m_save.m_replyKind = ADD_FRIEND;
    m_save.m_message = save.m_message;
    switch (save.m_message.m_type)
    {
    case REQUEST_FRIEND:
    {
        if (GET_FRIEND_SUCCESS != m_database.searchFriendInformationByID(
                 m_save.m_message.m_senderID, m_save.m_userInf))
        {
            return;
        }
        qDebug() << "request add friend";
        break;
    }
    case REFUSE_FRIEND:
        qDebug() << "refuse add friend";
        break;
    case AGREE_FRIEND:
    {
        if (!m_database.addFriend(m_save.m_message))
        {
            m_save.m_message.m_type = ADD_FRIEND_FAIL;
            break;
        }

        m_save.m_message.m_senderID = save.m_message.m_receiverID;
        m_save.m_message.m_receiverID = save.m_message.m_senderID;
        if (GET_FRIEND_SUCCESS != m_database.searchFriendInformationByID(
                 m_save.m_message.m_senderID, m_save.m_userInf))
        {
            return;
        }
        save.m_clientSocket->sendMessage(m_save);

        m_save.m_message.m_senderID = save.m_message.m_senderID;
        m_save.m_message.m_receiverID = save.m_message.m_receiverID;
        if (GET_FRIEND_SUCCESS != m_database.searchFriendInformationByID(
                 m_save.m_message.m_senderID, m_save.m_userInf))
        {
            m_save.m_message.m_type = ADD_FRIEND_FAIL;
            return;
        }
        qDebug() << "agree add friend";


        break;
    }
    default:
        return;
    }
//    m_save.m_replyKind = m_database.addFriend(m_save.m_message);
//    save.m_clientSocket->sendMessage(m_save);

    QMap<QString, IMClientSocketCtrl*>::iterator iter;
    iter = m_userMap.find(m_save.m_message.m_receiverID);
    if(m_userMap.end() == iter)
    {
        //m_database.messageRequest(save.message);
    }
    else
        iter.value()->sendMessage(m_save);
}


/*************************************************
Function Name: flockRequest()
Description: 
*************************************************/
void IMTcpServer::flockRequest(const SaveTmpInformation & save)
{
    m_save.m_replyKind = ADD_FLOCK;
    m_save.m_message = save.m_message;
    switch (save.m_message.m_type)
    {
    case REQUEST_FLOCK:
    {
        if (!m_database.searchFlockHost(m_save.m_message.m_receiverID,
                                        m_save.m_peerID))
        {
            return;
        }
        qDebug() << "request user add flock";
        break;
    }
    case FLOCK_REQUEST:
    {
        m_save.m_peerID = m_save.m_message.m_receiverID;
        break;
    }
    case FLOCK_REFUSE:
        m_save.m_peerID = m_save.m_message.m_receiverID;
        qDebug() << "refuse user add flock";
        break;
    case FLOCK_AGREE:
    {
        if (!m_database.addFlockMember(m_save.m_message.m_senderID,
                                       m_save.m_message.m_receiverID))
        {
            m_save.m_message.m_type = ADD_FLOCK_FAIL;
            break;
        }
//-----------------------------------------
        m_save.m_message.m_senderID = save.m_message.m_receiverID;
        m_save.m_message.m_receiverID = save.m_message.m_senderID;

        if (!m_database.searchFlockMember(m_save.m_message.m_receiverID,
                                          m_save.m_message.m_senderID,
                                          m_save.m_flockMember))
        {
            return;
        }

        if (!m_database.searchFlockInformation(
                    m_save.m_message.m_receiverID, m_save.m_flockInf))
        {
            m_save.m_message.m_type = ADD_FLOCK_FAIL;
            return;
        }

        m_save.m_message.m_type = AGREE_FLOCK;
        save.m_clientSocket->sendMessage(m_save);

        tellFlockMemberHaveNewMember(m_save.m_flockInf.m_flockID);

//-----------------------------------------
        m_save.m_message.m_type = FLOCK_AGREE;
        m_save.m_message.m_senderID = save.m_message.m_senderID;
        m_save.m_message.m_receiverID = save.m_message.m_receiverID;
        m_save.m_peerID = m_save.m_message.m_receiverID;
        qDebug() << "agree user add flock";

        break;
    }
    case AGREE_FLOCK:
    {
        if (!m_database.searchFlockHost(m_save.m_message.m_receiverID,
                                        m_save.m_peerID))
        {
            return;
        }

        if (!m_database.addFlockMember(m_save.m_message.m_receiverID,
                                       m_save.m_message.m_senderID))
        {
            m_save.m_message.m_type = ADD_FLOCK_FAIL;
            return;
        }

        if (!m_database.searchFlockMember(m_save.m_message.m_receiverID,
                                          m_save.m_message.m_senderID,
                                          m_save.m_flockMember))
        {
            return;
        }

        if (!m_database.searchFlockInformation(
                    m_save.m_message.m_receiverID, m_save.m_flockInf))
        {
            m_save.m_message.m_type = ADD_FLOCK_FAIL;
            return;
        }

        m_save.m_message.m_type = FLOCK_AGREE;
        m_save.m_message.m_senderID = save.m_message.m_receiverID;
        m_save.m_message.m_receiverID = save.m_message.m_senderID;
        save.m_clientSocket->sendMessage(m_save);

        tellFlockMemberHaveNewMember(m_save.m_flockInf.m_flockID);

        m_save.m_message.m_type = AGREE_FLOCK;
        m_save.m_message.m_senderID = save.m_message.m_senderID;     
        m_save.m_message.m_receiverID = save.m_message.m_receiverID; 

        break;
    }
    case REFUSE_FLOCK:
    {
        break;
    }
    default:
        return;
    }

    QMap<QString, IMClientSocketCtrl*>::iterator iter;
    iter = m_userMap.find(m_save.m_peerID);
    if(m_userMap.end() == iter)
    {
        //m_database.messageRequest(save.message);
    }
    else
        iter.value()->sendMessage(m_save);
}


/*************************************************
Function Name: flockRequest()
Description: 
*************************************************/
void IMTcpServer::discussionRequest(const SaveTmpInformation & save)
{
    m_save.m_replyKind = ADD_DISCUSSION;
    m_save.m_message = save.m_message;

    if (ADD_DISCUSSION != m_save.m_message.m_type)
        return;

    if (!m_database.addDiscussionMember(m_save.m_message.m_senderID,
                                   m_save.m_message.m_receiverID))
    {
        m_save.m_message.m_type = ADD_DISCUSSION_FAIL;
        save.m_clientSocket->sendMessage(m_save);
        return;
    }

    if (m_database.searchDiscussionInformation(
                m_save.m_message.m_senderID, m_save.m_discussionInf))
    {
        m_save.m_message.m_type = ADD_DISCUSSION_SUCCESS;
        QMap<QString, IMClientSocketCtrl*>::iterator iter;
        iter = m_userMap.find(m_save.m_message.m_receiverID);
        if(m_userMap.end() != iter)
            iter.value()->sendMessage(m_save);
    }


    if (m_database.searchDiscussionMember(m_save.m_message.m_senderID,
                                      m_save.m_message.m_receiverID,
                                      m_save.m_discussionMember))
    {
        int replyKind = m_database.searchDiscussionMembers(m_save.m_message.m_senderID,
                                                           m_save.m_discussionMembersVec);
        if (GET_DISCUSSION_MEMBERS_SUCCESS == replyKind)
        {
//             m_save.m_replyKind
            m_save.m_message.m_type = NEW_DISCUSSION_MEMBER;
            QMap<QString, IMClientSocketCtrl*>::iterator iter;
            for(int i=0; i<m_save.m_discussionMembersVec.size(); ++i)
            {
                if (m_save.m_discussionMembersVec[i].m_userID.
                        compare(m_save.m_message.m_receiverID) == 0)
                    continue;

                iter = m_userMap.find(m_save.m_discussionMembersVec[i].m_userID);
                if(m_userMap.end() != iter)
                    iter.value()->sendMessage(m_save);
            }
        }
    }


}

/*************************************************
Function Name: talkRequest()
Description:
*************************************************/
void IMTcpServer::talkRequest(const SaveTmpInformation & save)
{
    m_save.m_message = save.m_message;
    switch (m_save.m_message.m_type)
    {
    case TALK_MESSAGE:// == m_save.m_message.m_type)
    {
        m_save.m_replyKind = TALK;
        QMap<QString, IMClientSocketCtrl*>::iterator iter;
        iter = m_userMap.find(m_save.m_message.m_receiverID);

        m_database.addHistoryMessage(m_save.m_message);

        if(m_userMap.end() == iter)
        {
            //m_database.messageRequest(m_save.message);
            m_database.addOfflineMessage(m_save.m_message);
        }
        else
            iter.value()->sendMessage(m_save);
        break;
    }

    case REQUEST_FILE:
    case REFUSE_FILE:
    case REQUEST_VIDEO:
    {
        m_save.m_replyKind = TALK;
        QMap<QString, IMClientSocketCtrl*>::iterator iter;
        iter = m_userMap.find(m_save.m_message.m_receiverID);
        if(m_userMap.end() != iter)
        {
            //m_save.m_message.m_receiverIP =  iter.value()->peerAddress();
            iter.value()->sendMessage(m_save);
        }
        break;
    }

    case TALK_FLOCK:
    {
        m_save.m_replyKind = m_database.searchFlockMembers(m_save.m_message.m_receiverID,
                                                           m_save.m_flockMembersVec);
        if (GET_FLOCK_MEMBERS_SUCCESS == m_save.m_replyKind)
        {
             m_save.m_replyKind = TALK;
            QMap<QString, IMClientSocketCtrl*>::iterator iter;
            for(int i=0; i<m_save.m_flockMembersVec.size(); ++i)
            {
                iter = m_userMap.find(m_save.m_flockMembersVec[i].m_userID);
                if(m_userMap.end() == iter)
                {
                    //m_database.messageRequest(save.message);
                }
                else
                    iter.value()->sendMessage(m_save);
            }
        }
        break;
    }

    case TALK_DISCUSSION:
    {
        m_save.m_replyKind = m_database.searchDiscussionMembers(m_save.m_message.m_receiverID,
                                                           m_save.m_discussionMembersVec);
        if (GET_DISCUSSION_MEMBERS_SUCCESS == m_save.m_replyKind)
        {
             m_save.m_replyKind = TALK;
            QMap<QString, IMClientSocketCtrl*>::iterator iter;
            for(int i=0; i<m_save.m_discussionMembersVec.size(); ++i)
            {
                iter = m_userMap.find(m_save.m_discussionMembersVec[i].m_userID);
                if(m_userMap.end() == iter)
                {
                    //m_database.messageRequest(save.message);
                }
                else
                    iter.value()->sendMessage(m_save);
            }
        }
        break;
    }

    default:
        break;
    }
}

/*************************************************
Function Name: changeStatu()
Description:
*************************************************/
void IMTcpServer::tellFriendsStatusChanged(const QString &id, int status)
{
    m_save.m_replyKind = CHANGE_STATUE;
    m_save.m_status = status;
    m_save.m_peerID = id;
    m_database.searchFriendsID(id, m_save.m_IDVec);

    QMap<QString, IMClientSocketCtrl*>::iterator iter;
    for(int i=0; i<m_save.m_IDVec.size(); ++i)
    {
        iter = m_userMap.find(m_save.m_IDVec[i]);
        if(iter != m_userMap.end())
        {
            iter.value()->sendMessage(m_save);
        }
    }
}

/*************************************************
Function Name: tellFriendsInformationChanged()
Description:
*************************************************/
void IMTcpServer::tellFriendsInformationChanged(const QString & id)
//                                                const FriendInformation &fri)
{
    m_save.m_replyKind = CHANGE_INFORMATION;
//    m_save.m_friendInf = fri;
    if (!m_database.searchFriendsID(id, m_save.m_IDVec))
        return;
    m_save.m_friendInf.m_headPortrait = m_save.m_userInf.m_headPortrait;
    m_save.m_friendInf.m_userID = m_save.m_userInf.m_userID;
    m_save.m_friendInf.m_nickname = m_save.m_userInf.m_nickname;
//    m_save.m_friendInf.m_groupName =
//    m_save.m_friendInf.m_remarkName =
    m_save.m_friendInf.m_status = m_save.m_userInf.m_status;

    QMap<QString, IMClientSocketCtrl*>::iterator iter;
    for(int i=0; i<m_save.m_IDVec.size(); ++i)
    {
        iter = m_userMap.find(m_save.m_IDVec[i]);
        if(iter != m_userMap.end())
        {
            iter.value()->sendMessage(m_save);
        }
    }
}


/*************************************************
Function Name: tellMembersFlockDroped()
Description:
*************************************************/
void IMTcpServer::tellMembersFlockDroped(const QString & flockID)
{
    m_save.m_replyKind = m_database.searchFlockMembers(flockID,
                                                       m_save.m_flockMembersVec);
    if (GET_FLOCK_MEMBERS_SUCCESS == m_save.m_replyKind)
    {
         m_save.m_replyKind = DROP_FLOCK_SUCCESS;
         m_save.m_flockID = flockID;
        QMap<QString, IMClientSocketCtrl*>::iterator iter;
        for(int i=0; i<m_save.m_flockMembersVec.size(); ++i)
        {
            iter = m_userMap.find(m_save.m_flockMembersVec[i].m_userID);
//                if(iter != m_userMap.end())
//                {
//                    iter.value()->sendMessage(m_save);
//                }
            if(m_userMap.end() == iter)
            {
                //m_database.messageRequest(save.message);
            }
            else
                iter.value()->sendMessage(m_save);
        }
    }


}



/*************************************************
Function Name: tellMembersDiscussionDroped()
Description:
*************************************************/
void IMTcpServer::tellMembersDiscussionDroped(const QString & discussionID)
{
    m_save.m_replyKind = m_database.searchDiscussionMembers(discussionID,
                                                       m_save.m_discussionMembersVec);
    if (GET_DISCUSSION_MEMBERS_SUCCESS == m_save.m_replyKind)
    {
         m_save.m_replyKind = DROP_DISCUSSION_SUCCESS;
         m_save.m_discussionID = discussionID;
        QMap<QString, IMClientSocketCtrl*>::iterator iter;
        for(int i=0; i<m_save.m_discussionMembersVec.size(); ++i)
        {
            iter = m_userMap.find(m_save.m_discussionMembersVec[i].m_userID);
//                if(iter != m_userMap.end())
//                {
//                    iter.value()->sendMessage(m_save);
//                }
            if(m_userMap.end() == iter)
            {
                //m_database.messageRequest(save.message);
            }
            else
                iter.value()->sendMessage(m_save);
        }
    }
}

/*************************************************
Function Name: tellMembersFlockChanged()
Description:
*************************************************/
void IMTcpServer::tellMembersFlockChanged(const FlockInformation & flock)
{
    int kind = m_database.searchFlockMembers(flock.m_flockID,
                                             m_save.m_flockMembersVec);
    if (GET_FLOCK_MEMBERS_SUCCESS == kind)
    {
        QMap<QString, IMClientSocketCtrl*>::iterator iter;
        for(int i=0; i<m_save.m_flockMembersVec.size(); ++i)
        {
            iter = m_userMap.find(m_save.m_flockMembersVec[i].m_userID);
            if(iter != m_userMap.end())
            {
                iter.value()->sendMessage(m_save);
            }
        }
    }
}



/*************************************************
Function Name: tellMembersDiscussionChanged()
Description:  
*************************************************/
void IMTcpServer::tellMembersDiscussionChanged(const DiscussionInformation & discussion)
{
    int kind = m_database.searchDiscussionMembers(discussion.m_discussionID,
                                             m_save.m_discussionMembersVec);
    if (GET_DISCUSSION_MEMBERS_SUCCESS == kind)
    {
        QMap<QString, IMClientSocketCtrl*>::iterator iter;
        for(int i=0; i<m_save.m_discussionMembersVec.size(); ++i)
        {
            iter = m_userMap.find(m_save.m_discussionMembersVec[i].m_userID);
            if(iter != m_userMap.end())
            {
                iter.value()->sendMessage(m_save);
            }
        }
    }
}


/*************************************************
Function Name: tellFlockMemberHaveNewMember()
Description:  
*************************************************/
void IMTcpServer::tellFlockMemberHaveNewMember(const QString & flockID)
{
    int replyKind = m_database.searchFlockMembers(flockID,
                                                       m_save.m_flockMembersVec);
    if (GET_FLOCK_MEMBERS_SUCCESS == replyKind)
    {
//         m_save.m_replyKind = ADD_FLOCK;
//         m_save.m_flockID = flockID;
        m_save.m_message.m_type = NEW_FLOCK_MEMBER;

        QMap<QString, IMClientSocketCtrl*>::iterator iter;
        for(int i=0; i<m_save.m_flockMembersVec.size(); ++i)
        {
            if (m_save.m_flockMembersVec[i].m_userID.compare(m_save.m_flockMember.m_userID) == 0)
                continue;
            if (m_save.m_flockMembersVec[i].m_userID.compare(m_save.m_flockInf.m_creatorID) == 0)
                continue;

            iter = m_userMap.find(m_save.m_flockMembersVec[i].m_userID);
            if(m_userMap.end() == iter)
            {
                //m_database.messageRequest(save.message);
            }
            else
                iter.value()->sendMessage(m_save);
        }
    }
}



/*************************************************
Function Name: tellFlockMemberHaveLeavedMember()
Description:  
*************************************************/
void IMTcpServer::tellFlockMemberHaveLeavedMember(const QString & flockID)
{
    int replyKind = m_database.searchFlockMembers(flockID,  m_save.m_flockMembersVec);
    if (GET_FLOCK_MEMBERS_SUCCESS == replyKind)
    {
//         m_save.m_replyKind = ADD_FLOCK;
//         m_save.m_flockID = flockID;
        m_save.m_replyKind = LEAVE_FLOCK_MEMBER;

        QMap<QString, IMClientSocketCtrl*>::iterator iter;
        for(int i=0; i<m_save.m_flockMembersVec.size(); ++i)
        {
//            if (m_save.m_flockMembersVec[i].m_userID.compare(m_save.m_flockMember.m_userID) == 0)
//                continue;
            if (m_save.m_flockMembersVec[i].m_userID.compare(m_save.m_peerID) == 0)
                continue;

            iter = m_userMap.find(m_save.m_flockMembersVec[i].m_userID);
            if(m_userMap.end() != iter)
                iter.value()->sendMessage(m_save);
        }
    }
}


/*************************************************
Function Name: tellDiscussionMemberHaveNewMember()
Description:  
*************************************************/
void IMTcpServer::tellDiscussionMemberHaveNewMember(const QString & discussionID)
{
}


/*************************************************
Function Name: tellDiscussionMemberHaveLeavedMember()
Description:  
*************************************************/
void IMTcpServer::tellDiscussionMemberHaveLeavedMember(const QString & discussionID)
{
    int replyKind = m_database.searchDiscussionMembers(m_save.m_message.m_senderID,
                                                       m_save.m_discussionMembersVec);
    if (GET_DISCUSSION_MEMBERS_SUCCESS == replyKind)
    {
        m_save.m_replyKind = LEAVE_DISCUSSION_MEMBER;
/*        m_save.m_message.m_type */
        QMap<QString, IMClientSocketCtrl*>::iterator iter;
        for(int i=0; i<m_save.m_discussionMembersVec.size(); ++i)
        {
            iter = m_userMap.find(m_save.m_discussionMembersVec[i].m_userID);
            if(m_userMap.end() != iter)
                iter.value()->sendMessage(m_save);
        }
    }
}

/*
    enum ConnectionType {
        AutoConnection,
        DirectConnection,
        QueuedConnection,
        AutoCompatConnection,
        BlockingQueuedConnection,
        UniqueConnection =  0x80
    };
    */
