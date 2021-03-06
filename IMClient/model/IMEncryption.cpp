#include "IMEncryption.h"

QMutex IMEncryption::s_mutex;
QAtomicPointer<IMEncryption> IMEncryption::s_instance = 0; 

IMEncryption& IMEncryption::getInstace(void)
{
#if 0
    #ifndef Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
    if (!QAtomicPointer::isTestAndSetNative())
    {
        qDebug() << "Error: TestAndSetNative not supported!";
    }
    #endif
#endif


    if (s_instance.testAndSetOrdered(0, 0))
    {
        QMutexLocker locker(&s_mutex);
        s_instance.testAndSetOrdered(0, new  IMEncryption);
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
