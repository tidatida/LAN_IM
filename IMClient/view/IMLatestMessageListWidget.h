#ifndef IMLATESTMESSAGELISTWIDGET_H
#define IMLATESTMESSAGELISTWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QScrollArea;
class QMenu;
class IMMainWidget;

class IMLatestMessageListWidget : public QWidget
{
    Q_OBJECT
public:
    IMLatestMessageListWidget(IMMainWidget *mainWidget, QWidget *parent = 0);
    void addItem(QWidget *item);
    void removeItem(QWidget *item);
    int size();
    //create  right button  menu 
    void creatMenu();

signals:
    void timerStatus(bool isOpen);

public slots:
    void showMenu();
protected:
    void mousePressEvent(QMouseEvent *e);

private:
    QVBoxLayout *m_layout;
    QWidget *m_contentsWidget;
    QScrollArea *m_scrollArea;

    // right button  menu 
    QMenu *m_menu;

    IMMainWidget *m_mainWidget;

    int m_mesCounter;
};

#endif // IMLATESTMESSAGELISTWIDGET_H
