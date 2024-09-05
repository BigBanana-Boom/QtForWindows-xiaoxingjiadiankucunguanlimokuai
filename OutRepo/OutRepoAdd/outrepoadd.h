#ifndef OUTREPOADD_H
#define OUTREPOADD_H

#include "../MethodClass/chinesesort.h"
#include "../MethodClass/refreshrepotableid.h"
#include "outrepoadddialog.h"
#include "../CustomWidget/searchdialog.h"
#include "../CustomWidget/simpledialog.h"
#include <QCollator>
#include <QComboBox>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

class OutRepoAdd : public QWidget
{
    Q_OBJECT
public:
    explicit OutRepoAdd(QWidget *parent = nullptr,
                        QSqlDatabase *db = nullptr,
                        QSqlQuery *query = nullptr);
    ~OutRepoAdd();

    // public，因为要被外类修改**********************************************************
    int *returnid;
    // public，因为要被外类修改**********************************************************
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
    void RefreshOutRepoAddSlot();
private slots:
    void onCurrentCategoryChanged(const QString &text);
    void onCurrentNameChanged(const QString &text);
    void onCurrentRepoChanged(const QString &text);
    void onCurrentValueChanged(int value);
    void showMessage();
    void onSearchButtonClicked();
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
    QHBoxLayout *leftzonerow1;
    QHBoxLayout *leftzonerow2;
    QHBoxLayout *leftzonerow3;
    QVBoxLayout *rightzone;
    QHBoxLayout *rightzonerow1;
    QHBoxLayout *rightzonerow2;
    QTableWidget *tableWidget01;
    // 总布局*******************************************************************************

    // 标签*********************************************************************************
    QLabel *qlabel01;
    QLabel *qlabel02;
    QLabel *qlabel03;
    QLabel *qlabel04;
    // 标签*********************************************************************************

    // 左区域*******************************************************************************
    QComboBox *qcombobox01;
    QPushButton *searchbutton;
    QComboBox *qcombobox02;
    QComboBox *qcombobox03;
    // 左区域*******************************************************************************

    // 右区域*******************************************************************************
    QSpinBox *qspinbox01;
    QPushButton *qpushbutton01;
    // 右区域*******************************************************************************

    // 数据库连接***************************************************************************
    QSqlDatabase *db;
    QSqlQuery *query;
    QStringList *sqlgroup;
    // 数据库连接***************************************************************************

    // 函数*********************************************************************************
    void SubmitAddOperation();
    void ProcessTable();
    // 函数*********************************************************************************

    // 自定义部件***************************************************************************
    OutRepoAddDialog *outrepoadddialog;
    SimpleDialog *simpledialog;
    SearchDialog *searchdialog;
    // 自定义部件***************************************************************************

    // 成员变量*****************************************************************************
    QString *currentdatetime;
    QString *currentproductcategory;
    QString *currentproductname;
    QString *currentrepo;
    int *currentproductnumber;
    // 成员变量*****************************************************************************
};

#endif // OUTREPOADD_H
