#ifndef IMFLOCKLISTWIDGET_H
#define IMFLOCKLISTWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QScrollArea;
class QMenu;
class IMMainWidget;


class IMFlockListWidget : public QWidget
{
    Q_OBJECT
public:
    IMFlockListWidget(IMMainWidget *mainWidget, QWidget *parent = 0);
    void addItem(QWidget *item);
    void removeItem(QWidget *item);

    //create  right button  menu 
    void creatMenu();

signals:
    
public slots:
    void showMenu();

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    QVBoxLayout *m_layout;
    QWidget *m_contentsWidget;
    QScrollArea *m_flocksScrollArea;

    // right button  menu 
    QMenu *m_menu;

    IMMainWidget *m_mainWidget;
};

#endif // IMFLOCKLISTWIDGET_H
