/*********************************************
File Name: IMClientFileCtrl.h
Author: jet.F.R
Date: 2014.3.23
Description:
Changes:
********************************************/
#ifndef IMCLIENTFILECTRL_H
#define IMCLIENTFILECTRL_H

#include <QObject>
class QXmlStreamWriter;
class QXmlStreamReader;
class QTextBrowser;

class IMClientFileCtrl : public QObject
{
    Q_OBJECT
public:
    explicit IMClientFileCtrl(QObject *parent = 0);
    // write autologin's file
    static bool writeAutoLogin(const QString &fileName, const QString &id,
                        const QString &pwd, const bool isAuto = false);
    // read autologin's file
    static bool readAutoLogin(const QString &fileName,QString &id,
                         QString &pwd, bool &isAuto);

    // remove file
    static bool remove(const QString &filename);

    static QString simplifyRichText(QString richText);

    static void saveTalkHistory(const QString filePath, const QString fileName,
                                const QTextBrowser *messagaShow);
    static void readTalkHistory(const QString filePath, const QString fileName,
                                QTextBrowser *messagaShow);

signals:
    
public slots:

private:
//    QXmlStreamWriter m_write;
//    QXmlStreamReader m_read;

};

#endif // IMCLIENTFILECTRL_H
