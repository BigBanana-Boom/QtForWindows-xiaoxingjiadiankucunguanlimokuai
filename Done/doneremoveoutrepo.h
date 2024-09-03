#ifndef DONEREMOVEOUTREPO_H
#define DONEREMOVEOUTREPO_H

#include "refreshrepotableid.h"
#include <QApplication>
#include <QComboBox>
#include <QDateTime>
#include <QDebug>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidget>
#include <QVector>
#include <QVBoxLayout>

class DoneRemoveOutRepo : public QDialog
{
    Q_OBJECT
public:
    explicit DoneRemoveOutRepo(QWidget *parent = nullptr,
                               QSqlDatabase *db = nullptr,
                               QSqlQuery *query = nullptr,
                               int *currentID = nullptr,
                               QDateTime *currentdatetime = nullptr,
                               QString *currentproductcategory = nullptr,
                               QString *currentproductname = nullptr,
                               int *currentproductnumber = nullptr);
    ~DoneRemoveOutRepo();
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
    void SubmitRemoveOperation();
    void Close();
private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *inputZone;
    QHBoxLayout *buttonZone;

    QLabel *inputLabel;
    struct InputZoneData {
        QHBoxLayout* layout;
        QLabel* label;
        QSpinBox* spinBox;
        QLabel* label2;
    };
    QVector<InputZoneData> inputZones;
    QLabel *messageLabel;
    QLabel *prompt;

    QPushButton *confirmButton;
    QPushButton *cancelButton;

    QSqlDatabase *db;
    QSqlQuery *query;
    QStringList *sqlgroup;
    int *currentID;
    QDateTime *currentdatetime;
    QString *currentproductcategory;
    QString *currentproductname;
    int *currentproductnumber;
};

#endif // DONEREMOVEOUTREPO_H
