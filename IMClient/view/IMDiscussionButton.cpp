#include "IMDiscussionButton.h"
#include "model/IMConstant.h"
#include <QMenu>
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include "IMMainWidget.h"
#include "IMDiscussionChatWidget.h"
#include "control/IMMainCtrl.h"

IMDiscussionButton::IMDiscussionButton(const DiscussionInformation &info,
                                       IMMainWidget *mainWidget,
                                       QWidget *parent) :
    QPushButton(parent)
{
    m_discussionInfo = info;
    m_mainWidget = mainWidget;

    if (m_mainWidget == NULL)
        return;
    m_mainCtrl = m_mainWidget->getMainCtrl();
    m_isOpen = false;
     m_isShow = false;

    QHBoxLayout *layout = new QHBoxLayout;

    m_labelHead = new QLabel;
    m_labelHead->setFixedSize(HEAD_SMALL_SIZE, HEAD_SMALL_SIZE);
    m_labelMes = new QLabel;

    layout->addWidget(m_labelHead);
    layout->addWidget(m_labelMes);
    layout->addStretch();
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);
    setMinimumSize(100,40);

    m_menu = NULL;
    setButtonStatus();
    creatMenu();
    setStyleSheet("QPushButton{border: 0;}");
}



IMDiscussionButton::~IMDiscussionButton()
{
}

/*************************************************
Function Name: openChatRoom()
Description: 
*************************************************/
void IMDiscussionButton::openChatRoom()
{
    if (m_mainWidget == NULL)
        return;

    if(m_isOpen)
    {
//        qDebug() << "discussion room opened";
//        m_discussionRoom->raise();
//        m_discussionRoom->activateWindow();
//        m_discussionRoom->show();
        return;
    }
    m_isOpen = true;

    IMDiscussionChatWidget *chatRoom = new IMDiscussionChatWidget(m_discussionInfo,
                                                                  m_mainWidget);
    m_discussionRoom = chatRoom;

    m_mainWidget->insertDiscussionRoomMap(m_discussionInfo.m_discussionID, chatRoom);
    connect(chatRoom, SIGNAL(sendMessagesFromChat(TalkMessage &)),
            m_mainWidget, SLOT(receiveMessagesFromChat(TalkMessage &)));
    connect(chatRoom, SIGNAL(roomQuitSignal()),  this, SLOT(chatRoomQuit()));

    qDebug() << m_discussionInfo.m_discussionName << "request discussion members";
    m_mainCtrl->getDiscussionMembers(m_discussionInfo.m_discussionID);
    connect(m_mainCtrl, SIGNAL(getDiscussionMembersSuccess(QVector<DiscussionMember>)),
            this, SLOT(setDiscussionMemberList(QVector<DiscussionMember>)));
    connect(m_mainCtrl, SIGNAL(getDiscussionMembersSuccess(QVector<DiscussionMember>)),
            chatRoom, SLOT(setDiscussionMemberList(QVector<DiscussionMember>)));


//    chatRoom->show();
}

/*************************************************
Function Name: showChatRoom()
Description: 
*************************************************/
void IMDiscussionButton::showChatRoom()
{
    m_discussionRoom->raise();
    m_discussionRoom->activateWindow();
    m_discussionRoom->show();
    m_isShow = true;
}

/*************************************************
Function Name: closeChatRoom()
Description: 
*************************************************/
void IMDiscussionButton::closeChatRoom()
{
    if(m_isOpen)
    {
        m_discussionRoom->close();
        m_isOpen = false;
        m_isShow = false;
    }
}

/*************************************************
Function Name: setButtonStatus()
Description: 
*************************************************/
void IMDiscussionButton::setButtonStatus()
{
    qDebug() << "discussion-button " << "name:" << m_discussionInfo.m_discussionName;
    qDebug() << "discussion-button " << "theme:" << m_discussionInfo.m_theme;

    QString str = QString(":/images/discussion.png");

    QPixmap pixmap;
    QIcon icon(str);
    pixmap = icon.pixmap(QSize(HEAD_SMALL_SIZE, HEAD_SMALL_SIZE));
    m_labelHead->setPixmap(pixmap);

//    m_labelHead->setPixmap(QPixmap(str));
    QString text = QString("%1\n%3").arg(m_discussionInfo.m_discussionName, m_discussionInfo.m_theme);
    m_labelMes->setText(text);
}


/*************************************************
Function Name: deleteDiscussionMember()
Description: 
*************************************************/
void IMDiscussionButton::deleteDiscussionMember(const QString & memberID)
{
    for (int i =0; i<m_discussionMembersVec.size(); ++i)
    {
        if (0 == memberID.compare(m_discussionMembersVec[i].m_userID))
        {
            m_discussionMembersVec[i].m_userID = "0";
        }
    }
}

/*************************************************
Function Name: addDiscussionMember()
Description: 
*************************************************/
void IMDiscussionButton::addDiscussionMember(const QString & memberID)
{
    int size = m_discussionMembersVec.size();
    m_discussionMembersVec.resize(size + 1);

    m_discussionMembersVec[size].m_userID = memberID;
}

//public slots:----------------------------------------------

/*************************************************
Function Name: onDoubleClickDiscussionButton()
Description: 
*************************************************/
void IMDiscussionButton::onDoubleClickDiscussionButton()
{
    openChatRoom();
    showChatRoom();
    m_mainWidget->removeLinkButton(m_discussionInfo.m_discussionID);
}

/*************************************************
Function Name: onClickRightButton()
Description: 
*************************************************/
void IMDiscussionButton::onClickRightButton()
{
    if (m_menu == NULL)
    {
        creatMenu();
    }
    m_menu->exec(QCursor::pos());
}

/*************************************************
Function Name: onClickSendMessage()
Description: 
*************************************************/
void IMDiscussionButton::onClickSendMessage()
{
    openChatRoom();
}

/*************************************************
Function Name: onClickShowRecord()
Description: 
*************************************************/
void IMDiscussionButton::onClickShowRecord()
{
}

/*************************************************
Function Name: onClickDropDiscussion()
Description: 
*************************************************/
void IMDiscussionButton::onClickDropDiscussion()
{
    QMessageBox::StandardButton returnBtn;

    returnBtn = QMessageBox::question(NULL, tr("drop discussion group"),
        QString(tr("r u sure to drop discussion group(%1)？")).arg(m_discussionInfo.m_discussionName),
        QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(QMessageBox::No == returnBtn)
        return;

    if (NULL != m_mainWidget)
        m_mainWidget->dropDiscussion(m_discussionInfo.m_discussionID);
}

/*************************************************
Function Name: onClickLeaveDiscussion()
Description: 
*************************************************/
void IMDiscussionButton::onClickLeaveDiscussion()
{
    QMessageBox::StandardButton returnBtn;

    returnBtn = QMessageBox::question(NULL, tr("discussion group"),
        QString(tr("Are you sure exit discussion group(%1)？")).arg(m_discussionInfo.m_discussionName),
        QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(QMessageBox::Yes == returnBtn)
    {
         if (NULL != m_mainWidget)
            m_mainWidget->leaveDiscussion(m_mainWidget->getLocalMyInformation().m_userID,
                                          m_discussionInfo.m_discussionID);

    }
}

/*************************************************
Function Name: onClickAddMemberDiscussion()
Description: 
*************************************************/
void IMDiscussionButton::onClickAddMember()
{
    bool isOk = false;
    QString memberID = QInputDialog::getText(NULL, "add discuss member",
                                           "please input the ID to be added",
                                           QLineEdit::Normal,
                                           "",
                                           &isOk);
    if (!isOk)
        return;

    // mark

    if (0 == memberID.compare(m_mainWidget->getLocalMyInformation().m_userID))
    {
        QMessageBox::critical(NULL, tr("add failed"), tr("can't add yourself"));
        return;
    }
    for (int i =0; i<m_discussionMembersVec.size(); ++i)
    {
        if (0 == memberID.compare(m_discussionMembersVec[i].m_userID))
        {
            QMessageBox::critical(NULL, tr("add failed"), tr("this user is already in discussion group"));
            return;
        }
    }

//    TempStrings temp;
//    temp.m_one = m_myself.m_userID;
//    temp.m_two = friendID;
//    temp.m_three = checkMes;

    TalkMessage mes;
    mes.m_senderID = m_discussionInfo.m_discussionID; // discussion group ID
    mes.m_receiverID = memberID;  // memeber ID
//    mes.m_text = checkMes;
    mes.m_type = ADD_DISCUSSION;

    if (NULL != m_mainCtrl)
        m_mainCtrl->addDiscussion(mes);
}

/*************************************************
Function Name: onClickShowInformation()
Description: 
*************************************************/
void IMDiscussionButton::onClickShowInformation()
{
    if (m_mainWidget == NULL)
        return;
    m_mainWidget->showDiscussionInformation(m_discussionInfo);
}

/*************************************************
Function Name: chatRoomQuit()
Description: 
*************************************************/
void IMDiscussionButton::chatRoomQuit()
{
    m_isOpen = false;
    m_isShow = false;
    if (NULL != m_mainWidget)
        m_mainWidget->removeDiscussionChatWidget(m_discussionInfo.m_discussionID);
}

/*************************************************
Function Name: setDiscussionMemberList()
Description: 
*************************************************/
void IMDiscussionButton::setDiscussionMemberList(const QVector<DiscussionMember> & memberList)
{
    int len = memberList.size();
    if (len <= 0) return;


    if (0 != memberList[0].m_discussionID.compare(m_discussionInfo.m_discussionID))
        return;

//    getRoomPoint()->setdiscussionMemberList(memberList);
//    int len = memberList.size();
    m_discussionMembersVec.clear();
    m_discussionMembersVec.resize(len);
    for(int i=0; i<len; i++)
    {
        m_discussionMembersVec[i] = memberList[i];
    }


}

//remark:protected:----------------------------------------

/*************************************************
Function Name: mousePressEvent
Description: 
*************************************************/
void IMDiscussionButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        onClickRightButton();
        return;
    }
    QPushButton::mousePressEvent(event);
}

/*************************************************
Function Name: mouseDoubleClickEvent
Description: 
*************************************************/
void IMDiscussionButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
//        emit leftDoubleClickSignal();
        onDoubleClickDiscussionButton();
        return;
    }
    QPushButton::mouseDoubleClickEvent(event);
}


//remark:private:----------------------------------------
/*************************************************
Function Name: getStatusFromInt()
Description: 
*************************************************/
void IMDiscussionButton::creatMenu(/*const QList<QString> *groutList*/)
{
    m_menu = new QMenu(this);
    QAction *sendMessage = new QAction(tr("send discuss group msg"), m_menu);
    QAction *showRecord = new QAction(tr("look msg"), m_menu);
    QAction *showInformation = new QAction(tr("look info"), m_menu);
    QAction *addMember = new QAction(tr("add member"), m_menu);

    connect(sendMessage, SIGNAL(triggered()),
        this, SLOT(onClickSendMessage()));
    connect(showRecord, SIGNAL(triggered()),
        this, SLOT(onClickShowRecord()));
    connect(showInformation, SIGNAL(triggered()),
        this, SLOT(onClickShowInformation()));
    connect(addMember, SIGNAL(triggered()),
        this, SLOT(onClickAddMember()));

    m_menu->addAction(sendMessage);
    m_menu->addAction(showRecord);
    m_menu->addAction(showInformation);
    m_menu->addAction(addMember);

    if (m_mainWidget->getLocalMyInformation().m_userID == m_discussionInfo.m_creatorID)
    {
        QAction *dropDiscussion = new QAction(tr("drop the discussion"), m_menu);
        connect(dropDiscussion, SIGNAL(triggered()),
                this, SLOT(onClickDropDiscussion()));
        m_menu->addAction(dropDiscussion);
    }
    else
    {
        QAction *leaveDiscussion = new QAction(tr("quit from the disscussion"), m_menu);
        connect(leaveDiscussion, SIGNAL(triggered()),
            this, SLOT(onClickLeaveDiscussion()));
        m_menu->addAction(leaveDiscussion);
    }
}


