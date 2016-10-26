#ifndef IMFLOCKCHATWIDGET_H
#define IMFLOCKCHATWIDGET_H

#include <QWidget>
#include "model/IMConstant.h"
#include <QMap>

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
class FlockInformation;
class IMClickLabel;
class QTextCharFormat;
class IMFlockMemberButton;
class IMFlockMemberListWidget;
class IMMainWidget;

class IMFlockChatWidget : public QWidget
{
    Q_OBJECT
public:
    IMFlockChatWidget(const FlockInformation & flock, IMMainWidget *,
                      QWidget *parent = 0);
    ~IMFlockChatWidget();
    // add 群成员发来,s 信息
    void appendMessageShow(const TalkMessage &mes);
    // 设置聊天窗口显示信息
    void setLabelStatus();
    // 设置群信息
    void setChatInformation(const FlockInformation & flock);

    // 设置群成员 name 片
    void setFlockMemberRemark(const TempStrings &);

    //  get 群信息
    FlockInformation getFlockInformation() const
    {
        return m_flockInfor;
    }

    // add 成员 button 
    bool addFlockMemberButton(const FlockMember &);

    // delete  成员 button 
    bool removeFlockMemberButton(const QString & memberID);

signals:
    void sendMessagesFromChat(TalkMessage &);
    //退出信 number 
    void roomQuitSignal();
    
public slots:

    // 设置群成员列 table 
    void setFlockMemberList(const QVector<FlockMember> &);

protected:
    //重载close  event 
    void closeEvent(QCloseEvent *event);

private slots:
    // 字体样式
    void setInputTextFont(const QFont &font);
    // 字体大小
    void setInputTextSize(const QString & size);
    // 加粗
    void onClickBtnBold(bool checked);
    // 斜体
    void onClickBtnItalic(bool checked);
    // 下划线
    void onClickBtnUnderline(bool checked);
    // 颜色
    void onClickBtnColor();
    // 清空
    void onClickBtnClear();
    // 聊天历史记录
    void onClickBtnHistory(bool checked);
    // 当编辑器,s 字体格式改变时，我们让部件状态也随之改变
    void currentFormatChanged(const QTextCharFormat &format);
    // close 
    void onClickBtnClose();
    // 发送聊天信息
    void onClickBtnSend();

private:
    void initIMFlockChatWidget();
    void linkSignalWithSlot();
    void setWidgetToolBtn();
    void saveHistoryMessage();
    void readHistoryMessage();

private:
    IMClickLabel *m_labelHead;
    QLabel *m_labelInformation;      // 群 name  群  theme 
//    QLabel *m_labelTheme;          // 群  theme 
    QTextBrowser *m_tbMessageShow;   // 显示聊天信息

    QFontComboBox *m_cbFont;         // 字体样式选择框
    QComboBox *m_cbSize;             // 字体大小选择框
    QToolButton *m_toolBtnBold;      // 加粗
    QToolButton *m_toolBtnItalic;    // 斜体
    QToolButton *m_toolBtnUnderline; // 下划线
    QToolButton *m_toolBtnColor;     // 颜色
    //    QToolButton *m_toolBtnExpression;//  table 情---------
    //    QToolButton *m_toolBtnScreen;    // 截图---------
    QToolButton *m_toolBtnClear;     // 清空
    QToolButton *m_toolBtnHistory;   // 历史记录
    IMInputTextEdit *m_textInput;          // 信息 input 框
    QPushButton *m_btnClose;            // close  button 
    QPushButton *m_btnSend;             // 发送

    QWidget *m_dockWidget;
    QLabel *m_labelDockWidget;
    QTextBrowser *m_tbHistoryShow;   // 显示聊天历史记录
    IMFlockMemberListWidget *m_memberListWidget;
    FlockInformation m_flockInfor;
    TalkMessage m_mes;

    QMap<QString, IMFlockMemberButton *> m_flockMemberMap; // 群成员ID  and  群成员 button   map  table 

    IMMainWidget *m_mainWidget;

    QVector<TalkMessage> m_messagesVec;
};

#endif // IMFLOCKCHATWIDGET_H
