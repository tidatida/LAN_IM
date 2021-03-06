#include "IMFlockButton.h"
#include <QMenu>
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include "IMChatWidget.h"
#include "IMMainWidget.h"
#include "IMFlockChatWidget.h"
#include "control/IMMainCtrl.h"

IMFlockButton::IMFlockButton(const FlockInformation &info,
                             IMMainWidget *mainWidget,
                             QWidget *parent) :
    QPushButton(parent)
{
    m_flockInfo = info;
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

IMFlockButton:: ~IMFlockButton()
{
}

/*************************************************
Function Name: openChatRoom()
Description: open 聊天窗口
*************************************************/
void IMFlockButton::openChatRoom()
{
    if (m_mainWidget == NULL)
        return;

    if(m_isOpen)
    {
//        qDebug() << "flock room opened";
//        m_flockRoom->raise();
//        m_flockRoom->activateWindow();
//        m_flockRoom->show();
        return;
    }
    m_isOpen = true;

    IMFlockChatWidget *chatRoom = new IMFlockChatWidget(m_flockInfo, m_mainWidget);
    m_flockRoom = chatRoom;
    m_mainWidget->insertFlockRoomMap(m_flockInfo.m_flockID, chatRoom);
    connect(chatRoom, SIGNAL(sendMessagesFromChat(TalkMessage &)),
            m_mainWidget, SLOT(receiveMessagesFromChat(TalkMessage &)));
    connect(chatRoom, SIGNAL(roomQuitSignal()),  this, SLOT(chatRoomQuit()));



//    if (m_flockMembersVec.empty())
//    {
    qDebug() << m_flockInfo.m_flockName << "request flock members";
    m_mainCtrl->getFlockMembers(m_flockInfo.m_flockID);
    connect(m_mainCtrl, SIGNAL(getFlockMembersSuccess(QVector<FlockMember>)),
            this, SLOT(setFlockMemberList(QVector<FlockMember>)));
    connect(m_mainCtrl, SIGNAL(getFlockMembersSuccess(QVector<FlockMember>)),
            chatRoom, SLOT(setFlockMemberList(QVector<FlockMember>)));
//    }
//    else
//    {
//        qDebug() << m_flockInfo.m_flockName << "have flock members" << m_flockMembersVec.size();
//        chatRoom->setFlockMemberList(m_flockMembersVec);
//    }
//    chatRoom->show();
}

/*************************************************
Function Name: showChatRoom()
Description: 显示聊天窗口
*************************************************/
void IMFlockButton::showChatRoom()
{
    m_flockRoom->raise();
    m_flockRoom->activateWindow();
    m_flockRoom->show();
    m_isShow = true;
}

/*************************************************
Function Name: closeChatRoom()
Description: close 聊天窗口
*************************************************/
void IMFlockButton::closeChatRoom()
{
    if(m_isOpen)
    {
        m_flockRoom->close();
        m_isOpen = false;
        m_isShow = false;
    }
}

/*************************************************
Function Name: setButtonStatus()
Description:  set button显示信息
*************************************************/
void IMFlockButton::setButtonStatus()
{
    qDebug() << "flock-button " << "name:" << m_flockInfo.m_flockName;
    qDebug() << "flock-button " << "theme:" << m_flockInfo.m_theme;

    QString str = QString(":/images/flock.png");

    QPixmap pixmap;
    QIcon icon(str);
    pixmap = icon.pixmap(QSize(HEAD_SMALL_SIZE, HEAD_SMALL_SIZE));
    m_labelHead->setPixmap(pixmap);

//    m_labelHead->setPixmap(QPixmap(str));
    QString text = QString("%1\n%3").arg(m_flockInfo.m_flockName, m_flockInfo.m_theme);
    m_labelMes->setText(text);
}


/*************************************************
Function Name: deleteFlockMember()
Description: delete  群成员
*************************************************/
void IMFlockButton::deleteFlockMember(const QString & memberID)
{
    for (int i =0; i<m_flockMembersVec.size(); ++i)
    {
        if (0 == memberID.compare(m_flockMembersVec[i].m_userID))
        {
            m_flockMembersVec[i].m_userID = "0";
        }
    }
}

/*************************************************
Function Name: addFlockMember()
Description: add 群成员
*************************************************/
void IMFlockButton::addFlockMember(const QString & memberID)
{
    int size = m_flockMembersVec.size();
    m_flockMembersVec.resize(size + 1);

    m_flockMembersVec[size].m_userID = memberID;

}

//public slots:----------------------------------------------

/*************************************************
Function Name: onDoubleClickFlockButton()
Description: 左键 双击
*************************************************/
void IMFlockButton::onDoubleClickFlockButton()
{
    openChatRoom();
    showChatRoom();
    m_mainWidget->removeLinkButton(m_flockInfo.m_flockID);
}

/*************************************************
Function Name: onClickRightButton()
Description:  right button  click  button 
*************************************************/
void IMFlockButton::onClickRightButton()
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
Description: 发送群消息
*************************************************/
void IMFlockButton::onClickSendMessage()
{
    openChatRoom();
}

/*************************************************
Function Name: onClickShowRecord()
Description: 查看消息记录
*************************************************/
void IMFlockButton::onClickShowRecord()
{
}


/*************************************************
Function Name: onClickShowInformation()
Description: 显示群详细信息
*************************************************/
void IMFlockButton::onClickShowInformation()
{
    if (m_mainWidget == NULL)
        return;
    m_mainWidget->showFlockInformation(m_flockInfo);
}


/*************************************************
Function Name: onClickDropFlock()
Description: 解散群
*************************************************/
void IMFlockButton::onClickDropFlock()
{

    QMessageBox::StandardButton returnBtn;

    returnBtn = QMessageBox::question(NULL, tr("解散群"),
        QString(tr("你确定要解散群(%1)吗？")).arg(m_flockInfo.m_flockName),
        QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(QMessageBox::No == returnBtn)
        return;
    if (m_mainWidget == NULL)
        return;
    m_mainWidget->dropFlock(m_flockInfo.m_flockID);
}

/*************************************************
Function Name: onClickLeaveFlock()
Description:  quit from  群
*************************************************/
void IMFlockButton::onClickLeaveFlock()
{
    QMessageBox::StandardButton returnBtn;

    returnBtn = QMessageBox::question(NULL, tr(" quit from  群"),
        QString(tr("你确定要 quit from  群(%1)吗？")).arg(m_flockInfo.m_flockName),
        QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if (m_mainWidget == NULL)
        return;
    if(QMessageBox::Yes == returnBtn)
        m_mainWidget->leaveFlock(m_mainWidget->getLocalMyInformation().m_userID,
                                 m_flockInfo.m_flockID);
}

/*************************************************
Function Name: onClickAddMemberFlock()
Description: add 群成员
*************************************************/
void IMFlockButton::onClickAddMemberFlock()
{
    bool isOk = false;
    QString memberID = QInputDialog::getText(NULL, "add 群成员",
                                           " please  input 对方 account  ",
                                           QLineEdit::Normal,
                                           "",
                                           &isOk);
    if (!isOk)
        return;

    // mark
    // 检验 是否全是 数字 或者 一开始就限制 或者 重写一个messagebox

    if (0 == memberID.compare(m_mainWidget->getLocalMyInformation().m_userID))
    {
        QMessageBox::critical(NULL, tr("add 失败"), tr("不能add 自己"));
        return;
    }
    for (int i =0; i<m_flockMembersVec.size(); ++i)
    {
        if (0 == memberID.compare(m_flockMembersVec[i].m_userID))
        {
            QMessageBox::critical(NULL, tr("add 失败"), tr("该user  already 经是该群成员"));
            return;
        }
    }

    bool isOkMes = false;
    QString checkMes = QInputDialog::getText(NULL, "add 群成员",
                       " please  input verify 信息",
                       QLineEdit::Normal,
                       QString(tr("hello,我是群%1(%2),s 群 main ，request  your 加入我们,s 群")).
                                             arg(m_flockInfo.m_flockID,
                                                 m_flockInfo.m_flockName),
                       &isOkMes);
    if (!isOkMes)
        return;

//    TempStrings temp;
//    temp.m_one = m_myself.m_userID;
//    temp.m_two = friendID;
//    temp.m_three = checkMes;

    TalkMessage mes;
    mes.m_senderID = m_flockInfo.m_flockID; // 群ID
    mes.m_receiverID = memberID;  // 成员ID
    mes.m_text = checkMes;
    mes.m_type = FLOCK_REQUEST;

    if (NULL != m_mainCtrl)
        m_mainCtrl->addFlock(mes);
}

/*************************************************
Function Name: onClickEnterSpace()
Description: 进入空间
*************************************************/
void IMFlockButton::onClickEnterSpace()
{
}

/*************************************************
Function Name: chatRoomQuit()
Description: 聊天窗口close 了
*************************************************/
void IMFlockButton::chatRoomQuit()
{
    m_isOpen = false;
    m_isShow = false;
    if (NULL != m_mainWidget)
        m_mainWidget->removeFlockChatWidget(m_flockInfo.m_flockID);
}

/*************************************************
Function Name: setFlockMemeberList()
Description:  set 群成员 table  
*************************************************/
void IMFlockButton::setFlockMemberList(const QVector<FlockMember> & memberList)
{
    int len = memberList.size();
    if (len <= 0) return;


    //  other ,s flockrequest server  get 群成员,s 时候，
    // 会影响到 other ,s flock， 可以 判断一下flockID.
    if (0 != memberList[0].m_flockID.compare(m_flockInfo.m_flockID))
        return;

//    getRoomPoint()->setFlockMemberList(memberList);
//    int len = memberList.size();
    m_flockMembersVec.clear();
    m_flockMembersVec.resize(len);
    for(int i=0; i<len; i++)
    {
        m_flockMembersVec[i] = memberList[i];
    }

}

//remark:protected:----------------------------------------

/*************************************************
Function Name: mousePressEvent
Description:  mouse 单击 event 
*************************************************/
void IMFlockButton::mousePressEvent(QMouseEvent *event)
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
void IMFlockButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
//        emit leftDoubleClickSignal();
        onDoubleClickFlockButton();
        return;
    }
    QPushButton::mouseDoubleClickEvent(event);
}


//remark:private:----------------------------------------
/*************************************************
Function Name: getStatusFromInt()
Description: create  right button  menu 
*************************************************/
void IMFlockButton::creatMenu(/*const QList<QString> *groutList*/)
{
    m_menu = new QMenu(this);
    QAction *sendMessage = new QAction(tr("发送群消息"), m_menu);
    QAction *showRecord = new QAction(tr("查看消息记录"), m_menu);
    QAction *showInfo = new QAction(tr("查看资料"), m_menu);
    QAction *enterSpace = new QAction(tr("进入群空间"), m_menu);
    // mark
    // add  群成员
    // modify 群资料 放在查看资料里面
    // delete   群成员

    connect(sendMessage, SIGNAL(triggered()),
        this, SLOT(onDoubleClickFlockButton()));
    connect(showRecord, SIGNAL(triggered()),
        this, SLOT(onClickShowRecord()));
    connect(showInfo, SIGNAL(triggered()),
        this, SLOT(onClickShowInformation()));
    connect(enterSpace, SIGNAL(triggered()),
        this, SLOT(onClickEnterSpace()));

    m_menu->addAction(sendMessage);
    m_menu->addAction(showRecord);
    m_menu->addAction(showInfo);
    m_menu->addAction(enterSpace);
    m_menu->addSeparator();

    if (m_mainWidget == NULL)
        return;

    if (m_mainWidget->getLocalMyInformation().m_userID == m_flockInfo.m_creatorID)
    {
        QAction *dropFlock = new QAction(tr("解散该群"), m_menu);
        connect(dropFlock, SIGNAL(triggered()),
                this, SLOT(onClickDropFlock()));
        m_menu->addAction(dropFlock);

        QAction *addMember = new QAction(tr("add 群成员"), m_menu);
        connect(addMember, SIGNAL(triggered()),
                this, SLOT(onClickAddMemberFlock()));
        m_menu->addAction(addMember);
    }
    else
    {
        QAction *leaveFlock = new QAction(tr(" quit from  该群"), m_menu);
        connect(leaveFlock, SIGNAL(triggered()),
            this, SLOT(onClickLeaveFlock()));
        m_menu->addAction(leaveFlock);
    }
}
