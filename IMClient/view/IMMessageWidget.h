#ifndef IMMESSAGEWIDGET_H
#define IMMESSAGEWIDGET_H

#include <QWidget>
#include "model/IMConstant.h"

class QLabel;
class QToolButton;
class QPixmap;
class QListView;
class CustomLineEdit;
class QTextBrowser;
class QTextCharFormat;
class QStringListModel;
class IMMainWidget;
class QModelIndex;

class IMMessageWidget : public QWidget
{
    Q_OBJECT
public:
    IMMessageWidget(IMMainWidget *, QWidget *parent = 0);

    virtual ~IMMessageWidget();

    //  set   box  ,s model
    void setListModelGroup(const QStringList & groupList);
    void setListModelGroup();

    //  set  好友 ,s model
    void setListModelFriend(const QStringList & friendList);
    void setListModelFriend(const QString & groupName);

    enum Mode{ LOCAL, NETWORK};
    //  set 模式
    void setShowMode(Mode mode);

    void setMessageShow(const QVector<TalkMessage> & mesVec);
    
signals:
    void currentIndexClicked(int);
public slots:
    // delete  某日,s 信息记录
    virtual void onClickDeleteDate() = 0;
    // delete  某好友信息记录
    virtual void onClickDeleteOne() = 0;
    // delete  全部消息记录
    virtual void onClickDeleteAll() = 0;
    // 导人消息记录
    virtual void onClickImport(){}
    // 导出某好友消息记录
    virtual void onClickExportOne() = 0;
    // 导出 all 消息记录
    virtual void onClickExportAll() = 0;
    //  get 消息记录
    virtual void onClickGetMessage() = 0;

    // 单击  box 列 table 
    void groupItemClicked(const QModelIndex &);
    // 单击 好友列 table 
    void friendItemClicked(const QModelIndex &);
//    virtual void friendItemClicked(const QModelIndex &) = 0;

protected:
    int m_indexOfFriendList;
    QString m_name;
    QDate m_date;
    CustomLineEdit *m_leBirthday;
    QListView *m_listViewGroup;
    QListView *m_listViewFriend;
    QTextBrowser *m_tbMessageShow;

private:
    // init 
    void initIMMessageWidget();
    // 链接信 number  and 槽
    void linkSignalWithSlot();

private:
    IMMainWidget * m_mainWidget;

    QStringList m_groupList;
    QStringList m_friendList;

    QStringListModel *m_modelGroup;
    QStringListModel *m_modelFriend;


    QLabel *m_labelInformation;
//    QToolButton *m_toolBtnDeleteDate;
    QToolButton *m_toolBtnDeleteOne;
    QToolButton *m_toolBtnDeleteAll;
    QToolButton *m_tooBtnImport;
    QToolButton *m_toolBtnExportOne;
    QToolButton *m_toolBtnExportAll;
    QToolButton *m_toolBtnGetMessage;
};

#endif // IMMESSAGEWIDGET_H
