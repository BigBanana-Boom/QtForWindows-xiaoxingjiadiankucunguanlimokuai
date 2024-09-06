#ifndef INREPO_H
#define INREPO_H

#include "CustomButton/gradientbutton.h"
#include "CustomButton/arrowbutton.h"
#include "InRepoAdd/inrepoadd.h"
#include "InRepoChange/inrepochange.h"
#include "InRepoRemove/inreporemove.h"
#include "InRepoSearch/inreposearch.h"
#include "xlsxdocument.h"
#include <QCollator>
#include <QCoreApplication>
#include <QDebug>
#include <QFileDialog>
#include <QFrame>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
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

class InRepo : public QWidget
{
    Q_OBJECT
public:
    explicit InRepo(QWidget *parent = nullptr,
                    QSqlDatabase *db = nullptr,
                    QSqlQuery *query = nullptr);
    ~InRepo();
private slots:
    void RefreshInRepoTableSlot();
    void RefreshInRepoTableSlot_DifferentSelect();
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
    QDateTime *IRsearchingdatetime;
    QDateTime *IRsearchingdatetime02;
    QString *IRsearchingrepo;
    QString *IRsearchingproductcategory;
    QString *IRsearchingproductname;
    // 成员变量*****************************************************************************

    // 内容布局*****************************************************************************
    QHBoxLayout *fivebutton;
    QStackedWidget *stackedWidget;
    InRepoAdd *inRepoAddWindow;
    InRepoRemove *inRepoRemoveWindow;
    InRepoChange *inRepoChangeWindow;
    InRepoSearch *inRepoSearchWindow;
    // 内容布局*****************************************************************************

    // 增删改查导***************************************************************************
    GradientButton *inrepoadd;
    GradientButton *inreporemove;
    GradientButton *inrepochange;
    GradientButton *inreposearch;
    GradientButton *inrepoexport;
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

#endif // INREPO_H
