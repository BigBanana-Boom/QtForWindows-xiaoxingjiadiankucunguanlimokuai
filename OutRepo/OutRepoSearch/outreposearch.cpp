/*
 *
 * on... Changed();不用连锁所有的
 * Refresh...();需要更新所有的
 *
 */
#include "outreposearch.h"

OutRepoSearch::OutRepoSearch(QWidget *parent,
                       QSqlDatabase *db,
                       QSqlQuery *query,
                       QDateTime *ORsearchingdatetime,
                       QDateTime *ORsearchingdatetime02,
                       QString *ORsearchingproductcategory,
                       QString *ORsearchingproductname,
                       QString *ORsearchingrepo)
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
    qlabel01(new QLabel("待查找最早出库日期：", this)),
    qlabel02(new QLabel("待查找最晚出库日期：", this)),
    qlabel03(new QLabel("待查找出库类别：", this)),
    qlabel04(new QLabel("待查找出库名称：", this)),
    qlabel05(new QLabel("待查找出库位置：", this)),
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
    ORsearchingdatetime(ORsearchingdatetime),
    ORsearchingdatetime02(ORsearchingdatetime02),
    ORsearchingproductcategory(ORsearchingproductcategory),
    ORsearchingproductname(ORsearchingproductname),
    ORsearchingrepo(ORsearchingrepo)
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT DISTINCT 出库时间 FROM 出库表 "
                     "ORDER BY 出库时间 LIMIT 1");
    /* ORDER BY 出库时间 LIMIT 1 */
    sqlgroup->append("SELECT DISTINCT 出库时间 FROM 出库表 "
                     "ORDER BY 出库时间 DESC LIMIT 1");
    /* ORDER BY 出库时间 DESC LIMIT 1 */
    sqlgroup->append("SELECT DISTINCT 出库类别 FROM 出库表");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT DISTINCT 出库名称 FROM 出库表 WHERE 出库类别 = ?");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT DISTINCT 出库位置 FROM 出库表 "
                     "WHERE 出库类别 = ? AND 出库名称 = ?");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    // 数据库语句***************************************************************************

    // 左区域*******************************************************************************
    // 最早出库日期*************************************************************************
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
    *ORsearchingdatetime = qdatetimeedit01->dateTime();
    // 填充内容******************************************************************************
    // 最早出库日期*************************************************************************
    // 最晚出库日期*************************************************************************
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
    *ORsearchingdatetime02 = qdatetimeedit02->dateTime();
    // 填充内容******************************************************************************
    // 最晚出库日期*************************************************************************
    // 出库类别*****************************************************************************
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
        *ORsearchingproductcategory = "暂无";
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
        *ORsearchingproductcategory = qcombobox01->currentText();
    }
    // 填充内容******************************************************************************
    // 出库类别*****************************************************************************
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
    // 出库名称*****************************************************************************
    // 样式**********************************************************************************
    qlabel04->setFont(*qfont01);
    qcombobox02->setFont(*qfont02);
    qcombobox02->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qcombobox02->clear();
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*ORsearchingproductcategory);
    query->exec();
    if(*ORsearchingproductcategory == "不选择") {
        qcombobox02->addItem("不选择");
        *ORsearchingproductname = "不选择";
    } else if (!query->next()) {
        qcombobox02->addItem("暂无");
        *ORsearchingproductname = "暂无";
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
        *ORsearchingproductname = qcombobox02->currentText();
    }
    // 填充内容******************************************************************************
    // 出库名称*****************************************************************************
    // 出库位置*****************************************************************************
    // 样式**********************************************************************************
    qlabel05->setFont(*qfont01);
    qcombobox03->setFont(*qfont02);
    qcombobox03->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qcombobox03->clear();
    query->prepare(sqlgroup->at(4));
    query->addBindValue(*ORsearchingproductcategory);
    query->addBindValue(*ORsearchingproductname);
    query->exec();
    if(*ORsearchingproductname == "不选择") {
        qcombobox03->addItem("不选择");
        *ORsearchingrepo = "不选择";
    } else if(!query->next()) {
        qcombobox03->addItem("暂无");
        *ORsearchingrepo = "暂无";
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
        *ORsearchingrepo = qcombobox03->currentText();
    }
    // 填充内容******************************************************************************
    // 出库位置*****************************************************************************
    qpushbutton01->setFont(*qfont01);
    qpushbutton01->setMinimumWidth(110);
    qpushbutton02->setFont(*qfont01);
    qpushbutton02->setMinimumWidth(110);
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
            this, &OutRepoSearch::onSearchingBeginDateTimeChanged);
    connect(qdatetimeedit02, &QDateTimeEdit::dateTimeChanged,
            this, &OutRepoSearch::onSearchingEndDateTimeChanged);
    connect(qcombobox01, &QComboBox::currentTextChanged,
            this, &OutRepoSearch::onSearchingProductCategoryChanged);
    connect(qcombobox02, &QComboBox::currentTextChanged,
            this, &OutRepoSearch::onSearchingProductNameChanged);
    connect(qcombobox03, &QComboBox::currentTextChanged,
            this, &OutRepoSearch::onSearchingRepoChanged);
    connect(qpushbutton01, &QPushButton::pressed, this,
            &OutRepoSearch::SubmitResetOperation);
    connect(qpushbutton02, &QPushButton::pressed, this,
            &OutRepoSearch::SubmitSearchOperation);
    // 信号和槽函数*************************************************************************
}
OutRepoSearch::~OutRepoSearch() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete sqlgroup;
    // 删除new对象*************************************************************************
}
void OutRepoSearch::SubmitSearchOperation() {
    emit RefreshOutRepoTableSignal_DifferentSelect();
}
void OutRepoSearch::SubmitResetOperation() {
    emit RefreshOutRepoTableSignal();
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
    *ORsearchingdatetime = qdatetimeedit01->dateTime();
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qdatetimeedit01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingBeginDateTimeChanged(*ORsearchingdatetime);
    // 启槽函数******************************************************************************
    // 关信号********************************************************************************
    qdatetimeedit01->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qdatetimeedit02->clear();
    query->exec(sqlgroup->at(1));
    if(query->next()) {
        qdatetimeedit02->setDateTime(query->value(0).toDateTime());
    } else {
        qdatetimeedit02->setDateTime(QDateTime::currentDateTime());
    }
    *ORsearchingdatetime02 = qdatetimeedit02->dateTime();
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qdatetimeedit01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingEndDateTimeChanged(*ORsearchingdatetime02);
    // 启槽函数******************************************************************************
    qcombobox01->setCurrentText("不选择");
    qcombobox02->setCurrentText("不选择");
    qcombobox03->setCurrentText("不选择");
}
void OutRepoSearch::onSearchingBeginDateTimeChanged(
        const QDateTime &datetime) {
    // 记录更新******************************************************************************
    *ORsearchingdatetime = datetime;
    // 记录更新******************************************************************************
}
void OutRepoSearch::onSearchingEndDateTimeChanged(
        const QDateTime &datetime) {
    // 记录更新******************************************************************************
    *ORsearchingdatetime02 = datetime;
    // 记录更新******************************************************************************
}
void OutRepoSearch::onSearchingProductCategoryChanged(
        const QString &text) {
    // 记录更新******************************************************************************
    *ORsearchingproductcategory = text;
    // 记录更新******************************************************************************
    // 关信号********************************************************************************
    qcombobox02->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qcombobox02->clear();
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*ORsearchingproductcategory);
    query->exec();
    if(*ORsearchingproductcategory == "不选择") {
        qcombobox02->addItem("不选择");
        *ORsearchingproductname = "不选择";
    } else if (!query->next()) {
        qcombobox02->addItem("暂无");
        *ORsearchingproductname = "暂无";
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
        *ORsearchingproductname = qcombobox02->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号*******************************************************************************
    qcombobox02->blockSignals(false);
    // 开信号*******************************************************************************
    // 启槽函数*****************************************************************************
    onSearchingProductNameChanged(*ORsearchingproductname);
    // 启槽函数*****************************************************************************
}
void OutRepoSearch::onSearchingProductNameChanged(const QString &text) {
    // 记录更新******************************************************************************
    *ORsearchingproductname = text;
    // 记录更新******************************************************************************
    // 关信号********************************************************************************
    qcombobox03->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qcombobox03->clear();
    query->prepare(sqlgroup->at(4));
    query->addBindValue(*ORsearchingproductcategory);
    query->addBindValue(*ORsearchingproductname);
    query->exec();
    if(*ORsearchingproductname == "不选择") {
        qcombobox03->addItem("不选择");
        *ORsearchingrepo = "不选择";
    } else
    if(!query->next()) {
        qcombobox03->addItem("暂无");
        *ORsearchingrepo = "暂无";
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
        *ORsearchingrepo = qcombobox03->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qcombobox03->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingRepoChanged(*ORsearchingrepo);
    // 启槽函数******************************************************************************
}
void OutRepoSearch::onSearchingRepoChanged(const QString &text) {
    // 记录更新******************************************************************************
    *ORsearchingrepo = text;
    // 记录更新******************************************************************************
}
void OutRepoSearch::RefreshOutRepoSearchSlot() {
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
    *ORsearchingdatetime = qdatetimeedit01->dateTime();
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qdatetimeedit02->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingBeginDateTimeChanged(*ORsearchingdatetime);
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
    *ORsearchingdatetime02 = qdatetimeedit02->dateTime();
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qdatetimeedit02->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingEndDateTimeChanged(*ORsearchingdatetime02);
    // 启槽函数******************************************************************************
    // 关信号********************************************************************************
    qcombobox01->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qcombobox01->clear();
    query->exec(sqlgroup->at(2));
    if(!query->next()) {
        qcombobox01->addItem("暂无");
        *ORsearchingproductcategory = "暂无";
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
        *ORsearchingproductcategory = qcombobox01->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qcombobox01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingProductCategoryChanged(*ORsearchingproductcategory);
    // 启槽函数******************************************************************************
}
