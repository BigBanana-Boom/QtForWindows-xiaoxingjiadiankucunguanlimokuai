#ifndef MODIFYREPO_H
#define MODIFYREPO_H

#include "AddInRepoInfo/addinrepoinfo.h"
#include "AddRepo/addrepo.h"
#include "AddRepoInfo/addrepoinfo.h"
#include "ClearInRepo/clearinrepo.h"
#include "ClearOutRepo/clearoutrepo.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSqlDatabase>
#include <QTableWidget>

class ModifyRepo : public QWidget
{
    Q_OBJECT
public:
    explicit ModifyRepo(QWidget *parent = nullptr,
                        QSqlDatabase *db = nullptr,
                        QSqlQuery *query = nullptr);
    ~ModifyRepo();
private:
    // 字体*********************************************************************************
    QFont *qfont01;
    QFont *qfont02;
    QFont *qfont03;
    QFont *qfont04;
    // 字体*********************************************************************************

    // 布局*********************************************************************************
    QVBoxLayout *mainLayout;
    QHBoxLayout *titleLayout;
    QGridLayout *contentLayout;
    // 布局*********************************************************************************

    // 标题*********************************************************************************
    QLabel *qlabel01;
    // 标题*********************************************************************************

    // 数据库*******************************************************************************
    QSqlDatabase *db;
    QSqlQuery *query;
    QStringList *sqlgroup;
    QString *whereclause;
    QString *whereclausesql;
    // 数据库*******************************************************************************

    // 内容布局*****************************************************************************
    QPushButton *qpushbutton01;
    QPushButton *qpushbutton02;
    QPushButton *qpushbutton03;
    QPushButton *qpushbutton04;
    QPushButton *qpushbutton05;
    QPushButton *qpushbutton06;
    QPushButton *qpushbutton07;
    QPushButton *qpushbutton08;
    QPushButton *qpushbutton09;
    // 内容布局*****************************************************************************

    // 总布局*******************************************************************************
    QFrame *line;
    // 总布局*******************************************************************************
};

#endif // MODIFYREPO_H
