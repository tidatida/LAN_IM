#include "IMFlockMemberButton.h"
#include <QMenu>
#include <QLabel>
#include "IMMainWidget.h"
#include "IMChatWidget.h"
#include "control/IMMainCtrl.h"
#include "IMFlockChatWidget.h"
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>

IMFlockMemberButton::IMFlockMemberButton(const FlockMember &flockMember,
                                         IMFlockChatWidget *flockWidget,
                                         IMMainWidget *mainWidget, QWidget *parent) :
    QPushButton(parent)
{
    m_info = flockMember;
    m_flockWidget = flockWidget;
    m_mainWidget = mainWidget;
    m_mainCtrl = m_mainWidget->getMainCtrl();
    m_isOpen = false;

    QHBoxLayout *layout = new QHBoxLayout;

    m_labelHead = new QLabel;
    m_labelHead->setFixedSize(HEAD_MINI_SIZE, HEAD_MINI_SIZE);
    m_labelMes = new QLabel;

    layout->addWidget(m_labelHead);
    layout->addWidget(m_labelMes);
    layout->addStretch();
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);
    setMinimumHeight(25);

    m_menu = NULL;
    setButtonStatus();
    creatMenu();
    setStyleSheet("QPushButton{border: 0;}");
}

IMFlockMemberButton::~IMFlockMemberButton()
{
}

/*************************************************
Function Name: openChatRoom()
Description: open 聊天窗口
*************************************************/
void IMFlockMemberButton::openChatRoom()
{
    qDebug() << "chat room with flock member is open";
    if(m_isOpen)
    {
        m_flockWidget->raise();
        m_flockWidget->activateWindow();
        m_flockWidget->show();
        return;
    }
    qDebug() << "create chat room with flock member";
//    ChatInformation chatInf;
//    chatInf.m_headPortrait = m_info.m_headPortrait;
//    chatInf.m_friendID = m_info.m_userID;
////    chatInf.m_friendMark = m_info.m_mark;
//    chatInf.m_friendNickname = m_info.m_nickname;
//    chatInf.m_friendRemark = m_info.m_remarkName;

//    m_isOpen = true;
//    IMChatWidget *chatRoom = new IMChatWidget(chatInf);
//    m_flockWidget = chatRoom;
//    m_mainWidget->insertChatRoomMap(chatInf.m_friendID, chatRoom);
//    connect(chatRoom, SIGNAL(sendMessagesFromChat(TalkMessage &)),
//            m_mainWidget, SLOT(receiveMessagesFromChat(TalkMessage &)));
//    connect(chatRoom, SIGNAL(roomQuitSignal()),  this, SLOT(chatRoomQuit()));
//    chatRoom->show();
}

/*************************************************
Function Name: closeChatRoom()
Description: close 聊天窗口
*************************************************/
void IMFlockMemberButton::closeChatRoom()
{
    if(m_isOpen)
    {
        m_flockWidget->close();
        m_isOpen = false;
    }
}


/*************************************************
Function Name: setButtonStatus()
Description:   set button显示信息
*************************************************/
void IMFlockMemberButton::setButtonStatus()
{
    QString str = QString("resource/image/head/%1.bmp").
        arg(QString::number(m_info.m_headPortrait));

    QString text, mark;
    m_strFlockStatus = getFlockStatusFromInt(m_info.m_flockStatus);
    m_strLoginStatus = getLoginStatusFromInt(m_info.m_loginStatus);
    if(m_info.m_remark.isEmpty())
        mark = m_info.m_nickname;
    else
        mark = m_info.m_remark;
    if(OFFLINE == m_info.m_loginStatus || INVISIBLE == m_info.m_loginStatus)
    {
        QPixmap pixmap;
        QIcon icon(str);
        pixmap = icon.pixmap(QSize(HEAD_MINI_SIZE, HEAD_MINI_SIZE),
                             QIcon::Disabled, QIcon::On);
        m_labelHead->setPixmap(pixmap);

        text = QString("<font size=\"FONT_SIEZE\" color=gray>[%1]%2(%3)[%4]</font>").
                arg(m_strFlockStatus, mark, m_info.m_userID, m_strLoginStatus);
    }
    else
    {
        QPixmap pixmap;
        QIcon icon(str);
        pixmap = icon.pixmap(QSize(HEAD_MINI_SIZE, HEAD_MINI_SIZE));
        m_labelHead->setPixmap(pixmap);

        text = QString("<font size=\"FONT_SIEZE\" color=red>[%1]</font>"
                       "<font size=\"FONT_SIEZE\" color=green>%2</font>"
                       "<font size=\"FONT_SIEZE\" color=blue>(%3)</font>"
                       "<font size=\"FONT_SIEZE\" color=black>[%4]</font>").
                arg(m_strFlockStatus, mark, m_info.m_userID, m_strLoginStatus);
    }
    //    text = QString("[%1]%2(%3)").arg(m_strStatus, mark, m_info.m_userID);

        //<font size=\"FONT_SIEZE\" color=green>%1    %2: </font>

    m_labelMes->setText(text);

}

//remark:public slots:-----------------------------------------------

//  right button  click  button 
void IMFlockMemberButton::onClickRightButton(/*const QPoint &*/)
{
    if (m_menu == NULL)
    {
        //create  right button  menu 
        creatMenu();
    }
    m_menu->exec(QCursor::pos());
}

/*************************************************
Function Name: onClickSendMessage()
Description: 发送 Instant 消息
*************************************************/
void IMFlockMemberButton::onClickSendMessage()
{
    openChatRoom();
}

/*************************************************
Function Name: onClickSendMail()
Description: 发送电子邮件
*************************************************/
void IMFlockMemberButton::onClickSendMail()
{
}

/*************************************************
Function Name: onClickShowInformation()
Description: 显示成员详细信息
*************************************************/
void IMFlockMemberButton::onClickShowInformation()
{
    m_mainWidget->getFriendInformation(m_info.m_userID);
}

/*************************************************
Function Name: onClickChangeRemark()
Description: modify群 name 片
*************************************************/
void IMFlockMemberButton::onClickChangeRemark()
{
    bool isOk = false;
    QString remark = QInputDialog::getText(NULL, "modify群 name 片",
                                           " please  input  new ,s 群 name 片",
                                           QLineEdit::Normal,
                                           m_info.m_remark,
                                           &isOk);

    if (isOk && 0 != remark.compare(m_info.m_remark))
    {
        qDebug("request-change-remark");
        TempStrings tmpStr;
        tmpStr.m_one = m_info.m_flockID;
        tmpStr.m_two = m_info.m_userID;
        tmpStr.m_three = remark;
        m_mainWidget->changeFlockMemberRemark(tmpStr);
    }

}

/*************************************************
Function Name: onClickEnterSpace
Description: 进入空间
*************************************************/
void IMFlockMemberButton::onClickEnterSpace()
{
}

/*************************************************
Function Name: onClickRemoveMember
Description: 移除该成员
*************************************************/
void IMFlockMemberButton::onClickRemoveMember()
{
    QMessageBox::StandardButton returnBtn;

    returnBtn = QMessageBox::question(NULL, tr("移除群成员"),
        QString(tr("你确定要将成员%1,从群%2中移除吗？")).
            arg(m_info.m_userID,m_flockWidget->getFlockInformation().m_flockID),
        QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if (m_mainWidget == NULL)
        return;
    if(QMessageBox::Yes == returnBtn)
        m_mainWidget->leaveFlock(m_info.m_userID,
                                 m_flockWidget->getFlockInformation().m_flockID);
}


/*************************************************
Function Name: onClickAddFriend
Description: 加好友
*************************************************/
void IMFlockMemberButton::onClickAddFriend()
{
    m_mainWidget->addFriend(m_info.m_userID);
}


/*************************************************
Function Name: onDoubleClickMemberButton
Description: 左键 双击
*************************************************/
void IMFlockMemberButton::onDoubleClickMemberButton()
{
    openChatRoom();
}

/*************************************************
Function Name: chatRoomQuit
Description: 聊天窗口close 了
*************************************************/
void IMFlockMemberButton::chatRoomQuit()
{
    m_isOpen = false;
//    if (NULL != m_flockWidget)
//        m_flockWidget->removeChatWidget(m_info.m_userID);
}


//remark:protected:----------------------------------------

/*************************************************
Function Name: mousePressEvent
Description:  mouse 单击 event 
*************************************************/
void IMFlockMemberButton::mousePressEvent(QMouseEvent *event)
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
void IMFlockMemberButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
//        emit leftDoubleClickSignal();
        onDoubleClickMemberButton();
        return;
    }
    QPushButton::mouseDoubleClickEvent(event);
}



//remark:private:----------------------------------------

/*************************************************
Function Name: getFlockStatusFromInt()
Description: 将群成员身份从数字形式转换为字符串形式
*************************************************/
QString IMFlockMemberButton::getFlockStatusFromInt(const int n) const
{
    switch (n)
    {
    case FLOCK_HOST:
        return tr("群 main ");
        break;
    case FLOCK_ADMAIN:
//        return tr("管理员");
//        break;
    case FLOCK_MEMBER:
        return tr("成员");
        break;
    default:
        break;
    }
    return NULL;
}


/*************************************************
Function Name: getLoginStatusFromInt()
Description: 将好友 online 状态从数字形式转换为字符串形式
*************************************************/
QString IMFlockMemberButton::getLoginStatusFromInt(const int n) const
{
//    ONLINE = 0,    //  online 
//    INVISIBLE = 1, //  Invisible 
//    BUSY = 2,      //  busy 
//    LEAVE = 3,     //  away 
//    NOTDISTURB = 4 //  please  dont disturb 
    switch (n)
    {
    case ONLINE:
        return tr(" online ");
        break;
    case OFFLINE:
    case INVISIBLE:
        return tr(" offline ");
        break;
    case BUSY:
        return tr(" busy ");
        break;
    case LEAVE:
        return tr(" away ");
        break;
    case NOTDISTURB:
        return tr(" please  dont disturb ");
        break;
    default:
        break;
    }
    return NULL;
}


/*************************************************
Function Name: getStatusFromInt()
Description: create  right button  menu 
*************************************************/
void IMFlockMemberButton::creatMenu(/*const QList<QString> *groutList*/)
{
    m_menu = new QMenu(this);
    QAction *sendMessage = new QAction(tr("发送 Instant 消息"), m_menu);
    QAction *sendMail = new QAction(tr("发送电子邮件"), m_menu);
    QAction *showInfo = new QAction(tr("查看资料"), m_menu);
    QAction *enterSpace = new QAction(tr("进入空间"), m_menu);
    QAction *removeMember= new QAction(tr("移除该成员"), m_menu);
    QAction *changeRemark = new QAction(tr("modify群 name 片"), m_menu);
    QAction *addRriend= new QAction(tr("加为好友"), m_menu);

    connect(sendMessage, SIGNAL(triggered()),
        this, SLOT(onClickSendMessage()));
    connect(sendMail, SIGNAL(triggered()),
        this, SLOT(onClickSendMail()));
    connect(showInfo, SIGNAL(triggered()),
        this, SLOT(onClickShowInformation()));
    connect(enterSpace, SIGNAL(triggered()),
        this, SLOT(onClickEnterSpace()));
    connect(removeMember, SIGNAL(triggered()),
        this, SLOT(onClickRemoveMember()));
    connect(changeRemark, SIGNAL(triggered()),
        this, SLOT(onClickChangeRemark()));
    connect(addRriend, SIGNAL(triggered()),
        this, SLOT(onClickAddFriend()));


    // 自己
    if (m_mainWidget->getLocalMyInformation().m_userID == m_info.m_userID)
    {
//        m_menu->addAction(showInfo);
        m_menu->addAction(enterSpace);
        m_menu->addAction(changeRemark);

    }

    // 不是自己 - 是群 main 
    else if (m_mainWidget->getLocalMyInformation().m_userID ==
             m_flockWidget->getFlockInformation().m_creatorID)
    {
        m_menu->addAction(sendMessage);
        m_menu->addAction(sendMail);
        m_menu->addAction(showInfo);
        m_menu->addAction(enterSpace);
        m_menu->addSeparator();
        m_menu->addAction(changeRemark);
        m_menu->addAction(removeMember);

        // 不是好友
        if (!m_mainWidget->isMyFriend(m_info.m_userID))
        {

            m_menu->addAction(addRriend);
        }
    }
    // 不是自己 - 不是群 main 
    else
    {
        m_menu->addAction(sendMessage);
        m_menu->addAction(sendMail);
        m_menu->addAction(showInfo);
        m_menu->addAction(enterSpace);
        m_menu->addSeparator();

        // 不是好友
        if (!m_mainWidget->isMyFriend(m_info.m_userID))
        {
            m_menu->addAction(addRriend);
        }
    }
}


