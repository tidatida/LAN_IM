/*********************************************
File Name： IMChatWidget.h
Author： jet.F.R
Date： 2014.3.26
Description： 
Changes：
********************************************/

#include "IMChatWidget.h"
#include <QLabel>
#include <qdebug.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QPixmap>
#include <QPushButton>
#include <QFrame>
#include <QFontComboBox>
#include <QComboBox>
#include <QTextBrowser>
#include <QDockWidget>
#include "model/IMTcpSocket.h"
#include <QMessageBox>
//#include "H264CameraWidget.h"
#include "IMInputTextEdit.h"
//#include "ShowVideoWidget.h"
#include "view/IMClickLabel.h"
#include <QCloseEvent>
#include <QColorDialog>
#include <QTextCharFormat>
#include <QFileDialog>
#include "IMFileSenderWidget.h"
#include "IMFileReceiverWidget.h"
#include "control/IMClientFileCtrl.h"
// mark public:--------------------------------------------------------------

IMChatWidget::IMChatWidget(const ChatInformation &chatInf, QWidget *parent) :
    QWidget(parent)
{
    m_chatInfor = chatInf;
    m_fileSender = new IMFileSenderWidget();
//    m_fileSender->hide();
    initIMChatWidget();
    setLabelStatus();
    linkSignalWithSlot();
    setWindowTitle(tr("IM friends window"));
}

//IMChatWidget::IMChatWidget(const QString &id, QWidget *parent) :
//    QWidget(parent)
//{
//    //m_chatInfor.m_friendID = id;
//    initIMMainWidget();
//    linkSignalWithSlot();
//    qDebug() << "fuck";
//}

IMChatWidget::~IMChatWidget()
{
    if (m_fileSender != NULL)
    {
        m_fileSender->close();
        m_fileSender->deleteLater();
        m_fileSender = NULL;
    }
}

/*************************************************
Function Name： appendMessageShow()
Description:  
*************************************************/
void IMChatWidget::appendMessageShow(const TalkMessage &mes)
{
    QString  name;
    if(m_chatInfor.m_friendRemark.isEmpty())
        name = m_chatInfor.m_friendNickname;
    else
        name = m_chatInfor.m_friendRemark;

//    QString dateTime = IMTcpSocket::getCurrentDateTime();
    QString temp = QString("<font size=\"FONT_SIEZE\" color=blue>%1    %2: </font>%3")
        .arg(name).arg(mes.m_dateTime.toString("yyyy-MM-dd hh:mm:ss")).arg(mes.m_text);
    m_tbMessageShow->append(temp);
}


/*************************************************
Function Name： pendingFile()
Description:  
*************************************************/
void IMChatWidget::pendingFile(const TalkMessage &mes)
{
    int btn = QMessageBox::information(this,tr("receive file"),
                                       tr("file from %1(%2):\n%3\n should you receive it？").
                                       arg(mes.m_senderID).
                                       arg(mes.m_senderIP).
                                       arg(mes.m_text),
                                       QMessageBox::Yes,QMessageBox::No);
    if(btn == QMessageBox::Yes)
    {
        QString name = QFileDialog::getSaveFileName(0,tr("save file"),mes.m_text);
        if(!name.isEmpty())
        {
                IMFileReceiverWidget *receiver = new IMFileReceiverWidget();
                receiver->setFileName(name);
                receiver->connectToHost(QHostAddress(mes.m_senderIP));
                receiver->move(500,200);
                receiver->show();
        }

    }
    else
    {
        m_mes.m_type = REFUSE_FILE;
        m_mes.m_receiverID = mes.m_senderID;
        m_mes.m_receiverIP = mes.m_senderIP;
        emit sendMessagesFromChat(m_mes);
    }
}


/*************************************************
Function Name： refusedSendFile()
Description:  
*************************************************/
void IMChatWidget::refusedSendFile()
{
    if (m_fileSender != NULL)
        m_fileSender->showRefused();
}

/*************************************************
Function Name： pendingVideo()
Description:  
*************************************************/
void IMChatWidget::pendingVideo(const TalkMessage &mes)
{
//    qDebug() << "video-receiveIP:" << mes.m_receiverIP
//             << "sendIP: " << mes.m_senderIP;
//    if(mes.m_receiverIP != IMTcpSocket::getIP())
//    {
//        return;
//    }

    int btn = QMessageBox::information(this,tr("request video"),
                                       tr("video request from%1(%2)，accept？")
                                       .arg(m_chatInfor.m_friendNickname)
                                       .arg(mes.m_senderID),
                                       QMessageBox::Yes,QMessageBox::No);
    if(btn == QMessageBox::Yes)
    {
        m_toolBtnVideo->setEnabled(false);
        m_mes.m_type = AGREE_VOICE;
        m_mes.m_receiverID = mes.m_senderID;
        m_mes.m_receiverIP = mes.m_senderIP;
        m_mes.m_text = "port";

        qDebug() << "create video window";
        showCamera(mes);

        // 
//            QString name = QFileDialog::getSaveFileName(0,tr("save file"),fileName);
//            if(!name.isEmpty())
//            {
//                fileReceiver *receiver = new fileReceiver(this);
//                receiver->setFileName(name);
//                receiver->setHostAddress(QHostAddress(serverAddress));
//                receiver->move(500,200);
//                receiver->show();
//            }
    }
    else
    {
        m_mes.m_type = REFUSE_VIDEO;
        m_mes.m_receiverID = mes.m_senderID;
        m_mes.m_receiverIP = mes.m_senderIP;
    //    m_mes.m_senderID = m_chatInfor.m_;
    //    m_mes.m_senderIP = IMTcpSocket::getIP();
    }
    emit sendMessagesFromChat(m_mes);
}

/*************************************************
Function Name： initIMMainWidget()
Description:  
*************************************************/
void IMChatWidget::showVideoWidget(const TalkMessage &mes)
{
    qDebug() << "show video widget.";
}


/*************************************************
Function Name： showCamera()
Description:  
*************************************************/
void IMChatWidget::showCamera(const TalkMessage &mes)
{
//    qDebug() << "port:" << mes.m_text.toInt()
//             << "IP" << mes.m_senderIP.toStdString().data();

//    m_camera = new H264CameraWidget(mes.m_text.toInt(),
//                                    mes.m_senderIP.toStdString().data());
//    m_camera->show();
//    m_camera->startCapture();
}


/*************************************************
Function Name： closeVideoWidget()
Description:  
*************************************************/
void IMChatWidget::closeVideoWidget()
{
}

/*************************************************
Function Name： setChatWidgetStatus()
Description:  
*************************************************/
void IMChatWidget::setLabelStatus()
{
    QString str = QString("resource/image/head/%1.bmp").
        arg(QString::number(m_chatInfor.m_headPortrait));

    QString  name;
    if(m_chatInfor.m_friendRemark.isEmpty())
        name = m_chatInfor.m_friendNickname;
    else
        name = m_chatInfor.m_friendRemark;

    QPixmap pixmap;
    QIcon icon(str);
    pixmap = icon.pixmap(QSize(HEAD_BIG_SIZE, HEAD_BIG_SIZE));
    m_labelHead->setPixmap(pixmap);
    m_labelName->setText(name);
    m_labelMark->setText(m_chatInfor.m_friendMark);

}

/*************************************************
Function Name： setChatInformation()
Description:  
*************************************************/
void IMChatWidget::setChatInformation(const ChatInformation & chatInfo)
{
    if (chatInfo.m_friendID != m_chatInfor.m_friendID)
        return;
    m_chatInfor.m_headPortrait = m_chatInfor.m_headPortrait;
    m_chatInfor.m_friendNickname = m_chatInfor.m_friendNickname;
    m_chatInfor.m_friendRemark = m_chatInfor.m_friendRemark;
    m_chatInfor.m_friendMark = m_chatInfor.m_friendMark;
    m_chatInfor.m_friendIP = m_chatInfor.m_friendIP;
    m_chatInfor.m_friendStatus = m_chatInfor.m_friendStatus;
}

/*************************************************
Function Name： setFriendIP()
Description:  
*************************************************/
void IMChatWidget::setFriendIP(const QString & ip)
{
    m_chatInfor.m_friendIP = ip;
    m_labelFriendIP->setText(QString(tr("friend IP: %1")).arg(ip));

}

/*************************************************
Function Name： closeEvent()
Description:  
*************************************************/
void IMChatWidget::closeEvent(QCloseEvent *event)
{
    if (m_fileSender != 0)
    {
        if (!m_fileSender->isStopped())
        {
            QString temp = tr("file is transfering, are you sure to close window");
            QMessageBox::StandardButton rb;
            rb = QMessageBox::question(this, tr("close chat"), temp,
                QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
            if(rb == QMessageBox::No)
            {
                event->ignore();
                return;
            }
        }
    }

    emit roomQuitSignal();
    saveHistoryMessage();

    event->accept();
}

// mark private:--------------------------------------------------


/*************************************************
Function Name： initIMChatWidget()
Description:  
*************************************************/
void IMChatWidget::initIMChatWidget()
{
    setWidgetToolBtn();

    /*********friend msg interface**************/
    QHBoxLayout *hLayoutFriend = new QHBoxLayout;
    QVBoxLayout *vLayoutFriend = new QVBoxLayout;
    QVBoxLayout *vLayoutFriendInfo = new QVBoxLayout;
    QHBoxLayout *hLayoutFriendInter = new QHBoxLayout;

//    m_pmHeadPortrait = new QPixmap;
//    m_frameHeadPortrait = new QFrame;
    m_labelHead = new IMClickLabel;
    m_labelName = new QLabel();
    m_labelMark = new QLabel();

    vLayoutFriendInfo->addWidget(m_labelName);
    vLayoutFriendInfo->addWidget(m_labelMark);

    hLayoutFriendInter->addWidget(m_toolBtnVideo);
    hLayoutFriendInter->addWidget(m_toolBtnVoice);
    hLayoutFriendInter->addWidget(m_toolBtnFile);
    hLayoutFriendInter->addWidget(m_toolBtnSpace);
    hLayoutFriendInter->addStretch();

    hLayoutFriend->addWidget(m_labelHead);
    hLayoutFriend->addLayout(vLayoutFriendInfo);
    hLayoutFriend->addStretch();
//    vLayoutFriend->addLayout(hLayoutFriendInter);

//    hLayoutFriend->addWidget(m_frameHeadPortrait);
//    hLayoutFriend->addWidget(m_labelHead);
    vLayoutFriend->addLayout(hLayoutFriend);
    vLayoutFriend->addLayout(hLayoutFriendInter);
//    vLayoutFriend->addStretch();

    /*********input widget**************/
    QHBoxLayout *hLayoutInputTool = new QHBoxLayout;

//    hLayoutInputTool->addWidget(m_toolBtnFont);
    hLayoutInputTool->addWidget(m_cbFont);
    hLayoutInputTool->addWidget(m_cbSize);
    hLayoutInputTool->addStretch();

    hLayoutInputTool->addWidget(m_toolBtnBold);
    hLayoutInputTool->addWidget(m_toolBtnItalic);
    hLayoutInputTool->addWidget(m_toolBtnUnderline);
    hLayoutInputTool->addWidget(m_toolBtnColor);
    hLayoutInputTool->addWidget(m_toolBtnClear);
    hLayoutInputTool->addWidget(m_toolBtnHistory);


    /*********bottom ip and status **************/
    QHBoxLayout *hLayoutBtm = new QHBoxLayout;
    m_labelFriendIP = new QLabel(tr("ip"));
    m_btnClose = new QPushButton(tr("close"));
    m_btnSend = new QPushButton(tr("send"));
    m_btnSend->setDefault(true);
//    m_btnSend->setFocus();
    hLayoutBtm->addWidget(m_labelFriendIP);
    hLayoutBtm->addStretch();
    hLayoutBtm->addWidget(m_btnClose);
    hLayoutBtm->addWidget(m_btnSend);

    /******************left layout**********************/
    m_tbMessageShow = new QTextBrowser;
    m_tbMessageShow->setMinimumSize(400, 280);
    m_textInput = new IMInputTextEdit;
    m_textInput->setMinimumWidth(100);
    m_textInput->setMaximumHeight(170);
    QVBoxLayout *vLayoutLeft = new QVBoxLayout;
    //vLayoutLeft->addLayout(hLayoutFriend);
    vLayoutLeft->addWidget(m_tbMessageShow);
    vLayoutLeft->addLayout(hLayoutInputTool);
    vLayoutLeft->addWidget(m_textInput);
    vLayoutLeft->addLayout(hLayoutBtm);

    /******************middle layout**********************/
    QHBoxLayout *hLayoutMid = new QHBoxLayout;


//    m_tbHistoryShow->setFixedWidth(300);
    m_dockHistoty = new QWidget;
    m_dockHistoty->hide();//setHidden(true);
    m_dockHistoty->setFixedWidth(250);
    m_tbHistoryShow = new QTextBrowser(m_dockHistoty);
    QLabel *lableHistory = new QLabel(tr("msg record"));
    QVBoxLayout *vLayoutHistory = new QVBoxLayout;
    vLayoutHistory->addWidget(lableHistory);
    vLayoutHistory->addWidget(m_tbHistoryShow);
    vLayoutHistory->setContentsMargins(0,0,0,0);
    m_dockHistoty->setLayout(vLayoutHistory);
//    m_dockHistoty->setFeatures(QDockWidget::DockWidgetMovable
//                               | QDockWidget::DockWidgetFloatable
//                               | QDockWidget::DockWidgetClosable);
//    m_dockHistoty->setFeatures(QDockWidget::DockWidgetClosable);
//    m_dockHistoty->setAllowedAreas(Qt::RightDockWidgetArea);
//    m_dockHistoty->setWidget(m_tbHistoryShow);
//    this->addDockWidget(Qt::LeftDockWidgetArea,dock);
    // remove tile bar
//    QWidget* lTitleBar = m_dockHistoty->titleBarWidget();
//    QWidget* lEmptyWidget = new QWidget();
//    m_dockHistoty->setTitleBarWidget(lEmptyWidget);
//    delete lTitleBar;
    //end


    /*
    QDockWidget *dock = new QDockWidget(tr("DockWindow 1"),this);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    QTextEdit *title1 = new QTextEdit();
    title1->setText("Window 1");
    dock->setWidget(title1);
    this->addDockWidget(Qt::LeftDockWidgetArea,dock);
    */
    hLayoutMid->addLayout(vLayoutLeft);
    hLayoutMid->addWidget(m_dockHistoty);

    /***********************the entire layout**************************/


    QVBoxLayout *vLayoutMain = new QVBoxLayout(this);

//    vLayoutMain->setSizeConstraint(QLayout::SetFixedSize);
    vLayoutMain->addLayout(vLayoutFriend);
    vLayoutMain->addLayout(hLayoutMid);
//    hLayoutMain->addWidget(m_tbHistoryShow);
//    hLayoutMain->addWidget(m_dockHistoty);
    setLayout(vLayoutMain);

//    setCentralWidget();
    m_textInput->setFocus();
}



/*************************************************
Function Name： linkSignalWithSlot()
Description:  connect signal with slot
*************************************************/
void IMChatWidget::linkSignalWithSlot()
{
    connect(m_textInput, SIGNAL(sendMessage()),
            this, SLOT(onClickBtnSend()));
    connect(m_btnSend, SIGNAL(clicked()),
            this, SLOT(onClickBtnSend()));
    connect(m_btnClose, SIGNAL(clicked()),
            this, SLOT(onClickBtnClose()));

    connect(m_toolBtnVideo, SIGNAL(clicked()),
            this, SLOT(onClickBtnVideo()));
    connect(m_toolBtnVoice, SIGNAL(clicked()),
            this, SLOT(onClickBtnVoice()));
    connect(m_toolBtnFile, SIGNAL(clicked()),
            this, SLOT(onClickBtnFile()));
    connect(m_toolBtnSpace, SIGNAL(clicked()),
            this, SLOT(onClickBtnSpace()));

    connect(m_cbFont, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(setInputTextFont(QFont)));
    connect(m_cbSize, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(setInputTextSize(QString)));
    connect(m_toolBtnBold, SIGNAL(clicked(bool)),
            this, SLOT(onClickBtnBold(bool)));
    connect(m_toolBtnItalic, SIGNAL(clicked(bool)),
            this, SLOT(onClickBtnItalic(bool)));
    connect(m_toolBtnUnderline, SIGNAL(clicked(bool)),
            this, SLOT(onClickBtnUnderline(bool)));

    connect(m_toolBtnColor, SIGNAL(clicked()),
            this, SLOT(onClickBtnColor()));
    connect(m_toolBtnClear, SIGNAL(clicked()),
            this, SLOT(onClickBtnClear()));

    connect(m_toolBtnHistory, SIGNAL(clicked(bool)),
            this, SLOT(onClickBtnHistory(bool)));

//    connect(m_toolBtnHistory, SIGNAL(toggled(bool)),
//            m_dockHistoty, SLOT(setVisible(bool)));

    connect(m_textInput, SIGNAL(currentCharFormatChanged(QTextCharFormat)),
            this, SLOT(currentFormatChanged(QTextCharFormat)));

}

/*************************************************
Function Name： setWidgetToolBtn()
Description:  set panel picture
*************************************************/
void IMChatWidget::setWidgetToolBtn()
{
    m_toolBtnVideo = new QToolButton;
//    m_toolBtnVideo->setStyleSheet("QToolButton { background-color: red; border: none; }");
//    m_toolBtnVideo->setStyleSheet("QToolButton { image:url(:/images/camera.png); border: none; width: CHAT_WIDGET_TOOL_SIZEpx; height: CHAT_WIDGET_TOOL_SIZEpx;}");
    m_toolBtnVideo->setIcon(QIcon(":/images/camera.png"));
    m_toolBtnVideo->setAutoRaise(true);
    m_toolBtnVideo->setToolTip(tr("video"));
    m_toolBtnVideo->setStatusTip(tr("open video"));
//    m_toolBtnVideo->setAutoFillBackground(true);

//    m_toolBtnVideo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_toolBtnVideo->setIconSize(QSize(CHAT_WIDGET_TOOL_SIZE,CHAT_WIDGET_TOOL_SIZE));
    //m_toolBtnVideo->setEnabled(true);

    m_toolBtnVoice = new QToolButton;
    m_toolBtnVoice->setIcon(QIcon(":/images/microphone.png"));
    m_toolBtnVoice->setAutoRaise(true);
    m_toolBtnVoice->setToolTip(tr("vadio"));
    m_toolBtnVoice->setStatusTip(tr("open vadio"));
    m_toolBtnVoice->setIconSize(QSize(CHAT_WIDGET_TOOL_SIZE,CHAT_WIDGET_TOOL_SIZE));
//    connect(m_toolBtnVoice, SIGNAL(clicked()),
//            this, SLOT(onClickBtnVoice()));

    m_toolBtnFile = new QToolButton;
    m_toolBtnFile->setIcon(QIcon(":/images/send_file.png"));
    m_toolBtnFile->setAutoRaise(true);
    m_toolBtnFile->setToolTip(tr("send file"));
    m_toolBtnFile->setStatusTip(tr("send file"));
    m_toolBtnFile->setIconSize(QSize(CHAT_WIDGET_TOOL_SIZE,CHAT_WIDGET_TOOL_SIZE));

    m_toolBtnSpace = new QToolButton;
    m_toolBtnSpace->setIcon(QIcon(":/images/space.png"));
    m_toolBtnSpace->setAutoRaise(true);
    m_toolBtnSpace->setToolTip(tr("space"));
    m_toolBtnSpace->setStatusTip(tr("open space"));
    m_toolBtnSpace->setIconSize(QSize(CHAT_WIDGET_TOOL_SIZE,CHAT_WIDGET_TOOL_SIZE));
//---------------------------------------------------------------------------
//    m_toolBtnFont = new QToolButton;
//    m_toolBtnFont->setIcon(QIcon(":/images/font.png"));
//    m_toolBtnFont->setAutoRaise(true);
//    m_toolBtnFont->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));

    m_cbFont = new QFontComboBox;
    m_cbFont->setToolTip(tr("font"));
    m_cbFont->setStatusTip(tr("set font"));
    m_cbSize = new QComboBox;
    m_cbSize->setToolTip(tr("size"));
    m_cbSize->setStatusTip(tr("set font size"));
    for (int i=9;  i<=22; ++i)
    {
        m_cbSize->addItem(QString::number(i));
    }
    m_cbSize->setCurrentIndex(0);

    m_cbSize->setMaxVisibleItems(10);
    m_cbFont->setMaxVisibleItems(10);

    m_toolBtnBold = new QToolButton;
    m_toolBtnBold->setCheckable(true);
    m_toolBtnBold->setIcon(QIcon(":/images/font_bold.png"));
    m_toolBtnBold->setAutoRaise(true);
    m_toolBtnBold->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));
    m_toolBtnBold->setToolTip(tr("bold"));
    m_toolBtnBold->setStatusTip(tr("make bold"));

    m_toolBtnItalic = new QToolButton;
    m_toolBtnItalic->setCheckable(true);
    m_toolBtnItalic->setIcon(QIcon(":/images/font_italic.png"));
    m_toolBtnItalic->setAutoRaise(true);
    m_toolBtnItalic->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));
    m_toolBtnItalic->setToolTip(tr("italic"));
    m_toolBtnItalic->setStatusTip(tr("make intalic"));

    m_toolBtnUnderline = new QToolButton;
    m_toolBtnUnderline->setCheckable(true);
    m_toolBtnUnderline->setIcon(QIcon(":/images/font_underline.png"));
    m_toolBtnUnderline->setAutoRaise(true);
    m_toolBtnUnderline->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));
    m_toolBtnUnderline->setToolTip(tr("undeline"));
    m_toolBtnUnderline->setStatusTip(tr("make underlined"));

    m_toolBtnColor = new QToolButton;
    m_toolBtnColor->setIcon(QIcon(":/images/colour.png"));
    m_toolBtnColor->setAutoRaise(true);
    m_toolBtnColor->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));
    m_toolBtnColor->setToolTip(tr("color"));
    m_toolBtnColor->setStatusTip(tr("set color"));

    m_toolBtnClear = new QToolButton;
    m_toolBtnClear->setIcon(QIcon(":/images/clear.png"));
    m_toolBtnClear->setAutoRaise(true);
    m_toolBtnClear->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));
    m_toolBtnClear->setToolTip(tr("clear"));
    m_toolBtnClear->setStatusTip(tr("clean msg"));

    m_toolBtnHistory = new QToolButton;
    m_toolBtnHistory->setIcon(QIcon(":/images/message.png"));
    m_toolBtnHistory->setAutoRaise(true);
    m_toolBtnHistory->setCheckable(true);
    m_toolBtnHistory->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));
    m_toolBtnHistory->setToolTip(tr("msg record"));
    m_toolBtnHistory->setStatusTip(tr("open msg record"));
}

/*************************************************
Function Name： saveHistoryMessage()
Description:  保存历史记录
*************************************************/
void IMChatWidget::saveHistoryMessage()
{
    QString filePath = LOCAL_HISTORY_MESSAGE_PATH;
    filePath.append(m_chatInfor.m_myID);
    QString fileName = QString("%1_%2_friend.imres")
            .arg(m_chatInfor.m_myID, m_chatInfor.m_friendID);

    IMClientFileCtrl::saveTalkHistory(filePath, fileName, m_tbMessageShow);
}

/*************************************************
Function Name： readHistoryMessage()
Description:  
*************************************************/
void IMChatWidget::readHistoryMessage()
{
    QString filePath = LOCAL_HISTORY_MESSAGE_PATH;
    filePath.append(m_chatInfor.m_myID);
    QString fileName = QString("%1_%2_friend.imres")
            .arg(m_chatInfor.m_myID, m_chatInfor.m_friendID);

    IMClientFileCtrl::readTalkHistory(filePath, fileName, m_tbHistoryShow);

//    tbHistory->verticalScrollBar()->setValue(
//                tbHistory->verticalScrollBar()->maximum());
}

// private slots:-----------------------------------------------------
/*************************************************
Function Name： onClickBtnVideo()
Description:  
*************************************************/
void IMChatWidget::onClickBtnVideo()
{
//    m_toolBtnVideo->setEnabled(false);
//    m_mes.m_type = REQUEST_VIDEO;
//    m_mes.m_receiverID = m_chatInfor.m_friendID;
//    m_mes.m_text = "2222";
////    m_mes.m_senderID = m_chatInfor.m_;
////    m_mes.m_senderIP = IMTcpSocket::getIP();

//    qDebug() << "";
//    // show wait
//    m_videoShow = new ShowVideoWidget(2222);

//    connect(this, SIGNAL(destroyed()),
//            m_videoShow, SLOT(deleteLater()));
//    m_videoShow->show();

//    emit sendMessagesFromChat(m_mes);

}


/*************************************************
Function Name： onClickBtnVoice()
Description:  voice
*************************************************/
void IMChatWidget::onClickBtnVoice()
{
}


/*************************************************
Function Name： onClickBtnFile()
Description:  send file
*************************************************/
void IMChatWidget::onClickBtnFile()
{
    if (m_fileSender->isVisible())
    {
        return;
    }
    if (OFFLINE == m_chatInfor.m_friendStatus)
    {
        QMessageBox::critical(NULL, tr("send file"), tr("friend is offline, can't send file now"));
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName.isEmpty())
    {
        QMessageBox::information(this,tr("warning"),tr("please select file"));
        return;
    }
    m_fileSender->initSender();
    if (!m_fileSender->startSending(fileName))
        return;
    m_fileSender->move(500, 200);
    m_fileSender->show();

    //m_toolBtnFile->setEnabled(false);
    m_mes.m_type = REQUEST_FILE;
    m_mes.m_receiverID = m_chatInfor.m_friendID;
    m_mes.m_text = fileName;

    emit sendMessagesFromChat(m_mes);
}


/*************************************************
Function Name： onClickBtnSpace()
Description:   
*************************************************/
void IMChatWidget::onClickBtnSpace()
{
}


/*************************************************
Function Name： setInputTextFont()
Description:   
*************************************************/
void IMChatWidget::setInputTextFont(const QFont &font)
{
    m_textInput->setCurrentFont(font);
    m_textInput->setFocus();
}

/*************************************************
Function Name： setInputTextSize()
Description:   
*************************************************/
void IMChatWidget::setInputTextSize(const QString &size)
{
    m_textInput->setFontPointSize(size.toDouble());
    m_textInput->setFocus();
}


/*************************************************
Function Name： onClickBtnBold()
Description:   
*************************************************/
void IMChatWidget::onClickBtnBold(bool checked)
{
    if(checked)
        m_textInput->setFontWeight(QFont::Bold);
    else
        m_textInput->setFontWeight(QFont::Normal);
    m_textInput->setFocus();
}

/*************************************************
Function Name： onClickBtnItalic()
Description:    
*************************************************/
void IMChatWidget::onClickBtnItalic(bool checked)
{
    m_textInput->setFontItalic(checked);
    m_textInput->setFocus();
}


/*************************************************
Function Name： onClickBtnUnderline()
Description:   
*************************************************/
void IMChatWidget::onClickBtnUnderline(bool checked)
{
    m_textInput->setFontUnderline(checked);
    m_textInput->setFocus();
}

/*************************************************
Function Name： onClickBtnColor()
Description:   
*************************************************/
void IMChatWidget::onClickBtnColor()
{
    QColor color = QColorDialog::getColor(color,this);
    if(color.isValid())
    {
        m_textInput->setTextColor(color);
        m_textInput->setFocus();

        //		saveFile.color = colorDialog->currentColor();
        //		saveFontColor();
    }

}

/*************************************************
Function Name： onClickBtnClear()
Description:  
*************************************************/
void IMChatWidget::onClickBtnClear()
{
    saveHistoryMessage();
    m_tbMessageShow->clear();
}


/*************************************************
Function Name： onClickBtnHistory()
Description:  
*************************************************/
void IMChatWidget::onClickBtnHistory(bool checked)
{
    m_dockHistoty->setHidden(!checked);
    if (checked)
    {
        readHistoryMessage();
    }
}

/*************************************************
Function Name： currentFormatChanged()
Description:  
*************************************************/
void IMChatWidget::currentFormatChanged(const QTextCharFormat &format)
{
    m_cbFont->setCurrentFont(format.font());

    if(format.fontPointSize()<9)  
        m_cbSize->setCurrentIndex(3); 
    else m_cbSize->setCurrentIndex(
            m_cbSize->findText(QString::number(format.fontPointSize())));

    m_toolBtnBold->setChecked(format.font().bold());
    m_toolBtnItalic->setChecked(format.font().italic());
    m_toolBtnUnderline->setChecked(format.font().underline());
//    color = format.foreground().color();
}

/*************************************************
Function Name： onClickBtnClocse()
Description:  
*************************************************/
void IMChatWidget::onClickBtnClose()
{
    this->close();
}


/*************************************************
Function Name： onClickBtnSend()
Description:  
*************************************************/
void IMChatWidget::onClickBtnSend()
{
    if (m_textInput->toPlainText().isEmpty())
        return;
    QString sendString = m_textInput->toHtml();
    m_textInput->clear();
//    QString dateTime = IMTcpSocket::getCurrentDateTime();
    QDateTime dateTime = QDateTime::currentDateTime();
    QString temp = QString("<font size=\"FONT_SIEZE\" color=green>%1    %2: </font>%3")
        .arg(" I ").arg(dateTime.toString("yyyy-MM-dd hh:mm:ss")).arg(sendString);
    m_tbMessageShow->append(temp);

    m_mes.m_text = sendString;
    m_mes.m_type = TALK_MESSAGE;
    m_mes.m_receiverID = m_chatInfor.m_friendID;
    m_mes.m_dateTime = dateTime;
//    m_mes.m_senderID = m_chatInfor.m_;
//    m_mes.m_senderIP = IMTcpSocket::getIP();

    emit sendMessagesFromChat(m_mes);
}
