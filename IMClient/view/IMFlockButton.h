#ifndef IMFLOCKBUTTON_H
#define IMFLOCKBUTTON_H

#include <QPushButton>
#include "model/IMConstant.h"

class QMenu;
class QLabel;
class IMMainWidget;
class IMFlockChatWidget;
class IMMainCtrl;

class IMFlockButton : public QPushButton
{
    Q_OBJECT
public:
    IMFlockButton(const FlockInformation &info, IMMainWidget *mainWidget,
                  QWidget *parent = 0);
    ~IMFlockButton();
    
    bool isRoomOpen() const
    {
        return m_isOpen;
    }
    bool isRoomShow() const
    {
        return m_isShow;
    }
    IMFlockChatWidget *getRoomPoint() const
    {
        return m_flockRoom;
    }
    FlockInformation &getInformation()
    {	return m_flockInfo;	}
    FlockInformation getInformation() const
    {	return m_flockInfo;	}
    void setChangedInformation(const FlockInformation & flock)
    {
        if (m_flockInfo.m_flockID != flock.m_flockID)
            return;

//        m_flockInfo.m_creatorID = flock.m_creatorID;
//        m_flockInfo.m_createDate = flock.m_createDate;
        m_flockInfo.m_flockName = flock.m_flockName;
        m_flockInfo.m_theme = flock.m_theme;
        setButtonStatus();
    }
    // open 聊天窗口
    void openChatRoom();
    // 显示聊天窗口
    void showChatRoom();
    // close 聊天窗口
    void closeChatRoom();

    //  set button显示信息
    void setButtonStatus();

    // delete  群成员
    void deleteFlockMember(const QString & memberID);
    // add 群成员
    void addFlockMember(const QString & memberID);

signals:
    void leaveFlockSignal(const QString &);

public slots:
    // 左键 双击
    void onDoubleClickFlockButton();
    //  right button  click  button 
    void onClickRightButton();
    // 发送群消息
    void onClickSendMessage();
    // 查看消息记录
    void onClickShowRecord();
    // 显示群详细信息
    void onClickShowInformation();
    // 解散群
    void onClickDropFlock();
    //  quit from  群
    void onClickLeaveFlock();
    // add 群成员
    void onClickAddMemberFlock();
    // 进入空间
    void onClickEnterSpace();
    //聊天窗口close 了
    void chatRoomQuit();

    //  set 成员 table  
    void setFlockMemberList(const QVector<FlockMember> &);

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *);

private:
    // create  right button  menu 
    void creatMenu(/*const QList<QString> *groutList*/);

private:
    FlockInformation m_flockInfo;

    // 聊天窗口是否open 了
    bool m_isOpen;
    // 聊天窗口是否显示
    bool m_isShow;
    //  right button  menu 
    QMenu *m_menu;
//    IMFlockChatWidget *m_chatRoom;
    IMMainWidget *m_mainWidget;
    IMMainCtrl *m_mainCtrl;

    QLabel *m_labelHead;
//    QIcon *m_iconHead;
    QLabel *m_labelMes;
    IMFlockChatWidget *m_flockRoom;
    QVector<FlockMember> m_flockMembersVec;
};

#endif // IMFLOCKBUTTON_H
