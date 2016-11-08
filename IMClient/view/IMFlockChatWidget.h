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

    
    void appendMessageShow(const TalkMessage &mes);
    void setLabelStatus();
    void setChatInformation(const FlockInformation & flock);

    void setFlockMemberRemark(const TempStrings &);
    FlockInformation getFlockInformation() const
    {
        return m_flockInfor;
    }

    bool addFlockMemberButton(const FlockMember &);
    bool removeFlockMemberButton(const QString & memberID);

signals:
    void sendMessagesFromChat(TalkMessage &);
    void roomQuitSignal();
    
public slots:

    void setFlockMemberList(const QVector<FlockMember> &);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
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
    void initIMFlockChatWidget();
    void linkSignalWithSlot();
    void setWidgetToolBtn();
    void saveHistoryMessage();
    void readHistoryMessage();

private:
    IMClickLabel *m_labelHead;
    QLabel *m_labelInformation;
    QTextBrowser *m_tbMessageShow;

    QFontComboBox *m_cbFont;
    QComboBox *m_cbSize;
    QToolButton *m_toolBtnBold;
    QToolButton *m_toolBtnItalic;
    QToolButton *m_toolBtnUnderline;
    QToolButton *m_toolBtnColor;
    QToolButton *m_toolBtnClear;
    QToolButton *m_toolBtnHistory;
    IMInputTextEdit *m_textInput;
    QPushButton *m_btnClose;
    QPushButton *m_btnSend;

    QWidget *m_dockWidget;
    QLabel *m_labelDockWidget;
    QTextBrowser *m_tbHistoryShow;
    IMFlockMemberListWidget *m_memberListWidget;
    FlockInformation m_flockInfor;
    TalkMessage m_mes;

    QMap<QString, IMFlockMemberButton *> m_flockMemberMap; 

    IMMainWidget *m_mainWidget;

    QVector<TalkMessage> m_messagesVec;
};

#endif // IMFLOCKCHATWIDGET_H
