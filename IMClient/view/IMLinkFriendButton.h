#ifndef IMLINKFRIENDBUTTON_H
#define IMLINKFRIENDBUTTON_H

#include <QPushButton>
#include "IMLinkButton.h"
#include "model/IMConstant.h"

class QLabel;
class IMFriendButton;

class IMLinkFriendButton : public IMLinkButton
{
    Q_OBJECT
public:
    IMLinkFriendButton(IMFriendButton * btn, QWidget *parent = 0);
    ~IMLinkFriendButton();


    void setButtonStatus();

public slots:
    void onDoubleClickButton();
    void ignoreMessage();


private:
    IMFriendButton * m_friendBtn;
    FriendInformation m_info;

};

#endif // IMLinkFriendButton_H
