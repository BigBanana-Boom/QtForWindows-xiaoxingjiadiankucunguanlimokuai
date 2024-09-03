#include "donesearch.h"

DoneSearch::DoneSearch(QWidget *parent,
                        QSqlDatabase *db,
                        QSqlQuery *query,
                        QDateTime *Dsearchingdatetime,
                        QDateTime *Dsearchingdatetime02,
                        QString *Dsearchingproductcategory,
                        QString *Dsearchingproductname)
    : QWidget(parent),
      qfont01(new QFont("楷体", 16, QFont::Bold)),
      qfont02(new QFont("楷体", 16)),
      zone(new QHBoxLayout(this)),
      leftzone(new QVBoxLayout()),
      leftzonerow1(new QHBoxLayout()),
      leftzonerow2(new QHBoxLayout()),
      leftzonerow3(new QHBoxLayout()),
      rightzone(new QVBoxLayout()),
      rightzonerow1(new QHBoxLayout()),
      rightzonerow2(new QHBoxLayout()),
      rightzonerow3(new QHBoxLayout()),
      qlabel01(new QLabel("待查找最早已定日期：", this)),
      qlabel02(new QLabel("待查找最晚已定日期：", this)),
      qlabel03(new QLabel("待查找已定类别：", this)),
      qlabel04(new QLabel("待查找已定名称：", this)),
      qdatetimeedit01(new QDateTimeEdit(this)),
      qdatetimeedit02(new QDateTimeEdit(this)),
      qcombobox01(new QComboBox(this)),
      qcombobox02(new QComboBox(this)),
      qpushbutton00(new QPushButton("重置筛选条件", this)),
      qpushbutton01(new QPushButton("查找符合记录", this)),
      db(db),
      query(query),
      sqlgroup(new QStringList()),
      Dsearchingdatetime(Dsearchingdatetime),
      Dsearchingdatetime02(Dsearchingdatetime02),
      Dsearchingproductcategory(Dsearchingproductcategory),
      Dsearchingproductname(Dsearchingproductname)
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT DISTINCT 已定时间 FROM 已定表 "
                     "ORDER BY 已定时间 LIMIT 1");
    /* ORDER BY 已定时间 LIMIT 1 */
    sqlgroup->append("SELECT DISTINCT 已定时间 FROM 已定表 "
                     "ORDER BY 已定时间 DESC LIMIT 1");
    /* ORDER BY 已定时间 DESC LIMIT 1 */
    sqlgroup->append("SELECT DISTINCT 已定类别 FROM 已定表");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT DISTINCT 已定名称 FROM 已定表 WHERE 已定类别 = ?");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    // 数据库语句***************************************************************************

    // 左区域********************************************************************************
    // 最早已定日期*************************************************************************
    // 样式**********************************************************************************
    qlabel01->setFont(*qfont01);
    qdatetimeedit01->setFont(*qfont02);
    qdatetimeedit01->setDisplayFormat("yyyy-MM-dd");
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qdatetimeedit01->clear();
    query->exec(sqlgroup->at(0));
    if(query->next()) {
        qdatetimeedit01->setDateTime(query->value(0).toDateTime());
    } else {
        qdatetimeedit01->setDateTime(QDateTime::currentDateTime());
    }
    *Dsearchingdatetime = qdatetimeedit01->dateTime();
    // 填充内容******************************************************************************
    // 最早已定日期*************************************************************************
    // 最晚已定日期*************************************************************************
    // 样式**********************************************************************************
    qlabel02->setFont(*qfont01);
    qdatetimeedit02->setFont(*qfont02);
    qdatetimeedit02->setDisplayFormat("yyyy-MM-dd");
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qdatetimeedit02->clear();
    query->exec(sqlgroup->at(1));
    if(query->next()) {
        qdatetimeedit02->setDateTime(query->value(0).toDateTime());
    } else {
        qdatetimeedit02->setDateTime(QDateTime::currentDateTime());
    }
    *Dsearchingdatetime02 = qdatetimeedit02->dateTime();
    // 填充内容******************************************************************************
    // 最晚已定日期***********************************************************************
    // 请选择已定类别*********************************************************************
    // 样式**********************************************************************************
    qlabel03->setFont(*qfont01);
    qcombobox01->setFont(*qfont02);
    qcombobox01->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qcombobox01->clear();
    query->exec(sqlgroup->at(2));
    if(!query->next()) {
        qcombobox01->addItem("暂无");
        *Dsearchingproductcategory = "暂无";
     } else {
             QStringList stringList;
             QString item = query->value(0).toString();
             stringList.append(item);
             while (query->next()) {
                 QString item = query->value(0).toString();
                 stringList.append(item);
             }
             ChineseSort sorter;
             sorter(&stringList);
             for (int i = 0; i < stringList.size(); ++i) {
             qcombobox01->addItem(stringList.at(i));
         }
         qcombobox01->addItem("不选择");
         qcombobox01->setCurrentText("不选择");
        *Dsearchingproductcategory = qcombobox01->currentText();
    }
    // 填充内容******************************************************************************
    // 请选择已定类别***********************************************************************
    leftzonerow1->addWidget(qlabel01);
    leftzonerow1->addWidget(qdatetimeedit01, 1);
    leftzonerow2->addWidget(qlabel02);
    leftzonerow2->addWidget(qdatetimeedit02, 1);
    leftzonerow3->addWidget(qlabel03);
    leftzonerow3->addWidget(qcombobox01, 1);
    leftzone->addLayout(leftzonerow1);
    leftzone->addLayout(leftzonerow2);
    leftzone->addLayout(leftzonerow3);
    leftzone->setSpacing(8);
    leftzone->setContentsMargins(QMargins(0, 4, 0, 4));
    zone->addLayout(leftzone);
    // 左区域********************************************************************************

    // 右区域********************************************************************************
    // 请选择已定名称***********************************************************************
    // 样式**********************************************************************************
    qlabel04->setFont(*qfont01);
    qcombobox02->setFont(*qfont02);
    qcombobox02->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qcombobox02->clear();
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*Dsearchingproductcategory);
    query->exec();
    if(*Dsearchingproductcategory == "不选择") {
        qcombobox02->addItem("不选择");
        *Dsearchingproductname = qcombobox02->currentText();
    } else if(!query->next()) {
        qcombobox02->addItem("暂无");
        *Dsearchingproductname = qcombobox02->currentText();
    } else {
        QStringList stringList;
        QString item = query->value(0).toString();
        stringList.append(item);
        while (query->next()) {
            QString item = query->value(0).toString();
            stringList.append(item);
        }
        ChineseSort sorter;
        sorter(&stringList);
        qcombobox02->clear();
        for (int i = 0; i < stringList.size(); ++i) {
            qcombobox02->addItem(stringList.at(i));
        }
        qcombobox02->addItem("不选择");
        qcombobox02->setCurrentText("不选择");
        *Dsearchingproductname = qcombobox02->currentText();
    }
    // 填充内容******************************************************************************
    // 请选择已定名称***********************************************************************
    qpushbutton00->setFont(*qfont01);
    qpushbutton01->setFont(*qfont01);
    rightzonerow1->addWidget(qlabel04);
    rightzonerow1->addWidget(qcombobox02, 1);
    rightzonerow2->addWidget(qpushbutton00);
    rightzonerow3->addWidget(qpushbutton01);
    rightzone->addLayout(rightzonerow1);
    rightzone->addLayout(rightzonerow2);
    rightzone->addLayout(rightzonerow3);
    rightzone->setSpacing(8);
    rightzone->setContentsMargins(QMargins(0, 4, 0, 4));
    zone->addLayout(rightzone);
    // 右区域********************************************************************************

    // 信号和槽函数*************************************************************************
    connect(qdatetimeedit01, &QDateTimeEdit::dateTimeChanged,
            this, &DoneSearch::onSearchingBeginDateTimeChanged);
    connect(qdatetimeedit02, &QDateTimeEdit::dateTimeChanged,
            this, &DoneSearch::onSearchingEndDateTimeChanged);
    connect(qcombobox01, &QComboBox::currentTextChanged,
            this, &DoneSearch::onSearchingProductCategoryChanged);
    connect(qcombobox02, &QComboBox::currentTextChanged,
            this, &DoneSearch::onSearchingProductNameChanged);
    connect(qpushbutton00, &QPushButton::pressed, this,
            &DoneSearch::SubmitResetOperation);
    connect(qpushbutton01, &QPushButton::pressed, this,
            &DoneSearch::SubmitSearchOperation);
    // 信号和槽函数*************************************************************************
}
DoneSearch::~DoneSearch() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete sqlgroup;
    // 删除new对象*************************************************************************
}
void DoneSearch::SubmitSearchOperation() {
    emit RefreshDoneTableSignal_DifferentSelect();
}
void DoneSearch::SubmitResetOperation() {
    emit RefreshDoneTableSignal();
    // 关信号********************************************************************************
    qdatetimeedit01->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qdatetimeedit01->clear();
    query->exec(sqlgroup->at(0));
    if(query->next()) {
        qdatetimeedit01->setDateTime(query->value(0).toDateTime());
    } else {
        qdatetimeedit01->setDateTime(QDateTime::currentDateTime());
    }
    *Dsearchingdatetime = qdatetimeedit01->dateTime();
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qdatetimeedit01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingBeginDateTimeChanged(*Dsearchingdatetime);
    // 启槽函数******************************************************************************
    // 关信号********************************************************************************
    qdatetimeedit02->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qdatetimeedit02->clear();
    query->exec(sqlgroup->at(1));
    if(query->next()) {
        qdatetimeedit02->setDateTime(query->value(0).toDateTime());
    } else {
        qdatetimeedit02->setDateTime(QDateTime::currentDateTime());
    }
    *Dsearchingdatetime02 = qdatetimeedit02->dateTime();
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qdatetimeedit02->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingEndDateTimeChanged(*Dsearchingdatetime02);
    // 启槽函数******************************************************************************
    qcombobox01->setCurrentText("不选择");
    qcombobox02->setCurrentText("不选择");
}
void DoneSearch::onSearchingBeginDateTimeChanged(const QDateTime &datetime) {
    // 记录更新******************************************************************************
    *Dsearchingdatetime = datetime;
    // 记录更新******************************************************************************
}
void DoneSearch::onSearchingEndDateTimeChanged(const QDateTime &datetime) {
    // 记录更新******************************************************************************
    *Dsearchingdatetime02 = datetime;
    // 记录更新******************************************************************************
}
void DoneSearch::onSearchingProductCategoryChanged(const QString &text) {
    // 记录更新******************************************************************************
    *Dsearchingproductcategory = text;
    // 记录更新******************************************************************************
    // 关信号********************************************************************************
    qcombobox02->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qcombobox02->clear();
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*Dsearchingproductcategory);
    query->exec();
    if(*Dsearchingproductcategory == "不选择") {
        qcombobox02->addItem("不选择");
        *Dsearchingproductname = qcombobox02->currentText();
    } else if(!query->next()) {
        qcombobox02->addItem("暂无");
        *Dsearchingproductname = qcombobox02->currentText();
    } else {
        QStringList stringList;
        QString item = query->value(0).toString();
        stringList.append(item);
        while (query->next()) {
            QString item = query->value(0).toString();
            stringList.append(item);
        }
        ChineseSort sorter;
        sorter(&stringList);
        qcombobox02->clear();
        for (int i = 0; i < stringList.size(); ++i) {
            qcombobox02->addItem(stringList.at(i));
        }
        qcombobox02->addItem("不选择");
        qcombobox02->setCurrentText("不选择");
        *Dsearchingproductname = qcombobox02->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qcombobox02->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingProductNameChanged(*Dsearchingproductname);
    // 启槽函数******************************************************************************
}
void DoneSearch::onSearchingProductNameChanged(const QString &text) {
    // 记录更新******************************************************************************
    *Dsearchingproductname = text;
    // 记录更新******************************************************************************
}
void DoneSearch::RefreshDoneSearchSlot() {
    // 关信号********************************************************************************
    qdatetimeedit01->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qdatetimeedit01->clear();
    query->exec(sqlgroup->at(0));
    if(query->next()) {
        qdatetimeedit01->setDateTime(query->value(0).toDateTime());
    } else {
        qdatetimeedit01->setDateTime(QDateTime::currentDateTime());
    }
    *Dsearchingdatetime = qdatetimeedit01->dateTime();
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qdatetimeedit01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingBeginDateTimeChanged(*Dsearchingdatetime);
    // 启槽函数******************************************************************************
    // 关信号********************************************************************************
    qdatetimeedit02->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qdatetimeedit02->clear();
    query->exec(sqlgroup->at(1));
    if(query->next()) {
        qdatetimeedit02->setDateTime(query->value(0).toDateTime());
    } else {
        qdatetimeedit02->setDateTime(QDateTime::currentDateTime());
    }
    *Dsearchingdatetime02 = qdatetimeedit02->dateTime();
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qdatetimeedit02->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingEndDateTimeChanged(*Dsearchingdatetime02);
    // 启槽函数******************************************************************************
    // 关信号********************************************************************************
    qcombobox01->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qcombobox01->clear();
    query->exec(sqlgroup->at(2));
    if(!query->next()) {
        qcombobox01->addItem("暂无");
        *Dsearchingproductcategory = "暂无";
     } else {
             QStringList stringList;
             QString item = query->value(0).toString();
             stringList.append(item);
             while (query->next()) {
                 QString item = query->value(0).toString();
                 stringList.append(item);
             }
             ChineseSort sorter;
             sorter(&stringList);
             for (int i = 0; i < stringList.size(); ++i) {
             qcombobox01->addItem(stringList.at(i));
         }
         qcombobox01->addItem("不选择");
         qcombobox01->setCurrentText("不选择");
        *Dsearchingproductcategory = qcombobox01->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qcombobox01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingProductCategoryChanged(*Dsearchingproductcategory);
    // 启槽函数******************************************************************************
}
