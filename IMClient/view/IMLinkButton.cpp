#include "IMLinkButton.h"
#include <QMenu>
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

IMLinkButton::IMLinkButton(QWidget *parent) :
    QPushButton(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    m_labelHead = new QLabel;
    m_labelHead->setFixedSize(HEAD_SMALL_SIZE, HEAD_SMALL_SIZE);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->setContentsMargins(0,0,0,0);
    m_labelInfo = new QLabel;
    m_labelMes = new QLabel;
    rightLayout->addWidget(m_labelInfo);
    rightLayout->addWidget(m_labelMes);

    mainLayout->addWidget(m_labelHead);
    mainLayout->addLayout(rightLayout);
    mainLayout->addStretch();
    mainLayout->setContentsMargins(0,0,0,0);
    setLayout(mainLayout);
    setMinimumSize(100,40);

    m_menu = NULL;

    setStyleSheet("QPushButton{border: 0;}");
}

/*************************************************
Function Name: setLatestMessage()
Description:   
*************************************************/
void IMLinkButton::setLatestMessage(const TalkMessage & mes)
{
    m_labelMes->setText(mes.m_text);
}


/*************************************************
Function Name: onClickRightButton()
Description:  
*************************************************/
void IMLinkButton::onClickRightButton(/*const QPoint &*/)
{
    if (m_menu == NULL)
    {
        //create  right button  menu 
        creatMenu();
    }
    m_menu->exec(QCursor::pos());
}


//remark:protected:----------------------------------------

/*************************************************
Function Name: mousePressEvent
Description:   
*************************************************/
void IMLinkButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        onClickRightButton();
        return;
    }
    QPushButton::mousePressEvent(event);
}

/*************************************************
Function Name: mouseDoubleClickEvent
Description:   
*************************************************/
void IMLinkButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
//        emit leftDoubleClickSignal();
        onDoubleClickButton();
        return;
    }
    QPushButton::mouseDoubleClickEvent(event);
}



//remark:private:----------------------------------------

/*************************************************
Function Name: getStatusFromInt()
Description: create  right button  menu 
*************************************************/
void IMLinkButton::creatMenu(/*const QList<QString> *groutList*/)
{
    m_menu = new QMenu(this);
    QAction *showMessage = new QAction(tr("view message"), m_menu);
    QAction *ignoreMessage = new QAction(tr("ignore message"), m_menu);
    connect(showMessage, SIGNAL(triggered()),
            this, SLOT(onDoubleClickButton()));
    connect(ignoreMessage, SIGNAL(triggered()),
            this, SLOT(ignoreMessage()));

    m_menu->addAction(showMessage);
    m_menu->addAction(ignoreMessage);
}
