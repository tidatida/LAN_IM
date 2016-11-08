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

    FlockMember &getInformation(){	
        return m_info;	
    }

    FlockMember getInformation() const{	
        return m_info;	
    }

    void setChangedInformation(const FlockMember & mem){
        if (m_info.m_flockID != mem.m_flockID){
            return;
        }

        if (m_info.m_flockID != mem.m_userID){
            return;
        }

        m_info.m_headPortrait = mem.m_headPortrait;
        m_info.m_nickname = mem.m_nickname;
        m_info.m_remark = mem.m_remark;
    }

    void setRemark(const TempStrings & tmpStr){
        if (0 != tmpStr.m_one.compare(m_info.m_flockID)){
            return;
        }

        if (0 != tmpStr.m_two.compare(m_info.m_userID)){
            return;
        }

        m_info.m_remark = tmpStr.m_three;

        setButtonStatus();
    }

    void openChatRoom();
    void closeChatRoom();
    void setButtonStatus();

signals:
    void deleteMemberSignal(const QString &);
public slots:

    void onClickRightButton(/*const QPoint &*/);
    void onClickSendMessage();
    void onClickSendMail();

    void onClickShowInformation();
    void onClickChangeRemark();
    void onClickEnterSpace();
    void onClickRemoveMember();
    void onClickAddFriend();

    void onDoubleClickMemberButton();
    void chatRoomQuit();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *);


private:
    QString getFlockStatusFromInt(const int n) const;

    QString getLoginStatusFromInt(const int n) const;
    void creatMenu(/*const QList<QString> *groutList*/);

private:
    FlockMember m_info;
    QString m_strFlockStatus;
    QString m_strLoginStatus;
    bool m_isOpen;

    //  right button  menu 
    QMenu *m_menu;
    IMFlockChatWidget *m_flockWidget;
    IMMainWidget *m_mainWidget;
    IMMainCtrl *m_mainCtrl;

    QLabel *m_labelHead;
    QLabel *m_labelMes;

};

#endif // IMFLOCKMEMBERBUTTON_H
