#ifndef IMMAILCTRL_H
#define IMMAILCTRL_H

#include <QObject>
#include "model/IMConstant.h"
#include <QVector>


class IMTcpSocket;
class QString;
class QTreeView;
class QModelIndex;
class QStandardItem;
class QStandardItemModel;


class IMMailCtrl : public QObject
{
    Q_OBJECT
public:
    IMMailCtrl(const QString & id, QObject *parent = 0);
    ~IMMailCtrl();

signals:
    void getInMailsSuccess(const QVector<MailInformation> &);
    void getOutMailsSuccess(const QVector<MailInformation> &);
    void deleteMailSuccess(const int &);
    void getOutMail(const MailInformation &);
    void getInMail(const MailInformation &);

public slots:
    void requestSendMail(const MailInformation &);
    void requestGetInMails();
    void requestGetOutMails();
    void requestDeleteMail(const MailInformation & mail);
    void requestSetMailRead(const MailInformation & mail);

    void readMessage();

private:

private:
    QString m_myID;
    IMTcpSocket *m_tcpSocket;
    quint16 m_blockSize;

    QVector<MailInformation> m_inMailsVec;
    QVector<MailInformation> m_outMailsVec;
    MailInformation m_mail;
    QString m_peerID;
    int m_mailID;
};

#endif // IMMAILCTRL_H
