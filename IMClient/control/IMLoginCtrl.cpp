/*********************************************
File Name: IMLoginCtrl.cpp
Author: jet.F.R
Date: 2014.3.10
Description:
Changes:
********************************************/

#include "IMLoginCtrl.h"
#include "model/IMConstant.h"
#include "model/IMEncryption.h"

#include <QMessageBox>
#include <QHostAddress>
#include <QDataStream>
#include <QDateTime>
#include <QtNetwork>
#include <QInputDialog>
#include <QDebug>

#define dbg qDebug()<<"FILE.("<<__FILE__<<") FUNCTION.("<<__FUNCTION__<<") LINE.("<<__LINE__<<")."

// public:-----------------------------------------------------------------
IMLoginCtrl::IMLoginCtrl(QObject *parent) :
    QObject(parent)
{ dbg;
    m_tcpSocket = new IMTcpSocket(this);
    m_tcpSocket->setFlag(1);
    connect(m_tcpSocket, SIGNAL(showConnectionStatus(QString, bool)),
            this, SLOT(changeLoginMessage(QString, bool)));

    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(sendRequest()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

IMLoginCtrl::~IMLoginCtrl()
{ dbg;
//    if (m_tcpSocket != NULL)
//    { dbg;
//        if (m_tcpSocket->isConnected())
//            m_tcpSocket->abort();
//            m_tcpSocket->close();
//        delete m_tcpSocket;
//        m_tcpSocket = NULL;
//    }
}


/*************************************************
Function Name: login()
Description: 
Input: const QString &id: , const QString &pwd:
*************************************************/
void IMLoginCtrl::login(const QString &id, const QString &pwd, const int status)
{ dbg;
    m_kind = LOGIN;
    m_loginInfo.m_userID = id;
    m_loginInfo.m_password = pwd;
    m_loginInfo.m_status = status;

    dbg;
    if (m_tcpSocket->isConnected())
    { dbg;
        dbg;
        requestLogin();
    }
    else
    { dbg;
        dbg;
        m_blockSize = 0;
        m_tcpSocket->requestConnect();
    }
    //delete clientSender;
}

/*************************************************
Function Name: getQuestionAndAnswer()
Description: 
*************************************************/
void IMLoginCtrl::getQuestionAndAnswer(const QString & id)
{ dbg;
    m_kind = GET_QUESTION_ANSWER;
    m_id = id;
    if (m_tcpSocket->isConnected())
    { dbg;
        requestGetQuestionAndAnswer();
    }
    else
    { dbg;
        m_blockSize = 0;
        m_tcpSocket->requestConnect();
    }
}

// mark: public slots:--------------------------------------------------------
/*************************************************
Function Name: changeLoginMessage()
Description: 
Input: const QString &mes: , bool isLogin:
Output: NULL
Changes: NULL
*************************************************/
void IMLoginCtrl::changeLoginMessage(const QString &mes, bool isLogin)
{ dbg;
    emit getLoginMessgae(mes, isLogin);
}

// mark: private slots:--------------------------------------------------

/*************************************************
Function Name: requestLogin()
Description: 
Input: NULL
Output: NULL
Changes: NULL
*************************************************/
void IMLoginCtrl::requestLogin()
{ dbg;
    dbg;
    if (NULL == m_tcpSocket){ dbg;
        dbg;
        return;
    }

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    // 
    out << quint16(0) << int(LOGIN) << m_loginInfo;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
    dbg;

}



/*************************************************
Function Name: sendRequest()
Description: 
*************************************************/
void IMLoginCtrl::sendRequest()
{ dbg;
    switch (m_kind)
    { dbg;
    case LOGIN:
    { dbg;
        dbg;
        requestLogin();
        break;
    }
    case GET_QUESTION_ANSWER:
    { dbg;
        dbg;
        requestGetQuestionAndAnswer();
        break;
    }
    default:
        dbg;
        break;
    }
}

// private slots:---------------------------------------------

/*************************************************
Function Name: requestGetQuestionAndAnswer()
Description: 
*************************************************/
void IMLoginCtrl::requestGetQuestionAndAnswer()
{ dbg;
    if (NULL == m_tcpSocket){ dbg;
        dbg;
        return;
    }

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    // 
    out << quint16(0) << int(GET_QUESTION_ANSWER) << m_id;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name: readMessage()
Description: 
Input: NULL
Output: NULL
Changes: NULL
*************************************************/
void IMLoginCtrl::readMessage()
{ dbg;
    QDataStream in(m_tcpSocket);
    // 
    if (m_blockSize == 0)
    { dbg;
        if (m_tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> m_blockSize;
    }

    if (m_tcpSocket->bytesAvailable() < m_blockSize)
        return;
    int type;

    in >> type;

//    QString id;
//    bool is;
//    QString nickName;
    switch (type)
    { dbg;
    case LOGIN_SUCCESS:
        in >> m_myself;
        emit getLoginMessgae(tr("login successfully"), true, &m_myself);
        break;
    case LOGIN_FAIL:
        emit getLoginMessgae(tr("login failed.account or passwd error."),false);
        break;
    case HAVE_LOGINED:
        emit getLoginMessgae(tr("login failed.account already exists.."),false);
        break;
    case GET_QUESTION_ANSWER_FAIL:
    { dbg;
        QMessageBox::critical(NULL, tr("reset passwd"), tr("failed, passwd doesn't exists.！"));
        break;
    }
    case GET_QUESTION_ANSWER_SUCCESS:
    { dbg;
        in >> m_tempStr;
        emit getQuestionAndAnswerSuccess(m_tempStr);

        while (1)
        { dbg;
            bool isOkMes = false;
            QString str = QString(tr("reset passwd:%1\nplease intput answer:"))
                    .arg(m_tempStr.m_two);
            QString answer = QInputDialog::getText(NULL, "reset passwd",
                                                   str,
                                                   QLineEdit::Normal,
                                                   NULL,
                                                   &isOkMes);
            if (!isOkMes)
                break;
            if (answer != m_tempStr.m_three)
            { dbg;
                str = QString(tr("bad answer!"));
                QMessageBox::critical(NULL, tr("reset passwd"), str);
                continue;
            }
            else
            { dbg;
                str = QString(tr("good answer!\nyour accout is:%1\nyour passwd is:%2"))
                        .arg(m_id)
                        .arg(IMEncryption::getInstace()
                             .getXorEncryptDecrypt(m_tempStr.m_one, 10));
                QMessageBox::information(NULL, tr("reset passwd"), str);
            }
            break;
        }
        break;

    }
    default:
        break;
    }

    QByteArray data = m_tcpSocket->readAll();
    qDebug() << "leaved in socket: " << data.size();
    m_blockSize = 0;
}

// mark: private----------------------------------------------------------

