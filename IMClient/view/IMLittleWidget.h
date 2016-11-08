#ifndef IMLITTLEWIDGET_H
#define IMLITTLEWIDGET_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
struct TempStrings;

class IMLittleWidget : public QWidget
{
    Q_OBJECT
public:
    IMLittleWidget(int num, QWidget *parent = 0);
    virtual ~IMLittleWidget() = 0;

    void setLabelsText(const QString & first = "",
                      const QString & second = "",
                      const QString & third = "");

    TempStrings getInputInformation() const;

    void setPasswordStyle();
    void setAllEnabled(bool enable);
signals:
    
public slots:
    virtual void onClickedBtnOk() = 0;
    void onClickedBtnClose();
private:
    int m_numOfLineEdit; 
    QLabel *m_labelFirst;
    QLabel *m_labelSecond;
    QLabel *m_labelThird;
    QLineEdit *m_leFirst;
    QLineEdit *m_leSecond;
    QLineEdit *m_leThird;
    QPushButton *m_btnOk;
    QPushButton *m_btnClose;
};

#endif // IMLITTLEWIDGET_H
