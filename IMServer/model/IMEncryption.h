/*********************************************
File Name: IMEncryption.h
Author: jet.F.R
Date: 2014.3.17
Description: encrypt, decrypt
Changes:
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
    static IMEncryption& getInstace(void);

    QString getXorEncryptDecrypt(const QString &, const char &);
    QString byteToQString(const QByteArray &byte);
    QByteArray qstringToByte(const QString &strInfo);

private:
    IMEncryption(){};
    IMEncryption(const  IMEncryption &);
    IMEncryption & operator =(const  IMEncryption &);

    QReadWriteLock m_internalMutex;
    static  QMutex s_mutex;
    static  QAtomicPointer<IMEncryption> s_instance;
};

QMutex IMEncryption::s_mutex;
QAtomicPointer<IMEncryption> IMEncryption::s_instance = 0; /*  init */

IMEncryption& IMEncryption::getInstace(void)
{
#if 0
/* FIXME, i DON'T KNOW HOW TO DEAL WITH  SUCH AN ERRROR.  */
    #ifndef Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
    /* running check */
    if (!QAtomicPointer::isTestAndSetNative())
    {
        qDebug() << "Error: TestAndSetNative not supported!";
    }
    #endif
#endif

    if (s_instance.testAndSetOrdered(0, 0))/* first check */
    {
        QMutexLocker locker(&s_mutex);/* lock*/
        s_instance.testAndSetOrdered(0, new  IMEncryption);/* second check */
    }
    return  *s_instance;
}

QString IMEncryption::getXorEncryptDecrypt(const QString &str, const char &key)
{
    QString result;
    QByteArray bs = qstringToByte(str);

    for(int i=0; i<bs.size(); i++)
    {
        bs[i] = bs[i] ^ key;
    }

    result = byteToQString(bs);
    return result;
}


QString IMEncryption::byteToQString(const QByteArray &byte)
{
    QString result;
    if (byte.size() > 0)
    {
        QTextCodec *codec = QTextCodec::codecForName("utf-8");
        result = codec->toUnicode(byte);
    }

    return result;
}

QByteArray IMEncryption::qstringToByte(const QString &strInfo)
{
    QByteArray result;
    if (strInfo.length() > 0)
    {
        QTextCodec *codec = QTextCodec::codecForName("utf-8");
        result = codec->fromUnicode(strInfo);
    }
    return result;
}


#endif // IMENCRYPTION_H
