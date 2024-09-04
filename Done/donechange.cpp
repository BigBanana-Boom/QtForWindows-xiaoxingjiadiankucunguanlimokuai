#include "donechange.h"

DoneChange::DoneChange(QWidget *parent, QSqlDatabase *db, QSqlQuery *query)
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
      qlabel01(new QLabel("待修改已定编号：", this)),
      qlabel02(new QLabel("待修改已定时间：", this)),
      qlabel03(new QLabel("待修改已定类别：", this)),
      qlabel04(new QLabel("待修改已定名称：", this)),
      qlabel05(new QLabel("待修改已定数量：", this)),
      qlabel06(new QLabel("修改后已定数量：", this)),
      qcombobox00(new QComboBox(this)),
      qreadonlylineedit01(new QLineEdit(this)),
      qreadonlylineedit02(new QLineEdit(this)),
      qreadonlylineedit03(new QLineEdit(this)),
      qreadonlylineedit04(new QLineEdit(this)),
      qspinbox01(new QSpinBox(this)),
      yeschange(new QPushButton("确定修改该记录", this)),
      db(db),
      query(query),
      sqlgroup(new QStringList()),
      currentID(new int),
      currentdatetime(new QDateTime()),
      currentproductcategory(new QString()),
      currentproductname(new QString()),
      currentproductnumber(new int),
      changedproductnumber(new int)
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT 已定编号 FROM 已定表 "
                     "ORDER BY 已定编号 DESC");
    /* ORDER BY 已定编号 DESC */
    sqlgroup->append("SELECT 已定时间 FROM 已定表 WHERE 已定编号 = ?");
    /* WHERE ...编号 = ?，很精确了，不用再排序 */
    sqlgroup->append("SELECT 已定类别 FROM 已定表 WHERE 已定编号 = ?");
    /* WHERE ...编号 = ?，很精确了，不用再排序 */
    sqlgroup->append("SELECT 已定名称 FROM 已定表 WHERE 已定编号 = ?");
    /* WHERE ...编号 = ?，很精确了，不用再排序 */
    sqlgroup->append("SELECT 已定数量 FROM 已定表 WHERE 已定编号 = ?");
    /* WHERE ...编号 = ?，很精确了，不用再排序 */
    sqlgroup->append("UPDATE 已定表 SET 已定数量 = ? WHERE 已定编号 = ?");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("WITH 临时表 AS (SELECT 库存类别, 库存名称, "
                     "SUM(存放数量) AS 存放数量_tmp "
                     "FROM 库存表 GROUP BY 库存类别, 库存名称) "
                     "SELECT 库存类别, 库存名称, 存放数量_tmp "
                     "FROM 临时表 WHERE 库存类别 = ? AND 库存名称 = ?");
    /* 不需要ORDER BY，因为只有一条记录 */
    // 数据库语句***************************************************************************

    // 左区域*******************************************************************************
    // 待修改已定编号***********************************************************************
    // 样式**********************************************************************************
    qlabel01->setFont(*qfont01);
    qcombobox00->setFont(*qfont02);
    qcombobox00->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qcombobox00->clear();
    query->exec(sqlgroup->at(0));
    if(!query->next()) {
        qcombobox00->addItem("暂无已定记录");
        *currentID = 0;
     } else {
        qcombobox00->addItem(query->value(0).toString());
        while (query->next()) {
            qcombobox00->addItem(query->value(0).toString());
        }
        *currentID = qcombobox00->currentText().toInt();
     }
    // 填充内容*****************************************************************************
    // 待修改已定编号***********************************************************************
    // 待修改已定时间***********************************************************************
    // 样式**********************************************************************************
    qlabel02->setFont(*qfont01);
    qreadonlylineedit01->setFont(*qfont02);
    qreadonlylineedit01->setReadOnly(true);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit01->clear();
    query->prepare(sqlgroup->at(1));
    query->addBindValue(*currentID);
    query->exec();
    if(*currentID == 0) {
        qreadonlylineedit01->setText(
                    QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        *currentdatetime = QDateTime::currentDateTime();
    } else {
        while(query->next()) {
            qreadonlylineedit01->setText(
                        query->value(0).toDateTime().toString("yyyy-MM-dd HH:mm:ss"));
            *currentdatetime = query->value(0).toDateTime();
        }
    }
    // 填充内容*****************************************************************************
    // 待修改已定时间***********************************************************************
    // 待修改已定类别***********************************************************************
    // 样式**********************************************************************************
    qlabel03->setFont(*qfont01);
    qreadonlylineedit02->setFont(*qfont02);
    qreadonlylineedit02->setReadOnly(true);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit02->clear();
    query->prepare(sqlgroup->at(2));
    query->addBindValue(*currentID);
    query->exec();
    if(*currentID == 0) {
        qreadonlylineedit02->setText("暂无已定记录");
        *currentproductcategory = "暂无已定记录";
    } else {
        while(query->next()) {
            qreadonlylineedit02->setText(query->value(0).toString());
            *currentproductcategory = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 待修改已定类别***********************************************************************
    // 待修改已定名称***********************************************************************
    // 样式**********************************************************************************
    qlabel04->setFont(*qfont01);
    qreadonlylineedit03->setFont(*qfont02);
    qreadonlylineedit03->setReadOnly(true);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit03->clear();
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*currentID);
    query->exec();
    if(*currentID == 0) {
        qreadonlylineedit03->setText("暂无已定记录");
        *currentproductname = "暂无已定记录";
    } else {
        while(query->next()) {
            qreadonlylineedit03->setText(query->value(0).toString());
            *currentproductname = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 待修改已定名称***********************************************************************
    // 左区域*******************************************************************************

    // 右区域*******************************************************************************
    // 待修改已定数量***********************************************************************
    // 样式**********************************************************************************
    qlabel05->setFont(*qfont01);
    qreadonlylineedit04->setFont(*qfont02);
    qreadonlylineedit04->setReadOnly(true);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit04->clear();
    query->prepare(sqlgroup->at(4));
    query->addBindValue(*currentID);
    query->exec();
    if(*currentID == 0) {
        qreadonlylineedit04->setText("暂无已定记录");
        *currentproductnumber = 0;
    } else {
        while(query->next()) {
            qreadonlylineedit04->setText(query->value(0).toString());
            *currentproductnumber = query->value(0).toInt();
        }
    }
    // 填充内容*****************************************************************************
    // 待修改已定数量***********************************************************************
    // 修改后已定数量***********************************************************************
    // 样式**********************************************************************************
    qlabel06->setFont(*qfont01);
    qspinbox01->setFont(*qfont02);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qspinbox01->clear();
    if(*currentID == 0) {
        qspinbox01->setMinimum(0);
        qspinbox01->setMaximum(0);
        qspinbox01->setValue(0);
        *changedproductnumber = 0;
    } else {
        qspinbox01->setMinimum(1);
        qspinbox01->setValue(*currentproductnumber);
        *changedproductnumber = *currentproductnumber;
    }
    // 填充内容*****************************************************************************
    // 修改后已定数量***********************************************************************
    // 修改提交按钮*************************************************************************
    yeschange->setFont(*qfont01);
    // 修改提交按钮*************************************************************************
    // 右区域*******************************************************************************

    // 总布局*******************************************************************************
    leftzonerow1->addWidget(qlabel01);
    leftzonerow1->addWidget(qcombobox00, 1);
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

    rightzonerow1->addWidget(qlabel05);
    rightzonerow1->addWidget(qreadonlylineedit04, 1);
    rightzonerow2->addWidget(qlabel06);
    rightzonerow2->addWidget(qspinbox01, 1);
    rightzonerow3->addWidget(yeschange);
    rightzone->addLayout(rightzonerow1);
    rightzone->addLayout(rightzonerow2);
    rightzone->addLayout(rightzonerow3);
    rightzone->addStretch(1);
    rightzone->setSpacing(8);
    rightzone->setContentsMargins(QMargins(0, 4, 0, 4));
    zone->addLayout(rightzone);
    // 总布局*******************************************************************************

    // 总区域*******************************************************************************
    mainLayout->addLayout(zone);
    ProcessTable();
    tableWidget01->resizeColumnsToContents();
    mainLayout->addWidget(tableWidget01);
    // 总区域*******************************************************************************

    // 信号与槽函数*************************************************************************
    connect(qcombobox00, &QComboBox::currentTextChanged,
            this, &DoneChange::onChangedIDChanged);
    using SpinBoxSignal = void (QSpinBox::*)(int);
    SpinBoxSignal spinBoxSignal = &QSpinBox::valueChanged;
    connect(qspinbox01, spinBoxSignal, this, &DoneChange::onChangedValueChanged);
    connect(yeschange, &QPushButton::clicked, this, &DoneChange::showMessage);
    // 信号与槽函数*************************************************************************
}
DoneChange::~DoneChange() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete sqlgroup;
    delete currentID;
    delete currentdatetime;
    delete currentproductnumber;
    delete currentproductcategory;
    delete currentproductname;
    delete changedproductnumber;
    // 删除new对象*************************************************************************
}
void DoneChange::onChangedIDChanged(const QString &text) {
    // 记录更新*****************************************************************************
    *currentID = text.toInt();
    // 记录更新*****************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit01->clear();
    query->prepare(sqlgroup->at(1));
    query->addBindValue(*currentID);
    query->exec();
    if(*currentID == 0) {
        qreadonlylineedit01->setText(
                    QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        *currentdatetime = QDateTime::currentDateTime();
    } else {
        while(query->next()) {
            qreadonlylineedit01->setText(
                        query->value(0).toDateTime().toString("yyyy-MM-dd HH:mm:ss"));
            *currentdatetime = query->value(0).toDateTime();
        }
    }
    // 填充内容*****************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit02->clear();
    query->prepare(sqlgroup->at(2));
    query->addBindValue(*currentID);
    query->exec();
    if(*currentID == 0) {
        qreadonlylineedit02->setText("暂无已定记录");
        *currentproductcategory = "暂无已定记录";
    } else {
        while(query->next()) {
            qreadonlylineedit02->setText(query->value(0).toString());
            *currentproductcategory = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit03->clear();
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*currentID);
    query->exec();
    if(*currentID == 0) {
        qreadonlylineedit03->setText("暂无已定记录");
        *currentproductname = "暂无已定记录";
    } else {
        while(query->next()) {
            qreadonlylineedit03->setText(query->value(0).toString());
            *currentproductname = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit04->clear();
    query->prepare(sqlgroup->at(4));
    query->addBindValue(*currentID);
    query->exec();
    if(*currentID == 0) {
        qreadonlylineedit04->setText("暂无已定记录");
        *currentproductnumber = 0;
    } else {
        while(query->next()) {
            qreadonlylineedit04->setText(query->value(0).toString());
            *currentproductnumber = query->value(0).toInt();
        }
    }
    // 填充内容*****************************************************************************
    // 关信号*******************************************************************************
    qspinbox01->blockSignals(true);
    // 关信号*******************************************************************************
    // 填充内容*****************************************************************************
    qspinbox01->clear();
    if(*currentID == 0) {
        qspinbox01->setMinimum(0);
        qspinbox01->setMaximum(0);
        qspinbox01->setValue(0);
        *changedproductnumber = 0;
    } else {
        qspinbox01->setMinimum(1);
        qspinbox01->setValue(*currentproductnumber);
        *changedproductnumber = *currentproductnumber;
    }
    // 填充内容*****************************************************************************
    // 开信号*******************************************************************************
    qspinbox01->blockSignals(false);
    // 开信号*******************************************************************************
    // 启槽函数*****************************************************************************
    onChangedValueChanged(*changedproductnumber);
    ProcessTable();
    // 启槽函数*****************************************************************************
}
void DoneChange::onChangedValueChanged(int value) {
    // 记录更新*****************************************************************************
    *changedproductnumber = value;
    // 记录更新*****************************************************************************
}
void DoneChange::ProcessTable() {
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
    tableWidget01->setColumnCount(3);
    query->prepare(sqlgroup->at(6));
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    query->exec();
    int row = 0;
    while (query->next()) {
        tableWidget01->insertRow(tableWidget01->rowCount());
        for(int i = 0; i < 3; i++) {
            QTableWidgetItem *item= new QTableWidgetItem(query->value(i).toString());
            item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
            tableWidget01->setItem(row, i, item);
        }
        ++row;
    }
    // 表格单元格***************************************************************************
    // 水平表头*****************************************************************************
    QStringList headers;
    headers << "库存类别" << "库存名称" << "库存存放数量";
    tableWidget01->setHorizontalHeaderLabels(headers);
    tableWidget01->horizontalHeader()->setFont(*qfont01);
    // 水平表头*****************************************************************************
    // 垂直表头*****************************************************************************
    tableWidget01->verticalHeader()->hide();
    // 垂直表头*****************************************************************************
    // 表属性*******************************************************************************
    tableWidget01->setFont(*qfont02);
    tableWidget01->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget01->resizeColumnsToContents();
    // 表属性*******************************************************************************
}
void DoneChange::showMessage()
{
    if(*currentID == 0) {
        // 新对象****************************************************************************
        simpledialog = new SimpleDialog(false, true, true, this);
        simpledialog->setDialogContent("已定表中暂无记录，无法修改");
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
    } else if (*currentproductnumber == *changedproductnumber) {
        // 新对象****************************************************************************
        simpledialog = new SimpleDialog(false, true, true, this);
        simpledialog->setDialogContent("已定表无变化，修改无效");
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
        donechangedialog = new DoneChangeDialog(false, true, true, this);
        donechangedialog->setDoneChangeID(QString::number(*currentID));
        donechangedialog->setDoneChangeDateTime(
                    currentdatetime->toString("yyyy-MM-dd hh:mm:ss"));
        donechangedialog->setDoneChangeCategory(*currentproductcategory);
        donechangedialog->setDoneChangeName(*currentproductname);
        donechangedialog->setDoneOriginalNumber(
                    QString::number(*currentproductnumber));
        donechangedialog->setDoneChangeNumber(
                    QString::number(*changedproductnumber));
        // 新对象****************************************************************************
        // 新对象的信号与槽*****************************************************************
        connect(donechangedialog, &DoneChangeDialog::accepted, this, [this]() {
            SubmitChangeOperation();
        });
        // 新对象的信号与槽*****************************************************************
        // 嗯，坏米饭************************************************************************
        // 调整位置**************************************************************************
        QRect parentGeometry = this->window()->window()->geometry();
        int dialogWidth = donechangedialog->width();
        int dialogHeight = donechangedialog->height();
        int x = (parentGeometry.width() - dialogWidth) / 2 + parentGeometry.x();
        int y = (parentGeometry.height() - dialogHeight) / 2 + parentGeometry.y();
        // 调整位置**************************************************************************
        // 移动对话框***********************************************************************
        donechangedialog->move(x, y);
        // 移动对话框***********************************************************************
        // 嗯，坏米饭************************************************************************
        donechangedialog->exec();
        delete donechangedialog;
    }
}
void DoneChange::SubmitChangeOperation() {
    // 更新数据表***************************************************************************
    // 更新已定表***************************************************************************
    query->prepare(sqlgroup->at(5));
    query->addBindValue(*changedproductnumber);
    query->addBindValue(*currentID);
    query->exec();
    // 更新已定表***************************************************************************
    // 更新数据表***************************************************************************
    // 放出信号******************************************************************************
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
    // 放出信号******************************************************************************
    // 更新自己**************************************************************************
    RefreshDoneChangeSlot();
    // 更新自己**************************************************************************
}
void DoneChange::RefreshDoneChangeSlot() {
    // 关信号****************************************************************************
    qcombobox00->blockSignals(true);
    // 关信号****************************************************************************
    // 填充内容*****************************************************************************
    qcombobox00->clear();
    query->exec(sqlgroup->at(0));
    if(!query->next()) {
        qcombobox00->addItem("暂无已定记录");
        *currentID = 0;
     } else {
        qcombobox00->addItem(query->value(0).toString());
        while (query->next()) {
            qcombobox00->addItem(query->value(0).toString());
        }
        *currentID = qcombobox00->currentText().toInt();
     }
    // 填充内容*****************************************************************************
    // 开信号****************************************************************************
    qcombobox00->blockSignals(false);
    // 开信号****************************************************************************
    // 启槽函数**************************************************************************
    onChangedIDChanged(QString::number(*currentID));
    // 启槽函数**************************************************************************
}
