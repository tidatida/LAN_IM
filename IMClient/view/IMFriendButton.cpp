#include "IMFriendButton.h"
#include <QMenu>
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include "view/IMChatWidget.h"
#include "view/IMMainWidget.h"

IMFriendButton::IMFriendButton(const FriendInformation &info,
                               QList<QString> *groupList,
                               IMMainWidget *mainWidget,
                               QWidget *parent) :
    QPushButton(parent)
{
    m_info = info;
    m_mainWidget = mainWidget;
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
    m_moveFriendMenu = NULL;
    m_groupList = groupList;
    setButtonStatus();


    setStyleSheet("QPushButton{border: 0;}");
}


IMFriendButton::~IMFriendButton()
{

}

/*************************************************
Function Name: openChatRoom()
Description: 
*************************************************/
void IMFriendButton::openChatRoom()
{

    if(m_isOpen)
    {
        return;
    }

    ChatInformation chatInf;
    chatInf.m_myID = m_mainWidget->getLocalMyInformation().m_userID;
    chatInf.m_headPortrait = m_info.m_headPortrait;

    chatInf.m_friendID = m_info.m_userID;
    chatInf.m_friendNickname = m_info.m_nickname;
    chatInf.m_friendRemark = m_info.m_remarkName;
    chatInf.m_friendStatus = m_info.m_status;

    m_isOpen = true;
    IMChatWidget *chatRoom = new IMChatWidget(chatInf);

    m_chatRoom = chatRoom;
    m_mainWidget->insertChatRoomMap(chatInf.m_friendID, chatRoom);
    connect(chatRoom, SIGNAL(sendMessagesFromChat(TalkMessage &)),m_mainWidget, SLOT(receiveMessagesFromChat(TalkMessage &)));
    connect(chatRoom, SIGNAL(roomQuitSignal()),  this, SLOT(chatRoomQuit()));
}


/*************************************************
Function Name: showChatRoom()
Description:
*************************************************/
void IMFriendButton::showChatRoom()
{
    m_chatRoom->raise();
    m_chatRoom->activateWindow();
    m_chatRoom->show();
    m_isShow = true;
}

/*************************************************
Function Name: closeChatRoom()
Description: 
*************************************************/
void IMFriendButton::closeChatRoom()
{
    if(m_isOpen)
    {
        m_chatRoom->close();
        m_isOpen = false;
        m_isShow = false;
    }
}

/*************************************************
Function Name: setButtonStatus()
Description:   
*************************************************/
void IMFriendButton::setButtonStatus()
{
    QString str = QString("resource/image/head/%1.bmp").
        arg(QString::number(m_info.m_headPortrait));

    QString text, mark;
    m_strStatus = getStatusFromInt(m_info.m_status);

    if(m_info.m_remarkName.isEmpty()){
        mark = m_info.m_nickname;
    }else{
        mark = m_info.m_remarkName;
    }

    if(OFFLINE == m_info.m_status || INVISIBLE == m_info.m_status)
    {
        QPixmap pixmap;
        QIcon icon(str);
        pixmap = icon.pixmap(QSize(HEAD_SMALL_SIZE, HEAD_SMALL_SIZE),
                             QIcon::Disabled, QIcon::On);
        m_labelHead->setPixmap(pixmap);

        text = QString("<font color=gray>%1(%2)<br>[%3]</font>").
                arg(m_info.m_userID).arg(mark).arg(m_strStatus);
                
    }else{
        m_labelHead->setPixmap(QPixmap(str));

        text = QString("<font color=green>%1(%2)<br>[%3]</font>").
                arg(m_info.m_userID).arg(mark).arg(m_strStatus);
    }
    m_labelMes->setText(text);
}


/*************************************************
Function Name: refreshMoveMenu()
Description: 
*************************************************/
void IMFriendButton::refreshMoveMenu()
{
    if (m_menu == NULL || m_moveFriendMenu == NULL)
    {
        return;
    }

    m_moveFriendMenu->clear();
    QString groupName;

    for (int i = 0; i<m_groupList->size(); ++i)
    {
        groupName = m_groupList->value(i);
        if (0 != groupName.compare(m_info.m_groupName))
        {
            QAction * action = new QAction(groupName, m_moveFriendMenu);

            m_moveFriendMenu->addAction(action);

            connect(action, SIGNAL(triggered()),this, SLOT(onClickMove()));

        }
    }
}

//remark:public slots:---------------------------

/*************************************************
Function Name: onDoubleClickFriendButton()
Description: 
*************************************************/
void IMFriendButton::onDoubleClickFriendButton()
{
    openChatRoom();
    showChatRoom();
    m_mainWidget->removeLinkButton(m_info.m_userID);
}


/*************************************************
Function Name: onClickRightButton()
Description:  right button 
*************************************************/
void IMFriendButton::onClickRightButton(/*const QPoint &*/)
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
void IMFriendButton::onClickSendMessage()
{
    openChatRoom();
}

/*************************************************
Function Name: onClickShowRecord()
Description: 
*************************************************/
void IMFriendButton::onClickShowRecord()
{
    m_mainWidget->showMessageWidget();
}

/*************************************************
Function Name: onClickSendMail()
Description: 
*************************************************/
void IMFriendButton::onClickSendMail()
{
    m_mainWidget->showMailWriteWidget(m_info.m_userID);
}

/*************************************************
Function Name: onClickShowInformation()
Description: 
*************************************************/
void IMFriendButton::onClickShowInformation()
{
    m_mainWidget->getFriendInformation(m_info.m_userID);
}

/*************************************************
Function Name: onClickChangeRemark()
Description: 
*************************************************/
void IMFriendButton::onClickChangeRemark()
{
    bool isOk = false;
    QString remark = QInputDialog::getText(NULL, "modify remark",
                                           " please  input  new  nickname",
                                           QLineEdit::Normal,
                                           m_info.m_remarkName,
                                           &isOk);

    if (isOk && 0 != remark.compare(m_info.m_remarkName))
    {
        qDebug("request-change-remark");
        m_mainWidget->changeFriendRemark(m_info.m_userID, remark);
    }

}

/*************************************************
Function Name: onClickMove()
Description:  move friend to  other  box 
*************************************************/
void IMFriendButton::onClickMove()
{
    QAction* action = dynamic_cast<QAction*>(sender());
    m_mainWidget->moveFriendToBox(m_info.m_userID, m_info.m_groupName, action->text());
}

/*************************************************
Function Name: onClickRemoveFriend()
Description: delete friend
*************************************************/
void IMFriendButton::onClickRemoveFriend()
{
    QMessageBox::StandardButton returnBtn;

    returnBtn = QMessageBox::question(NULL, tr("delete friend"),
        QString(tr("Are you sure to delete friend(%1)？")).arg(m_info.m_userID),
        QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(QMessageBox::Yes == returnBtn){
        m_mainWidget->deleteFriend(m_info.m_userID);
    }

}

/*************************************************
Function Name: chatRoomQuit()
Description: 
*************************************************/
void IMFriendButton::onClickEnterSpace()
{
}

/*************************************************
Function Name: chatRoomQuit()
Description: 
*************************************************/
void IMFriendButton::chatRoomQuit()
{
    m_isOpen = false;
    m_isShow = false;
    
    if (NULL != m_mainWidget){
        m_mainWidget->removeChatWidget(m_info.m_userID);
    }
}

//remark:protected:----------------------------------------

/*************************************************
Function Name: mousePressEvent
Description:  mouse click event 
*************************************************/
void IMFriendButton::mousePressEvent(QMouseEvent *event)
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
Description:  mouse 双击 event 
*************************************************/
void IMFriendButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        onDoubleClickFriendButton();
        return;
    }

    QPushButton::mouseDoubleClickEvent(event);
}



//remark:private:----------------------------------------

/*************************************************
Function Name: getStatusFromInt()
Description: 
*************************************************/
QString IMFriendButton::getStatusFromInt(const int n) const
{
    switch (n)
    {
        case ONLINE:
            return tr("online");
            break;

        case OFFLINE:
        case INVISIBLE:
            return tr("offline");
            break;

        case BUSY:
            return tr("busy");
            break;

        case LEAVE:
            return tr("away");
            break;

        case NOTDISTURB:
            return tr("please don't disturb");
            break;

        default:
            break;
    }

    return NULL;
}


/*************************************************
Function Name: getStatusFromInt()
Description: create right button  menu 
*************************************************/
void IMFriendButton::creatMenu(/*const QList<QString> *groutList*/)
{
    m_menu = new QMenu(this);
    QAction *sendMessage = new QAction(tr("send Instant Message"), m_menu);
    QAction *showRecord = new QAction(tr("display message record"), m_menu);
    QAction *sendMail = new QAction(tr("send email"), m_menu);

    QAction *showInfo = new QAction(tr("view info"), m_menu);
    QAction *changeRemar = new QAction(tr("modify remark nickname"), m_menu);
    QAction *removeFriend = new QAction(tr("delete friend"), m_menu);
    QAction *enterSpace = new QAction(tr("enter friend space"), m_menu);

    m_moveFriendMenu= new QMenu(tr(" move friend to"), m_menu);
    refreshMoveMenu();

    connect(sendMessage, SIGNAL(triggered()),this, SLOT(onDoubleClickFriendButton()));
    connect(showRecord, SIGNAL(triggered()),this, SLOT(onClickShowRecord()));
    connect(sendMail, SIGNAL(triggered()),this, SLOT(onClickSendMail()));

    connect(showInfo, SIGNAL(triggered()),this, SLOT(onClickShowInformation()));
    connect(changeRemar, SIGNAL(triggered()),this, SLOT(onClickChangeRemark()));
    connect(removeFriend, SIGNAL(triggered()),this, SLOT(onClickRemoveFriend()));
    connect(enterSpace, SIGNAL(triggered()),this, SLOT(onClickEnterSpace()));

    m_menu->addAction(sendMessage);
    m_menu->addAction(showRecord);
    m_menu->addAction(sendMail);
    m_menu->addAction(showInfo);
    m_menu->addAction(changeRemar);
    m_menu->addSeparator();

    m_menu->addMenu(m_moveFriendMenu);
    m_menu->addAction(removeFriend);
    m_menu->addAction(enterSpace);

}


