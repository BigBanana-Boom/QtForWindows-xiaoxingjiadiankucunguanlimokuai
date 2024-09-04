/*
 *
 * on... Changed();不用连锁所有的
 * Refresh...();需要更新所有的
 *
 */
#include "outreporemove.h"

OutRepoRemove::OutRepoRemove(QWidget *parent,
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
      leftzonerow4(new QHBoxLayout()),
      rightzonerow1(new QHBoxLayout()),
      rightzonerow2(new QHBoxLayout()),
      rightzonerow3(new QHBoxLayout()),
      tableWidget01(new QTableWidget(this)),
      qlabel01(new QLabel("待删除出库编号：", this)),
      qlabel02(new QLabel("待删除出库时间：", this)),
      qlabel03(new QLabel("待删除出库类别：", this)),
      qlabel04(new QLabel("待删除出库名称：", this)),
      qlabel05(new QLabel("待删除出库位置：", this)),
      qlabel06(new QLabel("待删除出库数量：", this)),
      qcombobox01(new QComboBox(this)),
      searchbutton(new QPushButton(this)),
      qreadonlylineedit01(new QLineEdit(this)),
      qreadonlylineedit02(new QLineEdit(this)),
      qreadonlylineedit03(new QLineEdit(this)),
      qreadonlylineedit04(new QLineEdit(this)),
      qreadonlylineedit05(new QLineEdit(this)),
      yesremove(new QPushButton("确定删除该记录", this)),
      db(db),
      query(query),
      sqlgroup(new QStringList()),
      currentID(new int),
      currentdatetime(new QDateTime()),
      currentproductcategory(new QString()),
      currentproductname(new QString()),
      currentrepo(new QString()),
      currentproductnumber(new int)
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT 出库编号 FROM 出库表 "
                     "WHERE 出库时间 > ? ORDER BY 出库编号 DESC");
    /* ORDER BY 出库编号 DESC */
    sqlgroup->append("SELECT 出库时间 FROM 出库表 WHERE 出库编号 = ?");
    /* WHERE ...编号 = ?，很精确了，不用再排序 */
    sqlgroup->append("SELECT 出库类别 FROM 出库表 WHERE 出库编号 = ?");
    /* WHERE ...编号 = ?，很精确了，不用再排序 */
    sqlgroup->append("SELECT 出库名称 FROM 出库表 WHERE 出库编号 = ?");
    /* WHERE ...编号 = ?，很精确了，不用再排序 */
    sqlgroup->append("SELECT 出库位置 FROM 出库表 WHERE 出库编号 = ?");
    /* WHERE ...编号 = ?，很精确了，不用再排序 */
    sqlgroup->append("SELECT 出库数量 FROM 出库表 WHERE 出库编号 = ?");
    /* WHERE ...编号 = ?，很精确了，不用再排序 */
    sqlgroup->append("DELETE FROM 出库表 WHERE 出库编号 = ?");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("SELECT 存放数量 FROM 库存表 "
                     "WHERE 存放位置 = ? AND 库存类别 = ? AND 库存名称 = ?");
    /* 不需要ORDER BY，因为只有一条记录 */
    sqlgroup->append("INSERT INTO 库存表 (库存类别, 库存名称, 存放位置, 存放数量) "
                     "VALUES (?, ?, ?, ?)");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("UPDATE 库存表 SET 存放数量 = 存放数量 + ? "
                     "WHERE 存放位置 = ? AND 库存类别 = ? AND 库存名称 = ?");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("SELECT 库存类别, 库存名称, 存放位置, 存放数量 FROM 库存表 "
                     "WHERE 库存类别 = ? AND 库存名称 = ? AND 存放位置 = ?");
    /* 不需要ORDER BY，因为只有一条记录 */
    // 数据库语句***************************************************************************

    // 左区域*******************************************************************************
    // 待删除出库编号***********************************************************************
    // 样式**********************************************************************************
    qlabel01->setFont(*qfont01);
    qcombobox01->setFont(*qfont02);
    qcombobox01->setEditable(false);
    searchbutton->setIcon(QIcon(":/Image/search.png"));
    searchbutton->setIconSize(QSize(32, 32));
    searchbutton->setFixedSize(QSize(40, 40));
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qcombobox01->clear();
    query->prepare(sqlgroup->at(0));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-7));
    query->exec();
    if(!query->next()) {
        qcombobox01->addItem("暂无一周内出库记录");
        *currentID = 0;
    } else {
        qcombobox01->addItem(query->value(0).toString());
        while (query->next()) {
            qcombobox01->addItem(query->value(0).toString());
        }
        *currentID = qcombobox01->currentText().toInt();
    }
    // 填充内容*****************************************************************************
    // 待删除出库编号***********************************************************************
    // 待删除出库时间***********************************************************************
    // 样式**********************************************************************************
    qlabel02->setFont(*qfont01);
    qreadonlylineedit01->setFont(*qfont02);
    qreadonlylineedit01->setReadOnly(true);
    // 样式**********************************************************************************
    // 填充内容******************************************************************************
    qreadonlylineedit01->clear();
    if(*currentID == 0) {
        qreadonlylineedit01->setText(
                    QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        *currentdatetime = QDateTime::currentDateTime();
    } else {
        query->prepare(sqlgroup->at(1));
        query->addBindValue(*currentID);
        query->exec();
        while(query->next()) {
            qreadonlylineedit01->setText(
                        query->value(0).toDateTime().toString("yyyy-MM-dd HH:mm:ss"));
            *currentdatetime = query->value(0).toDateTime();
        }
    }
    // 填充内容******************************************************************************
    // 待删除出库时间***********************************************************************
    // 待删除出库类别***********************************************************************
    // 样式**********************************************************************************
    qlabel03->setFont(*qfont01);
    qreadonlylineedit02->setFont(*qfont02);
    qreadonlylineedit02->setReadOnly(true);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit02->clear();
    if(*currentID == 0) {
        qreadonlylineedit02->setText("暂无一周内出库记录");
        *currentproductcategory = "暂无一周内出库记录";
    } else {
        query->prepare(sqlgroup->at(2));
        query->addBindValue(*currentID);
        query->exec();
        while(query->next()) {
            qreadonlylineedit02->setText(query->value(0).toString());
            *currentproductcategory = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 待删除出库类别***********************************************************************
    // 待删除出库名称***********************************************************************
    // 样式**********************************************************************************
    qlabel04->setFont(*qfont01);
    qreadonlylineedit03->setFont(*qfont02);
    qreadonlylineedit03->setReadOnly(true);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit03->clear();
    if(*currentID == 0) {
        qreadonlylineedit03->setText("暂无一周内出库记录");
        *currentproductname = "暂无一周内出库记录";
    } else {
        query->prepare(sqlgroup->at(3));
        query->addBindValue(*currentID);
        query->exec();
        while(query->next()) {
            qreadonlylineedit03->setText(query->value(0).toString());
            *currentproductname = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 待删除出库名称***********************************************************************
    leftzonerow1->addWidget(qlabel01);
    leftzonerow1->addWidget(qcombobox01, 1);
    leftzonerow1->addWidget(searchbutton);
    leftzonerow2->addWidget(qlabel02);
    leftzonerow2->addWidget(qreadonlylineedit01, 1);
    leftzonerow3->addWidget(qlabel03);
    leftzonerow3->addWidget(qreadonlylineedit02, 1);
    leftzonerow4->addWidget(qlabel04);
    leftzonerow4->addWidget(qreadonlylineedit03, 1);
    leftzone->addLayout(leftzonerow1);
    leftzone->addLayout(leftzonerow2);
    leftzone->addLayout(leftzonerow3);
    leftzone->addLayout(leftzonerow4);
    leftzone->setSpacing(8);
    leftzone->setContentsMargins(QMargins(0, 4, 0, 4));
    zone->addLayout(leftzone);
    // 左区域********************************************************************************

    // 右区域********************************************************************************
    // 待删除出库位置***********************************************************************
    // 样式**********************************************************************************
    qlabel05->setFont(*qfont01);
    qreadonlylineedit04->setFont(*qfont02);
    qreadonlylineedit04->setReadOnly(true);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit04->clear();
    if(*currentID == 0) {
        qreadonlylineedit04->setText("暂无一周内出库记录");
        *currentrepo = "暂无一周内出库记录";
    } else {
        query->prepare(sqlgroup->at(4));
        query->addBindValue(*currentID);
        query->exec();
        while(query->next()) {
            qreadonlylineedit04->setText(query->value(0).toString());
            *currentrepo = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 待删除出库位置***********************************************************************
    // 待删除出库数量***********************************************************************
    // 样式**********************************************************************************
    qlabel06->setFont(*qfont01);
    qreadonlylineedit05->setFont(*qfont02);
    qreadonlylineedit05->setReadOnly(true);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit05->clear();
    if(*currentID == 0) {
        qreadonlylineedit05->setText("暂无一周内出库记录");
        *currentproductnumber = 0;
    } else {
        query->prepare(sqlgroup->at(5));
        query->addBindValue(*currentID);
        query->exec();
        while(query->next()) {
            qreadonlylineedit05->setText(query->value(0).toString());
            *currentproductnumber = query->value(0).toInt();
        }
    }
    // 填充内容*****************************************************************************
    // 待删除出库数量***********************************************************************
    yesremove->setFont(*qfont01);
    rightzonerow1->addWidget(qlabel05);
    rightzonerow1->addWidget(qreadonlylineedit04, 1);
    rightzonerow2->addWidget(qlabel06);
    rightzonerow2->addWidget(qreadonlylineedit05, 1);
    rightzonerow3->addWidget(yesremove);
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

    // 信号与槽****************************************************************************
    connect(searchbutton, &QPushButton::clicked,
            this, &OutRepoRemove::onSearchButtonClicked);
    connect(qcombobox01, &QComboBox::currentTextChanged,
            this, &OutRepoRemove::onCurrentIDChanged);
    connect(yesremove, &QPushButton::clicked,
            this, &OutRepoRemove::showMessage);
    // 信号与槽****************************************************************************
}
OutRepoRemove::~OutRepoRemove() {
    // 删除new对象************************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete sqlgroup;
    delete currentID;
    delete currentdatetime;
    delete currentproductcategory;
    delete currentproductname;
    delete currentrepo;
    delete currentproductnumber;
    // 删除new对象************************************************************************
}
void OutRepoRemove::onCurrentIDChanged(const QString &text) {
    // 记录更新*****************************************************************************
    *currentID = text.toInt();
    // 记录更新*****************************************************************************
    // 填充内容******************************************************************************
    qreadonlylineedit01->clear();
    if(*currentID == 0) {
        qreadonlylineedit01->setText(
                    QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        *currentdatetime = QDateTime::currentDateTime();
    } else {
        query->prepare(sqlgroup->at(1));
        query->addBindValue(*currentID);
        query->exec();
        while(query->next()) {
            qreadonlylineedit01->setText(
                        query->value(0).toDateTime().toString("yyyy-MM-dd HH:mm:ss"));
            *currentdatetime = query->value(0).toDateTime();
        }
    }
    // 填充内容******************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit02->clear();
    if(*currentID == 0) {
        qreadonlylineedit02->setText("暂无一周内出库记录");
        *currentproductcategory = "暂无一周内出库记录";
    } else {
        query->prepare(sqlgroup->at(2));
        query->addBindValue(*currentID);
        query->exec();
        while(query->next()) {
            qreadonlylineedit02->setText(query->value(0).toString());
            *currentproductcategory = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit03->clear();
    if(*currentID == 0) {
        qreadonlylineedit03->setText("暂无一周内出库记录");
        *currentproductname = "暂无一周内出库记录";
    } else {
        query->prepare(sqlgroup->at(3));
        query->addBindValue(*currentID);
        query->exec();
        while(query->next()) {
            qreadonlylineedit03->setText(query->value(0).toString());
            *currentproductname = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit04->clear();
    if(*currentID == 0) {
        qreadonlylineedit04->setText("暂无一周内出库记录");
        *currentrepo = "暂无一周内出库记录";
    } else {
        query->prepare(sqlgroup->at(4));
        query->addBindValue(*currentID);
        query->exec();
        while(query->next()) {
            qreadonlylineedit04->setText(query->value(0).toString());
            *currentrepo = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit05->clear();
    if(*currentID == 0) {
        qreadonlylineedit05->setText("暂无一周内出库记录");
        *currentproductnumber = 0;
    } else {
        query->prepare(sqlgroup->at(5));
        query->addBindValue(*currentID);
        query->exec();
        while(query->next()) {
            qreadonlylineedit05->setText(query->value(0).toString());
            *currentproductnumber = query->value(0).toInt();
        }
    }
    // 填充内容*****************************************************************************
    // 启槽函数*****************************************************************************
    ProcessTable();
    // 启槽函数*****************************************************************************
}
void OutRepoRemove::ProcessTable() {
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
    query->prepare(sqlgroup->at(10));
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
void OutRepoRemove::showMessage()
{
    if(*currentID == 0) {
        // 新对象****************************************************************************
        simpledialog = new SimpleDialog(false, true, true, this);
        simpledialog->setDialogContent("出库表中暂无一周内记录，无法删除");
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
        outreporemovedialog = new OutRepoRemoveDialog(false, true, true, this);
        outreporemovedialog->setOutRepoRemoveID(QString::number(*currentID));
        outreporemovedialog->setOutRepoRemoveDateTime(
                    currentdatetime->toString("yyyy-MM-dd hh:mm:ss"));
        outreporemovedialog->setOutRepoRemoveCategory(*currentproductcategory);
        outreporemovedialog->setOutRepoRemoveName(*currentproductname);
        outreporemovedialog->setOutRepoRemoveRepo(*currentrepo);
        outreporemovedialog->setOutRepoRemoveNumber(
                    QString::number(*currentproductnumber));
        // 新对象****************************************************************************
        // 新对象的信号与槽*****************************************************************
        connect(outreporemovedialog, &OutRepoRemoveDialog::accepted, this, [this]() {
            SubmitRemoveOperation();
        });
        // 新对象的信号与槽*****************************************************************
        // 嗯，坏米饭************************************************************************
        // 调整位置**************************************************************************
        QRect parentGeometry = this->window()->window()->geometry();
        int dialogWidth = outreporemovedialog->width();
        int dialogHeight = outreporemovedialog->height();
        int x = (parentGeometry.width() - dialogWidth) / 2 + parentGeometry.x();
        int y = (parentGeometry.height() - dialogHeight) / 2 + parentGeometry.y();
        // 调整位置**************************************************************************
        // 移动对话框***********************************************************************
        outreporemovedialog->move(x, y);
        // 移动对话框***********************************************************************
        // 嗯，坏米饭************************************************************************
        outreporemovedialog->exec();
        delete outreporemovedialog;
    }
}
void OutRepoRemove::SubmitRemoveOperation() {
    // 更新数据表***************************************************************************
    // 更新出库表***************************************************************************
    query->prepare(sqlgroup->at(6));
    query->addBindValue(*currentID);
    query->exec();
    // 更新出库表***************************************************************************
    // 更新库存表***************************************************************************
    query->prepare(sqlgroup->at(7));
    query->addBindValue(*currentrepo);
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    query->exec();
    if(!query->next()) {
        query->prepare(sqlgroup->at(8));
        query->addBindValue(*currentproductcategory);
        query->addBindValue(*currentproductname);
        query->addBindValue(*currentrepo);
        query->addBindValue(*currentproductnumber);
        query->exec();
        RefreshRepoTableID refreshid(db, query);
    } else {
        query->prepare(sqlgroup->at(9));
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
    // 放出信号*****************************************************************************
    // 更新自己****************************************************************************
    RefreshOutRepoRemoveSlot();
    // 更新自己****************************************************************************
}
void OutRepoRemove::RefreshOutRepoRemoveSlot() {
    // 关信号********************************************************************************
    qcombobox01->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容*****************************************************************************
    qcombobox01->clear();
    query->prepare(sqlgroup->at(0));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-7));
    query->exec();
    if(!query->next()) {
        qcombobox01->addItem("暂无一周内出库记录");
        *currentID = 0;
    } else {
        qcombobox01->addItem(query->value(0).toString());
        while (query->next()) {
            qcombobox01->addItem(query->value(0).toString());
        }
        *currentID = qcombobox01->currentText().toInt();
    }
    // 填充内容*****************************************************************************
    // 开信号********************************************************************************
    qcombobox01->blockSignals(false);
    // 开信号********************************************************************************
    // 启槽函数******************************************************************************
    onCurrentIDChanged(QString::number(*currentID));
    // 启槽函数******************************************************************************
}
void OutRepoRemove::onSearchButtonClicked() {
    // 新对象****************************************************************************
    searchdialog = new SearchDialog(true, true, true, this, db, query, returnid);
    searchdialog->setDialogTitle("删 除 出 库 · 查 找");
    searchdialog->setTableName("出库表");
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
    delete searchdialog;
}
