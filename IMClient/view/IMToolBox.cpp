#include "IMToolBox.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QMenu>
#include <QDebug>
// mark public:------------------------------------------------------
IMToolItem::IMToolItem(const QString &title, QWidget *parent) :
    QWidget(parent), m_layout(new QVBoxLayout)
{
    m_isVisable = false;
    m_layout = new QVBoxLayout;
    m_label = new QLabel(title);
//    label->setStyleSheet("background-color: #1f2021;");
    m_layout->addWidget(m_label);

    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    setLayout(m_layout);

    creatMenu();
}

/*************************************************
Function Name: addItem()
Description:  add 
*************************************************/
void IMToolItem::addItem(QWidget *item)
{
    m_itemList.append(item);
    m_layout->addWidget(item);

    if (0 == m_itemList.size())
        item->setVisible(false);
    else
    {
        item->setVisible(m_isVisable);//m_itemList[0]->isVisible());
    }
}

/*************************************************
Function Name: removeItem()
Description:  delete  
*************************************************/
void IMToolItem::removeItem(QWidget *item)
{
    m_layout->removeWidget(item);
    m_itemList.removeAt(m_itemList.indexOf(item));
}


/*************************************************
Function Name: setTile()
Description:   set 标题
*************************************************/
void IMToolItem::setTile(const QString & title)
{
    m_label->setText(title);
}

/*************************************************
Function Name: getSize()
Description:   get 成员数量
*************************************************/
int IMToolItem::getSize()
{
    return m_itemList.size();
}

// mark protected:------------------------------------------------------
/*************************************************
Function Name: mousePressEvent
Description:  mouse  click  event 
*************************************************/
void IMToolItem:: mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        for (int i=0; i<m_itemList.size(); ++i)
        {
            m_itemList[i]->setVisible(!m_itemList[i]->isVisible());
        }

        if (m_itemList.size() > 0)
            m_isVisable = m_itemList[0]->isVisible();
        return;
    }
    else if (event->button() == Qt::RightButton)
    {
        onClickRightButton();
        return;
    }
    QWidget::mousePressEvent(event);
}

// mark private slots:--------------------------------------------------
/*************************************************
Function Name: renameBox()
Description:  重命 name 
*************************************************/
void IMToolItem::renameBox()
{
    qDebug() << "chose rename";
    emit renameBoxSignal(m_label->text());
}

/*************************************************
Function Name: removeBox()
Description:  delete  整个
*************************************************/
void IMToolItem::removeBox()
{
    qDebug() << "chose remove";
    emit removeBoxSignal(m_label->text());
}


/*************************************************
Function Name: onClickRightButton()
Description:  right button  click  button 
*************************************************/
void IMToolItem::onClickRightButton()
{
    if (m_menu == NULL)
    {
        //create  right button  menu 
        creatMenu();
    }
    m_menu->exec(QCursor::pos());
}

/*************************************************
Function Name: creatMenu
Description: create  right button  menu 
*************************************************/
void IMToolItem:: creatMenu()
{
    m_menu = new QMenu(this);
    QAction *rename = new QAction(tr("重命 name "), m_menu);
    QAction *remove = new QAction(tr("delete  "), m_menu);

    connect(rename, SIGNAL(triggered()),
            this, SLOT(renameBox()));
    connect(remove, SIGNAL(triggered()),
            this, SLOT(removeBox()));

    m_menu->addAction(rename);
    m_menu->addAction(remove);
}


IMToolBox::IMToolBox(QWidget *parent) :
    QWidget(parent), m_layout(new QVBoxLayout)
{
    setLayout(m_layout);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
}

/*************************************************
Function Name: addItem()
Description:  add 
*************************************************/
void IMToolBox::addItem(IMToolItem *item)
{
    m_layout->addWidget(item);
}
