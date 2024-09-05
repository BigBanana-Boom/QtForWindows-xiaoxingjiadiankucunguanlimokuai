/*
 *
 * on... Changed();不用连锁所有的
 * Refresh...();需要更新所有的
 *
 */
#include "reposearch.h"

RepoSearch::RepoSearch(QWidget *parent,
                       QSqlDatabase *db,
                       QSqlQuery *query,
                       QString *Rsearchingproductcategory,
                       QString *Rsearchingproductname,
                       QString *Rsearchingrepo)
    : QWidget(parent),
      qfont01(new QFont("楷体", 16, QFont::Bold)),
      qfont02(new QFont("楷体", 16)),
      zone(new QHBoxLayout(this)),
      leftzone(new QVBoxLayout()),
      leftzonerow1(new QHBoxLayout()),
      leftzonerow2(new QHBoxLayout()),
      rightzone(new QVBoxLayout()),
      rightzonerow1(new QHBoxLayout()),
      rightzonerow2(new QHBoxLayout()),
      qlabel01(new QLabel("待查找库存类别：", this)),
      qlabel02(new QLabel("待查找库存名称：", this)),
      qlabel03(new QLabel("待查找库存位置：", this)),
      qcombobox01(new QComboBox(this)),
      qcombobox02(new QComboBox(this)),
      qcombobox03(new QComboBox(this)),
      qpushbutton01(new QPushButton("重置筛选条件", this)),
      qpushbutton02(new QPushButton("查找符合记录", this)),
      db(db),
      query(query),
      sqlgroup(new QStringList()),
      Rsearchingproductcategory(Rsearchingproductcategory),
      Rsearchingproductname(Rsearchingproductname),
      Rsearchingrepo(Rsearchingrepo)
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT DISTINCT 库存类别 FROM 库存表");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT DISTINCT 库存名称 FROM 库存表 WHERE 库存类别 = ?");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT DISTINCT 存放位置 FROM 库存表 "
                     "WHERE 库存类别 = ? AND 库存名称 = ?");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    // 数据库语句***************************************************************************

    // 左区域********************************************************************************
    // 库存类别*****************************************************************************
    // 样式**********************************************************************************
    qlabel01->setFont(*qfont01);
    qcombobox01->setFont(*qfont02);
    qcombobox01->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qcombobox01->clear();
    query->exec(sqlgroup->at(0));
    if(!query->next()) {
        qcombobox01->addItem("暂无");
        *Rsearchingproductcategory = "暂无";
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
        *Rsearchingproductcategory = qcombobox01->currentText();
    }
    // 填充内容******************************************************************************
    // 库存类别*****************************************************************************
    // 库存名称*****************************************************************************
    // 样式**********************************************************************************
    qlabel02->setFont(*qfont01);
    qcombobox02->setFont(*qfont02);
    qcombobox02->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qcombobox02->clear();
    query->prepare(sqlgroup->at(1));
    query->addBindValue(*Rsearchingproductcategory);
    query->exec();
    if(*Rsearchingproductcategory == "不选择") {
        qcombobox02->addItem("不选择");
        *Rsearchingproductname = qcombobox02->currentText();
    } else if(!query->next()) {
        qcombobox02->addItem("暂无");
        *Rsearchingproductname = qcombobox02->currentText();
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
        *Rsearchingproductname = qcombobox02->currentText();
    }
    // 填充内容******************************************************************************
    // 库存名称*****************************************************************************
    leftzonerow1->addWidget(qlabel01);
    leftzonerow1->addWidget(qcombobox01, 1);
    leftzonerow2->addWidget(qlabel02);
    leftzonerow2->addWidget(qcombobox02, 1);
    leftzone->addLayout(leftzonerow1);
    leftzone->addLayout(leftzonerow2);
    leftzone->setSpacing(8);
    leftzone->setContentsMargins(QMargins(0, 4, 0, 4));
    zone->addLayout(leftzone);
    // 左区域********************************************************************************

    // 右区域*******************************************************************************
    // 存放位置*****************************************************************************
    // 样式**********************************************************************************
    qlabel03->setFont(*qfont01);
    qcombobox03->setFont(*qfont02);
    qcombobox03->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qcombobox03->clear();
    query->prepare(sqlgroup->at(2));
    query->addBindValue(*Rsearchingproductcategory);
    query->addBindValue(*Rsearchingproductname);
    query->exec();
    if(*Rsearchingproductname == "不选择") {
        qcombobox03->addItem("不选择");
        *Rsearchingrepo = "不选择";
    } else if(!query->next()) {
        qcombobox03->addItem("暂无");
        *Rsearchingrepo = "暂无";
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
        *Rsearchingrepo = qcombobox03->currentText();
    }
    // 填充内容******************************************************************************
    // 存放位置*****************************************************************************
    qpushbutton01->setFont(*qfont01);
    qpushbutton02->setFont(*qfont01);
    rightzonerow1->addWidget(qlabel03);
    rightzonerow1->addWidget(qcombobox03, 1);
    rightzonerow2->addWidget(qpushbutton01);
    rightzonerow2->addWidget(qpushbutton02);
    rightzone->addLayout(rightzonerow1);
    rightzone->addLayout(rightzonerow2);
    rightzone->setSpacing(8);
    rightzone->setContentsMargins(QMargins(0, 4, 0, 4));
    zone->addLayout(rightzone);
    // 右区域********************************************************************************

    // 信号和槽函数*************************************************************************
    connect(qcombobox01, &QComboBox::currentTextChanged,
            this, &RepoSearch::onSearchingProductCategoryChanged);
    connect(qcombobox02, &QComboBox::currentTextChanged,
            this, &RepoSearch::onSearchingProductNameChanged);
    connect(qcombobox03, &QComboBox::currentTextChanged,
            this, &RepoSearch::onSearchingRepoChanged);
    connect(qpushbutton01, &QPushButton::pressed, this,
            &RepoSearch::SubmitResetOperation);
    connect(qpushbutton02, &QPushButton::pressed, this,
            &RepoSearch::SubmitSearchOperation);
    // 信号和槽函数*************************************************************************
}
RepoSearch::~RepoSearch() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete sqlgroup;
    // 删除new对象*************************************************************************
}
void RepoSearch::SubmitSearchOperation() {
    emit RefreshRepoTableSignal_DifferentSelect();
}
void RepoSearch::SubmitResetOperation() {
    emit RefreshRepoTableSignal();
    qcombobox01->setCurrentText("不选择");
    qcombobox02->setCurrentText("不选择");
    qcombobox03->setCurrentText("不选择");
}
void RepoSearch::onSearchingProductCategoryChanged(const QString &text) {
    // 记录更新******************************************************************************
    *Rsearchingproductcategory = text;
    // 记录更新******************************************************************************
    // 关信号********************************************************************************
    qcombobox02->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qcombobox02->clear();
    query->prepare(sqlgroup->at(1));
    query->addBindValue(*Rsearchingproductcategory);
    query->exec();
    if(*Rsearchingproductcategory == "不选择") {
        qcombobox02->addItem("不选择");
        *Rsearchingproductname = qcombobox02->currentText();
    } else if(!query->next()) {
        qcombobox02->addItem("暂无");
        *Rsearchingproductname = qcombobox02->currentText();
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
        *Rsearchingproductname = qcombobox02->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qcombobox02->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingProductNameChanged(*Rsearchingproductname);
    // 启槽函数******************************************************************************
}
void RepoSearch::onSearchingProductNameChanged(const QString &text) {
    // 记录更新******************************************************************************
    *Rsearchingproductname = text;
    // 记录更新******************************************************************************
    // 关信号********************************************************************************
    qcombobox03->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qcombobox03->clear();
    query->prepare(sqlgroup->at(2));
    query->addBindValue(*Rsearchingproductcategory);
    query->addBindValue(*Rsearchingproductname);
    query->exec();
    if(*Rsearchingproductname == "不选择") {
        qcombobox03->addItem("不选择");
        *Rsearchingrepo = "不选择";
    } else
    if(!query->next()) {
        qcombobox03->addItem("暂无");
        *Rsearchingrepo = "暂无";
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
        *Rsearchingrepo = qcombobox03->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qcombobox03->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingRepoChanged(*Rsearchingrepo);
    // 启槽函数******************************************************************************
}
void RepoSearch::onSearchingRepoChanged(const QString &text) {
    // 记录更新******************************************************************************
    *Rsearchingrepo = text;
    // 记录更新******************************************************************************
}
void RepoSearch::RefreshRepoSearchSlot() {
    // 关信号********************************************************************************
    qcombobox01->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qcombobox01->clear();
    query->exec(sqlgroup->at(0));
    if(!query->next()) {
        qcombobox01->addItem("暂无");
        *Rsearchingproductcategory = "暂无";
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
        *Rsearchingproductcategory = qcombobox01->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qcombobox01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onSearchingProductCategoryChanged(*Rsearchingproductcategory);
    // 启槽函数******************************************************************************
}
