#ifndef INREPOADDNAME_H
#define INREPOADDNAME_H

#include "MethodClass/chinesesort.h"
#include <QApplication>
#include <QComboBox>
#include <QDebug>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVBoxLayout>

class InRepoAddName : public QDialog
{
    Q_OBJECT
public:
    explicit InRepoAddName(QWidget *parent = nullptr,
                           QSqlDatabase *db = nullptr,
                           QSqlQuery *query = nullptr,
                           QString *category = nullptr);
    ~InRepoAddName();
signals:
    // mainwindow下的done, outrepo, inrepo, repo, repoinfo, inrepoinfo表级信号
    void RefreshDoneTableSignal();
    void RefreshOutRepoTableSignal();
    void RefreshInRepoTableSignal();
    void RefreshRepoTableSignal();
    void RefreshRepoInfoTableSignal();
    void RefreshInRepoInfoTableSignal();
    // mainwindow下的done, outrepo, inrepo, repo, repoinfo, inrepoinfo表级信号
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
private slots:
    void SaveName();
private:
    QLabel *label0;
    QLineEdit *lineEdit0;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *prompt;
    QPushButton *okButton;

    QVBoxLayout *mainLayout;
    QHBoxLayout *inputZone0;
    QHBoxLayout *inputZone;

    QSqlDatabase *db;
    QSqlQuery *query;
    QStringList *sqlgroup;
    QString *category;
};

#endif // INREPOADDNAME_H
