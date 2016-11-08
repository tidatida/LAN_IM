#ifndef IMLINKDISCUSSIONBUTTON_H
#define IMLINKDISCUSSIONBUTTON_H

#include "IMLinkButton.h"
#include "model/IMConstant.h"

class QLabel;
class IMDiscussionButton;

class IMLinkDiscussionButton : public IMLinkButton
{
    Q_OBJECT
public:
    IMLinkDiscussionButton(IMDiscussionButton * btn, QWidget *parent = 0);
    ~IMLinkDiscussionButton();

    void setButtonStatus();

signals:
    
public slots:
    void onDoubleClickButton();
    void ignoreMessage();

private:
    IMDiscussionButton *m_discussionBtn;
    DiscussionInformation m_info;
    
};

#endif // IMLINKDISCUSSIONBUTTON_H
