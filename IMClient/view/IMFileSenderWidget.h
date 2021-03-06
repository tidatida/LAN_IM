#ifndef IMFILESENDERWIDGET_H
#define IMFILESENDERWIDGET_H

#include <QWidget>
#include <QTime>

class QProgressBar;
class QLabel;
class QPushButton;
class QTcpSocket;
class QTcpServer;
class QFile;

class IMFileSenderWidget : public QWidget
{
    Q_OBJECT
public:
    IMFileSenderWidget(QWidget *parent = 0);
    ~IMFileSenderWidget();

    // init 
    void initSender();
    // 被refuse  时触发  聊天窗体调用
    void showRefused();
    // init 文件server ，监听对方
    bool startSending(const QString &);
    bool isStopped();
    
signals:
//    void sendFileName(QString fileName,QString addr);
    
public slots:
    

private:
    // init 发送窗口
    void initIMFileSenderWidget();

private slots:
    // click “取消” button   取消发送
    void onClickBtnCancel();
    //  click “close ” button 
    void onClickBtnClose();
    // 当 Got  new connection 时触发 发送文件
    void sendMessage();
    // 根据发送情况实时更 new 进度条
    void updateClientProgress(qint64 numBytes);

    // connection 断开
    void showClosedConnect();

private:
    QLabel *m_labelFileName;
    QLabel *m_labelFileStatus;
    QProgressBar *m_barFile;
    QPushButton *m_btnCancel;
    QPushButton *m_btnClose;

    QTcpSocket *m_clientConnection;

    qint16 m_tcpPort;
    QTcpServer *m_fileSender;
    QString m_filePath;
    QString m_fileName;
    QFile *m_localFile;

    qint64 m_totalBytes;
    qint64 m_bytesWritten;
    qint64 m_bytesToWrite;
    qint64 m_loadSize;
    QByteArray m_outBlock;   // 缓存一次发送,s 数据
    QTime m_time;            // 计时器


    bool m_isStopped;
};

#endif // IMFILESENDERWIDGET_H
