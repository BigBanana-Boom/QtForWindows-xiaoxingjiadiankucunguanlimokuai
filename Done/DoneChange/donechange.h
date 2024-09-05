#ifndef DONECHANGE_H
#define DONECHANGE_H

#include "../MethodClass/refreshrepotableid.h"
#include "donechangedialog.h"
#include "../CustomWidget/searchdialog.h"
#include "../CustomWidget/simpledialog.h"
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
#include <QVBoxLayout>
#include <QWidget>

class DoneChange : public QWidget
{
    Q_OBJECT
public:
    explicit DoneChange(QWidget *parent = nullptr,
                        QSqlDatabase *db = nullptr,
                        QSqlQuery *query = nullptr);
    ~DoneChange();

    // public，因为要被外类给修改*******************************************************
    int *returnid;
    // public，因为要被外类给修改*******************************************************
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
    void RefreshDoneChangeSlot();
private slots:
    void showMessage();
    void onChangedIDChanged(const QString &text);
    void onChangedValueChanged(int value);
    void onSearchButtonClicked();
private:
    // 字体*********************************************************************************
    QFont *qfont01;
    QFont *qfont02;
    QFont *qfont03;
    // 字体*********************************************************************************

    // 布局*********************************************************************************
    QVBoxLayout *mainLayout;
    QHBoxLayout *zone;
    QVBoxLayout *leftzone;
    QVBoxLayout *rightzone;
    QHBoxLayout *leftzonerow1;
    QHBoxLayout *leftzonerow2;
    QHBoxLayout *leftzonerow3;
    QHBoxLayout *leftzonerow4;
    QHBoxLayout *rightzonerow1;
    QHBoxLayout *rightzonerow2;
    QHBoxLayout *rightzonerow3;
    QTableWidget *tableWidget01;
    // 布局*********************************************************************************

    // 标签*********************************************************************************
    QLabel *qlabel01;
    QLabel *qlabel02;
    QLabel *qlabel03;
    QLabel *qlabel04;
    QLabel *qlabel05;
    QLabel *qlabel06;
    // 标签*********************************************************************************

    // 左区域*******************************************************************************
    QComboBox *qcombobox01;
    QPushButton *searchbutton;
    QLineEdit *qreadonlylineedit01;
    QLineEdit *qreadonlylineedit02;
    // 左区域*******************************************************************************

    // 右区域*******************************************************************************
    QLineEdit *qreadonlylineedit03;
    QLineEdit *qreadonlylineedit04;
    QSpinBox *qspinbox01;
    QPushButton *yeschange;
    // 右区域*******************************************************************************

    // 数据库连接***************************************************************************
    QSqlDatabase *db;
    QSqlQuery *query;
    QStringList *sqlgroup;
    // 数据库连接***************************************************************************

    // 函数*********************************************************************************
    void SubmitChangeOperation();
    void ProcessTable();
    // 函数*********************************************************************************

    // 自定义部件***************************************************************************
    DoneChangeDialog *donechangedialog;
    SimpleDialog *simpledialog;
    SearchDialog *searchdialog;
    // 自定义部件***************************************************************************

    // 成员变量*****************************************************************************
    int *currentID;
    QDateTime *currentdatetime;
    QString *currentproductcategory;
    QString *currentproductname;
    int *currentproductnumber;
    int *changedproductnumber;
    // 成员变量*****************************************************************************
};

#endif // DONECHANGE_H
