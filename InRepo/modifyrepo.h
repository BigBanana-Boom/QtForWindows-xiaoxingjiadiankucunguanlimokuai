#ifndef MODIFYREPO_H
#define MODIFYREPO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSqlDatabase>
#include <QTableWidget>

class ModifyRepo : public QWidget
{
    Q_OBJECT
public:
    explicit ModifyRepo(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
private:
    // 布局等硬定义
    QVBoxLayout *mainLayout;
    QHBoxLayout *titleLayout;
    QHBoxLayout *contentLayout;
    // 布局等硬定义

    // 标题布局
    QLabel *qlabel01;
    // 标题布局
};

#endif // MODIFYREPO_H
