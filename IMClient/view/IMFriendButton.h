#ifndef IMFRIENDBUTTON_H
#define IMFRIENDBUTTON_H

#include <QPushButton>
#include "model/IMConstant.h"

class QMenu;
class IMChatWidget;
class IMMainWidget;
class QLabel;

class IMFriendButton : public QPushButton
{
    Q_OBJECT
public:
    IMFriendButton(const FriendInformation &info, QList<QString> *groupList,
                   IMMainWidget *mainWidget, QWidget *parent = 0);
    ~IMFriendButton();

    bool isRoomOpen() const
    {
        return m_isOpen;
    }
    bool isRoomShow() const
    {
        return m_isShow;
    }
    IMChatWidget *getRoomPoint() const
    {
        return m_chatRoom;
    }
    FriendInformation &getInformation()
    {	return m_info;	}
    FriendInformation getInformation() const
    {	return m_info;	}
    void setChangedInformation(const FriendInformation & fri)
    {
        if (m_info.m_userID != fri.m_userID)
            return;
        m_info.m_headPortrait = fri.m_headPortrait;
        m_info.m_nickname = fri.m_nickname;
//        m_info.m_status = fri.m_status;
    }
    // create 聊天窗口
    void openChatRoom();
    // 显示聊天窗口
    void showChatRoom();
    // close 聊天窗口
    void closeChatRoom();

    // 设置button显示信息
    void setButtonStatus();
    // 刷 new  menu 中 box 信息
    void refreshMoveMenu();

signals:
    void deleteFriendSignal(const QString &);
//    void leftDoubleClickSignal();

public slots:
    // 左键 双击
    void onDoubleClickFriendButton();
    //  right button  click  button 
    void onClickRightButton(/*const QPoint &*/);

    // 发送即时消息
    void onClickSendMessage();
    // 查看消息记录
    void onClickShowRecord();
    // 发送电子邮件
    void onClickSendMail();
    // 显示好友详细信息
    void onClickShowInformation();
    //  click modify好友备注
    void onClickChangeRemark();
    //  move 好友至 other  box 
    void onClickMove();
    // delete  好友
    void onClickRemoveFriend();
    // 进入空间
    void onClickEnterSpace();

    //聊天窗口close 了
    void chatRoomQuit();

//    //modify好友状态
//    void changeRemark(const QString &newRemark);
//    void changeStatus(int status);

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *);



private:
    // 将好友状态从数字形式转换为字符串形式
    QString getStatusFromInt(const int n) const;
    // create  right button  menu 
    void creatMenu(/*const QList<QString> *groutList*/);


private:
    FriendInformation m_info;
    //以字符串形式储存好友状态信息
    QString m_strStatus;
    // 聊天窗口是否open 了
    bool m_isOpen;
    // 聊天窗口是否显示
    bool m_isShow;
    //  right button  menu 
    QMenu *m_menu;
    QMenu *m_moveFriendMenu;
    IMChatWidget *m_chatRoom;
    IMMainWidget *m_mainWidget;

    QLabel *m_labelHead;
//    QIcon *m_iconHead;
    QLabel *m_labelMes;

    QList<QString> *m_groupList;
};

#endif // IMFRIENDBUTTON_H
