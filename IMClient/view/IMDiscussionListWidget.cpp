#include "IMDiscussionListWidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMenu>
#include "IMMainWidget.h"
#include <QDebug>
#include <QMouseEvent>
IMDiscussionListWidget::IMDiscussionListWidget(IMMainWidget *mainWidget, QWidget *parent) :
    QWidget(parent),  m_layout(new QVBoxLayout)
{
    m_mainWidget = mainWidget;
    QVBoxLayout *mainLayout=new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    m_contentsWidget = new QWidget;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    m_contentsWidget->setLayout(m_layout);
    m_contentsWidget->setStyleSheet("QWidget{border: 0;}");

    m_discussionsScrollArea = new QScrollArea(this);
    m_discussionsScrollArea->setWidgetResizable(true);
    m_discussionsScrollArea->setAlignment(Qt::AlignLeft);

    m_discussionsScrollArea->setWidget(m_contentsWidget);

    mainLayout->addWidget(m_discussionsScrollArea);
    setLayout(mainLayout);

    setStyleSheet("QWidget{border: 0;}");

    //create  right button  menu 
    creatMenu();
}


/*************************************************
Function Name: addItem()
Description:  add 
*************************************************/
void IMDiscussionListWidget::addItem(QWidget *item)
{
    // Remove last spacer item if present.
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
void IMDiscussionListWidget::removeItem(QWidget *item)
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
void IMDiscussionListWidget::creatMenu()
{
    m_menu = new QMenu(this);
    QAction *actCreateDiscussion = new QAction(tr(" create 讨论 box "), this);
//    QAction *actAddFlock = new QAction(tr("add 讨论 box "), this);
    QAction *actRefresh = new QAction(tr("刷 new 讨论 box  table  "), this);

    connect(actCreateDiscussion, SIGNAL(triggered()),
        m_mainWidget, SLOT(createDiscussion()));
//    connect(actAddDiscussion, SIGNAL(triggered()),
//        m_mainWidget, SLOT(onClickAddFlock()));
    connect(actRefresh, SIGNAL(triggered()),
        m_mainWidget, SLOT(getDiscussionsInformation()));

    m_menu->addAction(actCreateDiscussion);
//    m_menu->addAction(actAddDiscussion);
    m_menu->addAction(actRefresh);
}


/*************************************************
Function Name: showMenu()
Description:  显示 right button  menu 
*************************************************/
void IMDiscussionListWidget::showMenu()
 {
    if (m_menu == NULL)
    {
        //create  right button  menu 
        creatMenu();
    }
    m_menu->exec(QCursor::pos());
 }


/*************************************************
Function Name: mousePressEvent
Description:  mouse 单击 event 
*************************************************/
void IMDiscussionListWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        showMenu();
        return;
    }
    QWidget::mousePressEvent(event);
}
