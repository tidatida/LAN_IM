#ifndef IMDATABASECTRL_H
#define IMDATABASECTRL_H

#include <QObject>
#include "model/IMConstant.h"

class QSqlQuery;
class QSqlDatabase;
class QDateTime;

class IMDatabaseCtrl : public QObject
{
    Q_OBJECT
public:
    IMDatabaseCtrl(const QString myID, QObject *parent = 0);
    ~IMDatabaseCtrl();
    bool createConnection();
    void close();
    bool isOpen();

    bool addHistoryMessage(const TalkMessage &);
    bool searchHistoryMessage(const QString &myID , const QString &friendID,
                              const QDate &date, QVector<TalkMessage> &mesVec);
    int exportHistoryMessageOneFriend(const QString &myID ,
                                      const QString &friendID,
                                      const QString &fileName);
    int exportHistoryMessageAll(const QString &myID, const QString &fileName);

    int deleteHistoryMessageOneFriend(const QString myID, const QString friendID);
    int deleteHistoryMessageAll(const QString myID);

signals:
    
public slots:

private:
    void errorSQLOrder(QSqlQuery query, QString mark);
    void createTable();
private:
    QSqlDatabase *m_db;
    QString m_myID;
    QString m_localHistoryTableName;
};

#endif // IMDATABASECTRL_H
