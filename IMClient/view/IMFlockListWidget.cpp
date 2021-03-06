#include "IMFlockListWidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMenu>
#include "IMMainWidget.h"
#include <QDebug>
#include <QMouseEvent>

IMFlockListWidget::IMFlockListWidget(IMMainWidget *mainWidget, QWidget *parent) :
    QWidget(parent),  m_layout(new QVBoxLayout), m_mainWidget(mainWidget)
{
    if (NULL == m_mainWidget){
        return;
    }

    QVBoxLayout *mainLayout=new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    m_contentsWidget = new QWidget;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    m_contentsWidget->setLayout(m_layout);
    m_contentsWidget->setStyleSheet("QWidget{border: 0;}");

    m_flocksScrollArea = new QScrollArea(this);
    m_flocksScrollArea->setWidgetResizable(true);
    m_flocksScrollArea->setAlignment(Qt::AlignLeft);

    m_flocksScrollArea->setWidget(m_contentsWidget);

    mainLayout->addWidget(m_flocksScrollArea);
    setLayout(mainLayout);

    setStyleSheet("QWidget{border: 0;}");

    creatMenu();
}


/*************************************************
Function Name: addItem()
Description:  add 
*************************************************/
void IMFlockListWidget::addItem(QWidget *item)
{
    int count = m_layout->count();

    if (count > 1)
    {
        m_layout->removeItem(m_layout->itemAt(count - 1));
    }

    // Add item and make sure it stretches the remaining space.
    m_layout->addWidget(item);
    m_layout->addStretch();
}

/*************************************************
Function Name: removeItem()
Description:  delete  
*************************************************/
void IMFlockListWidget::removeItem(QWidget *item)
{
    m_layout->removeWidget(item);

    if (m_layout->count() == 1)
    {
        m_layout->removeItem(m_layout->itemAt(0));
    }
}


/*************************************************
Function Name: creatMenu()
Description:  create  right button  menu 
*************************************************/
void IMFlockListWidget::creatMenu()
{
    m_menu = new QMenu(this);
    QAction *actCreateFlock = new QAction(tr(" create group"), this);
    QAction *actAddFlock = new QAction(tr("add group"), this);
    QAction *actRefresh = new QAction(tr("refresh group table"), this);

    connect(actCreateFlock, SIGNAL(triggered()),m_mainWidget, SLOT(createFlock()));
    connect(actAddFlock, SIGNAL(triggered()),m_mainWidget, SLOT(onClickAddFlock()));
    connect(actRefresh, SIGNAL(triggered()),m_mainWidget, SLOT(getFlocksInformation()));

    m_menu->addAction(actCreateFlock);
    m_menu->addAction(actAddFlock);
    m_menu->addAction(actRefresh);
}


/*************************************************
Function Name: showMenu()
Description:  display right button  menu 
*************************************************/
void IMFlockListWidget::showMenu()
 {
    if (m_menu == NULL)
    {
        creatMenu();
    }

    m_menu->exec(QCursor::pos());
 }


/*************************************************
Function Name: mousePressEvent
Description:  mouse click event 
*************************************************/
void IMFlockListWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        showMenu();
        return;
    }

    QWidget::mousePressEvent(event);
}
