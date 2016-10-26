#ifndef IMFILERECEIVERWIDGET_H
#define IMFILERECEIVERWIDGET_H

#include <QWidget>
#include <QHostAddress>
#include <QTime>

class QProgressBar;
class QLabel;
class QPushButton;
class QPushButton;
class QTcpSocket;
class QTcpServer;
class QFile;
class QAbstractSocket;


class IMFileReceiverWidget : public QWidget
{
    Q_OBJECT
public:
    IMFileReceiverWidget(QWidget *parent = 0);
    ~IMFileReceiverWidget();

    // 设置文件 name 
    void setFileName(const QString & fileName);
    // 设置server 地址并connection server 
    void connectToHost(const QHostAddress & address);
    
signals:
    

    
private:
    // init 
    void initIMFileReceiverWidget();

public slots:
    //  click “close ” button 
    void onClickBtnClose();
    //  click “取消” button  中途取消,s 操作
    void onClickBtnCancel();
    // 读取收到,s 文件
    void readMessage();
    // 错误process   
    void displayError(QAbstractSocket::SocketError);
    // connection 断开
    void showClosedConnect();

private:
    QLabel *m_labelFileName;
    QLabel *m_labelFileStatus;
    QProgressBar *m_barFile;
    QPushButton *m_btnClose;
    QPushButton *m_btnCancel;

    QTcpSocket *m_fileReceiver;
    quint16 m_blockSize;
    QHostAddress m_hostAddress;
    qint16 m_tcpPort;

    qint64 m_totalBytes;
    qint64 m_bytesReceived;
    qint64 m_bytesToReceive;
    qint64 m_fileNameSize;
    QString m_fileName;
    QFile *m_localFile;
    QByteArray m_inBlock;

    QTime m_time;

};

#endif // IMFILERECEIVERWIDGET_H
