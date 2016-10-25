#ifndef IMFLOCKMEMBERBUTTON_H
#define IMFLOCKMEMBERBUTTON_H

#include <QPushButton>
#include "model/IMConstant.h"

class QMenu;
class QLabel;
class IMFlockChatWidget;
class IMChatWidget;
class IMMainWidget;
class IMMainCtrl;
\
class IMFlockMemberButton : public QPushButton
{
    Q_OBJECT
public:
    IMFlockMemberButton(const FlockMember &, IMFlockChatWidget *,
                        IMMainWidget *, QWidget *parent = 0);
    ~IMFlockMemberButton();

    FlockMember &getInformation()
    {	return m_info;	}
    FlockMember getInformation() const
    {	return m_info;	}
    void setChangedInformation(const FlockMember & mem)
    {
        if (m_info.m_flockID != mem.m_flockID)
            return;
        if (m_info.m_flockID != mem.m_userID)
            return;

        m_info.m_headPortrait = mem.m_headPortrait;
        m_info.m_nickname = mem.m_nickname;
        // m_loginStatus;
        m_info.m_remark = mem.m_remark;
        // m_flockStatus;
        // m_joinDate



    }

    void setRemark(const TempStrings & tmpStr)
    {
        if (0 != tmpStr.m_one.compare(m_info.m_flockID))
            return;
        if (0 != tmpStr.m_two.compare(m_info.m_userID))
            return;

        m_info.m_remark = tmpStr.m_three;

        setButtonStatus();
    }

    // open 聊天窗口
    void openChatRoom();
    // close 聊天窗口
    void closeChatRoom();
    // 设置button显示信息
    void setButtonStatus();

signals:
    void deleteMemberSignal(const QString &);
public slots:

    // 右键点击按键
    void onClickRightButton(/*const QPoint &*/);

    // 发送即时消息
    void onClickSendMessage();
    //  发送电子邮件
    void onClickSendMail();
    // 显示成员详细信息
    void onClickShowInformation();
    // modify群名片
    void onClickChangeRemark();
    // 进入空间
    void onClickEnterSpace();
    // 移除该成员
    void onClickRemoveMember();
    // 加为好友
    void onClickAddFriend();

    // 左键 双击
    void onDoubleClickMemberButton();
    //聊天窗口close 了
    void chatRoomQuit();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *);


private:
    // 将好友状态从数字形式转换为字符串形式
    QString getFlockStatusFromInt(const int n) const;

    // 将好友在线状态从数字形式转换为字符串形式
    QString getLoginStatusFromInt(const int n) const;
    // create 右键菜单
    void creatMenu(/*const QList<QString> *groutList*/);


private:
    FlockMember m_info;
    QString m_strFlockStatus; // 身份
    QString m_strLoginStatus; // 在线状态
    // 聊天窗口是否open 了
    bool m_isOpen;

    // 右键菜单
    QMenu *m_menu;
//    IMChatWidget *m_chatRoom;
    IMFlockChatWidget *m_flockWidget;
    IMMainWidget *m_mainWidget;
    IMMainCtrl *m_mainCtrl;

    QLabel *m_labelHead;
    QLabel *m_labelMes;

};

#endif // IMFLOCKMEMBERBUTTON_H
