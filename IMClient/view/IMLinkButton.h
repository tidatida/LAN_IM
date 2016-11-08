#ifndef IMLINKBUTTON_H
#define IMLINKBUTTON_H

#include <QPushButton>
#include "model/IMConstant.h"
class QLabel;

class IMLinkButton : public QPushButton
{
    Q_OBJECT
public:
    IMLinkButton(QWidget *parent = 0);
    virtual ~IMLinkButton(){}

    void setLatestMessage(const TalkMessage & mes);

    virtual void setButtonStatus() = 0;
    
signals:
    void deleteLinkButton(const QString & id);

    
public slots:
    virtual void onDoubleClickButton() = 0;
    //  right button  click  button 
    virtual void onClickRightButton(/*const QPoint &*/);
    virtual void ignoreMessage() = 0;

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *);

protected:
    QLabel *m_labelHead;
    QLabel *m_labelInfo;
    QLabel *m_labelMes;

    //  right button  menu 
    QMenu *m_menu;

private:
    // create  right button  menu 
    void creatMenu(/*const QList<QString> *groutList*/);
};

#endif // IMLINKBUTTON_H
