/*********************************************
File Name: IMChatWidget.h
Author: jet.F.R
Date: 2014.3.26
Description: 
Changes:
********************************************/

#ifndef IMCHATWIDGET_H
#define IMCHATWIDGET_H

#include <QWidget>
#include "model/IMConstant.h"

class QComboBox;
class QFontComboBox;
class IMInputTextEdit;
class QDockWidget;
class QPixmap;
class QFrame;
class QLabel;
class QPushButton;
class QToolButton;
class QTextBrowser;
//class H264CameraWidget;
//class ShowVideoWidget;
class IMClickLabel;
class QTextCharFormat;
class IMFileSenderWidget;


class IMChatWidget : public QWidget
{
    Q_OBJECT
public:
    IMChatWidget(const ChatInformation & chatInf,QWidget *parent = 0);
//    IMChatWidget(const QString &id, QWidget *parent = 0);

    ~IMChatWidget();
    void appendMessageShow(const TalkMessage &mes);
    void pendingFile(const TalkMessage &mes);
    void refusedSendFile();

    void pendingVideo(const TalkMessage &mes);
    void showVideoWidget(const TalkMessage &mes);
    void showCamera(const TalkMessage &mes);
    void startCapture();
    void closeVideoWidget();

    void setLabelStatus();
    void setChatInformation(const ChatInformation & chatInfo);
    void setFriendIP(const QString & ip);
    
signals:
    void sendMessagesFromChat(TalkMessage &);
    void roomQuitSignal();
public slots:

protected:
    void closeEvent(QCloseEvent *event);

private slots:

    void onClickBtnVideo();
    void onClickBtnVoice();
    void onClickBtnFile();
    void onClickBtnSpace();

    void setInputTextFont(const QFont &font);
    void setInputTextSize(const QString & size);
    void onClickBtnBold(bool checked);
    void onClickBtnItalic(bool checked);
    void onClickBtnUnderline(bool checked);
    void onClickBtnColor();
    void onClickBtnClear();
    void onClickBtnHistory(bool checked);
    void currentFormatChanged(const QTextCharFormat &format);
    void onClickBtnClose();
    void onClickBtnSend();

private:
    void initIMChatWidget();
    void linkSignalWithSlot();
    void setWidgetToolBtn();
    void saveHistoryMessage();
    void readHistoryMessage();

private:
//    QPixmap *m_pmHeadPortrait;
//    QFrame *m_frameHeadPortrait;
    IMClickLabel *m_labelHead;
    QLabel *m_labelName;
    QLabel *m_labelMark;
    QToolButton *m_toolBtnVideo;
    QToolButton *m_toolBtnVoice;
    QToolButton *m_toolBtnFile;
    QToolButton *m_toolBtnSpace;
    QTextBrowser *m_tbMessageShow;

//    QToolButton *m_toolBtnFont;
    QFontComboBox *m_cbFont;         
    QComboBox *m_cbSize;             
    QToolButton *m_toolBtnBold;      
    QToolButton *m_toolBtnItalic;    
    QToolButton *m_toolBtnUnderline; 
    QToolButton *m_toolBtnColor;     
//    QToolButton *m_toolBtnExpression;
//    QToolButton *m_toolBtnScreen;    
    QToolButton *m_toolBtnClear;      
    QToolButton *m_toolBtnHistory;   
    IMInputTextEdit *m_textInput;          
    QLabel *m_labelFriendIP;             
    QPushButton *m_btnClose;            
    QPushButton *m_btnSend;             

    QWidget *m_dockHistoty;
    QTextBrowser *m_tbHistoryShow;   

    ChatInformation m_chatInfor;
    TalkMessage m_mes;

//    H264CameraWidget *m_camera;
//    ShowVideoWidget *m_videoShow;

    IMFileSenderWidget *m_fileSender;
};

#endif // IMCHATWIDGET_H
