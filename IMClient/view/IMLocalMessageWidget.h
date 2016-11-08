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
    void onClickDeleteDate();
    void onClickDeleteOne();
    void onClickDeleteAll();
    void onClickImport();
    void onClickExportOne();
    void onClickExportAll();
    void onClickGetMessage();
    
private:
    IMMainWidget * m_mainWidget;
};

#endif // IMLOCALMESSAGEWIDGET_H
