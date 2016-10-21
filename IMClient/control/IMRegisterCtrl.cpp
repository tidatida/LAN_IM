/*********************************************
File Name： IMRegisterCtrl.cpp
Author： jet.F.R
Date： 2014.3.17
Description： 
Changes：
********************************************/
#include "IMRegisterCtrl.h"
#include "model/IMTcpSocket.h"
#include "IMClientMessageCtrl.h"

#include <QMessageBox>

// mark: public------------------------------------------------------
IMRegisterCtrl::IMRegisterCtrl(QObject *parent) :
    QObject(parent)
{
    m_tcpSocket = new IMTcpSocket(this);
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(requestRegister()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(resetBtnRegister()));
    connect(m_tcpSocket, SIGNAL(disconnected()),
            this, SLOT(resetBtnRegister()));
}


IMRegisterCtrl::~IMRegisterCtrl()
{
}


/*************************************************
Function Name： registerAccount()
Description: 
Input： IMUser 
Output： NULL
Changes： NULL
*************************************************/
void IMRegisterCtrl::registerAccount(const UserInformation &user)
{
    m_user = user;
    if (m_tcpSocket->isConnected())
    {
        requestRegister();
    }
    else
    {
        m_blockSize = 0;
        m_tcpSocket->requestConnect();
    }
}

/*************************************************
Function Name： requestRegister()
Description: 
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMRegisterCtrl::requestRegister()
{
    qDebug() << "requestRegister";
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(REGISTER)  << m_user;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
//    qDebug() << "bytesAvailable:" << m_tcpSocket->bytesAvailable();
}

/*************************************************
Function Name： readMessage()
Description: 
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMRegisterCtrl::readMessage()
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

    switch (type)
    {
    case REGISTER_SUCCESS:
        in >> m_user.m_userID >> m_user.m_regDateTime;
        QMessageBox::about(NULL, tr("register result"),
                           tr("%1, hello！ congritulation, register successfully.. "
                              "your ID is %2, please rememeber. \n register time：%3")
                           .arg(m_user.m_nickname,
                                m_user.m_userID,
                                m_user.m_regDateTime.
                                toString("yyyy-MM-dd hh:mm:ss")));
        break;
    case REGISTER_FAIL:
        QMessageBox::about(NULL, tr("register result"), tr("register failed"));
    }

    emit signalResetBtnRegister(true);

    m_blockSize = 0;
}


/*************************************************
Function Name： resetBtnRegister()
Description: 
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMRegisterCtrl::resetBtnRegister()
{
    emit signalResetBtnRegister(true);
}
// mark: private------------------------------------------------------
