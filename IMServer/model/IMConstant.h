/*********************************************
File Name: IMConstant.h
Author: jet.F.R
Date: 2014.3.10
Description:define a structure and constant parameter.
Changes:
********************************************/

#ifndef IMCONSTANT_H
#define IMCONSTANT_H

#include <QFont>
#include <QColor>
#include <QDataStream>
#include <QDateTime>
#include <QVector>
#include <QString>
#include <QObject>
class IMClientSocketCtrl;

static const QString GROUP_NAME_DEFAULT = QString(QObject::tr("New Friends"));

struct ServerNode
{
    QString ipAddress;			/* server ip address */
    int port;					/* server port */
    ServerNode()
    {	port = 0;	}
};

/* login status */
enum LoginStatus
{
    ONLINE = 0,    /* online */
    INVISIBLE = 1, /* hided */ 
    BUSY = 2,      /* busying */
    LEAVE = 3,     /* leaved away */
    NOTDISTURB = 4,/* no disturb */
    OFFLINE = 5    /* offline */
};

/* group identity */
enum FlockStatus
{
    FLOCK_HOST = 0,    /* group owner */
    FLOCK_ADMAIN = 1,  /* group admin */
    FLOCK_MEMBER = 2   /* group memeber */
};

/* discuss group identity */
enum DiscussionStatus
{
    DISCUSSION_HOST = 0,    /* chargeman */
    DISCUSSION_MEMBER = 1   /* discuss memeber */
};

enum MailStatus
{
    MAIL_UNREAD = 0,
    MAIL_READ = 1
};


/* msg type */
enum MessageType
{
    /***********************client to server************************/
    CHECK_CONNECTION,           /* wether connected with server */
    LOGIN,                      /* login */
    REGISTER,                   /* register */
    GET_QUESTION_ANSWER,    /* get question and answer foe recover passwd */
    GET_QUESTION_ANSWER_SUCCESS,
    GET_QUESTION_ANSWER_FAIL,

    CHECK_MESSAGE,              /* check if there is msg for me */ 

    GET_ALL_FRIENDS,            /* get friends info */
    GET_ALL_FLOCKS,             /* get all groups info */
    GET_ALL_DISCUSSIONS,        /* get all discuss group info */
    GET_FLOCK_MEMBERS,          /* get all memebers of a group */
    GET_DISCUSSIONS_MEMBERS,    /* get all memebers of a discuss group */

    TALK,				/* start a talk session */
    ADD_FRIEND,                 /* add a friend */



    ADD_FLOCK,                   /* add to a group */
    ADD_DISCUSSION,              /* add to a discuss session */

    FLOCK_ADD_MEMBER,            /* add group memeber */

    GET_FRIEND_INFORMATION,		/* get a friend info */
    DELETE_FRIEND,				/* delete a friend */
    GET_MYSELF_INFORMATION,		/* get myself info */
    CHANGE_INFORMATION,			/* chang myself info */
    CHANGE_REMARK,				/* change mem of a friend */
    CHANGE_PASSWORD,			/* change my passwd  */
    CHANGE_STATUE,				/* change my status */
    /* there is also seperate friend into group */
    QUIT,						/* quit */

    /***********************server to client************************/

    LOGIN_SUCCESS ,
    LOGIN_FAIL,
    HAVE_LOGINED,
    REGISTER_SUCCESS,
    REGISTER_FAIL,

    REMOVE_BOX,
    REMOVE_BOX_SUCCESS,
    REMOVE_BOX_FAIL,
    RENAME_BOX,
    RENAME_BOX_SUCCESS,
    RENAME_BOX_FAIL,
    CREATE_BOX,
    CREATE_BOX_SUCEESS,
    CREATE_BOX_FAIL,
    MOVE_FRIEND_BOX,
    MOVE_FRIEND_BOX_SUCCESS,
    MOVE_FRIEND_BOX_FAIL,


    GET_ALL_FRIENDS_SUCCESS,
    GET_ALL_FRIENDS_FAIL,
    NO_FRIEND,
    GET_ALL_FLOCKS_SUCCESS,
    GET_ALL_FLOCKS_FAIL,
    NO_FLOCK,
    GET_ALL_DISCUSSIONS_SUCCESS,
    GET_ALL_DISCUSSIONS_FAIL,
    NO_DISCUSSION,

    GET_FLOCK_MEMBERS_FAIL,
    GET_FLOCK_MEMBERS_SUCCESS,
    NO_FLOCK_MEMBER,
    GET_DISCUSSION_MEMBERS_FAIL,
    GET_DISCUSSION_MEMBERS_SUCCESS,
    NO_DISCUSSION_MEMBER,

    NO_MESSAGE,
    HAVE_MESSAGE,
    HAVE_TALK_MESSAGE,

    FRIEND_REQUESTED,
    FRIEDN_NO_ACCOUNT,
    ALREAD_FRIENDS,			    /* reply friend */

    GET_FRIEND_FAIL,
    GET_FRIEND_SUCCESS,
    DELETE_FRIEND_FAIL,
    DELETE_FRIEND_SUCCESS,
    GET_MYSELF_FAIL,
    GET_MYSELF_SUCCESS,
    CHANGE_INFORMATION_FAIL,
    CHANGE_INFORMATION_SUCCESS,

    CHANGE_REMARK_FAIL,
    CHANGE_REMARK_SUCCESS,

    OLD_PWD_IS_WRONG,
    CHANGE_PWD_FAIL,
    CHANGE_PWD_SUCCESS,

    /***********************client to client************************/

    REQUEST_FRIEND,
    AGREE_FRIEND,
    REFUSE_FRIEND,
    ADD_FRIEND_FAIL,
    ADD_FRIEND_SUCCESS,
    END_ADD_FRIEND,
    BE_DELETED,		     /* deleted by others */

    MESSAGE,
    TALK_MESSAGE,

    REQUEST_FLOCK,
    FLOCK_AGREE,
    FLOCK_REFUSE,
    ADD_FLOCK_FAIL,
    ADD_FLOCK_SUCCESS,
    NEW_FLOCK_MEMBER,
    LEAVE_FLOCK_MEMBER,


    FLOCK_REQUEST,
    AGREE_FLOCK,
    REFUSE_FLOCK,


    CREATE_FLOCK,
    CREATE_FLOCK_FAIL,
    CREATE_FLOCK_SUCCESS,

    CREATE_DISCUSSION,
    CREATE_DISCUSSION_FAIL,
    CREATE_DISCUSSION_SUCCESS,

    DROP_FLOCK,
    DROP_FLOCK_FAIL,
    DROP_FLOCK_SUCCESS,

    DROP_DISCUSSION,
    DROP_DISCUSSION_FAIL,
    DROP_DISCUSSION_SUCCESS,

    LEAVE_FLOCK,
    LEAVE_FLOCK_SUCCESS,
    LEAVE_FLCCK_FAIL,
    LEAVE_DISCUSSION,
    LEAVE_DISCUSSION_FAIL,
    LEAVE_DISCUSSION_SUCCESS,


    ADD_DISCUSSION_FAIL,
    ADD_DISCUSSION_SUCCESS,
    NEW_DISCUSSION_MEMBER,
    LEAVE_DISCUSSION_MEMBER,

    CHANGE_FLOCK,
    CHANGE_FLOCK_SUCCESS,
    CHANGE_FLOCK_FAIL,

    CHANGE_FLOCK_REMARK,
    CHANGE_FLOCK_REMARK_FAIL,
    CHANGE_FLOCK_REMARK_SUCCESS,

    CHANGE_DISCUSSION,
    CHANGE_DISCUSSION_SUCCESS,
    CHANGE_DISCUSSION_FAIL,

    TALK_FLOCK,               /* large-group talk  */ 
    TALK_DISCUSSION,          /* group talk */

    REQUEST_VIDEO,
    REFUSE_VIDEO,
    END_VIDEO,
    REQUEST_VOICE,
    AGREE_VOICE,
    REFUSE_VOICE,
    END_VOICE,
    REQUEST_FILE,
    AGREE_FILE,
    REFUSE_FILE,
    END_FILE,

    /* mail modules */
    GET_IN_MAILS,
    GET_IN_MAILS_SUCCESS,
    GET_IN_MAILS_FAIL,

    GET_OUT_MAILS,
    GET_OUT_MAILS_SUCCESS,
    GET_OUT_MAILS_FAIL,

    SEND_MAIL,
    SEND_MAIL_SUCCESS,
    SEND_MAIL_FAIL,

    RECEIVE_MAIL,
    RECEIVE_MAIL_SUCCESS,
    RECEIVE_MAIL_FAIL,

    DELETE_IN_MAIL,
    DELETE_IN_MAIL_SUCCESS,
    DELETE_IN_MAIL_FAIL,
    DELETE_OUT_MAIL,
    DELETE_OUT_MAIL_SUCCESS,
    DELETE_OUT_MAIL_FAIL,

    SET_MAIL_READ,

    GET_HISTORY_MESSAGE,
    GET_HISTORY_MESSAGE_SUCCESS,
    GET_HISTORY_MESSAGE_FAIL
};


/* store font-type and font-color */
struct SaveFile
{
    QFont m_font;
    QColor m_color;
    friend QDataStream & operator<< (QDataStream &out, const SaveFile &sf)
    {
       out << sf.m_font << sf.m_color;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, SaveFile &sf)
    {
       in >> sf.m_font >> sf.m_color;
       return in;
    }
};

struct MailInformation
{
    int m_mailID;
    QString m_senderAddress;
    QString m_receiverAddress;
    QString m_theme;
    QString m_content;
    QDateTime m_dateTime;
    int m_status;

    MailInformation()
    {
        m_status = MAIL_UNREAD;
    }

    /* redefine ip operator */
    friend QDataStream &operator<<(QDataStream &out, const MailInformation &mail)
    {
        out << mail.m_mailID << mail.m_senderAddress << mail.m_receiverAddress
            << mail.m_theme << mail.m_content << mail.m_dateTime << mail.m_status;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, MailInformation &mail)
    {
        in >> mail.m_mailID >> mail.m_senderAddress >> mail.m_receiverAddress
           >> mail.m_theme >> mail.m_content >> mail.m_dateTime >> mail.m_status;
        return in;
    }
};

/* user info */
struct UserInformation
{
    //    QString m_picture;
    int m_headPortrait;
    QString m_userID;
    QString m_nickname;
    QString m_password;
    QString m_sex;
    QDate m_birthday;
    QString m_question;
    QString m_answer;
    QString m_name;
    QString m_phone;
    QString m_address;
    QDateTime m_regDateTime;
    //    QString m_mark;
    int m_status;

    UserInformation()
    {
       m_status = OFFLINE;
       m_headPortrait = 1;
    }
    /* redefine ip operator */
    friend QDataStream &operator<<(QDataStream &out, const UserInformation &user)
    {
       out << user.m_headPortrait << user.m_userID << user.m_nickname
           << user.m_password << user.m_sex << user.m_birthday
           << user.m_question << user.m_answer << user.m_name
           << user.m_phone << user.m_address << user.m_regDateTime
           << user.m_status;
       return out;
    }

    friend QDataStream &operator>>(QDataStream &in, UserInformation &user)
    {
       in >> user.m_headPortrait >> user.m_userID >> user.m_nickname
          >> user.m_password >> user.m_sex >> user.m_birthday
          >> user.m_question >> user.m_answer >> user.m_name
          >>  user.m_phone >> user.m_address >> user.m_regDateTime
          >> user.m_status;
       return in;
    }
};

/* freind info */
struct FriendInformation
{
//    QString m_picture;
    int m_headPortrait;
    QString m_userID;
    QString m_nickname;
    QString m_groupName;
    QString m_remarkName;
    int m_status;

    FriendInformation()
    {
       m_status = OFFLINE;
       m_headPortrait = 1;
       m_groupName = GROUP_NAME_DEFAULT;
    }

    //重载 input 输出操作符
    friend QDataStream & operator<< (QDataStream &out,
                                    const FriendInformation &fri)
    {
       out << fri.m_headPortrait << fri.m_userID << fri.m_nickname
           << fri.m_groupName << fri.m_remarkName << fri.m_status;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, FriendInformation &fri)
    {
       in >> fri.m_headPortrait >> fri.m_userID >> fri.m_nickname
          >> fri.m_groupName >> fri.m_remarkName >> fri.m_status;
       return in;
    }
};

/* msg stroed in vary little windows */
struct TempStrings
{
    QString m_one;
    QString m_two;
    QString m_three;
    friend QDataStream & operator<< (QDataStream &out, const TempStrings &str)
    {
       out << str.m_one << str.m_two << str.m_three;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, TempStrings &str)
    {
       in >> str.m_one >> str.m_two >> str.m_three;
       return in;
    }
};

/* chat window info */
struct ChatInformation
{
     QString m_myID;
//     QString m_myNickname;
    int m_headPortrait;
    QString m_friendID;
    QString m_friendNickname;
    QString m_friendRemark;
    QString m_friendMark;
    QString m_friendIP;
    int m_friendStatus;

    ChatInformation()
    {
       m_friendStatus = OFFLINE;
       m_headPortrait= 1;
       m_friendMark = QString(QObject::tr("friend signature"));
    }

//    /* redifne operator */
//    friend QDataStream & operator<< (QDataStream &out, const ChatInformation &chat)
//    {
//       out << chat.m_headPortrait << chat.m_friendID << chat.m_friendNickname
//           << chat.m_friendRemark << chat.m_friendMark << chat.m_friendIP;
//       return out;
//    }
//    friend QDataStream & operator>> (QDataStream &in, ChatInformation &chat)
//    {
//       in >> chat.m_headPortrait >> chat.m_friendID >> chat.m_friendNickname
//          >> chat.m_friendRemark >> chat.m_friendMark >> chat.m_friendIP;
//       return in;
//    }
};

/* talk msg */
struct TalkMessage
{
    int m_type;               /* msg type */
    QString m_senderID;       /* sender id */
    QString m_senderIP;       /* sender ip */
    QString m_receiverID;     /* receiver id */
    QString m_receiverIP;     /* receiver ip */
    QString m_text;           /* msg content */
    QDateTime m_dateTime;

    TalkMessage() {	m_type = 0; }

    friend QDataStream & operator<< (QDataStream &out, const TalkMessage &mes)
    {
       out << mes.m_type << mes.m_senderID << mes.m_senderIP << mes.m_receiverID
           << mes.m_receiverIP << mes.m_text << mes.m_dateTime;
       return out;
    }

    friend QDataStream & operator>> (QDataStream &in, TalkMessage &mes)
    {
       in >> mes.m_type >> mes.m_senderID >> mes.m_senderIP >> mes.m_receiverID
          >> mes.m_receiverIP >> mes.m_text >>  mes.m_dateTime;
       return in;
    }
};

/* user login info */
struct LoginInformation
{
    QString m_userID;
    QString m_password;
    int m_status;

    LoginInformation()
    {	m_status = OFFLINE;	}
    friend QDataStream & operator<< (QDataStream &out, const LoginInformation &li)
    {
       out << li.m_userID << li.m_password << li.m_status;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, LoginInformation &li)
    {
       in >> li.m_userID >> li.m_password >> li.m_status;
       return in;
    }
};

/* discussion-group memeber */
struct FlockMember
{
    QString m_flockID;     /* group id  */
    QString m_userID;      /* user id */
    int m_headPortrait;    /* avatar id */
    QString m_nickname;    /* user nick name*/
    int m_loginStatus;     /* login status */
    QString m_remark;      /* name in this disscussion-group */
    int m_flockStatus;     /* user id */
    QDateTime m_joinDate;  /* join timestamp */

    friend QDataStream & operator<< (QDataStream &out, const FlockMember &flockMember)
    {
       out << flockMember.m_flockID << flockMember.m_userID
           << flockMember.m_headPortrait << flockMember.m_nickname
           << flockMember.m_loginStatus << flockMember.m_remark
           << flockMember.m_flockStatus << flockMember.m_joinDate;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, FlockMember &flockMember)
    {
       in >> flockMember.m_flockID >> flockMember.m_userID
          >> flockMember.m_headPortrait >> flockMember.m_nickname
          >> flockMember.m_loginStatus >> flockMember.m_remark
          >> flockMember.m_flockStatus >> flockMember.m_joinDate;
       return in;
    }
};

/* discussion memeber */
struct DiscussionMember
{
    QString m_discussionID;/* discussion id */
    QString m_userID;      /* user id */
    int m_headPortrait;    /* avatar id */
    QString m_nickname;    /* user nick name */
    int m_loginStatus;     /* login status */
    int m_discussionStatus;/* user id */
    QDateTime m_joinDate;  /* join timestamp */

    friend QDataStream & operator<< (QDataStream &out, const DiscussionMember &disMember)
    {
       out << disMember.m_discussionID << disMember.m_userID
           << disMember.m_headPortrait << disMember.m_nickname
           << disMember.m_loginStatus << disMember.m_discussionStatus
           << disMember.m_joinDate;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, DiscussionMember &disMember)
    {
       in >> disMember.m_discussionID >> disMember.m_userID
          >> disMember.m_headPortrait >> disMember.m_nickname
          >> disMember.m_loginStatus  >> disMember.m_discussionStatus
          >> disMember.m_joinDate;
       return in;
    }
};

/* group info */
struct FlockInformation
{
    QString m_flockID;
    QString m_creatorID;
    QDate m_createDate;
    QString m_flockName;
    QString m_theme;

    friend QDataStream & operator<< (QDataStream &out, const FlockInformation &flock)
    {
       out << flock.m_flockID << flock.m_creatorID << flock.m_createDate
           << flock.m_flockName << flock.m_theme;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, FlockInformation &flock)
    {
       in >> flock.m_flockID >> flock.m_creatorID >> flock.m_createDate
          >> flock.m_flockName >> flock.m_theme;
       return in;
   }
};

/* discussion info */
struct DiscussionInformation
{
    QString m_discussionID;
    QString m_creatorID;
    QDate m_createDate;
    QString m_discussionName;
    QString m_theme;

    friend QDataStream & operator<< (QDataStream &out, const DiscussionInformation &dis)
    {
       out << dis.m_discussionID << dis.m_creatorID << dis.m_createDate
           << dis.m_discussionName << dis.m_theme;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, DiscussionInformation &dis)
    {
       in >> dis.m_discussionID >> dis.m_creatorID >> dis.m_createDate
          >> dis.m_discussionName >> dis.m_theme;
       return in;
    }
};

/* strcture to store tmp msg, used by signal/slot */
struct SaveTmpInformation
{
    int m_requestKind;
    int m_replyKind;
    IMClientSocketCtrl *m_clientSocket;

    QString m_myID;
    QString m_peerID;
    QDate m_date;
    QString m_groupName;
    QString m_groupNameF;
    UserInformation m_userInf;
    LoginInformation m_loginInf;
    FriendInformation m_friendInf;
    TalkMessage m_message;
    int m_status;
    TempStrings m_tempStr;
    QVector<TalkMessage> m_messageVec;
    QVector<FriendInformation> m_friendsVec;
    QVector<QString> m_IDVec;

    QString m_flockID;
    FlockMember m_flockMember;
    FlockInformation m_flockInf;
    QVector<FlockInformation> m_flocksVec;
    QVector<FlockMember> m_flockMembersVec;
    QString m_discussionID;
    DiscussionMember m_discussionMember;
    DiscussionInformation m_discussionInf;
    QVector<DiscussionInformation> m_discussionsVec;
    QVector<DiscussionMember> m_discussionMembersVec;

    int m_mailID;
    MailInformation m_mail;
    QVector<MailInformation>  m_inMailsVec;
    QVector<MailInformation>  m_outMailsVec;

    QString m_title;
    QString m_newTitle;

    QString m_socketID;

    QVector<TalkMessage> m_historyMessageVec;
};


/* avatar size */
const int HEAD_BIG_SIZE = 40;
const int HEAD_SMALL_SIZE = 35;
const int HEAD_MINI_SIZE = 20;

/* chat room size */
const int CHAT_WIDGET_TOOL_SIZE = 20;
const int CHAT_WIDGET_TOOL_SMALL_SIZE = 15;

const int FONT_SIZE = 2;

static const QString MAIL_ADDRESS_FORMAT = "@im.com";

static const QString LOCAL_HISTORY_MESSAGE_PATH = "resource/history/local/";
static const QString NETWORK_HISTORY_MESSAGE_PATH = "resource/history/network/";

#endif // IMCONSTANT_H
