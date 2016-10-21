/*********************************************
File Name： IMEncryption.h
Author： jet.F.R
Date： 2014.3.17
Description： 
Changes：
********************************************/

#ifndef IMENCRYPTION_H
#define IMENCRYPTION_H

#include <QAtomicPointer>
#include <QMutexLocker>
#include <QReadWriteLock>
#include <QString>
#include <QDebug>
#include <QTextCodec>

class IMEncryption
{
public:
    // 
    static IMEncryption& getInstace(void);

    // 
    QString getXorEncryptDecrypt(const QString &, const char &);
    // 
    QString byteToQString(const QByteArray &byte);
    // 
    QByteArray qstringToByte(const QString &strInfo);

private:
    IMEncryption(){}
    IMEncryption(const  IMEncryption &);
    IMEncryption & operator =(const  IMEncryption &);

    QReadWriteLock m_internalMutex;
    static  QMutex s_mutex;
    static  QAtomicPointer<IMEncryption> s_instance; 
};

#endif // IMENCRYPTION_H
