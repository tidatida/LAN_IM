#ifndef IMLOCALMESSAGEWIDGET_H
#define IMLOCALMESSAGEWIDGET_H

#include <QWidget>
#include "IMMessageWidget.h"

class IMMainWidget;

class IMLocalMessageWidget : public IMMessageWidget
{
    Q_OBJECT
public:
    IMLocalMessageWidget(IMMainWidget *, QWidget *parent = 0);
    ~IMLocalMessageWidget();
    
signals:
    
public slots:
    // delete  某日,s 信息记录
    void onClickDeleteDate();
    // delete  某好友信息记录
    void onClickDeleteOne();
    // delete  全部消息记录
    void onClickDeleteAll();
    // 导人消息记录
    void onClickImport();
    // 导出当前好友消息记录
    void onClickExportOne();
    // 导出 all 消息记录
    void onClickExportAll();
    //  get 消息记录
    void onClickGetMessage();
//    // 单击好友 table  项
//    void friendItemClicked(const QModelIndex &);
    
private:
    IMMainWidget * m_mainWidget;
};

#endif // IMLOCALMESSAGEWIDGET_H
