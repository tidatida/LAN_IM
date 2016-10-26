/*********************************************
File Name: IMLoginCtrl.h
Author: jet.F.R
Date: 2014.3.10
Description: 
Changes:
********************************************/

#ifndef IMLOGINCTRL_H
#define IMLOGINCTRL_H

#include <QObject>
#include "model/IMTcpSocket.h"

class IMTcpSocket;

/*************************************************
Class Name: IMLoginCtrl
Description: 
*************************************************/
class IMLoginCtrl : public QObject
{
    Q_OBJECT
public:
    explicit IMLoginCtrl(QObject *parent = 0);

    ~IMLoginCtrl();

    void login(const QString &id ,const QString & pwd = "",
                     const int status = ONLINE);
    void getQuestionAndAnswer(const QString &id);

signals:
    void getLoginMessgae(const QString &, bool isLogin = false,
                         const UserInformation * me = 0);
    void getQuestionAndAnswerSuccess(const TempStrings & tmpStr);

public slots:
    void changeLoginMessage(const QString &mes, bool isLogin);


private slots:
    void requestGetQuestionAndAnswer();
    void requestLogin();

    void sendRequest();

    void readMessage();

private:

private:
    int m_kind;
    quint16 m_blockSize;
    IMTcpSocket *m_tcpSocket;
    LoginInformation m_loginInfo;
    UserInformation m_myself;
    TempStrings m_tempStr;
    QString m_id;
};

#endif // IMLOGINCTRL_H
