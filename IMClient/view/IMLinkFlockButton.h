#ifndef IMLINKFLOCKBUTTON_H
#define IMLINKFLOCKBUTTON_H

#include "IMLinkButton.h"
#include "model/IMConstant.h"

class QLabel;
class IMFlockButton;

class IMLinkFlockButton : public IMLinkButton
{
    Q_OBJECT
public:
    IMLinkFlockButton(IMFlockButton * btn, QWidget *parent = 0);
    ~IMLinkFlockButton();

    void setButtonStatus();

signals:
    
public slots:
    void onDoubleClickButton();
    void ignoreMessage();

private:
    IMFlockButton *m_flockBtn;
    FlockInformation m_info;

};

#endif // IMLINKFLOCKBUTTON_H
