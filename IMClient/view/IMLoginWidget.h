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
    // 显示mainframe
    void showMainWidget();
    //  set 状态标签
    void setLabelStatus(const QString &mes, bool isLogin,
                        const UserInformation *me = 0);
    //  get m_isAutoLogin
    bool getIsAutoLogin();
    // 单击“ Login ” button 
    void onClickBtnLogin();

protected:
    // process    timer 器 event 
    void timerEvent(QTimerEvent * event);
private slots:
    // 单击"Register  account  "标签
    void onClickLabelRegister();
    // 单击“Forget passwd?"标签
    void onClickLabelForgotPwd();
    //  auto  Login 选择框改变
    void onClickCbAutoLogin(int state);
private:
    // init  Login 界面
    void initIMLoginWidget();
    // connection 信 number  and 槽
    void linkSignalWithSlot();
    // close  timer 器
    void closeTimer();
    //  set server 信息
    void setServer(const QString &ip = "127.0.0.1", const int port = 1234);
    // 读取 auto  Login 配置文件
    bool readAutoLoginFile(const QString &);

private:
    QLineEdit *m_leUserID;    // id
    QLineEdit *m_leUserPwd;   //  passwd
    IMClickLabel *m_labelRegister;  // Register  account  
    IMClickLabel *m_labelForgotPwd; // Forget passwd?
    QCheckBox *m_cbKeepPwd;   //  remember  passwd
    QCheckBox *m_cbAutoLogin; //  auto  Login 
    QComboBox *m_cbxStatus;   //  Login 状态
    QPushButton *m_btnLogin;  //  Login  button 

    QPushButton *m_moreButton;// 拓展 button 
    QWidget *m_extendedWidget;// 拓展界面
    QLineEdit *m_hostAddress; // server ip address 
    QLineEdit *m_hostPort;    // server  port 

    QLabel *m_labelStatus;    // 状态标签
    bool m_isLogin;           // 是否能 Login 
    IMLoginCtrl *m_loginCtrl; // used to   control   Login 

    int m_timerID;            //  timer 器ID
    bool m_closeTimer;        //  timer 器是否close 
    int m_counter;            // 计数器
    bool m_isAutoLogin;         // 是否 auto  Login 

    int m_status;
};

#endif // IMLOGINWIDGET_H
