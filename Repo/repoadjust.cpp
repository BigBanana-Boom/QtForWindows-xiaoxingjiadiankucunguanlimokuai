/*
 *
 * on... Changed();不用连锁所有的
 * Refresh...();需要更新所有的
 *
 */
#include "repoadjust.h"

RepoAdjust::RepoAdjust(QWidget *parent,
                       QSqlDatabase *db,
                       QSqlQuery *query)
    : QWidget(parent),
    qfont01(new QFont("楷体", 16, QFont::Bold)),
    qfont02(new QFont("楷体", 16)),
    qfont03(new QFont("Microsoft YaHei", 8, QFont::Bold)),
    mainLayout(new QVBoxLayout(this)),
    zone(new QHBoxLayout()),
    leftzone(new QVBoxLayout()),
    rightzone(new QVBoxLayout()),
    leftzonerow1(new QHBoxLayout()),
    leftzonerow2(new QHBoxLayout()),
    leftzonerow3(new QHBoxLayout()),
    rightzonerow1(new QHBoxLayout()),
    rightzonerow2(new QHBoxLayout()),
    rightzonerow3(new QHBoxLayout()),
    tableWidget01(new QTableWidget(this)),
    qlabel01(new QLabel("待转存库存类别：", this)),
    qlabel02(new QLabel("待转存库存名称：", this)),
    qlabel03(new QLabel("待转存库存旧位置：", this)),
    qlabel04(new QLabel("待转存库存新位置：", this)),
    qlabel05(new QLabel("待转存库存数量：", this)),
    qcombobox01(new QComboBox(this)),
    qcombobox02(new QComboBox(this)),
    qcombobox03(new QComboBox(this)),
    qcombobox04(new QComboBox(this)),
    qspinbox01(new QSpinBox(this)),
    yeschange(new QPushButton("确定转存该记录", this)),
    db(db),
    query(query),
    sqlgroup(new QStringList()),
    currentdatetime(new QString(
                        QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))),
    currentproductcategory(new QString()),
    currentproductname(new QString()),
    originalrepo(new QString()),
    laterrepo(new QString()),
    currentproductnumber(new int)
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT DISTINCT 库存类别 FROM 库存表");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT DISTINCT 库存名称 FROM 库存表 WHERE 库存类别 = ?");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT 存放位置 FROM 库存表 "
                     "WHERE 库存类别 = ? AND 库存名称 = ?");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT 仓库名称 FROM 附表1仓库信息表 WHERE 仓库名称 != ?");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT 存放数量 FROM 库存表 "
                     "WHERE 库存类别 = ? AND 库存名称 = ? AND 存放位置 = ?");
    /* 不需要ORDER BY，因为只有一条记录 */
    sqlgroup->append("SELECT 库存类别, 库存名称, 存放位置, 存放数量 FROM 库存表 "
                     "WHERE 库存类别 = ? AND 库存名称 = ? AND "
                     "(存放位置 = ? OR 存放位置 = ?) "
                     "ORDER BY 存放位置");
    /* ORDER BY 存放位置 */
    sqlgroup->append("INSERT INTO 附表3库存调整表 "
                     "(调库时间, 库存位置, 库存类别, 库存名称, 库存变化) "
                     "VALUES (?, ?, ?, ?, ?)");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("UPDATE 库存表 SET 存放数量 = 存放数量 - ? "
                     "WHERE 库存类别 = ? AND 库存名称 = ? AND 存放位置 = ?");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("DELETE FROM 库存表 WHERE 库存类别 = ? "
                     "AND 库存名称 = ? AND 存放位置 = ?");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("UPDATE 库存表 SET 存放数量 = 存放数量 + ? "
                     "WHERE 库存类别 = ? AND 库存名称 = ? AND 存放位置 = ?");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("INSERT INTO 库存表 (库存类别, 库存名称, 存放位置, 存放数量) "
                     "VALUES (?, ?, ?, ?)");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("SELECT * FROM 库存表 LIMIT 1");
    /* 只是检验表是否为空，没有多大实际意义 */
    // 数据库语句***************************************************************************

    // 左区域*******************************************************************************
    // 待转存库存类别***********************************************************************
    // 样式**********************************************************************************
    qlabel01->setFont(*qfont01);
    qcombobox01->setFont(*qfont02);
    qcombobox01->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qcombobox01->clear();
    query->exec(sqlgroup->at(0));
    if(!query->next()) {
        qcombobox01->addItem("暂无");
        *currentproductcategory = "暂无";
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
        *currentproductcategory = qcombobox01->currentText();
    }
    // 填充内容*****************************************************************************
    // 待转存库存类别***********************************************************************
    // 待转存库存名称***********************************************************************
    // 样式**********************************************************************************
    qlabel02->setFont(*qfont01);
    qcombobox02->setFont(*qfont02);
    qcombobox02->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qcombobox02->clear();
    query->prepare(sqlgroup->at(1));
    query->addBindValue(*currentproductcategory);
    query->exec();
    if(!query->next()) {
        qcombobox02->addItem("暂无");
        *currentproductname = "暂无";
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
        *currentproductname = qcombobox02->currentText();
    }
    // 填充内容*****************************************************************************
    // 待转存库存名称***********************************************************************
    // 待转存库存旧位置*********************************************************************
    // 样式**********************************************************************************
    qlabel03->setFont(*qfont01);
    qcombobox03->setFont(*qfont02);
    qcombobox03->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qcombobox03->clear();
    query->prepare(sqlgroup->at(2));
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    query->exec();
    if(!query->next()) {
        qcombobox03->addItem("暂无");
        *originalrepo = "暂无";
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
        *originalrepo = qcombobox03->currentText();
    }
    // 填充内容******************************************************************************
    // 待转存库存旧位置*********************************************************************
    leftzonerow1->addWidget(qlabel01);
    leftzonerow1->addWidget(qcombobox01, 1);
    leftzonerow2->addWidget(qlabel02);
    leftzonerow2->addWidget(qcombobox02, 1);
    leftzonerow3->addWidget(qlabel03);
    leftzonerow3->addWidget(qcombobox03, 1);
    leftzone->addLayout(leftzonerow1);
    leftzone->addLayout(leftzonerow2);
    leftzone->addLayout(leftzonerow3);
    leftzone->setSpacing(8);
    leftzone->setContentsMargins(QMargins(0, 4, 0, 4));
    zone->addLayout(leftzone);
    // 左区域*******************************************************************************

    // 右区域*******************************************************************************
    // 待转存库存新位置*********************************************************************
    // 样式**********************************************************************************
    qlabel04->setFont(*qfont01);
    qcombobox04->setFont(*qfont02);
    qcombobox04->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qcombobox04->clear();
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*originalrepo);
    query->exec();
    if(!query->next()) {
        qcombobox04->addItem("暂无");
        *laterrepo = "暂无";
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
            qcombobox04->addItem(stringList.at(i));
        }
        *laterrepo = qcombobox04->currentText();
    }
    // 填充内容******************************************************************************
    // 待转存库存新位置*********************************************************************
    // 待修改存放数量***********************************************************************
    // 样式**********************************************************************************
    qlabel05->setFont(*qfont01);
    qspinbox01->setFont(*qfont02);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qspinbox01->clear();
    query->prepare(sqlgroup->at(4));
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    query->addBindValue(*originalrepo);
    query->exec();
    if(!query->next()) {
        qspinbox01->setMinimum(0);
        qspinbox01->setMaximum(0);
        qspinbox01->setValue(0);
        *currentproductnumber = 0;
    } else {
        qspinbox01->setMinimum(1);
        qspinbox01->setMaximum(query->value(0).toInt());
        qspinbox01->setValue(query->value(0).toInt());
        *currentproductnumber = qspinbox01->value();
    }
    // 填充内容*****************************************************************************
    // 待修改存放数量***********************************************************************
    // 修改提交按钮*************************************************************************
    yeschange->setFont(*qfont01);
    // 修改提交按钮*************************************************************************
    rightzonerow1->addWidget(qlabel04);
    rightzonerow1->addWidget(qcombobox04, 1);
    rightzonerow2->addWidget(qlabel05);
    rightzonerow2->addWidget(qspinbox01, 1);
    rightzonerow3->addWidget(yeschange);
    rightzone->addLayout(rightzonerow1);
    rightzone->addLayout(rightzonerow2);
    rightzone->addLayout(rightzonerow3);
    rightzone->addStretch(1);
    rightzone->setSpacing(8);
    rightzone->setContentsMargins(QMargins(0, 4, 0, 4));
    zone->addLayout(rightzone);
    // 右区域*******************************************************************************

    // 总区域*******************************************************************************
    mainLayout->addLayout(zone);
    ProcessTable();
    tableWidget01->resizeColumnsToContents();
    mainLayout->addWidget(tableWidget01);
    // 总区域*******************************************************************************

    // 信号与槽函数*************************************************************************
    connect(qcombobox01, &QComboBox::currentTextChanged,
            this, &RepoAdjust::onCurrentCategoryChanged);
    connect(qcombobox02, &QComboBox::currentTextChanged,
            this, &RepoAdjust::onCurrentNameChanged);
    connect(qcombobox03, &QComboBox::currentTextChanged,
            this, &RepoAdjust::onOriginalRepoChanged);
    connect(qcombobox04, &QComboBox::currentTextChanged,
            this, &RepoAdjust::onLaterRepoChanged);
    using SpinBoxSignal = void (QSpinBox::*)(int);
    SpinBoxSignal spinBoxSignal = &QSpinBox::valueChanged;
    connect(qspinbox01, spinBoxSignal, this, &RepoAdjust::onCurrentValueChanged);
    connect(yeschange, &QPushButton::clicked, this, &RepoAdjust::showMessage);
    connect(tableWidget01->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &RepoAdjust::selectColumnOnHeaderClick);
    // 信号与槽函数*************************************************************************
}
RepoAdjust::~RepoAdjust() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete sqlgroup;
    delete currentdatetime;
    delete currentproductcategory;
    delete currentproductname;
    delete originalrepo;
    delete laterrepo;
    delete currentproductnumber;
    // 删除new对象*************************************************************************
}
void RepoAdjust::onCurrentCategoryChanged(const QString &text) {
    // 记录更新*****************************************************************************
    *currentproductcategory = text;
    // 记录更新*****************************************************************************
    // 关信号********************************************************************************
    qcombobox02->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容*****************************************************************************
    qcombobox02->clear();
    query->prepare(sqlgroup->at(1));
    query->addBindValue(*currentproductcategory);
    query->exec();
    if(!query->next()) {
        qcombobox02->addItem("暂无");
        *currentproductname = "暂无";
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
        *currentproductname = qcombobox02->currentText();
    }
    // 填充内容*****************************************************************************
    // 开信号********************************************************************************
    qcombobox02->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onCurrentNameChanged(*currentproductname);
    // 启槽函数******************************************************************************
}
void RepoAdjust::onCurrentNameChanged(const QString &text) {
    // 记录更新*****************************************************************************
    *currentproductname = text;
    // 记录更新*****************************************************************************
    // 关信号*******************************************************************************
    qcombobox03->blockSignals(true);
    // 关信号*******************************************************************************
    // 填充内容******************************************************************************
    qcombobox03->clear();
    query->prepare(sqlgroup->at(2));
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    query->exec();
    if(!query->next()) {
        qcombobox03->addItem("暂无");
        *originalrepo = "暂无";
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
        *originalrepo = qcombobox03->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号*******************************************************************************
    qcombobox03->blockSignals(false);
    // 开信号*******************************************************************************
    // 启槽函数*****************************************************************************
    onOriginalRepoChanged(*originalrepo);
    // 启槽函数*****************************************************************************
}
void RepoAdjust::onOriginalRepoChanged(const QString &text) {
    // 记录更新*****************************************************************************
    *originalrepo = text;
    // 记录更新*****************************************************************************
    // 关信号*******************************************************************************
    qcombobox04->blockSignals(true);
    // 关信号*******************************************************************************
    // 填充内容******************************************************************************
    qcombobox04->clear();
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*originalrepo);
    query->exec();
    if(!query->next()) {
        qcombobox04->addItem("暂无");
        *laterrepo = "暂无";
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
            qcombobox04->addItem(stringList.at(i));
        }
        *laterrepo = qcombobox04->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号*******************************************************************************
    qcombobox04->blockSignals(false);
    // 开信号*******************************************************************************
    // 启槽函数*****************************************************************************
    onLaterRepoChanged(*laterrepo);
    // 启槽函数*****************************************************************************
    // 关信号*******************************************************************************
    qspinbox01->blockSignals(true);
    // 关信号*******************************************************************************
    // 开信号*******************************************************************************
    qspinbox01->blockSignals(false);
    // 开信号*******************************************************************************
    // 填充内容*****************************************************************************
    qspinbox01->clear();
    query->prepare(sqlgroup->at(4));
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    query->addBindValue(*originalrepo);
    query->exec();
    if(!query->next()) {
        qspinbox01->setMinimum(0);
        qspinbox01->setMaximum(0);
        qspinbox01->setValue(0);
        *currentproductnumber = 0;
    } else {
        qspinbox01->setMinimum(1);
        qspinbox01->setMaximum(query->value(0).toInt());
        qspinbox01->setValue(query->value(0).toInt());
        *currentproductnumber = qspinbox01->value();
    }
    // 填充内容*****************************************************************************
    // 启槽函数*****************************************************************************
    onCurrentValueChanged(*currentproductnumber);
    // 启槽函数*****************************************************************************
}
void RepoAdjust::onLaterRepoChanged(const QString &text) {
    // 记录更新*****************************************************************************
    *laterrepo = text;
    // 记录更新*****************************************************************************
    // 启槽函数*****************************************************************************
    ProcessTable();
    // 启槽函数*****************************************************************************
}
void RepoAdjust::onCurrentValueChanged(int value) {
    // 记录更新*****************************************************************************
    *currentproductnumber = value;
    // 记录更新*****************************************************************************
}
void RepoAdjust::ProcessTable() {
    // 清理以防止内存泄漏******************************************************************
    for (int row = 0; row < tableWidget01->rowCount(); ++row) {
        for (int col = 0; col < tableWidget01->columnCount(); ++col) {
            // 取出项**************************************************************************
            QTableWidgetItem* item = tableWidget01->takeItem(row, col);
            // 取出项**************************************************************************
            if (item) {
                // 删除项，释放内存************************************************************
                delete item;
                // 删除项，释放内存************************************************************
            }
        }
    }
    // 清理以防止内存泄漏******************************************************************
    // 表格初始化***************************************************************************
    tableWidget01->clear();
    tableWidget01->setSortingEnabled(false);
    tableWidget01->setRowCount(0);
    tableWidget01->setColumnCount(4);
    // 表格初始化***************************************************************************
    // 表格单元格***************************************************************************
    query->prepare(sqlgroup->at(5));
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    query->addBindValue(*originalrepo);
    query->addBindValue(*laterrepo);
    query->exec();
    int row = 0;
    while (query->next()) {
        tableWidget01->insertRow(tableWidget01->rowCount());
        for(int i = 0; i < 4; i++) {
            if(i == 3) {
                int value = query->value(i).toInt();
                QTableWidgetItem *item= new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                item->setData(Qt::DisplayRole, value);
                tableWidget01->setItem(row, i, item);
            } else {
                QTableWidgetItem *item =
                        new QTableWidgetItem(query->value(i).toString());
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                tableWidget01->setItem(row, i, item);
            }
        }
        ++row;
    }
    // 表格单元格***************************************************************************
    // 水平表头*****************************************************************************
    QStringList headers;
    headers<< "库存类别" << "库存名称" << "库存存放位置" << "库存存放数量";
    tableWidget01->setHorizontalHeaderLabels(headers);
    headerView01_row = tableWidget01->horizontalHeader();
    headerView01_row->setFont(*qfont01);
    headerView01_row->setStyleSheet("");
    headerView01_row->setStyleSheet(
                "QHeaderView::up-arrow {image: none;}"
                "QHeaderView::down-arrow {image: none;}");
    // 水平表头*****************************************************************************
    // 垂直表头*****************************************************************************
    headerView01_column = tableWidget01->verticalHeader();
    headerView01_column->hide();
    // 垂直表头*****************************************************************************
    // 表属性*******************************************************************************
    tableWidget01->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget01->resizeColumnsToContents();
    tableWidget01->setFont(*qfont02);
    tableWidget01->setSortingEnabled(true);
    // 表属性*******************************************************************************
}
void RepoAdjust::showMessage()
{
    query->exec(sqlgroup->at(11));
    if(!query->next()) {
        // 新对象****************************************************************************
        simpledialog = new SimpleDialog(false, true, true, this);
        simpledialog->setDialogContent("库存表中暂无记录，无法转存");
        // 新对象****************************************************************************
        // 嗯，坏米饭************************************************************************
        // 调整位置**************************************************************************
        QRect parentGeometry = this->window()->window()->geometry();
        int dialogWidth = simpledialog->width();
        int dialogHeight = simpledialog->height();
        int x = (parentGeometry.width() - dialogWidth) / 2 + parentGeometry.x();
        int y = (parentGeometry.height() - dialogHeight) / 2 + parentGeometry.y();
        // 调整位置**************************************************************************
        // 移动对话框***********************************************************************
        simpledialog->move(x, y);
        // 移动对话框***********************************************************************
        // 嗯，坏米饭************************************************************************
        simpledialog->exec();
        delete simpledialog;
    } else {
        // 新对象****************************************************************************
        repoadjustdialog = new RepoAdjustDialog(false, true, true, this);
        repoadjustdialog->setRepoAdjustCategory(*currentproductcategory);
        repoadjustdialog->setRepoAdjustName(*currentproductname);
        repoadjustdialog->setRepoAdjustOldRepo(*originalrepo);
        repoadjustdialog->setRepoAdjustNewRepo(*laterrepo);
        repoadjustdialog->setRepoAdjustNumber(
                    QString::number(*currentproductnumber));
        // 新对象****************************************************************************
        // 新对象的信号与槽*****************************************************************
        connect(repoadjustdialog, &RepoAdjustDialog::accepted, this, [this]() {
            SubmitAdjustOperation();
        });
        // 新对象的信号与槽*****************************************************************
        // 嗯，坏米饭************************************************************************
        // 调整位置**************************************************************************
        QRect parentGeometry = this->window()->window()->geometry();
        int dialogWidth = repoadjustdialog->width();
        int dialogHeight = repoadjustdialog->height();
        int x = (parentGeometry.width() - dialogWidth) / 2 + parentGeometry.x();
        int y = (parentGeometry.height() - dialogHeight) / 2 + parentGeometry.y();
        // 调整位置**************************************************************************
        // 移动对话框***********************************************************************
        repoadjustdialog->move(x, y);
        // 移动对话框***********************************************************************
        // 嗯，坏米饭************************************************************************
        repoadjustdialog->exec();
        delete repoadjustdialog;
    }
}
void RepoAdjust::SubmitAdjustOperation() {
    // 更新数据表***************************************************************************
    // 更新调库表***************************************************************************
    query->prepare(sqlgroup->at(6));
    query->addBindValue(*currentdatetime);
    query->addBindValue(*originalrepo);
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    QString result;
    QTextStream stream(&result);
    stream << "-" << *currentproductnumber;
    query->addBindValue(result);
    query->exec();

    query->prepare(sqlgroup->at(6));
    query->addBindValue(*currentdatetime);
    query->addBindValue(*laterrepo);
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    result = "";
    stream << "+" << *currentproductnumber;
    query->addBindValue(result);
    query->exec();
    // 更新调库表***************************************************************************
    // 更新库存表***************************************************************************
    query->prepare(sqlgroup->at(4));
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    query->addBindValue(*originalrepo);
    query->exec(); query->next();
    int originalnumber = query->value(0).toInt();
    if(originalnumber > *currentproductnumber) {
        query->prepare(sqlgroup->at(7));
        query->addBindValue(*currentproductnumber);
        query->addBindValue(*currentproductcategory);
        query->addBindValue(*currentproductname);
        query->addBindValue(*originalrepo);
    } else if(originalnumber == *currentproductnumber) {
        query->prepare(sqlgroup->at(8));
        query->addBindValue(*currentproductcategory);
        query->addBindValue(*currentproductname);
        query->addBindValue(*originalrepo);
    }
    query->prepare(sqlgroup->at(4));
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    query->addBindValue(*laterrepo);
    query->exec();
    if(query->next()) {
        query->prepare(sqlgroup->at(9));
        query->addBindValue(*currentproductnumber);
        query->addBindValue(*currentproductcategory);
        query->addBindValue(*currentproductname);
        query->addBindValue(*laterrepo);
    } else {
        query->prepare(sqlgroup->at(10));
        query->addBindValue(*currentproductnumber);
        query->addBindValue(*currentproductcategory);
        query->addBindValue(*currentproductname);
        query->addBindValue(*laterrepo);
    }
    // 更新库存表***************************************************************************
    // 更新数据表***************************************************************************
    // 放出信号*****************************************************************************
    // mainwindow下的done, outrepo, inrepo, repo, repoinfo, inrepoinfo表级信号
    emit RefreshDoneTableSignal();
    emit RefreshOutRepoTableSignal();
    emit RefreshInRepoTableSignal();
    emit RefreshRepoTableSignal();
    emit RefreshRepoInfoTableSignal();
    emit RefreshInRepoInfoTableSignal();
    // mainwindow下的done, outrepo, inrepo, repo, repoinfo, inrepoinfo表级信号
    // done下的doneadd, doneremove, donechange, donesearch窗口信号
    emit RefreshDoneAddSignal();
    emit RefreshDoneRemoveSignal();
    emit RefreshDoneChangeSignal();
    emit RefreshDoneSearchSignal();
    // done下的doneadd, doneremove, donechange, donesearch窗口信号
    // outrepo下的outrepoadd, outreporemove, outrepochange, outreposearch窗口信号
    emit RefreshOutRepoAddSignal();
    emit RefreshOutRepoRemoveSignal();
    emit RefreshOutRepoChangeSignal();
    emit RefreshOutRepoSearchSignal();
    // outrepo下的outrepoadd, outreporemove, outrepochange, outreposearch窗口信号
    // inrepo下的inrepoadd, inreporemove, inrepochange, inreposearch窗口信号
    emit RefreshInRepoAddSignal();
    emit RefreshInRepoRemoveSignal();
    emit RefreshInRepoChangeSignal();
    emit RefreshInRepoSearchSignal();
    // inrepo下的inrepoadd, inreporemove, inrepochange, inreposearch窗口信号
    // repo下的repoadd, reporemove, repochange, reposearch窗口信号
    emit RefreshRepoAddSignal();
    emit RefreshRepoRemoveSignal();
    emit RefreshRepoChangeSignal();
    emit RefreshRepoSearchSignal();
    // repo下的repoadd, reporemove, repochange, reposearch窗口信号
    // 放出信号*********************************************************************************
    // 更新自己********************************************************************************
    RefreshRepoAdjustSlot();
    // 更新自己********************************************************************************
}
void RepoAdjust::RefreshRepoAdjustSlot() {
    // 更新日期*****************************************************************************
    *currentdatetime = QDateTime::currentDateTime()
            .toString("yyyy-MM-dd hh:mm:ss");
    // 更新日期*****************************************************************************
    // 关信号*******************************************************************************
    qcombobox01->blockSignals(true);
    // 关信号*******************************************************************************
    // 填充内容*****************************************************************************
    qcombobox01->clear();
    query->exec(sqlgroup->at(0));
    if(!query->next()) {
        qcombobox01->addItem("暂无");
        *currentproductcategory = "暂无";
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
        *currentproductcategory = qcombobox01->currentText();
    }
    // 填充内容*****************************************************************************
    // 开信号********************************************************************************
    qcombobox01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onCurrentCategoryChanged(*currentproductcategory);
    // 启槽函数******************************************************************************
}
void RepoAdjust::selectColumnOnHeaderClick(int column) {
    tableWidget01->clearSelection();
    for (int row = 0; row < tableWidget01->rowCount(); ++row)
    {
        tableWidget01->item(row, column)->setSelected(true);
    }
}
