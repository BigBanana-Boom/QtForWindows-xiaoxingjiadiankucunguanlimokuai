#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include "qframelessdialog.h"
#include "CustomButton/dialoggradientbutton.h"
#include "CustomButton/exitgradientbutton.h"
#include <QDialog>
#include <QFile>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QTableWidget>
#include <QTextEdit>
#include <QVBoxLayout>

class SearchDialog : public QFramelessDialog
{
    Q_OBJECT
public:
    explicit SearchDialog(bool resizeEnable = true,
                          bool shadowBorder = true,
                          bool winNativeEvent = true,
                          QWidget *parent = nullptr,
                          QSqlDatabase *db = nullptr,
                          QSqlQuery *query = nullptr,
                          int *returnid = nullptr);
    ~SearchDialog();
    void setTableName(QString name);
    void setDialogTitle(QString title);
private slots:
    void onCloseButtonClicked();
    void RefreshDoneTable();
    void RefreshOutRepoTable();
    void RefreshInRepoTable();
    void RefreshRepoTable();
    void RefreshInRepoInfoTable();
private:
    // 字体********************************************************************************
    QFont *qfont01;
    QFont *qfont02;
    QFont *qfont03;
    QFont *qfont04;
    // 字体********************************************************************************

    // 总布局******************************************************************************
    QVBoxLayout *TotalVLayout;
    // 总布局******************************************************************************

    // 标题器件及内容*********************************************************************
    QWidget *titleWidget;
    QHBoxLayout *titleWidgetHLayout;
    QLabel *labelIcon;
    QLabel *labelTitle;
    // 右上方小大关按钮布局**************************************************************
    QVBoxLayout *closeVLayout;
    ExitGradientButton *closebutton;
    // 右上方小大关按钮布局**************************************************************
    // 标题器件及内容*********************************************************************

    // 标题器件与内容器件之间的分割线****************************************************
    QFrame *line;
    // 标题器件与内容器件之间的分割线****************************************************

    // 内容器件及内容**********************************************************************
    QWidget *contentWidget;
    QVBoxLayout *contentWidgetVLayout;
    // 标题*********************************************************************************
    QLabel *contentWidgetTitle;
    // 标题*********************************************************************************
    // 第一行******************************************************************************
    QLineEdit *qlineedit;
    DialogGradientButton *yesbutton;
    QHBoxLayout *rowOneHLayout;
    // 第一行******************************************************************************
    // 表格********************************************************************************
    QTableWidget *qtablewidget;
    // 表格********************************************************************************
    // 内容器件及内容**********************************************************************

    // 内容器件与按钮器件之间的分割线****************************************************
    QFrame *line2;
    // 内容器件与按钮器件之间的分割线****************************************************

    // 按钮器件及内容**********************************************************************
    QWidget *buttonWidget;
    QHBoxLayout *ButtonHLayout;
    DialogGradientButton *AcceptButton;
    // 按钮器件及内容**********************************************************************

    // 数据库连接***************************************************************************
    QSqlDatabase *db;
    QSqlQuery *query;
    QStringList *sqlgroup;
    QString *whereclause;
    QString *whereclausesql;
    // 数据库连接***************************************************************************

    // 一些细碎的变量***********************************************************************
    QString *tablename;
    // 一些细碎的变量***********************************************************************

    // 表格*********************************************************************************
    QHeaderView *headerView01_row;
    QHeaderView *headerView01_column;
    // 表格*********************************************************************************
};

#endif // SEARCHDIALOG_H
