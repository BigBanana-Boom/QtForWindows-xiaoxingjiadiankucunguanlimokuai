#ifndef INREPOSEARCH_H
#define INREPOSEARCH_H

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

class InRepoSearch : public QWidget
{
    Q_OBJECT
public:
    explicit InRepoSearch(QWidget *parent = nullptr,
                          QSqlDatabase *db = nullptr,
                          QSqlQuery *query = nullptr,
                          QDateTime *IRsearchingdatetime = nullptr,
                          QDateTime *IRsearchingdatetime02 = nullptr,
                          QString *IRsearchingproductcategory = nullptr,
                          QString *IRsearchingproductname = nullptr,
                          QString *IRsearchingrepo = nullptr
                          );
    ~InRepoSearch();
signals:
    void RefreshInRepoTableSignal();
    void RefreshInRepoTableSignal_DifferentSelect();
public slots:
    void RefreshInRepoSearchSlot();
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

    // 总布局*******************************************************************************
    QHBoxLayout *zone;
    QVBoxLayout *leftzone;
    QHBoxLayout *leftzonerow1;
    QHBoxLayout *leftzonerow2;
    QHBoxLayout *leftzonerow3;
    QVBoxLayout *rightzone;
    QHBoxLayout *rightzonerow1;
    QHBoxLayout *rightzonerow2;
    QHBoxLayout *rightzonerow3;
    // 总布局*******************************************************************************

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
    QDateTime *IRsearchingdatetime;
    QDateTime *IRsearchingdatetime02;
    QString *IRsearchingproductcategory;
    QString *IRsearchingproductname;
    QString *IRsearchingrepo;
    // 成员变量*****************************************************************************
};

#endif // INREPOSEARCH_H
