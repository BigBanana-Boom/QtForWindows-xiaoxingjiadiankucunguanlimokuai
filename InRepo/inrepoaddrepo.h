#ifndef INREPOADDREPO_H
#define INREPOADDREPO_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVBoxLayout>

class InRepoAddRepo : public QDialog
{
    Q_OBJECT
public:
    explicit InRepoAddRepo(QWidget *parent = nullptr,
                               QSqlDatabase *db = nullptr,
                               QSqlQuery *query = nullptr);
    ~InRepoAddRepo();
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
    void SaveRepo();
private:
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *prompt;
    QPushButton *okButton;

    QVBoxLayout *mainLayout;
    QHBoxLayout *inputZone;

    QSqlDatabase *db;
    QSqlQuery *query;
    QStringList *sqlgroup;
};

#endif // INREPOADDREPO_H
