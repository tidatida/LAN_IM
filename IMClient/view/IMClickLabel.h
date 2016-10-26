/*********************************************
File Name: IMClickLabel.h
Author: jet.F.R
Date: 2014.3.10
Description: 
Changes:
********************************************/

#ifndef IMCLICKLABEL_H
#define IMCLICKLABEL_H

#include <QLabel>


/*************************************************
Class Name: IMClickLabel
Description: 
*************************************************/
class IMClickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit IMClickLabel(QWidget *parent = 0);
    IMClickLabel(const QString &text, QWidget *parent=0);
signals:
    void clicked();//IMClickLabel* label);

protected:
    void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
public slots:
    
};

#endif // IMCLICKLABEL_H
