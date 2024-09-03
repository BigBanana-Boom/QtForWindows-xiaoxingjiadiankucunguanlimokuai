#include "repomodify.h"

RepoModify::RepoModify(QWidget *parent,
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
      qpushbutton01(new QPushButton("一天内盘库单", this)),
      qpushbutton02(new QPushButton("三天内盘库单", this)),
      qpushbutton03(new QPushButton("一周内盘库单", this)),
      qpushbutton04(new QPushButton("导出盘库单", this)),
      tableWidget01(new QTableWidget(this)),
      db(db),
      query(query),
      sqlgroup(new QStringList())
{
    // 数据库语句***************************************************************************
    sqlgroup->append("WITH 临时表1 AS ( "
                     "SELECT DISTINCT 入库类别, 入库名称, 入库位置 FROM 入库表 "
                     "WHERE 入库时间 > ?), "
                     "临时表2 AS ( "
                     "SELECT DISTINCT 出库类别, 出库名称, 出库位置 FROM 出库表 "
                     "WHERE 出库时间 > ?), "
                     "临时表3 AS ( "
                     "SELECT DISTINCT 已定类别, 已定名称 FROM 已定表 "
                     "WHERE 已定时间 > ?), "
                     "临时表4 AS ( "
                     "SELECT DISTINCT 库存类别, 库存名称, 库存位置 FROM 附表3库存调整表 "
                     "WHERE 调库时间 > ?), "
                     "临时表5 AS ("
                     "SELECT 库存类别, 库存名称, 存放位置, 存放数量 FROM 库存表 JOIN 临时表1 "
                     "ON 库存表.库存类别 = 临时表1.入库类别 AND "
                     "库存表.库存名称 = 临时表1.入库名称 AND "
                     "库存表.存放位置 = 临时表1.入库位置 "
                     "UNION "
                     "SELECT 库存类别, 库存名称, 存放位置, 存放数量 FROM 库存表 JOIN 临时表2 "
                     "ON 库存表.库存类别 = 临时表2.出库类别 AND "
                     "库存表.库存名称 = 临时表2.出库名称 AND "
                     "库存表.存放位置 = 临时表2.出库位置 "
                     "UNION "
                     "SELECT 库存类别, 库存名称, 存放位置, 存放数量 FROM 库存表 JOIN 临时表3 "
                     "ON 库存表.库存类别 = 临时表3.已定类别 AND "
                     "库存表.库存名称 = 临时表3.已定名称 "
                     "UNION "
                     "SELECT 库存表.库存类别, 库存表.库存名称, 库存表.存放位置, 库存表.存放数量 "
                     "FROM 库存表 JOIN 临时表4 ON "
                     "库存表.库存类别 = 临时表4.库存类别 AND "
                     "库存表.库存名称 = 临时表4.库存名称 AND "
                     "库存表.存放位置 = 临时表4.库存位置 "
                     "ORDER BY 库存表.存放位置 DESC, "
                     "库存表.库存类别 DESC, 库存表.库存名称 DESC) "
                     "SELECT ROW_NUMBER() OVER "
                     "(ORDER BY 临时表5.存放位置 DESC, 临时表5.库存类别 DESC, "
                     "临时表5.库存名称 DESC) AS 盘库编号, 临时表5.库存类别, 临时表5.库存名称, "
                     "临时表5.存放位置, 临时表5.存放数量 FROM 临时表5 "
                     "ORDER BY 盘库编号 DESC");
    // 数据库语句***************************************************************************

    // 左区域*******************************************************************************
    // 按钮1********************************************************************************
    qpushbutton01->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    qpushbutton01->setFont(*qfont01);
    // 按钮1********************************************************************************
    // 按钮2********************************************************************************
    qpushbutton02->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    qpushbutton02->setFont(*qfont01);
    // 按钮2********************************************************************************
    // 按钮3********************************************************************************
    qpushbutton03->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    qpushbutton03->setFont(*qfont01);
    // 按钮3********************************************************************************
    // 按钮4********************************************************************************
    qpushbutton04->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    qpushbutton04->setFont(*qfont01);
    // 按钮4********************************************************************************
    leftzone->addWidget(qpushbutton01);
    leftzone->addWidget(qpushbutton02);
    leftzone->addWidget(qpushbutton03);
    leftzone->addWidget(qpushbutton04);
    zone->addLayout(leftzone);
    // 左区域*******************************************************************************

    // 右区域*******************************************************************************
    RefreshRepoModifySlot1();
    rightzone->addWidget(tableWidget01);
    tableWidget01->resizeColumnsToContents();
    zone->addLayout(rightzone);
    // 右区域*******************************************************************************

    // 总区域*******************************************************************************
    mainLayout->addLayout(zone);
    // 总区域*******************************************************************************

    // 信号与槽函数*************************************************************************
    connect(qpushbutton01, &QPushButton::clicked, this,
            &RepoModify::RefreshRepoModifySlot1);
    connect(qpushbutton02, &QPushButton::clicked, this,
            &RepoModify::RefreshRepoModifySlot2);
    connect(qpushbutton03, &QPushButton::clicked, this,
            &RepoModify::RefreshRepoModifySlot3);
    connect(qpushbutton04, &QPushButton::clicked, this,
            &RepoModify::SaveFile);
    connect(tableWidget01->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &RepoModify::selectColumnOnHeaderClick);
    // 信号与槽函数*************************************************************************
}
RepoModify::~RepoModify() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete sqlgroup;
    // 删除new对象*************************************************************************
}
void RepoModify::RefreshRepoModifySlot1() {
    // 初始化表格***************************************************************************
    tableWidget01->clear();
    tableWidget01->sortItems(0, Qt::DescendingOrder);
    tableWidget01->setRowCount(0);
    tableWidget01->setColumnCount(5);
    // 初始化表格***************************************************************************
    // 水平表头*****************************************************************************
    QStringList headers;
    headers<< "盘库编号" << "库存类别" << "库存名称" << "存放位置" << "存放数量";
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
    // 表格单元格***************************************************************************
    query->prepare(sqlgroup->at(0));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-1));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-1));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-1));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-1));
    query->exec();
    int row = 0;
    while (query->next()) {
        tableWidget01->insertRow(tableWidget01->rowCount());
        for(int i = 0; i < 5; i++) {
            if(i == 0 || i == 4) {
                int value = query->value(i).toInt();
                QTableWidgetItem *item= new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                item->setData(Qt::DisplayRole, value);
                tableWidget01->setItem(row, i, item);
            } else {
                QTableWidgetItem *item= new QTableWidgetItem(query->value(i).toString());
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                tableWidget01->setItem(row, i, item);
            }
        }
        ++row;
    }
    // 表格单元格***************************************************************************
    // 表属性*******************************************************************************
    tableWidget01->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget01->resizeColumnsToContents();
    tableWidget01->setFont(*qfont02);
    tableWidget01->setSortingEnabled(true);
    // 表属性*******************************************************************************
}
void RepoModify::RefreshRepoModifySlot2() {
    // 初始化表格***************************************************************************
    tableWidget01->clear();
    tableWidget01->sortItems(0, Qt::DescendingOrder);
    tableWidget01->setRowCount(0);
    tableWidget01->setColumnCount(5);
    // 初始化表格***************************************************************************
    // 水平表头*****************************************************************************
    QStringList headers;
    headers<< "盘库编号" << "库存类别" << "库存名称" << "存放位置" << "存放数量";
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
    // 表格单元格***************************************************************************
    query->prepare(sqlgroup->at(0));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-3));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-3));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-3));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-3));
    query->exec();
    int row = 0;
    while (query->next()) {
        tableWidget01->insertRow(tableWidget01->rowCount());
        for(int i = 0; i < 5; i++) {
            if(i == 0 || i == 4) {
                int value = query->value(i).toInt();
                QTableWidgetItem *item= new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                item->setData(Qt::DisplayRole, value);
                tableWidget01->setItem(row, i, item);
            } else {
                QTableWidgetItem *item= new QTableWidgetItem(query->value(i).toString());
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                tableWidget01->setItem(row, i, item);
            }
        }
        ++row;
    }
    // 表格单元格***************************************************************************
    // 表属性*******************************************************************************
    tableWidget01->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget01->resizeColumnsToContents();
    tableWidget01->setFont(*qfont02);
    tableWidget01->setSortingEnabled(true);
    // 表属性*******************************************************************************
}
void RepoModify::RefreshRepoModifySlot3() {
    // 初始化表格***************************************************************************
    tableWidget01->clear();
    tableWidget01->sortItems(0, Qt::DescendingOrder);
    tableWidget01->setRowCount(0);
    tableWidget01->setColumnCount(5);
    // 初始化表格***************************************************************************
    // 水平表头*****************************************************************************
    QStringList headers;
    headers<< "盘库编号" << "库存类别" << "库存名称" << "存放位置" << "存放数量";
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
    // 表格单元格***************************************************************************
    query->prepare(sqlgroup->at(0));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-7));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-7));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-7));
    query->addBindValue(QDateTime(QDateTime::currentDateTime()).addDays(-7));
    query->exec();
    int row = 0;
    while (query->next()) {
        tableWidget01->insertRow(tableWidget01->rowCount());
        for(int i = 0; i < 5; i++) {
            if(i == 0 || i == 4) {
                int value = query->value(i).toInt();
                QTableWidgetItem *item= new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                item->setData(Qt::DisplayRole, value);
                tableWidget01->setItem(row, i, item);
            } else {
                QTableWidgetItem *item= new QTableWidgetItem(query->value(i).toString());
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                tableWidget01->setItem(row, i, item);
            }
        }
        ++row;
    }
    // 表格单元格***************************************************************************
    // 表属性*******************************************************************************
    tableWidget01->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget01->resizeColumnsToContents();
    tableWidget01->setFont(*qfont02);
    tableWidget01->setSortingEnabled(true);
    // 表属性*******************************************************************************
}
void RepoModify::SaveFile() {
    QString currentProjectPath = QCoreApplication::applicationDirPath();
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("导出盘库单"),
                                                    currentProjectPath,
                                                    tr("Excel 文件 (*.xlsx);;所有文件 (*)"));
    if (!fileName.isEmpty()) {
        QXlsx::Document xlsx;
        // 盘库表*****************************************************************************
        xlsx.write(1, 1, "盘库编号");
        xlsx.write(1, 2, "库存类别");
        xlsx.write(1, 3, "库存名称");
        xlsx.write(1, 4, "存放位置");
        xlsx.write(1, 5, "存放数量");
        for (int row = 0; row < tableWidget01->rowCount(); ++row) {
            for (int col = 0; col < tableWidget01->columnCount(); ++col) {
                QTableWidgetItem *item = tableWidget01->item(row, col);
                if (item) {
                    QString text = item->text();
                    xlsx.write(row+2, col+1, text);
                }
            }
        }
        // 盘库表*****************************************************************************
        xlsx.saveAs(fileName);
    }
}
void RepoModify::selectColumnOnHeaderClick(int column) {
    tableWidget01->clearSelection();
    for (int row = 0; row < tableWidget01->rowCount(); ++row)
    {
        tableWidget01->item(row, column)->setSelected(true);
    }
}
