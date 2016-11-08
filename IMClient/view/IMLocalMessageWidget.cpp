#include "IMLocalMessageWidget.h"
#include "view/IMMainWidget.h"
#include <QDebug>
#include <QModelIndex>
#include "CustomLineEdit.h"
#include <QListView>
#include <QMessageBox>

IMLocalMessageWidget::IMLocalMessageWidget(IMMainWidget *mainWidget, QWidget *parent) :
    IMMessageWidget(mainWidget, parent), m_mainWidget(mainWidget)
{
    if (m_mainWidget == NULL)
    {
        return;
    }
    setShowMode(LOCAL);
}


 IMLocalMessageWidget::~IMLocalMessageWidget()
 {
 }



 // public slots:------------------------------------

 /*************************************************
 Function Name: onClickDeleteDate()
 Description:  
 *************************************************/
 void IMLocalMessageWidget::onClickDeleteDate()
 {
 }

 /*************************************************
 Function Name: onClickDeleteOne()
 Description:  
 *************************************************/
 void IMLocalMessageWidget::onClickDeleteOne()
 {
     int row = m_listViewFriend->currentIndex().row();
     if (row < 0)
     {
         QString temp = QString(tr(" please  first 选择好友！"));
         QMessageBox::information(NULL, tr("delete  聊天记录"), temp);
         return;
     }
     if (NULL == m_mainWidget)
         return;
     m_mainWidget->deleteLocalMessage(m_indexOfFriendList);
 }

 /*************************************************
 Function Name: onClickDeleteAll()
 Description:  
 *************************************************/
 void IMLocalMessageWidget::onClickDeleteAll()
 {
     if (NULL == m_mainWidget)
         return;
     m_mainWidget->deleteLocalMessageAll();
 }

 /*************************************************
 Function Name: onClickImport()
 Description:  
 *************************************************/
 void IMLocalMessageWidget::onClickImport()
 {
 }

 /*************************************************
 Function Name: onClickExportOne()
 Description:  
 *************************************************/
 void IMLocalMessageWidget::onClickExportOne()
 {
     int row = m_listViewFriend->currentIndex().row();
     if (row < 0)
     {
         QString temp = QString(tr(" please  select friend first ~"));
         QMessageBox::information(NULL, tr("export chatting log"), temp);
         return;
     }
     if (NULL == m_mainWidget)
         return;
     m_mainWidget->exportLocalMessage(m_indexOfFriendList);
 }

 /*************************************************
 Function Name: onClickExportAll()
 Description:  
 *************************************************/
 void IMLocalMessageWidget::onClickExportAll()
 {
     if (NULL == m_mainWidget)
         return;
     m_mainWidget->exportLocalMessageAll();
 }


 /*************************************************
 Function Name: onClickGetMessage()
 Description:   
 *************************************************/
 void IMLocalMessageWidget::onClickGetMessage()
 {
//     if (m_listViewFriend->isSe)
     int row = m_listViewFriend->currentIndex().row();
     if (row < 0)
     {
         QString temp = QString(tr(" please select a friend firstly ~ "));
         QMessageBox::information(NULL, tr("display chatting logs "), temp);
         return;
     }
     m_date = m_leBirthday->getDate();
     qDebug() << "get  date:" <<  m_date;
     m_mainWidget->getLocalHistoryMessage(m_indexOfFriendList, m_date);
 }


// /*************************************************
// Function Name: friendItemClicked()
// Description:  
// *************************************************/
// void IMLocalMessageWidget::friendItemClicked(const QModelIndex & index)
// {
//     qDebug() << "friend:" << index.row() << ":" << index.data().toString();
//     emit currentIndexClicked(index.row());
// }
