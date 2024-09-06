#ifndef REPO_H
#define REPO_H

#include "../CustomButton/gradientbutton.h"
#include "../CustomButton/arrowbutton.h"
#include "RepoModify/repomodify.h"
#include "RepoAdjust/repoadjust.h"
#include "RepoChange/repochange.h"
#include "RepoSearch/reposearch.h"
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

class Repo : public QWidget
{
    Q_OBJECT
public:
    explicit Repo(QWidget *parent = nullptr,
                  QSqlDatabase *db = nullptr,
                  QSqlQuery *query = nullptr);
    ~Repo();
public slots:
    void RefreshRepoTableSlot();
private slots:
    void RefreshRepoTableSlot_DifferentSelect();
    void SaveFile();
    void toggleTableVisibility();
    void onSortIndicatorChanged(int column, Qt::SortOrder order);
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

    // 数据库*******************************************************************************
    QSqlDatabase *db;
    QSqlQuery *query;
    QStringList *sqlgroup;
    QString *whereclause;
    QString *whereclausesql;
    // 数据库*******************************************************************************

    // 成员变量*****************************************************************************
    QString *Rsearchingrepo;
    QString *Rsearchingproductcategory;
    QString *Rsearchingproductname;
    // 成员变量*****************************************************************************

    // 内容布局*****************************************************************************
    QHBoxLayout *fivebutton;
    QStackedWidget *stackedWidget;
    RepoModify *repoModifyWindow;
    RepoAdjust *repoAdjustWindow;
    RepoChange *repoChangeWindow;
    RepoSearch *repoSearchWindow;
    // 内容布局*****************************************************************************

    // 五个按钮*****************************************************************************
    GradientButton *repomodify;
    GradientButton *repoadjust;
    GradientButton *repochange;
    GradientButton *reposearch;
    GradientButton *repoexport;
    // 五个按钮*****************************************************************************

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

    // 函数*********************************************************************************
    void CustomSort(Qt::SortOrder order);
    int convertToInt(const QString text);
    // 函数*********************************************************************************
};

#endif // REPO_H
