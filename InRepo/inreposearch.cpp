/*
 *
 * on... Changed();不用连锁所有的
 * Refresh...();需要更新所有的
 *
 */
#include "inreposearch.h"

InRepoSearch::InRepoSearch(QWidget *parent,
                           QSqlDatabase *db,
                           QSqlQuery *query,
                           QDateTime *IRsearchingdatetime,
                           QDateTime *IRsearchingdatetime02,
                           QString *IRsearchingproductcategory,
                           QString *IRsearchingproductname,
                           QString *IRsearchingrepo)
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
      qlabel01(new QLabel("待查找最早入库日期：", this)),
      qlabel02(new QLabel("待查找最晚入库日期：", this)),
      qlabel03(new QLabel("待查找入库类别：", this)),
      qlabel04(new QLabel("待查找入库名称：", this)),
      qlabel05(new QLabel("待查找入库位置：", this)),
      qdatetimeedit01(new QDateTimeEdit(this)),
      qdatetimeedit02(new QDateTimeEdit(this)),
      qcombobox01(new QComboBox(this)),
      qcombobox02(new QComboBox(this)),
      qcombobox03(new QComboBox(this)),
      qpushbutton01(new QPushButton("重置筛选条件", this)),
      qpushbutton02(new QPushButton("查找符合记录", this)),
      db(db),
      query(query),
      sqlgroup(new QStringList()),
      IRsearchingdatetime(IRsearchingdatetime),
      IRsearchingdatetime02(IRsearchingdatetime02),
      IRsearchingproductcategory(IRsearchingproductcategory),
      IRsearchingproductname(IRsearchingproductname),
      IRsearchingrepo(IRsearchingrepo)
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT DISTINCT 入库时间 FROM 入库表 "
                     "ORDER BY 入库时间 LIMIT 1");
    /* ORDER BY 入库时间 LIMIT 1 */
    sqlgroup->append("SELECT DISTINCT 入库时间 FROM 入库表 "
                     "ORDER BY 入库时间 DESC LIMIT 1");
    /* ORDER BY 入库时间 DESC LIMIT 1 */
    sqlgroup->append("SELECT DISTINCT 入库类别 FROM 入库表");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT DISTINCT 入库名称 FROM 入库表 WHERE 入库类别 = ?");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT DISTINCT 入库位置 FROM 入库表 "
                     "WHERE 入库类别 = ? AND 入库名称 = ?");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    // 数据库语句***************************************************************************

    // 左区域********************************************************************************
    // 最早入库日期*************************************************************************
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
    *IRsearchingdatetime = qdatetimeedit01->dateTime();
    // 填充内容******************************************************************************
    // 最早入库日期*************************************************************************
    // 最晚入库日期*************************************************************************
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
    *IRsearchingdatetime02 = qdatetimeedit02->dateTime();
    // 填充内容******************************************************************************
    // 最晚入库日期*************************************************************************
    // 入库类别*****************************************************************************
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
        *IRsearchingproductcategory = "暂无";
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
        *IRsearchingproductcategory = qcombobox01->currentText();
    }
    // 填充内容******************************************************************************
    // 入库类别*****************************************************************************
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
    // 左区域*******************************************************************************

    // 右区域*******************************************************************************
    // 入库名称*****************************************************************************
    // 样式**********************************************************************************
    qlabel04->setFont(*qfont01);
    qcombobox02->setFont(*qfont02);
    qcombobox02->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qcombobox02->clear();
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*IRsearchingproductcategory);
    query->exec();
    if(*IRsearchingproductcategory == "不选择") {
        qcombobox02->addItem("不选择");
        *IRsearchingproductname = qcombobox02->currentText();
    } else if(!query->next()) {
        qcombobox02->addItem("暂无");
        *IRsearchingproductname = qcombobox02->currentText();
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
            qcombobox02->addItem(stringList.at(i));
        }
        qcombobox02->addItem("不选择");
        qcombobox02->setCurrentText("不选择");
        *IRsearchingproductname = qcombobox02->currentText();
    }
    // 填充内容******************************************************************************
    // 入库名称*****************************************************************************
    // 入库位置*****************************************************************************
    // 样式**********************************************************************************
    qlabel05->setFont(*qfont01);
    qcombobox03->setFont(*qfont02);
    qcombobox03->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qcombobox03->clear();
    query->prepare(sqlgroup->at(4));
    query->addBindValue(*IRsearchingproductcategory);
    query->addBindValue(*IRsearchingproductname);
    query->exec();
    if(*IRsearchingproductname == "不选择") {
        qcombobox03->addItem("不选择");
        *IRsearchingrepo = "不选择";
    } else
    if(!query->next()) {
        qcombobox03->addItem("暂无");
        *IRsearchingrepo = "暂无";
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
            qcombobox03->addItem(stringList.at(i));
        }
        qcombobox03->addItem("不选择");
        qcombobox03->setCurrentText("不选择");
        *IRsearchingrepo = qcombobox03->currentText();
    }
    // 填充内容******************************************************************************
    // 入库位置*****************************************************************************
    qpushbutton01->setFont(*qfont01);
    qpushbutton02->setFont(*qfont01);
    rightzonerow1->addWidget(qlabel04);
    rightzonerow1->addWidget(qcombobox02, 1);
    rightzonerow2->addWidget(qlabel05);
    rightzonerow2->addWidget(qcombobox03, 1);
    rightzonerow3->addWidget(qpushbutton01);
    rightzonerow3->addWidget(qpushbutton02);
    rightzone->addLayout(rightzonerow1);
    rightzone->addLayout(rightzonerow2);
    rightzone->addLayout(rightzonerow3);
    rightzone->setSpacing(8);
    rightzone->setContentsMargins(QMargins(0, 4, 0, 4));
    zone->addLayout(rightzone);
    // 右区域********************************************************************************

    // 信号和槽函数*************************************************************************
    connect(qdatetimeedit01, &QDateTimeEdit::dateTimeChanged,
            this, &InRepoSearch::onSearchingBeginDateTimeChanged);
    connect(qdatetimeedit02, &QDateTimeEdit::dateTimeChanged,
            this, &InRepoSearch::onSearchingEndDateTimeChanged);
    connect(qcombobox01, &QComboBox::currentTextChanged,
            this, &InRepoSearch::onSearchingProductCategoryChanged);
    connect(qcombobox02, &QComboBox::currentTextChanged,
            this, &InRepoSearch::onSearchingProductNameChanged);
    connect(qcombobox03, &QComboBox::currentTextChanged,
            this, &InRepoSearch::onSearchingRepoChanged);
    connect(qpushbutton01, &QPushButton::pressed, this,
            &InRepoSearch::SubmitResetOperation);
    connect(qpushbutton02, &QPushButton::pressed, this,
            &InRepoSearch::SubmitSearchOperation);
    // 信号和槽函数*************************************************************************
}
InRepoSearch::~InRepoSearch() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete sqlgroup;
    // 删除new对象*************************************************************************
}
void InRepoSearch::SubmitSearchOperation() {
    emit RefreshInRepoTableSignal_DifferentSelect();
}
void InRepoSearch::SubmitResetOperation() {
    emit RefreshInRepoTableSignal();
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
    *IRsearchingdatetime = qdatetimeedit01->dateTime();
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qdatetimeedit01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingBeginDateTimeChanged(*IRsearchingdatetime);
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
    *IRsearchingdatetime02 = qdatetimeedit02->dateTime();
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qdatetimeedit02->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingEndDateTimeChanged(*IRsearchingdatetime02);
    // 启槽函数******************************************************************************
    qcombobox01->setCurrentText("不选择");
    qcombobox02->setCurrentText("不选择");
    qcombobox03->setCurrentText("不选择");
}
void InRepoSearch::onSearchingBeginDateTimeChanged(const QDateTime &datetime) {
    // 记录更新******************************************************************************
    *IRsearchingdatetime = datetime;
    // 记录更新******************************************************************************
}
void InRepoSearch::onSearchingEndDateTimeChanged(const QDateTime &datetime) {
    // 记录更新******************************************************************************
    *IRsearchingdatetime02 = datetime;
    // 记录更新******************************************************************************
}
void InRepoSearch::onSearchingProductCategoryChanged(const QString &text) {
    // 记录更新******************************************************************************
    *IRsearchingproductcategory = text;
    // 记录更新******************************************************************************
    // 关信号********************************************************************************
    qcombobox02->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qcombobox02->clear();
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*IRsearchingproductcategory);
    query->exec();
    if(*IRsearchingproductcategory == "不选择") {
        qcombobox02->addItem("不选择");
        *IRsearchingproductname = qcombobox02->currentText();
    } else if(!query->next()) {
        qcombobox02->addItem("暂无");
        *IRsearchingproductname = qcombobox02->currentText();
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
            qcombobox02->addItem(stringList.at(i));
        }
        qcombobox02->addItem("不选择");
        qcombobox02->setCurrentText("不选择");
        *IRsearchingproductname = qcombobox02->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qcombobox02->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingProductNameChanged(*IRsearchingproductname);
    // 启槽函数******************************************************************************
}
void InRepoSearch::onSearchingProductNameChanged(const QString &text) {
    // 记录更新******************************************************************************
    *IRsearchingproductname = text;
    // 记录更新******************************************************************************
    // 关信号********************************************************************************
    qcombobox03->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qcombobox03->clear();
    query->prepare(sqlgroup->at(4));
    query->addBindValue(*IRsearchingproductcategory);
    query->addBindValue(*IRsearchingproductname);
    query->exec();
    if(*IRsearchingproductname == "不选择") {
        qcombobox03->addItem("不选择");
        *IRsearchingrepo = "不选择";
    } else
    if(!query->next()) {
        qcombobox03->addItem("暂无");
        *IRsearchingrepo = "暂无";
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
            qcombobox03->addItem(stringList.at(i));
        }
        qcombobox03->addItem("不选择");
        qcombobox03->setCurrentText("不选择");
        *IRsearchingrepo = qcombobox03->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qcombobox03->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingRepoChanged(*IRsearchingrepo);
    // 启槽函数******************************************************************************
}
void InRepoSearch::onSearchingRepoChanged(const QString &text) {
    // 记录更新******************************************************************************
    *IRsearchingrepo = text;
    // 记录更新******************************************************************************
}
void InRepoSearch::RefreshInRepoSearchSlot() {
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
    *IRsearchingdatetime = qdatetimeedit01->dateTime();
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qdatetimeedit01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingBeginDateTimeChanged(*IRsearchingdatetime);
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
    *IRsearchingdatetime02 = qdatetimeedit02->dateTime();
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qdatetimeedit02->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingEndDateTimeChanged(*IRsearchingdatetime02);
    // 启槽函数******************************************************************************
    // 关信号********************************************************************************
    qcombobox01->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qcombobox01->clear();
    query->exec(sqlgroup->at(2));
    if(!query->next()) {
        qcombobox01->addItem("暂无");
        *IRsearchingproductcategory = "暂无";
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
        *IRsearchingproductcategory = qcombobox01->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qcombobox01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingProductCategoryChanged(*IRsearchingproductcategory);
    // 启槽函数******************************************************************************
}
