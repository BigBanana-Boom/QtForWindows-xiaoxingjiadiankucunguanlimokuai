#ifndef OUTREPO_H
#define OUTREPO_H

#include "../CustomButton/gradientbutton.h"
#include "../CustomButton/arrowbutton.h"
#include "OutRepoAdd/outrepoadd.h"
#include "OutRepoChange/outrepochange.h"
#include "OutRepoRemove/outreporemove.h"
#include "OutRepoSearch/outreposearch.h"
#include "xlsxdocument.h"
#include <QAction>
#include <QCollator>
#include <QCoreApplication>
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

class OutRepo : public QWidget
{
    Q_OBJECT
public:
    explicit OutRepo(QWidget *parent = nullptr,
                     QSqlDatabase *db = nullptr,
                     QSqlQuery *query = nullptr);
    ~OutRepo();
private slots:
    void RefreshOutRepoTableSlot();
    void RefreshOutRepoTableSlot_DifferentSelect();
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

    // 标题*********************************************************************************
    QLabel *qlabel01;
    // 标题*********************************************************************************

    // 数据库连接***************************************************************************
    QSqlDatabase *db;
    QSqlQuery *query;
    QStringList *sqlgroup;
    QString *whereclause;
    QString *whereclausesql;
    // 数据库连接***************************************************************************

    // 成员变量*****************************************************************************
    QDateTime *ORsearchingdatetime;
    QDateTime *ORsearchingdatetime02;
    QString *ORsearchingrepo;
    QString *ORsearchingproductcategory;
    QString *ORsearchingproductname;
    // 成员变量*****************************************************************************

    // 内容布局*****************************************************************************
    QHBoxLayout *fivebutton;
    QStackedWidget *stackedWidget;
    OutRepoAdd *outRepoAddWindow;
    OutRepoRemove *outRepoRemoveWindow;
    OutRepoChange *outRepoChangeWindow;
    OutRepoSearch *outRepoSearchWindow;
    // 内容布局*****************************************************************************

    // 增删改查导***************************************************************************
    GradientButton *outrepoadd;
    GradientButton *outreporemove;
    GradientButton *outrepochange;
    GradientButton *outreposearch;
    GradientButton *outrepoexport;
    // 增删改查导***************************************************************************

    // 总布局*******************************************************************************
    QFrame *line;
    // 总布局*******************************************************************************

    // 表格*********************************************************************************
    QHeaderView *headerView01_row;
    QHeaderView *headerView01_column;
    QTableWidget *tableWidget01;
    ArrowButton *dropdowngradientbutton;
    QHeaderView *headerView02_row;
    QHeaderView *headerView02_column;
    QTableWidget *tableWidget02;
    // 表格*********************************************************************************
};

#endif // OUTREPO_H
