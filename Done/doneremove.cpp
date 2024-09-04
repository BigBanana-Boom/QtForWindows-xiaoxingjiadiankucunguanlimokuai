#include "doneremove.h"

DoneRemove::DoneRemove(QWidget *parent, QSqlDatabase *db, QSqlQuery *query)
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
      qlabel01(new QLabel("待删除已定编号：", this)),
      qlabel02(new QLabel("待删除已定时间：", this)),
      qlabel03(new QLabel("待删除已定类别：", this)),
      qlabel04(new QLabel("待删除已定名称：", this)),
      qlabel05(new QLabel("待删除已定数量：", this)),
      qcombobox01(new QComboBox(this)),
      qreadonlylineedit01(new QLineEdit(this)),
      qreadonlylineedit02(new QLineEdit(this)),
      qreadonlylineedit03(new QLineEdit(this)),
      qreadonlylineedit04(new QLineEdit(this)),
      yesremove(new QPushButton("确定删除记录", this)),
      yesremoveandoutrepo(new QPushButton("出库并且删除", this)),
      db(db),
      query(query),
      sqlgroup(new QStringList()),
      currentID(new int),
      currentdatetime(new QDateTime()),
      currentproductcategory(new QString()),
      currentproductname(new QString()),
      currentproductnumber(new int)
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
    sqlgroup->append("DELETE FROM 已定表 WHERE 已定编号 = ?");
    sqlgroup->append("CREATE TABLE IF NOT EXISTS 临时已定表 ( "
                     "已定编号 INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "已定时间 DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP, "
                     "已定类别 TEXT NOT NULL, "
                     "已定名称 TEXT NOT NULL, "
                     "已定数量 INTEGER NOT NULL);");
    sqlgroup->append("INSERT INTO 临时已定表 "
                     "(已定时间, 已定类别, 已定名称, 已定数量) "
                     "SELECT 已定时间, 已定类别, 已定名称, 已定数量 "
                     "FROM 已定表");
    sqlgroup->append("DROP TABLE 已定表;");
    sqlgroup->append("ALTER TABLE 临时已定表 RENAME TO 已定表;");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("SELECT SUM(存放数量) AS 存放数量_tmp "
                     "FROM 库存表 WHERE 库存类别 = ? AND 库存名称 = ? "
                     "GROUP BY 库存类别, 库存名称");
    /* 不需要ORDER BY，因为只有一条记录 */
    sqlgroup->append("WITH 临时表 AS (SELECT 库存类别, 库存名称, "
                     "SUM(存放数量) AS 存放数量_tmp "
                     "FROM 库存表 GROUP BY 库存类别, 库存名称) "
                     "SELECT 库存类别, 库存名称, 存放数量_tmp "
                     "FROM 临时表 WHERE 库存类别 = ? AND 库存名称 = ?");
    /* 不需要ORDER BY，因为只有一条记录 */
    sqlgroup->append("SELECT 存放位置, 存放数量 FROM 库存表 "
                     "WHERE 库存类别 = ? AND 库存名称 = ? "
                     "ORDER BY 存放位置 DESC");
    /* ORDER BY 存放位置 DESC */
    sqlgroup->append("INSERT INTO 出库表 "
                     "(出库时间, 出库位置, 出库类别, 出库名称, 出库数量) "
                     "VALUES (?, ?, ?, ?, ?)");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("SELECT 存放数量 FROM 库存表 "
                     "WHERE 存放位置 = ? AND 库存类别 = ? AND 库存名称 = ?");
    /* 不需要ORDER BY，因为只有一条记录 */
    sqlgroup->append("DELETE FROM 库存表 "
                     "WHERE 存放位置 = ? AND 库存类别 = ? AND 库存名称 = ?");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("UPDATE 库存表 SET 存放数量 = 存放数量 - ? "
                     "WHERE 存放位置 = ? AND 库存类别 = ? AND 库存名称 = ?");
    /* 数据库操作语句，不需要排序 */
    // 数据库语句***************************************************************************    

    // 左区域*******************************************************************************
    // 待删除已定编号***********************************************************************
    // 样式**********************************************************************************
    qlabel01->setFont(*qfont01);
    qcombobox01->setFont(*qfont02);
    qcombobox01->setEditable(false);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qcombobox01->clear();
    query->exec(sqlgroup->at(0));
    if(!query->next()) {
        qcombobox01->addItem("暂无已定记录");
        *currentID = 0;
    } else {
        qcombobox01->addItem(query->value(0).toString());
        while (query->next()) {
            qcombobox01->addItem(query->value(0).toString());
        }
        *currentID = qcombobox01->currentText().toInt();
    }
    // 填充内容*****************************************************************************
    // 待删除已定编号***********************************************************************
    // 待删除已定时间***********************************************************************
    // 样式**********************************************************************************
    qlabel02->setFont(*qfont01);
    qreadonlylineedit01->setFont(*qfont02);
    qreadonlylineedit01->setReadOnly(true);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
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
    // 填充内容*****************************************************************************
    // 待删除已定时间***********************************************************************
    // 待删除已定类别***********************************************************************
    // 样式**********************************************************************************
    qlabel03->setFont(*qfont01);
    qreadonlylineedit02->setFont(*qfont02);
    qreadonlylineedit02->setReadOnly(true);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit02->clear();
    if(*currentID == 0) {
        qreadonlylineedit02->setText("暂无已定记录");
        *currentproductcategory = "暂无已定记录";
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
    // 待删除已定类别***********************************************************************
    leftzonerow1->addWidget(qlabel01);
    leftzonerow1->addWidget(qcombobox01, 1);
    leftzonerow2->addWidget(qlabel02);
    leftzonerow2->addWidget(qreadonlylineedit01, 1);
    leftzonerow3->addWidget(qlabel03);
    leftzonerow3->addWidget(qreadonlylineedit02, 1);
    leftzone->addLayout(leftzonerow1);
    leftzone->addLayout(leftzonerow2);
    leftzone->addLayout(leftzonerow3);
    leftzone->setSpacing(8);
    leftzone->setContentsMargins(QMargins(0, 4, 0, 4));
    zone->addLayout(leftzone);
    // 左区域*******************************************************************************

    // 右区域*******************************************************************************
    // 待删除已定名称***********************************************************************
    // 样式**********************************************************************************
    qlabel04->setFont(*qfont01);
    qreadonlylineedit03->setFont(*qfont02);
    qreadonlylineedit03->setReadOnly(true);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit03->clear();
    if(*currentID == 0) {
        qreadonlylineedit03->setText("暂无已定记录");
        *currentproductname = "暂无已定记录";
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
    // 待删除已定名称***********************************************************************
    // 待删除已定数量***********************************************************************
    // 样式**********************************************************************************
    qlabel05->setFont(*qfont01);
    qreadonlylineedit04->setFont(*qfont02);
    qreadonlylineedit04->setReadOnly(true);
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit04->clear();
    if(*currentID == 0) {
        qreadonlylineedit04->setText("暂无已定记录");
        *currentproductnumber = 0;
    } else {
        query->prepare(sqlgroup->at(4));
        query->addBindValue(*currentID);
        query->exec();
        while(query->next()) {
            qreadonlylineedit04->setText(query->value(0).toString());
            *currentproductnumber = query->value(0).toInt();
        }
    }
    // 填充内容*****************************************************************************
    // 待删除已定数量***********************************************************************
    yesremove->setFont(*qfont01);
    yesremoveandoutrepo->setFont(*qfont01);
    rightzonerow1->addWidget(qlabel04);
    rightzonerow1->addWidget(qreadonlylineedit03, 1);
    rightzonerow2->addWidget(qlabel05);
    rightzonerow2->addWidget(qreadonlylineedit04, 1);
    rightzonerow3->addWidget(yesremove);
    rightzonerow3->addWidget(yesremoveandoutrepo);
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

    // 信号与槽*****************************************************************************
    connect(qcombobox01, &QComboBox::currentTextChanged,
            this, &DoneRemove::onCurrentIDChanged);
    connect(yesremove, &QPushButton::clicked,
            this, &DoneRemove::showMessage);
    connect(yesremoveandoutrepo, &QPushButton::clicked,
            this, &DoneRemove::showMessage2);
    // 信号与槽*****************************************************************************
}
DoneRemove::~DoneRemove() {
    // 删除new对象************************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete sqlgroup;
    delete currentID;
    delete currentdatetime;
    delete currentproductnumber;
    delete currentproductcategory;
    delete currentproductname;
    // 删除new对象************************************************************************
}
void DoneRemove::onCurrentIDChanged(const QString &text) {
    // 记录更新*****************************************************************************
    *currentID = text.toInt();
    // 记录更新*****************************************************************************
    // 填充内容*****************************************************************************
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
    // 填充内容*****************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit02->clear();
    if(*currentID == 0) {
        qreadonlylineedit02->setText("暂无已定记录");
        *currentproductcategory = "暂无已定记录";
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
        qreadonlylineedit03->setText("暂无已定记录");
        *currentproductname = "暂无已定记录";
    } else {
        query->prepare(sqlgroup->at(3));
        query->addBindValue(*currentID);
        query->exec();
        while(query->next()) {
            qreadonlylineedit03->setText(query->value(0).toString());
            *currentproductname = query->value(0).toString();
        }
    }
    // 填充内容****************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit04->clear();
    if(*currentID == 0) {
        qreadonlylineedit04->setText("暂无已定记录");
        *currentproductnumber = 0;
    } else {
        query->prepare(sqlgroup->at(4));
        query->addBindValue(*currentID);
        query->exec();
        while(query->next()) {
            qreadonlylineedit04->setText(query->value(0).toString());
            *currentproductnumber = query->value(0).toInt();
        }
    }
    // 填充内容*****************************************************************************
    // 启槽函数*****************************************************************************
    ProcessTable();
    // 启槽函数*****************************************************************************
}
void DoneRemove::ProcessTable() {
    // 表格单元格***************************************************************************
    tableWidget01->clear();
    tableWidget01->setRowCount(0);
    tableWidget01->setColumnCount(3);
    query->prepare(sqlgroup->at(11));
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
void DoneRemove::showMessage()
{
    if(*currentID == 0) {
        // 新对象****************************************************************************
        simpledialog = new SimpleDialog(false, true, true, this);
        simpledialog->setDialogContent("已定表中暂无记录，无法删除");
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
        doneremovedialog = new DoneRemoveDialog(false, true, true, this);
        doneremovedialog->setDoneRemoveID(QString::number(*currentID));
        doneremovedialog->setDoneRemoveDateTime(
                    currentdatetime->toString("yyyy-MM-dd hh:mm:ss"));
        doneremovedialog->setDoneRemoveCategory(*currentproductcategory);
        doneremovedialog->setDoneRemoveName(*currentproductname);
        doneremovedialog->setDoneRemoveNumber(
                    QString::number(*currentproductnumber));
        // 新对象****************************************************************************
        // 新对象的信号与槽*****************************************************************
        connect(doneremovedialog, &DoneRemoveDialog::accepted, this, [this]() {
            SubmitRemoveOperation();
        });
        // 新对象的信号与槽*****************************************************************
        // 嗯，坏米饭************************************************************************
        // 调整位置**************************************************************************
        QRect parentGeometry = this->window()->window()->geometry();
        int dialogWidth = doneremovedialog->width();
        int dialogHeight = doneremovedialog->height();
        int x = (parentGeometry.width() - dialogWidth) / 2 + parentGeometry.x();
        int y = (parentGeometry.height() - dialogHeight) / 2 + parentGeometry.y();
        // 调整位置**************************************************************************
        // 移动对话框***********************************************************************
        doneremovedialog->move(x, y);
        // 移动对话框***********************************************************************
        // 嗯，坏米饭************************************************************************
        doneremovedialog->exec();
        delete doneremovedialog;
    }
}
void DoneRemove::SubmitRemoveOperation() {
    // 更新数据表***************************************************************************
    // 更新已定表***************************************************************************
    query->prepare(sqlgroup->at(5));
    query->addBindValue(*currentID);
    query->exec();
    query->exec(sqlgroup->at(6));
    query->exec(sqlgroup->at(7));
    query->exec(sqlgroup->at(8));
    query->exec(sqlgroup->at(9));
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
    // done下的doneadd, 已定, donechange, donesearch窗口信号
    emit RefreshDoneAddSignal();
    emit RefreshDoneRemoveSignal();
    emit RefreshDoneChangeSignal();
    emit RefreshDoneSearchSignal();
    // done下的doneadd, 已定, donechange, donesearch窗口信号
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
    // 更新自己*****************************************************************************
    RefreshDoneRemoveSlot();
    // 更新自己*****************************************************************************
}
void DoneRemove::RefreshDoneRemoveSlot() {
    // 关信号********************************************************************************
    qcombobox01->blockSignals(true);
    // 关信号********************************************************************************
    // 填充内容*****************************************************************************
    qcombobox01->clear();
    query->exec(sqlgroup->at(0));
    if(!query->next()) {
        qcombobox01->addItem("暂无已定记录");
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
void DoneRemove::showMessage2()
{
    if(*currentID == 0) {
        // 新对象****************************************************************************
        simpledialog = new SimpleDialog(false, true, true, this);
        simpledialog->setDialogContent("已定表中暂无记录，无法删除");
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
        query->prepare(sqlgroup->at(10));
        query->addBindValue(*currentproductcategory);
        query->addBindValue(*currentproductname);
        query->exec();
        if(query->next() && query->value(0).toInt() >= *currentproductnumber) {
            // 为新对象准备变量*****************************************************************
            repoandnumberv = new QVector<RepoAndNumber>;
            repoandcurrentnumv = new QVector<RepoAndCurrentNum>;
            int reponum;
            query->prepare(sqlgroup->at(12));
            query->addBindValue(*currentproductcategory);
            query->addBindValue(*currentproductname);
            query->exec();
            while(query->next()) {
                /* 靠这个来保证doneremovedialog2的打头处的仓库位置，
                 * 跟doneremovedialog2的qspinbox处的值是相同的。
                 */
                RepoAndNumber item;
                item.repo = query->value(0).toString();
                item.number = query->value(1).toString();
                repoandnumberv->append(item);

                RepoAndCurrentNum item2;
                item2.repo = query->value(0).toString();
                item2.currentnum = QString::number(0);
                repoandcurrentnumv->append(item2);
                /* 靠这个来保证doneremovedialog2的打头处的仓库位置，
                 * 跟doneremovedialog2的qspinbox处的值是相同的。
                 */
            }
            reponum = repoandnumberv->size();
            // 为新对象准备变量*****************************************************************
            // 新对象****************************************************************************
            doneremovedialog2 = new DoneRemoveDialog2(
                        false, true, true, this, reponum,
                        *currentproductnumber, repoandcurrentnumv);
            doneremovedialog2->setDoneRemove2ID(QString::number(*currentID));
            doneremovedialog2->setDoneRemove2DateTime(
                        currentdatetime->toString("yyyy-MM-dd hh:mm:ss"));
            doneremovedialog2->setDoneRemove2Category(*currentproductcategory);
            doneremovedialog2->setDoneRemove2Name(*currentproductname);
            doneremovedialog2->setDoneRemove2Number(
                        QString::number(*currentproductnumber));
            doneremovedialog2->setDoneRemove2Repo(*repoandnumberv);
            // 新对象****************************************************************************
            // 新对象的信号和槽*****************************************************************
            connect(doneremovedialog2, &DoneRemoveDialog2::accepted, this, [this]() {
                SubmitRemoveOperation2();
            });
            // 新对象的信号和槽*****************************************************************
            // 嗯，坏米饭************************************************************************
            // 调整位置**************************************************************************
            QRect parentGeometry = this->window()->window()->geometry();
            int dialogWidth = doneremovedialog2->width();
            int dialogHeight = doneremovedialog2->height();
            int x = (parentGeometry.width() - dialogWidth) / 2 + parentGeometry.x();
            int y = (parentGeometry.height() - dialogHeight) / 2 + parentGeometry.y();
            // 调整位置**************************************************************************
            // 移动对话框***********************************************************************
            doneremovedialog2->move(x, y);
            // 移动对话框***********************************************************************
            // 嗯，坏米饭************************************************************************
            doneremovedialog2->exec();
            delete repoandnumberv;
            delete repoandcurrentnumv;
            delete doneremovedialog2;
        } else {
            // 新对象****************************************************************************
            simpledialog = new SimpleDialog(false, true, true, this);
            simpledialog->setDialogContent("库存表中存货不足，无法删除");
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
        }
    }
}
void DoneRemove::SubmitRemoveOperation2() {
    // 更新数据表***************************************************************************
    // 更新已定表***************************************************************************
    query->prepare(sqlgroup->at(5));
    query->addBindValue(*currentID);
    query->exec();
    query->exec(sqlgroup->at(6));
    query->exec(sqlgroup->at(7));
    query->exec(sqlgroup->at(8));
    query->exec(sqlgroup->at(9));
    // 更新已定表***************************************************************************
    int length = repoandcurrentnumv->size();
    for(int i = 0; i < length; i++) {
        if((*repoandcurrentnumv)[i].currentnum.toInt() == 0) {}
        else {
            QString currentrepo = (*repoandcurrentnumv)[i].repo;
            int outnumber = (*repoandcurrentnumv)[i].currentnum.toInt();
            // 更新出库表***********************************************************************
            query->prepare(sqlgroup->at(13));
            query->addBindValue(QDateTime::currentDateTime());
            query->addBindValue(currentrepo);
            query->addBindValue(*currentproductcategory);
            query->addBindValue(*currentproductname);
            query->addBindValue(outnumber);
            query->exec();
            // 更新出库表***********************************************************************
            // 更新库存表***********************************************************************
            query->prepare(sqlgroup->at(14));
            query->addBindValue(currentrepo);
            query->addBindValue(*currentproductcategory);
            query->addBindValue(*currentproductname);
            query->exec();
            query->next();
            if(outnumber == query->value(0).toInt()) {
                query->prepare(sqlgroup->at(15));
                query->addBindValue(currentrepo);
                query->addBindValue(*currentproductcategory);
                query->addBindValue(*currentproductname);
                query->exec();
                RefreshRepoTableID refreshid(db, query);
            } else {
                query->prepare(sqlgroup->at(16));
                query->addBindValue(outnumber);
                query->addBindValue(currentrepo);
                query->addBindValue(*currentproductcategory);
                query->addBindValue(*currentproductname);
                query->exec();
            }
            // 更新库存表***********************************************************************
        }
    }
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
    // done下的doneadd, 已定, donechange, donesearch窗口信号
    emit RefreshDoneAddSignal();
    emit RefreshDoneRemoveSignal();
    emit RefreshDoneChangeSignal();
    emit RefreshDoneSearchSignal();
    // done下的doneadd, 已定, donechange, donesearch窗口信号
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
    // 更新自己*****************************************************************************
    RefreshDoneRemoveSlot();
    // 更新自己*****************************************************************************
}
