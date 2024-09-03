#ifndef EVENTFILTERFORMAINWINDOW_H
#define EVENTFILTERFORMAINWINDOW_H

#include <QObject>
#include <QApplication>
#include <QMainWindow>
#include <QToolButton>
#include <QDebug>

class EventFilterForMainWindow : public QObject
{
    Q_OBJECT
public:
    explicit EventFilterForMainWindow(QObject *parent = nullptr);
    ~EventFilterForMainWindow();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // EVENTFILTERFORMAINWINDOW_H
