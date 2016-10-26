/*********************************************
File Name: IMRegisterWidget.h
Author: jet.F.R
Date: 2014.3.14
Description: clientRegister 界面
Changes:
********************************************/
#ifndef IMREGISTERWIDGET_H
#define IMREGISTERWIDGET_H

#include <QWidget>
#include "model/IMConstant.h"
class QPushButton;
class QLabel;
class QLineEdit;
class QCheckBox;
class QComboBox;
class IMRegisterCtrl;
class CustomLineEdit;

/*************************************************
Class Name: IMRegisterWidget
Description: clientRegister 帐号界面 class
*************************************************/
class IMRegisterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IMRegisterWidget(QWidget *parent = 0);
    ~IMRegisterWidget();
    
signals:
    
public slots:
    void resetBtnRegister(bool );    // 重置Register 按钮

protected:
    void moveEvent(QMoveEvent *);    // 窗口移动事件

private slots:
    void onClickBtnRegister();  // 单击“Register ”按钮
    void conClickBtnCancel();   // 单击“取消”按钮

private:
    // init Register 界面
    void initIMRegisterWidget();
    // connection 信号与槽
    void linkSignalWithSlot();


private:
    QLabel *m_labelHead;

//    QLabel *m_labelUserID;    // user 帐号
//    QLineEdit *m_leUserID;
//    QLabel *m_labelDesUserID;
    QLabel *m_labelNickname;   // user 昵称
    QLineEdit *m_leNickname;
    QLabel *m_labelDesNickname;// 昵称描述
    QLabel *m_labelPwd;        // user  passwd
    QLineEdit *m_lePwd;
    QLabel *m_labelDesPwd;
    QLabel *m_labelConfirmPwd;  // 确认 passwd
    QLineEdit *m_leConfirmPwd;
    QLabel *m_labelDesConfirmPwd;
    QLabel *m_labelSex;        // 性别
    QComboBox *m_cbxSex;
    QLabel *m_labelDesSex;
    QLabel *m_labelBirthday;   // 生日
    CustomLineEdit *m_leBirthday;
    QLabel *m_labelDesBirthday;
    QLabel *m_labelQuestion;   // passwd-protect question
    QLineEdit *m_leQuestion;
    QLabel *m_labelDesQuestion;
    QLabel *m_labelAnswer;     // 问题answer 
    QLineEdit *m_leAnswer;
    QLabel *m_labelDesAnswer;
    QLabel *m_labelName;       // 真实姓名
    QLineEdit *m_leName;
    QLabel *m_labelDesName;
    QLabel *m_labelPhone;      // 电话
    QLineEdit *m_lePhone;
    QLabel *m_labelDesPhone;
    QLabel *m_labelAddress;    // 地址
    QLineEdit *m_leAddress;
    QLabel *m_labelDesAddress;

    QPushButton *m_btnRegister;// "Register " 按钮
    QPushButton *m_btnCancel;  // "取消" 按钮

    IMRegisterCtrl * m_regCtrl;

    UserInformation m_userInf;
};

#endif // IMREGISTERWIDGET_H
