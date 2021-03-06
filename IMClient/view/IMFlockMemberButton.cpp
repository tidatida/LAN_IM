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
Description:
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
}

/*************************************************
Function Name: closeChatRoom()
Description:
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
Description: 
*************************************************/
void IMFlockMemberButton::setButtonStatus()
{
    QString str = QString("resource/image/head/%1.bmp").
        arg(QString::number(m_info.m_headPortrait));

    QString text, mark;
    m_strFlockStatus = getFlockStatusFromInt(m_info.m_flockStatus);
    m_strLoginStatus = getLoginStatusFromInt(m_info.m_loginStatus);


    if(m_info.m_remark.isEmpty()){
        mark = m_info.m_nickname;
    }else{
        mark = m_info.m_remark;
    }

    if(OFFLINE == m_info.m_loginStatus || INVISIBLE == m_info.m_loginStatus){
        QPixmap pixmap;
        QIcon icon(str);
        pixmap = icon.pixmap(QSize(HEAD_MINI_SIZE, HEAD_MINI_SIZE),
                             QIcon::Disabled, QIcon::On);
        m_labelHead->setPixmap(pixmap);

        text = QString("<font size=\"FONT_SIEZE\" color=gray>[%1]%2(%3)[%4]</font>").
                arg(m_strFlockStatus, mark, m_info.m_userID, m_strLoginStatus);
    
    }else{
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

    m_labelMes->setText(text);

}


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
Description: 
*************************************************/
void IMFlockMemberButton::onClickSendMessage()
{
    openChatRoom();
}

/*************************************************
Function Name: onClickSendMail()
Description: 
*************************************************/
void IMFlockMemberButton::onClickSendMail()
{
}

/*************************************************
Function Name: onClickShowInformation()
Description: 
*************************************************/
void IMFlockMemberButton::onClickShowInformation()
{
    m_mainWidget->getFriendInformation(m_info.m_userID);
}

/*************************************************
Function Name: onClickChangeRemark()
Description: 
*************************************************/
void IMFlockMemberButton::onClickChangeRemark()
{
    bool isOk = false;
    QString remark = QInputDialog::getText(NULL, "modify group name",
                                           " please input new group name",
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
Description: 
*************************************************/
void IMFlockMemberButton::onClickEnterSpace()
{
}

/*************************************************
Function Name: onClickRemoveMember
Description: 
*************************************************/
void IMFlockMemberButton::onClickRemoveMember()
{
    QMessageBox::StandardButton returnBtn;

    returnBtn = QMessageBox::question(NULL, tr("remove group member"),
                    QString(tr("Are you sure remove %1 from group %2 ？")).
                    arg(m_info.m_userID,m_flockWidget->getFlockInformation().m_flockID),
                    QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if (m_mainWidget == NULL){
        return;
    }

    if(QMessageBox::Yes == returnBtn){
        m_mainWidget->leaveFlock(m_info.m_userID,
                                 m_flockWidget->getFlockInformation().m_flockID);
    }

}


/*************************************************
Function Name: onClickAddFriend
Description:
*************************************************/
void IMFlockMemberButton::onClickAddFriend()
{
    m_mainWidget->addFriend(m_info.m_userID);
}


/*************************************************
Function Name: onDoubleClickMemberButton
Description:
*************************************************/
void IMFlockMemberButton::onDoubleClickMemberButton()
{
    openChatRoom();
}

/*************************************************
Function Name: chatRoomQuit
Description:
*************************************************/
void IMFlockMemberButton::chatRoomQuit()
{
    m_isOpen = false;
}


//remark:protected:----------------------------------------

/*************************************************
Function Name: mousePressEvent
Description:  mouse click event 
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
Description:  mouse double click event 
*************************************************/
void IMFlockMemberButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        onDoubleClickMemberButton();
        return;
    }

    QPushButton::mouseDoubleClickEvent(event);
}



//remark:private:----------------------------------------

/*************************************************
Function Name: getFlockStatusFromInt()
Description:
*************************************************/
QString IMFlockMemberButton::getFlockStatusFromInt(const int n) const
{
    switch (n)
    {
    case FLOCK_HOST:
        return tr("group owner");
        break;
    case FLOCK_ADMAIN:
        return tr("group admin");
        break;

    case FLOCK_MEMBER:
        return tr("group member");
        break;

    default:
        break;

    }

    return NULL;
}


/*************************************************
Function Name: getLoginStatusFromInt()
Description: 
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
    QAction *sendMessage = new QAction(tr("send Instant msg"), m_menu);
    QAction *sendMail = new QAction(tr("send email"), m_menu);
    QAction *showInfo = new QAction(tr("view profile"), m_menu);
    QAction *enterSpace = new QAction(tr("enter space"), m_menu);
    QAction *removeMember= new QAction(tr("remove"), m_menu);
    QAction *changeRemark = new QAction(tr("modify group name"), m_menu);
    QAction *addRriend= new QAction(tr("add friend"), m_menu);

    connect(sendMessage, SIGNAL(triggered()),this, SLOT(onClickSendMessage()));
    connect(sendMail, SIGNAL(triggered()),this, SLOT(onClickSendMail()));
    connect(showInfo, SIGNAL(triggered()),this, SLOT(onClickShowInformation()));
    connect(enterSpace, SIGNAL(triggered()),this, SLOT(onClickEnterSpace()));
    connect(removeMember, SIGNAL(triggered()),this, SLOT(onClickRemoveMember()));
    connect(changeRemark, SIGNAL(triggered()),this, SLOT(onClickChangeRemark()));
    connect(addRriend, SIGNAL(triggered()),this, SLOT(onClickAddFriend()));


    // self
    if (m_mainWidget->getLocalMyInformation().m_userID == m_info.m_userID)
    {
        m_menu->addAction(enterSpace);
        m_menu->addAction(changeRemark);

    }else if (m_mainWidget->getLocalMyInformation().m_userID ==
             m_flockWidget->getFlockInformation().m_creatorID){
            // group owner 

        m_menu->addAction(sendMessage);
        m_menu->addAction(sendMail);
        m_menu->addAction(showInfo);
        m_menu->addAction(enterSpace);
        m_menu->addSeparator();
        m_menu->addAction(changeRemark);
        m_menu->addAction(removeMember);

        // not friend
        if (!m_mainWidget->isMyFriend(m_info.m_userID))
        {
            m_menu->addAction(addRriend);
        }

    }else{
        m_menu->addAction(sendMessage);
        m_menu->addAction(sendMail);
        m_menu->addAction(showInfo);
        m_menu->addAction(enterSpace);
        m_menu->addSeparator();

        if (!m_mainWidget->isMyFriend(m_info.m_userID))
        {
            m_menu->addAction(addRriend);
        }
    }
}


