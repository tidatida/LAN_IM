/*********************************************
File Name: IMRegisterCtrl.h
Author: jet.F.R
Date: 2014.3.17
Description: 
Changes:
********************************************/

#ifndef IMREGISTERCTRL_H
#define IMREGISTERCTRL_H

#include <QObject>
#include "model/IMConstant.h"

class IMUser;
class IMTcpSocket;

/*************************************************
Class Name: IMRegisterCtrl
Description: 
*************************************************/
class IMRegisterCtrl : public QObject
{
    Q_OBJECT
public:
    explicit IMRegisterCtrl(QObject *parent = 0);

    ~IMRegisterCtrl();
    void registerAccount(const UserInformation &);
    
signals:
    void signalResetBtnRegister(bool );
public slots:

private slots:
    void requestRegister();
    void readMessage();
    void resetBtnRegister();
private:
    
private:
    UserInformation m_user;
    quint16 m_blockSize;
    IMTcpSocket *m_tcpSocket;

};

#endif // IMREGISTERCTRL_H
