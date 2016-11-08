/*********************************************
File Name: IMInputTextEdit.cpp
Author: jet.F.R
Date: 2014.3.26
Description:
Changes:
********************************************/

#include "IMInputTextEdit.h"
#include <QKeyEvent>

IMInputTextEdit::IMInputTextEdit(QWidget *parent) :
    QTextEdit(parent)
{

}

IMInputTextEdit::~IMInputTextEdit()
{

}


void IMInputTextEdit::keyPressEvent(QKeyEvent *event)
{
    bool isSend = (Qt::Key_Return==event->key() || Qt::Key_Enter==event->key())
        && (event->modifiers() & Qt::ControlModifier);

    if(isSend){
        emit sendMessage();
    }else{
        QTextEdit::keyPressEvent(event);
    }

}
