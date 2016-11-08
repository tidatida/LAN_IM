#ifndef IMINFORMATIONWIDGET_H
#define IMINFORMATIONWIDGET_H

#include <QWidget>
#include "model/IMConstant.h"

class QPushButton;
class QLabel;
class QLineEdit;
class QCheckBox;
class QComboBox;
class QFrame;
class CustomLineEdit;
class IMMainWidget;

static const int MAX_NUM = 133;

class IMInformationWidget : public QWidget
{
    Q_OBJECT
public:
    IMInformationWidget(IMMainWidget *mainWidget, QWidget *parent = 0);
     ~IMInformationWidget();

    void setReadOnly(bool isReadOnly, bool isEdit);
//    void setWrite();
    void setUserInformation(const UserInformation &user);
    UserInformation getInformation();
protected:
    void closeEvent(QCloseEvent *);
signals:
//    void sendInformation(const UserInformation &user);
public slots:
    void onClickCancelButton();
    void onClickOKButton();
    void onClickPretButton();
    void onClickNextButton();

private:
    void initIMLoginWidget();

protected:
    QLabel *m_labelUserID;    // user  account  
    QLineEdit *m_leUserID;

    QLabel *m_labelNickname;
    QLineEdit *m_leNickname;

    QFrame *m_frameHead;
    QLabel *m_labelHead;

    QPushButton *m_btnNext;
    QPushButton *m_btnPre;

    QLabel *m_labelConfirmPwd;
    QLineEdit *m_leConfirmPwd;
    QLabel *m_labelSex;
    QComboBox *m_cbxSex;

    QLabel *m_labelBirthday;
    CustomLineEdit *m_leBirthday;
    QLabel *m_labelName;
    QLineEdit *m_leName;
    QLabel *m_labelPhone;
    QLineEdit *m_lePhone;
    QLabel *m_labelAddress; 
    QLineEdit *m_leAddress;

    QPushButton *m_btnOk;
    QPushButton *m_btnCancel;

    int m_headNum;
    bool m_isReadOnly;
    bool m_isEdit;

    UserInformation m_userInf;
    IMMainWidget *m_mainWidget;
};

#endif // IMINFORMATIONWIDGET_H
