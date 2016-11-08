/*********************************************
File Name: IMInputTextEdit.h
Author: jet.F.R
Date: 2014.3.26
Description:
Changes:
********************************************/

#ifndef IMINPUTTEXTEDIT_H
#define IMINPUTTEXTEDIT_H

#include <QTextEdit>

class IMInputTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    IMInputTextEdit(QWidget *parent=0);
    ~IMInputTextEdit();

protected:
    // reload keyPressEvent
    void keyPressEvent(QKeyEvent *event);

signals:
    void sendMessage();
};

#endif // IMINPUTTEXTEDIT_H
