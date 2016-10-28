/*********************************************
File Name: IMLoginCtrl.cpp
Author: jet.F.R
Date: 2014.3.10
Description:
Changes:
********************************************/

#include "IMLoginCtrl.h"
#include "model/IMConstant.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QDataStream>
#include <QDateTime>
#include <QtNetwork>
#include <QInputDialog>
#include "model/IMEncryption.h"

// public:-----------------------------------------------------------------
IMLoginCtrl::IMLoginCtrl(QObject *parent) :
    QObject(parent)
{
    m_tcpSocket = new IMTcpSocket(this);
    m_tcpSocket->setFlag(1);
    connect(m_tcpSocket, SIGNAL(showConnectionStatus(QString, bool)),
            this, SLOT(changeLoginMessage(QString, bool)));

    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(sendRequest()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

IMLoginCtrl::~IMLoginCtrl()
{
//    if (m_tcpSocket != NULL)
//    {
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
{
    m_kind = LOGIN;
    m_loginInfo.m_userID = id;
    m_loginInfo.m_password = pwd;
    m_loginInfo. m_status = status;

    qDebug() <<"function:"<<__FUNCTION__ <<" line:"<<__LINE__;
    if (m_tcpSocket->isConnected())
    {
        qDebug() <<"function:"<<__FUNCTION__ <<" line:"<<__LINE__;
        requestLogin();
    }
    else
    {
        qDebug() <<"function:"<<__FUNCTION__ <<" line:"<<__LINE__;
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
{
    m_kind = GET_QUESTION_ANSWER;
    m_id = id;
    if (m_tcpSocket->isConnected())
    {
        requestGetQuestionAndAnswer();
    }
    else
    {
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
{
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
{
    qDebug() <<"function:"<<__FUNCTION__ <<" line:"<<__LINE__;
    if (NULL == m_tcpSocket){
        qDebug() <<"function:"<<__FUNCTION__ <<" line:"<<__LINE__;
        return;
    }

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(LOGIN) << m_loginInfo;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
    qDebug() <<"function:"<<__FUNCTION__ <<" line:"<<__LINE__;

}



/*************************************************
Function Name: sendRequest()
Description: 
*************************************************/
void IMLoginCtrl::sendRequest()
{
    switch (m_kind)
    {
    case LOGIN:
    {
        qDebug() <<"function:"<<__FUNCTION__ <<" line:"<<__LINE__;
        requestLogin();
        break;
    }
    case GET_QUESTION_ANSWER:
    {
        qDebug() <<"function:"<<__FUNCTION__ <<" line:"<<__LINE__;
        requestGetQuestionAndAnswer();
        break;
    }
    default:
        qDebug() <<"function:"<<__FUNCTION__ <<" line:"<<__LINE__;
        break;
    }
}

// private slots:---------------------------------------------

/*************************************************
Function Name: requestGetQuestionAndAnswer()
Description: 
*************************************************/
void IMLoginCtrl::requestGetQuestionAndAnswer()
{
    if (NULL == m_tcpSocket){
        qDebug() <<"function:"<<__FUNCTION__ <<" line:"<<__LINE__;
        return;
    }

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
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
{
    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_4_8);
    if (m_blockSize == 0)
    {
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
    {
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
    {
        QMessageBox::critical(NULL, tr("reset passwd"), tr("failed, passwd doesn't exists.！"));
        break;
    }
    case GET_QUESTION_ANSWER_SUCCESS:
    {
        in >> m_tempStr;
        emit getQuestionAndAnswerSuccess(m_tempStr);

        while (1)
        {
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
            {
                str = QString(tr("bad answer!"));
                QMessageBox::critical(NULL, tr("reset passwd"), str);
                continue;
            }
            else
            {
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

