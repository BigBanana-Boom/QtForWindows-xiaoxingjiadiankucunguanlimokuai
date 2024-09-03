#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "qframelessmainwindow.h"
#include "CustomButton/gradientbutton.h"
#include "CustomButton/gradientbuttonwithsimpleicon.h"
#include "Done/done.h"
#include "InRepo/inrepo.h"
#include "ModifyRepo/modifyrepo.h"
#include "OutRepo/outrepo.h"
#include "Repo/repo.h"
#include "refreshrepotableid.h"

class MainWindow : public QFramelessMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(bool resizeEnable = true, bool shadowBorder = true,
               bool winNativeEvent = true, QWidget *parent = 0);
    ~MainWindow();
    // 数据库与数据库连接****************************************************************
    QSqlDatabase *db;
    QSqlQuery *query;
    // 数据库与数据库连接****************************************************************
private slots:
    void onMinimizedButtonClicked();
    void onMaximizedButtonClicked();
    void onCloseButtonClicked();
    void slotMaximizedChanged(bool bMax);
private:
    // 字体********************************************************************************
    QFont *qfont01;
    QFont *qfont02;
    // 字体********************************************************************************

    // 中央器件及布局*********************************************************************
    QWidget *centralWidget;
    QVBoxLayout *centralWidgetVLayout;
    // 中央器件及布局*********************************************************************

    // 标题器件及内容*********************************************************************
    QWidget *titleWidget;
    QHBoxLayout *titleWidgetHLayout;
    QLabel *labelIcon;
    QLabel *labelTitle;
    // 右上方小大关按钮布局**************************************************************
    QVBoxLayout *minimizedVLayout;
    GradientButton *minimizedbutton;
    QVBoxLayout *maximizedVLayout;
    GradientButton *maximizedbutton;
    QVBoxLayout *closeVLayout;
    GradientButtonWithSimpleIcon *closebutton;
    // 右上方小大关按钮布局**************************************************************
    // 标题器件及内容*********************************************************************

    // 标题器件与内容器件之间的分割线****************************************************
    QFrame *line;
    // 标题器件与内容器件之间的分割线****************************************************

    // 内容器件及内容*********************************************************************
    QWidget *contentWidget;
    QHBoxLayout *contentWidgetHLayout;
    QVBoxLayout *leftContentLayout;
    QVBoxLayout *rightContentLayout;
    // 左内容布局**************************************************************************
    GradientButton *gradientbutton01;
    GradientButton *gradientbutton02;
    GradientButton *gradientbutton03;
    GradientButton *gradientbutton04;
    GradientButton *gradientbutton05;
    // 左内容布局**************************************************************************
    // 右内容布局**************************************************************************
    QStackedWidget *stackedWidget;
    Done *doneWindow;
    OutRepo *outRepoWindow;
    InRepo *inRepoWindow;
    Repo *repoWindow;
    ModifyRepo *modifyRepoWindow;
    // 右内容布局**************************************************************************
    // 内容器件及内容**********************************************************************

    // 函数******************************************************************************
    void InitDatabase();
    // 函数******************************************************************************
};
#endif // MAINWINDOW_H

/* 本不应将内容器件中的详细内容放到主窗口类中来写
 * 而是应该将内容器件中的详细内容放到一个新的器件类中写
 * 也不应该把标题器件中的详细内容放到主窗口类中来写
 * 而是应该将标题器件中的详细内容放到一个新的器件类中写
 * 但是放到这里来写，也无伤大雅
 * 所以最终依然把内容器件中的详细内容放到主窗口类中来写
 * 把标题器件中的详细内容放到主窗口类中来写
 */

/* 数据库与数据库连接设置为了public类型
 * 这样写是因为，现在用的是轻量级的sqlite数据库
 * 为了便于管理，减少差错
 * 选择在从程序开始，到程序结束为止，只使用一个数据库与数据库连接
 * 并且sqlite数据库足够容纳待存放的数据
 */
