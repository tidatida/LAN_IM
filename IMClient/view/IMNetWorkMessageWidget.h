#ifndef IMNETWORKMESSAGEWIDGET_H
#define IMNETWORKMESSAGEWIDGET_H

#include "IMMessageWidget.h"

class IMMainWidget;

class IMNetWorkMessageWidget : public IMMessageWidget
{
    Q_OBJECT
public:
    IMNetWorkMessageWidget(IMMainWidget *, QWidget *parent = 0);
    ~IMNetWorkMessageWidget();
    
signals:
    
public slots:
    // delete  某日,s 信息记录
    void onClickDeleteDate();
    // delete  某好友信息记录
    void onClickDeleteOne();
    // delete  全部消息记录
    void onClickDeleteAll();
    // 导出某好友消息记录
    void onClickExportOne();
    // 导出 all 消息记录
    void onClickExportAll();
    //  get 消息记录
    void onClickGetMessage();
//    // 单击好友列 table 项
//    void friendItemClicked(const QModelIndex & index);
private:
    IMMainWidget * m_mainWidget;
};

#endif // IMNETWORKMESSAGEWIDGET_H
