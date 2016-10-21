#ifndef IMDISCUSSIONBUTTON_H
#define IMDISCUSSIONBUTTON_H

#include <QPushButton>
#include "model/IMConstant.h"

class QMenu;
class QLabel;
class IMMainWidget;
class IMDiscussionChatWidget;
class IMMainCtrl;

class IMDiscussionButton : public QPushButton
{
    Q_OBJECT
public:
    IMDiscussionButton(const DiscussionInformation &info, IMMainWidget *mainWidget = 0,
                                QWidget *parent = 0);
    ~IMDiscussionButton();

    bool isRoomOpen() const
    {
        return m_isOpen;
    }
    bool isRoomShow() const
    {
        return m_isShow;
    }
    IMDiscussionChatWidget *getRoomPoint() const
    {
        return m_discussionRoom;
    }
    DiscussionInformation &getInformation()
    {	return m_discussionInfo;	}
    DiscussionInformation getInformation() const
    {	return m_discussionInfo;	}
    void setChangedInformation(const DiscussionInformation & discussion)
    {
        if (m_discussionInfo.m_discussionID != discussion.m_discussionID)
            return;

        m_discussionInfo.m_creatorID = discussion.m_creatorID;
        m_discussionInfo.m_createDate = discussion.m_createDate;
        m_discussionInfo.m_discussionName = discussion.m_discussionName;
        m_discussionInfo.m_theme = discussion.m_theme;
        setButtonStatus();
    }

    void openChatRoom();
    void showChatRoom();
    void closeChatRoom();

    void setButtonStatus();

    void deleteDiscussionMember(const QString & memberID);
    void addDiscussionMember(const QString & memberID);

signals:
    void leaveDiscussionSignal(const QString &);

public slots:
    void onDoubleClickDiscussionButton();
    void onClickRightButton();
    void onClickSendMessage();
    void onClickShowRecord();
    void onClickDropDiscussion();
    void onClickLeaveDiscussion();
    void onClickAddMember();
    void onClickShowInformation();
    void chatRoomQuit();

    void setDiscussionMemberList(const QVector<DiscussionMember> &);

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *);

private:
    void creatMenu(/*const QList<QString> *groutList*/);

private:
    DiscussionInformation m_discussionInfo;

    bool m_isOpen;
    bool m_isShow;
    QMenu *m_menu;
    IMDiscussionChatWidget *m_discussionRoom;
    IMMainWidget *m_mainWidget;
    IMMainCtrl *m_mainCtrl;
    QVector<DiscussionMember> m_discussionMembersVec;

    QLabel *m_labelHead;
//    QIcon *m_iconHead;
    QLabel *m_labelMes;
};

#endif // IMDISCUSSIONBUTTON_H
