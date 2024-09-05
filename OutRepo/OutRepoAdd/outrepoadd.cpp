/*
 *
 * on... Changed();不用连锁所有的
 * Refresh...();需要更新所有的
 *
 */
#include "outrepoadd.h"

OutRepoAdd::OutRepoAdd(QWidget *parent,
                       QSqlDatabase *db,
                       QSqlQuery *query)
    : QWidget{parent},
    qfont01(new QFont("楷体", 16, QFont::Bold)),
    qfont02(new QFont("楷体", 16)),
    qfont03(new QFont("Microsoft YaHei", 8, QFont::Bold)),
    mainLayout(new QVBoxLayout(this)),
    zone(new QHBoxLayout()),
    leftzone(new QVBoxLayout()),
    leftzonerow1(new QHBoxLayout()),
    leftzonerow2(new QHBoxLayout()),
    leftzonerow3(new QHBoxLayout()),
    rightzone(new QVBoxLayout()),
    rightzonerow1(new QHBoxLayout()),
    rightzonerow2(new QHBoxLayout()),
    tableWidget01(new QTableWidget(this)),
    qlabel01(new QLabel("待新增出库类别：", this)),
    qlabel02(new QLabel("待新增出库名称：", this)),
    qlabel03(new QLabel("待新增出库位置：", this)),
    qlabel04(new QLabel("待新增出库数量：", this)),
    qcombobox01(new QComboBox(this)),
    searchbutton(new QPushButton(this)),
    qcombobox02(new QComboBox(this)),
    qcombobox03(new QComboBox(this)),
    qspinbox01(new QSpinBox(this)),
    qpushbutton01(new QPushButton("确定新增该记录", this)),
    db(db),
    query(query),
    sqlgroup(new QStringList()),
    currentdatetime(new QString(
                        QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))),
    currentproductcategory(new QString()),
    currentproductname(new QString()),
    currentrepo(new QString()),
    currentproductnumber(new int)
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT DISTINCT 库存类别 FROM 库存表");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT DISTINCT 库存名称 FROM 库存表 WHERE 库存类别 = ?");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT DISTINCT 存放位置 FROM 库存表 "
                     "WHERE 库存类别 = ? AND 库存名称 = ?");
    /* 放到QComboBox里面的中文字段，不需要ORDER BY，因为有其他过程会处理排序 */
    sqlgroup->append("SELECT 存放数量 FROM 库存表 "
                     "WHERE 存放位置 = ? AND 库存类别 = ? AND 库存名称 = ?");
    /* 不需要ORDER BY，因为只有一条记录 */
    sqlgroup->append("INSERT INTO 出库表 "
                     "(出库时间, 出库位置, 出库类别, 出库名称, 出库数量) "
                     "VALUES (?, ?, ?, ?, ?)");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("DELETE FROM 库存表 "
                     "WHERE 存放位置 = ? AND 库存类别 = ? AND 库存名称 = ?");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("UPDATE 库存表 SET 存放数量 = 存放数量 - ? "
                     "WHERE 存放位置 = ? AND 库存类别 = ? AND 库存名称 = ?");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("SELECT 库存类别, 库存名称, 存放位置, 存放数量 FROM 库存表 "
                     "WHERE 库存类别 = ? AND 库存名称 = ? AND 存放位置 = ?");
    /* 不需要ORDER BY，因为只有一条记录 */
    // 数据库语句***************************************************************************

    // 左区域*******************************************************************************
    // 待新增出库类别***********************************************************************
    // 样式**********************************************************************************
    qlabel01->setFont(*qfont01);
    qcombobox01->setFont(*qfont02);
    qcombobox01->setEditable(false);
    searchbutton->setIcon(QIcon(":/Image/search.png"));
    searchbutton->setIconSize(QSize(32, 32));
    searchbutton->setFixedSize(QSize(40, 40));
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
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
    // 填充内容******************************************************************************
    // 待新增出库类别***********************************************************************
    // 待新增出库名称***********************************************************************
    // 样式**********************************************************************************
    qlabel02->setFont(*qfont01);
    qcombobox02->setFont(*qfont02);
    qcombobox02->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
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
    // 填充内容******************************************************************************
    // 待新增出库名称***********************************************************************
    // 待新增出库位置***********************************************************************
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
        *currentrepo = "暂无";
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
        *currentrepo = qcombobox03->currentText();
    }
    // 填充内容******************************************************************************
    // 待新增出库位置***********************************************************************
    leftzonerow1->addWidget(qlabel01);
    leftzonerow1->addWidget(qcombobox01, 1);
    leftzonerow1->addWidget(searchbutton);
    leftzonerow2->addWidget(qlabel02);
    leftzonerow2->addWidget(qcombobox02, 1);
    leftzonerow3->addWidget(qlabel03);
    leftzonerow3->addWidget(qcombobox03, 1);
    leftzone->addLayout(leftzonerow1);
    leftzone->addLayout(leftzonerow2);
    leftzone->addLayout(leftzonerow3);
    leftzone->setSpacing(8);
    leftzone->setContentsMargins(QMargins(0, 4, 0, 4));
    zone->addLayout(leftzone, 1);
    // 左区域*******************************************************************************

    // 右区域*******************************************************************************
    // 待新增出库数量***********************************************************************
    // 样式**********************************************************************************
    qlabel04->setFont(*qfont01);
    qspinbox01->setFont(*qfont02);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qspinbox01->clear();
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*currentrepo);
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
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
    // 填充内容******************************************************************************
    // 待新增出库数量***********************************************************************
    qpushbutton01->setFont(*qfont01);
    qpushbutton01->setMinimumWidth(220);
    rightzonerow1->addWidget(qlabel04);
    rightzonerow1->addWidget(qspinbox01, 1);
    rightzonerow2->addWidget(qpushbutton01);
    rightzone->addLayout(rightzonerow1);
    rightzone->addLayout(rightzonerow2);
    rightzone->addStretch(1);
    zone->addLayout(rightzone, 1);
    rightzone->setSpacing(8);
    rightzone->setContentsMargins(QMargins(0, 4, 0, 4));
    // 右区域*******************************************************************************

    // 总区域*******************************************************************************
    mainLayout->addLayout(zone);
    ProcessTable();
    tableWidget01->resizeColumnsToContents();
    mainLayout->addWidget(tableWidget01);
    // 总区域*******************************************************************************

    // 信号和槽函数*************************************************************************
    connect(searchbutton, &QPushButton::clicked,
            this, &OutRepoAdd::onSearchButtonClicked);
    connect(qcombobox01, &QComboBox::currentTextChanged,
            this, &OutRepoAdd::onCurrentCategoryChanged);
    connect(qcombobox02, &QComboBox::currentTextChanged,
            this, &OutRepoAdd::onCurrentNameChanged);
    connect(qcombobox03, &QComboBox::currentTextChanged,
            this, &OutRepoAdd::onCurrentRepoChanged);
    using SpinBoxSignal = void (QSpinBox::*)(int);
    SpinBoxSignal spinBoxSignal = &QSpinBox::valueChanged;
    connect(qspinbox01, spinBoxSignal, this, &OutRepoAdd::onCurrentValueChanged);
    connect(qpushbutton01, &QPushButton::pressed, this, &OutRepoAdd::showMessage);
    // 信号和槽函数*************************************************************************
}
OutRepoAdd::~OutRepoAdd() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete sqlgroup;
    delete currentproductcategory;
    delete currentproductname;
    delete currentrepo;
    delete currentproductnumber;
    delete currentdatetime;
    // 删除new对象*************************************************************************
}
void OutRepoAdd::onCurrentCategoryChanged(const QString &text){
    // 记录更新*****************************************************************************
    *currentproductcategory = text;
    // 记录更新*****************************************************************************
    // 关信号********************************************************************************
    qcombobox02->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
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
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qcombobox02->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onCurrentNameChanged(*currentproductname);
    // 启槽函数******************************************************************************
}
void OutRepoAdd::onCurrentNameChanged(const QString &text) {
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
        *currentrepo = "暂无";
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
        *currentrepo = qcombobox03->currentText();
    }
    // 填充内容******************************************************************************
    // 开信号*******************************************************************************
    qcombobox03->blockSignals(false);
    // 开信号*******************************************************************************
    // 启槽函数*****************************************************************************
    onCurrentRepoChanged(*currentrepo);
    // 启槽函数*****************************************************************************
}
void OutRepoAdd::onCurrentRepoChanged(const QString &text) {
    // 记录更新******************************************************************************
    *currentrepo = text;
    // 记录更新******************************************************************************
    // 关信号********************************************************************************
    qspinbox01->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容******************************************************************************
    qspinbox01->clear();
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*currentrepo);
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
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
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qspinbox01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onCurrentValueChanged(*currentproductnumber);
    ProcessTable();
    // 启槽函数******************************************************************************
}
void OutRepoAdd::onCurrentValueChanged(int value) {
    *currentproductnumber = value;
}
void OutRepoAdd::ProcessTable() {
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
    // 表格单元格***************************************************************************
    tableWidget01->clear();
    tableWidget01->setRowCount(0);
    tableWidget01->setColumnCount(4);
    query->prepare(sqlgroup->at(7));
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    query->addBindValue(*currentrepo);
    query->exec();
    int row = 0;
    while (query->next()) {
        tableWidget01->insertRow(tableWidget01->rowCount());
        for(int i = 0; i < 4; i++) {
            QTableWidgetItem *item= new QTableWidgetItem(query->value(i).toString());
            item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
            tableWidget01->setItem(row, i, item);
        }
        ++row;
    }
    // 表格单元格***************************************************************************
    // 水平表头*****************************************************************************
    QStringList headers;
    headers<< "库存类别" << "库存名称" << "库存存放位置" << "库存存放数量";
    tableWidget01->setHorizontalHeaderLabels(headers);
    tableWidget01->horizontalHeader()->setFont(*qfont01);
    // 水平表头*****************************************************************************
    // 垂直表头*****************************************************************************
    tableWidget01->verticalHeader()->hide();
    // 垂直表头*****************************************************************************
    // 表属性*******************************************************************************
    tableWidget01->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget01->resizeColumnsToContents();
    tableWidget01->setFont(*qfont02);
    // 表属性*******************************************************************************
}

void OutRepoAdd::showMessage()
{
    query->exec(sqlgroup->at(0));
    if(!query->next()) {
        // 新对象****************************************************************************
        simpledialog = new SimpleDialog(false, true, true, this);
        simpledialog->setDialogContent("库存表中暂无记录，无法新增");
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
        outrepoadddialog = new OutRepoAddDialog(false, true, true, this);
        outrepoadddialog->setOutRepoAddCategory(*currentproductcategory);
        outrepoadddialog->setOutRepoAddName(*currentproductname);
        outrepoadddialog->setOutRepoAddRepo(*currentrepo);
        outrepoadddialog->setOutRepoAddNumber(
                    QString::number(*currentproductnumber));
        // 新对象****************************************************************************
        // 新对象的信号与槽*****************************************************************
        connect(outrepoadddialog, &OutRepoAddDialog::accepted, this, [this]() {
            SubmitAddOperation();
        });
        // 新对象的信号与槽*****************************************************************
        // 嗯，坏米饭************************************************************************
        // 调整位置**************************************************************************
        QRect parentGeometry = this->window()->window()->geometry();
        int dialogWidth = outrepoadddialog->width();
        int dialogHeight = outrepoadddialog->height();
        int x = (parentGeometry.width() - dialogWidth) / 2 + parentGeometry.x();
        int y = (parentGeometry.height() - dialogHeight) / 2 + parentGeometry.y();
        // 调整位置**************************************************************************
        // 移动对话框***********************************************************************
        outrepoadddialog->move(x, y);
        // 移动对话框***********************************************************************
        // 嗯，坏米饭************************************************************************
        outrepoadddialog->exec();
        delete outrepoadddialog;
    }
}
void OutRepoAdd::SubmitAddOperation() {
    // 更新数据表***************************************************************************
    // 更新出库表***************************************************************************
    query->prepare(sqlgroup->at(4));
    query->addBindValue(*currentdatetime);
    query->addBindValue(*currentrepo);
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    query->addBindValue(*currentproductnumber);
    query->exec();
    // 更新出库表***************************************************************************
    // 更新库存表***************************************************************************
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*currentrepo);
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    query->exec();
    query->next();
    if(*currentproductnumber == query->value(0).toInt()) {
        query->prepare(sqlgroup->at(5));
        query->addBindValue(*currentrepo);
        query->addBindValue(*currentproductcategory);
        query->addBindValue(*currentproductname);
        query->exec();
        RefreshRepoTableID refreshid(db, query);
    } else {
        query->prepare(sqlgroup->at(6));
        query->addBindValue(*currentproductnumber);
        query->addBindValue(*currentrepo);
        query->addBindValue(*currentproductcategory);
        query->addBindValue(*currentproductname);
        query->exec();
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
    RefreshOutRepoAddSlot();
    // 更新自己********************************************************************************
}
void OutRepoAdd::RefreshOutRepoAddSlot() {
    // 更新日期*****************************************************************************
    *currentdatetime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    // 更新日期*****************************************************************************
    // 关信号*******************************************************************************
    qcombobox01->blockSignals(true);
    // 关信号*******************************************************************************
    // 填充内容******************************************************************************
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
    // 填充内容******************************************************************************
    // 开信号********************************************************************************
    qcombobox01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onCurrentCategoryChanged(*currentproductcategory);
    // 启槽函数******************************************************************************
}
void OutRepoAdd::onSearchButtonClicked() {
    // 新对象****************************************************************************
    returnid = new int;
    searchdialog = new SearchDialog(true, true, true, this, db, query, returnid);
    searchdialog->setDialogTitle("新 增 出 库 · 查 找");
    searchdialog->setTableName("库存表");
    // 新对象****************************************************************************
    // 嗯，坏米饭************************************************************************
    // 调整位置**************************************************************************
    QRect parentGeometry = this->window()->window()->geometry();
    int dialogWidth = searchdialog->width();
    int dialogHeight = searchdialog->height();
    int x = (parentGeometry.width() - dialogWidth) / 2 + parentGeometry.x();
    int y = (parentGeometry.height() - dialogHeight) / 2 + parentGeometry.y();
    // 调整位置**************************************************************************
    // 移动对话框***********************************************************************
    searchdialog->move(x, y);
    // 移动对话框***********************************************************************
    // 嗯，坏米饭************************************************************************
    searchdialog->exec();
    delete returnid;
    delete searchdialog;
}
