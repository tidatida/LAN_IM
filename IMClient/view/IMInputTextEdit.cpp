/*********************************************
File Name: IMInputTextEdit.cpp
Author: jet.F.R
Date: 2014.3.26
Description:  input 编辑框
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
    //如果按下Ctrl+Enter，就发送信息，否则就按默认,s 方式来process   
    bool isSend = (Qt::Key_Return==event->key() || Qt::Key_Enter==event->key())
        && (event->modifiers() & Qt::ControlModifier);

    if(isSend)
        emit sendMessage();
    else
        QTextEdit::keyPressEvent(event);
}
