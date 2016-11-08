/*********************************************
File Name: IMLoginWidget.h
Author: jet.F.R
Date: 2014.3.10
Description: client login interface
Changes:
********************************************/

#ifndef IMLOGINWIDGET_H
#define IMLOGINWIDGET_H

#include <QtWidgets/QWidget>

class QPushButton;
class QLabel;
class QLineEdit;
class QCheckBox;
class QComboBox;
class IMClickLabel;
class IMLoginCtrl;
struct UserInformation;

/*************************************************
Class Name: IMLoginWidget
Description: client login interface class
*************************************************/
class IMLoginWidget : public QWidget
{
    Q_OBJECT
    
public:
    IMLoginWidget(QWidget *parent = 0);
    ~IMLoginWidget();
signals:

public slots:
    void showMainWidget();
    void setLabelStatus(const QString &mes, bool isLogin,
                        const UserInformation *me = 0);
    bool getIsAutoLogin();
    void onClickBtnLogin();

protected:
    void timerEvent(QTimerEvent * event);
private slots:
    void onClickLabelRegister();
    void onClickLabelForgotPwd();
    void onClickCbAutoLogin(int state);
private:
    void initIMLoginWidget();
    void linkSignalWithSlot();
    void closeTimer();
    void setServer(const QString &ip = "127.0.0.1", const int port = 1234);
    bool readAutoLoginFile(const QString &);

private:
    QLineEdit *m_leUserID;
    QLineEdit *m_leUserPwd;
    IMClickLabel *m_labelRegister;  
    IMClickLabel *m_labelForgotPwd;
    QCheckBox *m_cbKeepPwd;
    QCheckBox *m_cbAutoLogin;
    QComboBox *m_cbxStatus;
    QPushButton *m_btnLogin;

    QPushButton *m_moreButton;
    QWidget *m_extendedWidget;
    QLineEdit *m_hostAddress;
    QLineEdit *m_hostPort;

    QLabel *m_labelStatus;
    bool m_isLogin;
    IMLoginCtrl *m_loginCtrl;

    int m_timerID;
    bool m_closeTimer;
    int m_counter;
    bool m_isAutoLogin;

    int m_status;
};

#endif // IMLOGINWIDGET_H
