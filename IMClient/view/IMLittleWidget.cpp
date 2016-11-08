#include "IMLittleWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include "model/IMConstant.h"

IMLittleWidget::IMLittleWidget(int num, QWidget *parent) :
    QWidget(parent), m_numOfLineEdit(num)
{
    Qt::WindowFlags flag = Qt::Window
        | Qt::WindowCloseButtonHint
        | Qt::WindowMinimizeButtonHint;
    setWindowFlags(flag);

    // mainframe layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    m_labelFirst = new QLabel(this);
    m_leFirst = new QLineEdit(this);
    mainLayout->addWidget(m_labelFirst);
    mainLayout->addWidget(m_leFirst);
    if (m_numOfLineEdit >= 2)
    {
        m_labelSecond = new QLabel(this);
        m_leSecond = new QLineEdit(this);
        mainLayout->addWidget(m_labelSecond);
        mainLayout->addWidget(m_leSecond);
    }
    if (m_numOfLineEdit >3)
    {
        m_labelThird = new QLabel(this);
        m_leThird= new QLineEdit(this);
        mainLayout->addWidget(m_labelThird);
        mainLayout->addWidget(m_leThird);
    }

    m_btnOk = new QPushButton(tr("Yes"));
    m_btnClose = new QPushButton(tr("Cancel"));
    QHBoxLayout *btnLayout = new QHBoxLayout(this);
    btnLayout->addStretch();
    btnLayout->addWidget(m_btnOk);
    btnLayout->addWidget(m_btnClose);

    mainLayout->addStretch();
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    connect(m_btnOk, SIGNAL(clicked()),this, SLOT(onClickedBtnOk()));
    connect(m_btnClose, SIGNAL(clicked()),this, SLOT(onClickedBtnClose()));
}


// public slots:-------------------------------------
/*************************************************
Function Name: onClickedBtnClose()
Description:  click  close /cancel  button 
*************************************************/
void IMLittleWidget::onClickedBtnClose()
{
    close();
}

/*************************************************
Function Name: onClickedBtnClose()
Description:  click  close /cancel  button 
*************************************************/
void IMLittleWidget::setLabelsText(const QString & first,
                  const QString & second,
                  const QString & third)
{
    if (m_numOfLineEdit >= 1 && !first.isEmpty())
        m_labelFirst->setText(first);

    if (m_numOfLineEdit >= 2 && !second.isEmpty())
        m_labelSecond->setText(second);

    if (m_numOfLineEdit >= 3 && !third.isEmpty())
        m_labelThird->setText(third);
}

/*************************************************
Function Name: getInputInformation()
Description:  
*************************************************/
TempStrings IMLittleWidget::getInputInformation() const
{
    TempStrings temp;
    temp.m_one = m_leFirst->text();

    if(m_numOfLineEdit >= 2){
        temp.m_two = m_leSecond->text();
    }

    if(m_numOfLineEdit >= 3){
        temp.m_three = m_leThird->text();
    }

    return temp;
}

/*************************************************
Function Name: setPasswordStyle()
Description: 
*************************************************/
void IMLittleWidget::setPasswordStyle()
{
    m_leFirst->setEchoMode(QLineEdit::Password);

    if(m_numOfLineEdit >= 2){
        m_leSecond->setEchoMode(QLineEdit::Password);
    }

    if(m_numOfLineEdit >= 3){
        m_leThird->setEchoMode(QLineEdit::Password);
    }
}

/*************************************************
Function Name: setAllEnabled()
Description: 
*************************************************/
void IMLittleWidget::setAllEnabled(bool enable)
{
    m_leFirst->setEnabled(enable);
    if(m_numOfLineEdit >= 2)
        m_leSecond->setEnabled(enable);
    if(m_numOfLineEdit >= 3)
        m_leThird->setEnabled(enable);
    m_btnOk->setEnabled(enable);
    m_btnClose->setEnabled(enable);
}
