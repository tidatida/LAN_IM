#include "IMDiscussionMemberListWidget.h"
#include <QVBoxLayout>
#include <QScrollArea>

IMDiscussionMemberListWidget::IMDiscussionMemberListWidget(QWidget *parent) :
    QWidget(parent),  m_layout(new QVBoxLayout)
{
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
}


/*************************************************
Function Name: addItem()
Description:  add 
*************************************************/
void IMDiscussionMemberListWidget::addItem(QWidget *item)
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
