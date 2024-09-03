#ifndef REPOSEARCH_H
#define REPOSEARCH_H

#include "chinesesort.h"
#include <QComboBox>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVBoxLayout>
#include <QWidget>

class RepoSearch : public QWidget
{
    Q_OBJECT
public:
    explicit RepoSearch(QWidget *parent = nullptr,
                        QSqlDatabase *db = nullptr,
                        QSqlQuery *query = nullptr,
                        QString *Rsearchingproductcategory = nullptr,
                        QString *Rsearchingproductname = nullptr,
                        QString *Rsearchingrepo = nullptr);
    ~RepoSearch();
signals:
    void RefreshRepoTableSignal();
    void RefreshRepoTableSignal_DifferentSelect();
public slots:
    void RefreshRepoSearchSlot();
private slots:
    void onSearchingProductCategoryChanged(const QString &text);
    void onSearchingProductNameChanged(const QString &text);
    void onSearchingRepoChanged(const QString &text);
    void SubmitSearchOperation();
    void SubmitResetOperation();
private:
    // 字体*********************************************************************************
    QFont *qfont01;
    QFont *qfont02;
    // 字体*********************************************************************************

    // 总布局*******************************************************************************
    QHBoxLayout *zone;
    QVBoxLayout *leftzone;
    QHBoxLayout *leftzonerow1;
    QHBoxLayout *leftzonerow2;
    QVBoxLayout *rightzone;
    QHBoxLayout *rightzonerow1;
    QHBoxLayout *rightzonerow2;
    // 总布局*******************************************************************************

    // 标签*********************************************************************************
    QLabel *qlabel01;
    QLabel *qlabel02;
    QLabel *qlabel03;
    // 标签*********************************************************************************

    // 左区域*******************************************************************************
    QComboBox *qcombobox01;
    QComboBox *qcombobox02;
    // 左区域*******************************************************************************

    // 右区域*******************************************************************************
    QComboBox *qcombobox03;
    QPushButton *qpushbutton01;
    QPushButton *qpushbutton02;
    // 右区域*******************************************************************************

    // 数据库连接***************************************************************************
    QSqlDatabase *db;
    QSqlQuery *query;
    QStringList *sqlgroup;
    // 数据库连接***************************************************************************

    // 成员变量*****************************************************************************
    QDateTime *Rsearchingdatetime;
    QDateTime *Rsearchingdatetime02;
    QString *Rsearchingproductcategory;
    QString *Rsearchingproductname;
    QString *Rsearchingrepo;
    // 成员变量*****************************************************************************

};

#endif // REPOSEARCH_H
