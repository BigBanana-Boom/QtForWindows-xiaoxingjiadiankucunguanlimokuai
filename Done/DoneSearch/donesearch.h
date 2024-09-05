#ifndef DONESEARCH_H
#define DONESEARCH_H

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

class DoneSearch : public QWidget
{
    Q_OBJECT
public:
    explicit DoneSearch(QWidget *parent = nullptr,
                        QSqlDatabase *db = nullptr,
                        QSqlQuery *query = nullptr,
                        QDateTime *Dsearchingdatetime = nullptr,
                        QDateTime *Dsearchingdatetime02 = nullptr,
                        QString *Dsearchingproductcategory = nullptr,
                        QString *Dsearchingproductname = nullptr);
    ~DoneSearch();
signals:
    void RefreshDoneTableSignal();
    void RefreshDoneTableSignal_DifferentSelect();
public slots:
    void RefreshDoneSearchSlot();
private slots:
    void onSearchingBeginDateTimeChanged(const QDateTime &datetime);
    void onSearchingEndDateTimeChanged(const QDateTime &datetime);
    void onSearchingProductCategoryChanged(const QString &text);
    void onSearchingProductNameChanged(const QString &text);
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
    // 标签*********************************************************************************

    // 左区域*******************************************************************************
    QDateTimeEdit *qdatetimeedit01;
    QDateTimeEdit *qdatetimeedit02;
    QComboBox *qcombobox01;
    // 左区域*******************************************************************************

    // 右区域*******************************************************************************
    QComboBox *qcombobox02;
    QPushButton *qpushbutton00;
    QPushButton *qpushbutton01;
    // 右区域*******************************************************************************

    // 数据库连接***************************************************************************
    QSqlDatabase *db;
    QSqlQuery *query;
    QStringList *sqlgroup;
    // 数据库连接***************************************************************************

    // 成员变量*****************************************************************************
    QDateTime *Dsearchingdatetime;
    QDateTime *Dsearchingdatetime02;
    QString *Dsearchingproductcategory;
    QString *Dsearchingproductname;
    // 成员变量*****************************************************************************
};

#endif // DONESEARCH_H
