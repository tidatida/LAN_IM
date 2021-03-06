/*********************************************
File Name: IMServerWindow.cpp
Author: jet.F.R
Date: 2014.3.10
Description: server mainframe class
Changes:
********************************************/

#include "IMServerWindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include "control/IMServerMessageCtrl.h"
#include <QListView>

IMServerWindow::IMServerWindow(QWidget *parent)
    : QWidget(parent)
{
    m_serverCtrl = new IMServerMessageCtrl(this);
    m_serverCtrl->runServer();

    QHBoxLayout *viewLayout = new QHBoxLayout;
    viewLayout->addWidget(m_serverCtrl->getIDListView());
    viewLayout->addWidget(m_serverCtrl->getAddressListView());

    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *labelTitle = new QLabel(tr("connection server user  account   table  :"));
    layout->addWidget(labelTitle);
    layout->addLayout(viewLayout);

    setLayout(layout);
}

IMServerWindow::~IMServerWindow()
{
    if (m_serverCtrl != NULL)
    {
        delete m_serverCtrl;
    }
}
