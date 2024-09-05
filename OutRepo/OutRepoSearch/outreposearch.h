#ifndef OUTREPOSEARCH_H
#define OUTREPOSEARCH_H

#include "../MethodClass/chinesesort.h"
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

class OutRepoSearch : public QWidget
{
    Q_OBJECT
public:
    explicit OutRepoSearch(QWidget *parent = nullptr,
                           QSqlDatabase *db = nullptr,
                           QSqlQuery *query = nullptr,
                           QDateTime *ORsearchingdatetime = nullptr,
                           QDateTime *ORsearchingdatetime02 = nullptr,
                           QString *ORsearchingproductcategory = nullptr,
                           QString *ORsearchingproductname = nullptr,
                           QString *ORsearchingrepo = nullptr);
    ~OutRepoSearch();
signals:
    void RefreshOutRepoTableSignal();
    void RefreshOutRepoTableSignal_DifferentSelect();
public slots:
    void RefreshOutRepoSearchSlot();
private slots:
    void onSearchingBeginDateTimeChanged(const QDateTime &datetime);
    void onSearchingEndDateTimeChanged(const QDateTime &datetime);
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

    // 布局*********************************************************************************
    QHBoxLayout *zone;
    QVBoxLayout *leftzone;
    QHBoxLayout *leftzonerow1;
    QHBoxLayout *leftzonerow2;
    QHBoxLayout *leftzonerow3;
    QVBoxLayout *rightzone;
    QHBoxLayout *rightzonerow1;
    QHBoxLayout *rightzonerow2;
    QHBoxLayout *rightzonerow3;
    // 布局*********************************************************************************

    // 标签*********************************************************************************
    QLabel *qlabel01;
    QLabel *qlabel02;
    QLabel *qlabel03;
    QLabel *qlabel04;
    QLabel *qlabel05;
    // 标签*********************************************************************************

    // 左区域*******************************************************************************
    QDateTimeEdit *qdatetimeedit01;
    QDateTimeEdit *qdatetimeedit02;
    QComboBox *qcombobox01;
    // 左区域*******************************************************************************

    // 右区域*******************************************************************************
    QComboBox *qcombobox02;
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
    QDateTime *ORsearchingdatetime;
    QDateTime *ORsearchingdatetime02;
    QString *ORsearchingproductcategory;
    QString *ORsearchingproductname;
    QString *ORsearchingrepo;
    // 成员变量*****************************************************************************
};

#endif // OUTREPOSEARCH_H
