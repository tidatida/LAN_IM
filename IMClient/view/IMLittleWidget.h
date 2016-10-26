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

    // 设置各编辑框,s 标题栏
    void setLabelsText(const QString & first = "",
                      const QString & second = "",
                      const QString & third = "");
    //  get user  input ,s 信息
    TempStrings getInputInformation() const;
    // 将user  input ,s 信息set to  passwd风格
    void setPasswordStyle();
    // set all  input 框设置可用属性
    void setAllEnabled(bool enable);
signals:
    
public slots:
    virtual void onClickedBtnOk() = 0;
    void onClickedBtnClose();
private:
    int m_numOfLineEdit; //  input 栏,s 个数
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
