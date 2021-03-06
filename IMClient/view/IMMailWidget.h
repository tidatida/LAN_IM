#ifndef IMMAILWIDGET_H
#define IMMAILWIDGET_H

#include <QWidget>
#include <QMap>
#include "model/IMConstant.h"

class QPushButton;
class QTabWidget;
class IMMailButton;
class IMMailOutWidget;
class IMMailInWidget;
class IMMailWriteWidget;
class QLabel;
class IMMailCtrl;
class IMMailInformationWidget;

class IMMailWidget : public QWidget
{
    Q_OBJECT
public:
    IMMailWidget(const QString & myID, QWidget *parent = 0);
    ~IMMailWidget();

    IMMailCtrl* getMailCtrl();
    QString getMyID();
    void showMailInformationWidget(const MailInformation & mail);
    void showMailInWidget();
    void showMailWriteWidget(const QString & address);

signals:

public slots:

private slots:
    //  set 收件箱
    void setInMailsWidget(const QVector<MailInformation> &);
    //  set 发件箱
    void setOutMailsWidget(const QVector<MailInformation> &);

    // add 收件箱 button 
    bool addInMailButton(const MailInformation &);
    // add 发件箱 button 
    bool addOutMailButton(const MailInformation &);
    // delete  邮件 button 
    void deleteMail(const int &);

    // add  new 邮件到发件箱
    bool addNewOutMailButton(const MailInformation &);
    // add  new 邮件到收件箱
    bool addNewInMailButton(const MailInformation &);

private:
    void initIMMailWidget();
    void linkSignalWithSlot();
    void clearContainers();

private:
//    QPushButton *m_btnWrite;        // 写信
//    QPushButton *m_btnIn;           // 收件箱
//    QPushButton *m_btnOut;          //  already 发送
//    QPushButton *m_btnDrafts;       // 草稿箱
//    QPushButton *m_btnTrash;        // 垃圾箱

    QString m_myID;

    QLabel *m_labelInformation;
    QTabWidget *m_tabWidget;
    IMMailOutWidget *m_outWidget;
    IMMailInWidget *m_inWidget;
    IMMailWriteWidget *m_writeWidget;
    IMMailInformationWidget *m_informationWidget;

    IMMailCtrl *m_mailCtrl;

    QMap<int, IMMailButton*> m_inMailMap;
    QMap<int, IMMailButton*> m_outMailMap;
};

#endif // IMMAILWIDGET_H
