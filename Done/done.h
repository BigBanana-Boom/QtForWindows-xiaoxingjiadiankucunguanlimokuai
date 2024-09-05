#ifndef DONE_H
#define DONE_H

#include "CustomButton/normalgradientbutton.h"
#include "CustomButton/dropdowngradientbutton.h"
#include "DoneAdd/doneadd.h"
#include "DoneChange/donechange.h"
#include "DoneRemove/doneremove.h"
#include "DoneSearch/donesearch.h"
#include "xlsxdocument.h"
#include <QAction>
#include <QCollator>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QFileDialog>
#include <QFrame>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStackedWidget>
#include <QStringList>
#include <QTableWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>
#include <QWidgetAction>

class Done : public QWidget
{
    Q_OBJECT
public:
    explicit Done(QWidget *parent = nullptr,
                  QSqlDatabase *db = nullptr,
                  QSqlQuery *query = nullptr);
    ~Done();
private slots:
    void RefreshDoneTableSlot();
    void RefreshDoneTableSlot_DifferentSelect();
    void SaveFile();
    void toggleTableVisibility();
    void selectColumnOnHeaderClickForTable01(int column);
    void selectColumnOnHeaderClickForTable02(int column);
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
    QVBoxLayout *contentLayout;
    QVBoxLayout *tableLayout;
    // 布局*********************************************************************************

    // 标题布局*****************************************************************************
    QLabel *qlabel01;
    // 标题布局*****************************************************************************

    // 数据库连接***************************************************************************
    QSqlDatabase *db;
    QSqlQuery *query;
    QStringList *sqlgroup;
    QString *whereclause;
    QString *whereclausesql;
    // 数据库连接***************************************************************************

    // 成员变量*****************************************************************************
    QDateTime *Dsearchingdatetime;
    QDateTime *Dsearchingdatetime02;
    QString *Dsearchingproductcategory;
    QString *Dsearchingproductname;
    // 成员变量*****************************************************************************

    // 内容布局*****************************************************************************
    QHBoxLayout *fivebutton;
    QStackedWidget *stackedWidget;
    DoneAdd *doneAddWindow;
    DoneRemove *doneRemoveWindow;
    DoneChange *doneChangeWindow;
    DoneSearch *doneSearchWindow;
    // 内容布局*****************************************************************************

    // 增删改查导***************************************************************************
    NormalGradientButton *doneadd;
    NormalGradientButton *doneremove;
    NormalGradientButton *donechange;
    NormalGradientButton *donesearch;
    NormalGradientButton *doneexport;
    // 增删改查导***************************************************************************

    // 总布局*******************************************************************************
    QFrame *line;
    // 总布局*******************************************************************************

    // 表格*********************************************************************************
    QHeaderView *headerView01_row;
    QHeaderView *headerView01_column;
    QTableWidget *tableWidget01;
    DropDownGradientButton *dropdowngradientbutton;
    QHeaderView *headerView02_row;
    QHeaderView *headerView02_column;
    QTableWidget *tableWidget02;
    // 表格*********************************************************************************
};

#endif // DONE_H
