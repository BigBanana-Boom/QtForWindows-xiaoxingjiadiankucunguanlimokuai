#include "eventfilterformainwindow.h"

// 构造函数****************************************************************************
EventFilterForMainWindow::EventFilterForMainWindow(QObject *parent)
    : QObject(parent)
{}
// 构造函数****************************************************************************
// 析构函数****************************************************************************
EventFilterForMainWindow::~EventFilterForMainWindow() {}
// 析构函数****************************************************************************
// 事件过滤器**************************************************************************
bool EventFilterForMainWindow::eventFilter(
        QObject *watched, QEvent *event)
{
    if (watched == parent() &&
            (event->type() == QEvent::Resize)) {
        qDebug() << event->type();
    }
    return QObject::eventFilter(watched, event);
}
// 事件过滤器**************************************************************************
