#ifndef REPOADJUST_H
#define REPOADJUST_H

#include "refreshrepotableid.h"
#include "chinesesort.h"
#include "CustomWidget/repoadjustdialog.h"
#include "CustomWidget/simpledialog.h"
#include <QCollator>
#include <QComboBox>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QTableWidget>
#include <QTextStream>
#include <QVBoxLayout>
#include <QWidget>

class RepoAdjust : public QWidget
{
    Q_OBJECT
public:
    explicit RepoAdjust(QWidget *parent = nullptr,
                        QSqlDatabase *db = nullptr,
                        QSqlQuery *query = nullptr);
    ~RepoAdjust();
signals:
    // mainwindow下的done, outrepo, inrepo, repo表级信号
    void RefreshDoneTableSignal();
    void RefreshOutRepoTableSignal();
    void RefreshInRepoTableSignal();
    void RefreshRepoTableSignal();
    void RefreshRepoInfoTableSignal();
    void RefreshInRepoInfoTableSignal();
    // mainwindow下的done, outrepo, inrepo, repo表级信号
    // done下的doneadd, doneremove, donechange, donesearch窗口信号
    void RefreshDoneAddSignal();
    void RefreshDoneRemoveSignal();
    void RefreshDoneChangeSignal();
    void RefreshDoneSearchSignal();
    // done下的doneadd, doneremove, donechange, donesearch窗口信号
    // outrepo下的outrepoadd, outreporemove, outrepochange, outreposearch窗口信号
    void RefreshOutRepoAddSignal();
    void RefreshOutRepoRemoveSignal();
    void RefreshOutRepoChangeSignal();
    void RefreshOutRepoSearchSignal();
    // outrepo下的outrepoadd, outreporemove, outrepochange, outreposearch窗口信号
    // inrepo下的inrepoadd, inreporemove, inrepochange, inreposearch窗口信号
    void RefreshInRepoAddSignal();
    void RefreshInRepoRemoveSignal();
    void RefreshInRepoChangeSignal();
    void RefreshInRepoSearchSignal();
    // inrepo下的inrepoadd, inreporemove, inrepochange, inreposearch窗口信号
    // repo下的repoadd, reporemove, repochange, reposearch窗口信号
    void RefreshRepoAddSignal();
    void RefreshRepoRemoveSignal();
    void RefreshRepoChangeSignal();
    void RefreshRepoSearchSignal();
    // repo下的repoadd, reporemove, repochange, reposearch窗口信号
public slots:
    void RefreshRepoAdjustSlot();
private slots:
    void showMessage();
    void onCurrentCategoryChanged(const QString &text);
    void onCurrentNameChanged(const QString &text);
    void onOriginalRepoChanged(const QString &text);
    void onLaterRepoChanged(const QString &text);
    void onCurrentValueChanged(int value);
    void selectColumnOnHeaderClick(int column);
private:
    // 字体*********************************************************************************
    QFont *qfont01;
    QFont *qfont02;
    QFont *qfont03;
    // 字体*********************************************************************************

    // 总布局*******************************************************************************
    QVBoxLayout *mainLayout;
    QHBoxLayout *zone;
    QVBoxLayout *leftzone;
    QVBoxLayout *rightzone;
    QHBoxLayout *leftzonerow1;
    QHBoxLayout *leftzonerow2;
    QHBoxLayout *leftzonerow3;
    QHBoxLayout *rightzonerow1;
    QHBoxLayout *rightzonerow2;
    QHBoxLayout *rightzonerow3;
    QHeaderView *headerView01_row;
    QHeaderView *headerView01_column;
    QTableWidget *tableWidget01;
    // 总布局*******************************************************************************

    // 标签*********************************************************************************
    QLabel *qlabel01;
    QLabel *qlabel02;
    QLabel *qlabel03;
    QLabel *qlabel04;
    QLabel *qlabel05;
    // 标签*********************************************************************************

    // 左区域*******************************************************************************
    QComboBox *qcombobox01;
    QComboBox *qcombobox02;
    QComboBox *qcombobox03;
    // 左区域*******************************************************************************

    // 右区域*******************************************************************************
    QComboBox *qcombobox04;
    QSpinBox *qspinbox01;
    QPushButton *yeschange;
    // 右区域*******************************************************************************

    // 数据库连接***************************************************************************
    QSqlDatabase *db;
    QSqlQuery *query;
    QStringList *sqlgroup;
    // 数据库连接***************************************************************************

    // 函数*********************************************************************************
    void SubmitAdjustOperation();
    void ProcessTable();
    // 函数*********************************************************************************

    // 自定义部件***************************************************************************
    RepoAdjustDialog *repoadjustdialog;
    SimpleDialog *simpledialog;
    // 自定义部件***************************************************************************

    // 成员变量*****************************************************************************
    QString *currentdatetime;
    QString *currentproductcategory;
    QString *currentproductname;
    QString *originalrepo;
    QString *laterrepo;
    int *currentproductnumber;
    // 成员变量*****************************************************************************
};

#endif // REPOADJUST_H
