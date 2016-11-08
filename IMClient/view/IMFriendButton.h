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

    
    void openChatRoom();
    void showChatRoom();
    void closeChatRoom();

    void setButtonStatus();
    void refreshMoveMenu();

signals:
    void deleteFriendSignal(const QString &);

public slots:
    void onDoubleClickFriendButton();
    void onClickRightButton(/*const QPoint &*/);

    void onClickSendMessage();
    void onClickShowRecord();
    void onClickSendMail();
    void onClickShowInformation();
    void onClickChangeRemark();
    void onClickMove();
    void onClickRemoveFriend();
    void onClickEnterSpace();

    void chatRoomQuit();


protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *);



private:
    QString getStatusFromInt(const int n) const;
    void creatMenu(/*const QList<QString> *groutList*/);


private:
    FriendInformation m_info;
    QString m_strStatus;
    bool m_isOpen;
    bool m_isShow;
    QMenu *m_menu;
    QMenu *m_moveFriendMenu;
    IMChatWidget *m_chatRoom;
    IMMainWidget *m_mainWidget;

    QLabel *m_labelHead;
    QLabel *m_labelMes;

    QList<QString> *m_groupList;
};

#endif // IMFRIENDBUTTON_H
