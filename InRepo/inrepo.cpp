#include "inrepo.h"

InRepo::InRepo(QWidget *parent, QSqlDatabase *db, QSqlQuery *query)
    : QWidget{parent},
    qfont01(new QFont("楷体", 24, QFont::Bold)),
    qfont02(new QFont("楷体", 20, QFont::Bold)),
    qfont03(new QFont("楷体", 16, QFont::Bold)),
    qfont04(new QFont("楷体", 16)),
    mainLayout(new QVBoxLayout(this)),
    titleLayout(new QHBoxLayout()),
    contentLayout(new QVBoxLayout()),
    tableLayout(new QVBoxLayout()),
    qlabel01(new QLabel("入 库", this)),
    db(db),
    query(query),
    sqlgroup(new QStringList()),
    whereclause(new QString()),
    whereclausesql(new QString()),
    IRsearchingdatetime(new QDateTime()),
    IRsearchingdatetime02(new QDateTime()),
    IRsearchingrepo(new QString()),
    IRsearchingproductcategory(new QString()),
    IRsearchingproductname(new QString()),
    fivebutton(new QHBoxLayout()),
    stackedWidget(new QStackedWidget(this)),
    inRepoAddWindow(new InRepoAdd(stackedWidget, db, query)),
    inRepoRemoveWindow(new InRepoRemove(stackedWidget, db, query)),
    inRepoChangeWindow(new InRepoChange(stackedWidget, db, query)),
    inRepoSearchWindow(new InRepoSearch(stackedWidget, db, query,
                                        IRsearchingdatetime,
                                        IRsearchingdatetime02,
                                        IRsearchingproductcategory,
                                        IRsearchingproductname,
                                        IRsearchingrepo)),
    inrepoadd(new NormalGradientButton(this)),
    inreporemove(new NormalGradientButton(this)),
    inrepochange(new NormalGradientButton(this)),
    inreposearch(new NormalGradientButton(this)),
    inrepoexport(new NormalGradientButton(this)),
    line(new QFrame(this)),
    tableWidget01(new QTableWidget(this)),
    dropdowngradientbutton(new DropDownGradientButton(this)),
    tableWidget02(new QTableWidget(this))
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT 入库编号, 入库时间, 入库类别, 入库名称, 入库位置, 入库数量 "
                     "FROM 入库表 "
                     "ORDER BY 入库编号 DESC");
    /* ORDER BY 已定编号 DESC */
    sqlgroup->append("WITH 入库汇总 AS ( "
                     "SELECT 入库类别 AS 入库汇总类别, 入库名称 AS 入库汇总名称, "
                     "SUM(入库数量) AS 入库汇总数量 "
                     "FROM 入库表 "
                     "GROUP BY 入库类别, 入库名称), "
                     "库存汇总 AS ( "
                     "SELECT 库存类别 AS 库存汇总类别, 库存名称 AS 库存汇总名称, "
                     "SUM(存放数量) AS 库存汇总数量 "
                     "FROM 库存表 "
                     "GROUP BY 库存类别, 库存名称) "
                     "SELECT ROW_NUMBER() OVER "
                     "(ORDER BY 入库汇总类别 DESC, 入库汇总名称 DESC) AS 入库汇总编号, "
                     "入库汇总类别, 入库汇总名称, 入库汇总数量, "
                     "COALESCE(库存汇总数量, 0) AS 当前库存数量 "
                     "FROM 入库汇总 LEFT JOIN 库存汇总 "
                     "ON 入库汇总.入库汇总类别 = 库存汇总.库存汇总类别 AND "
                     "入库汇总.入库汇总名称 = 库存汇总.库存汇总名称 "
                     "ORDER BY 入库汇总编号 DESC");
    /* ORDER BY 入库汇总编号 DESC */
    /* OVER (ORDER BY 入库汇总类别 DESC, 入库汇总名称 DESC) AS 入库汇总编号 */
    // 数据库语句***************************************************************************

    // 标题布局*****************************************************************************
    qlabel01->resize(100, 100);
    qlabel01->setFont(*qfont01);
    qlabel01->setAlignment(Qt::AlignCenter);
    titleLayout->addWidget(qlabel01);
    // 标题布局*****************************************************************************

    // 内容布局*****************************************************************************
    // 五个顶栏按钮*************************************************************************
    inrepoadd->setText("新增入库");
    inrepoadd->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    inrepoadd->setFont(*qfont02);
    inrepoadd->setMinimumHeight(50);
    inreporemove->setText("删除入库");
    inreporemove->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    inreporemove->setFont(*qfont02);
    inreporemove->setMinimumHeight(50);
    inrepochange->setText("修改入库");
    inrepochange->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    inrepochange->setFont(*qfont02);
    inrepochange->setMinimumHeight(50);
    inreposearch->setText("查找入库");
    inreposearch->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    inreposearch->setFont(*qfont02);
    inreposearch->setMinimumHeight(50);
    inrepoexport->setText("导出入库");
    inrepoexport->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    inrepoexport->setFont(*qfont02);
    inrepoexport->setMinimumHeight(50);
    fivebutton->addWidget(inrepoadd);
    fivebutton->addWidget(inreporemove);
    fivebutton->addWidget(inrepochange);
    fivebutton->addWidget(inreposearch);
    fivebutton->addWidget(inrepoexport);
    contentLayout->addLayout(fivebutton);
    // 五个顶栏按钮*************************************************************************
    // stackedWidget**********************************************************************
    stackedWidget->addWidget(inRepoAddWindow);
    stackedWidget->addWidget(inRepoRemoveWindow);
    stackedWidget->addWidget(inRepoChangeWindow);
    stackedWidget->addWidget(inRepoSearchWindow);
    stackedWidget->setCurrentWidget(inRepoAddWindow);
    stackedWidget->setStyleSheet(
        "QStackedWidget {"
        "   border: 1px solid #999999;"
        "}"
    );
    stackedWidget->setVisible(false);
    contentLayout->addWidget(stackedWidget);
    // stackedWidget**********************************************************************
    // 两个表格和下拉按钮******************************************************************
    RefreshInRepoTableSlot();
    dropdowngradientbutton->setSizePolicy(
                QSizePolicy::Expanding, QSizePolicy::Preferred);
    dropdowngradientbutton->setFixedHeight(40);
    dropdowngradientbutton->setArrowType(Qt::DownArrow);
    tableLayout->addWidget(tableWidget01);
    tableLayout->addWidget(dropdowngradientbutton);
    tableLayout->addWidget(tableWidget02);
    tableLayout->setSpacing(0);
    contentLayout->addLayout(tableLayout);
    // 两个表格和下拉按钮******************************************************************
    // 内容布局*****************************************************************************

    // 总布局*******************************************************************************
    mainLayout->addLayout(titleLayout);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("QFrame { color: grey; }");
    mainLayout->addWidget(line);
    mainLayout->addLayout(contentLayout);
    // 总布局*******************************************************************************

    // 信号与槽*****************************************************************************
    // 入库增*******************************************************************************
    connect(inrepoadd, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == inRepoAddWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(295);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(inRepoAddWindow);
        }
    });
    // 入库增*******************************************************************************
    // 入库删*******************************************************************************
    connect(inreporemove, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == inRepoRemoveWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(332);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(inRepoRemoveWindow);
        }
    });
    // 入库删*******************************************************************************
    // 入库改*******************************************************************************
    connect(inrepochange, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == inRepoChangeWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(332);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(inRepoChangeWindow);
        }
    });
    // 入库改*******************************************************************************
    // 入库查*******************************************************************************
    connect(inreposearch, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == inRepoSearchWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(180);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(inRepoSearchWindow);
        }
    });
    // 入库查*******************************************************************************
    // 入库导*******************************************************************************
    connect(inrepoexport, &QPushButton::clicked, this, &InRepo::SaveFile);
    // 入库导*******************************************************************************
    // 下拉框*******************************************************************************
    connect(dropdowngradientbutton, &QToolButton::clicked,
            this, &InRepo::toggleTableVisibility);
    // 下拉框*******************************************************************************
    // 选中表1******************************************************************************
    connect(headerView01_row, &QHeaderView::sectionClicked,
             this, &InRepo::selectColumnOnHeaderClickForTable01);
    // 选中表1******************************************************************************
    // 选中表2******************************************************************************
    connect(headerView02_row, &QHeaderView::sectionClicked,
             this, &InRepo::selectColumnOnHeaderClickForTable02);
    // 选中表2******************************************************************************
    // 信号与槽*****************************************************************************

    // 窗口属性*****************************************************************************
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    // 窗口属性*****************************************************************************
}
InRepo::~InRepo() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete qfont04;
    delete sqlgroup;
    delete whereclause;
    delete whereclausesql;
    delete IRsearchingdatetime;
    delete IRsearchingdatetime02;
    delete IRsearchingproductcategory;
    delete IRsearchingproductname;
    delete IRsearchingrepo;
    // 删除new对象*************************************************************************
}
void InRepo::RefreshInRepoTableSlot() {
    // 入库表*******************************************************************************
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
    tableWidget01->sortItems(0, Qt::DescendingOrder);
    tableWidget01->setRowCount(0);
    tableWidget01->setColumnCount(6);
    query->exec(sqlgroup->at(0));
    int row = 0;
    while (query->next()) {
        tableWidget01->insertRow(tableWidget01->rowCount());
        for(int i = 0; i < 6; i++) {
            if(i == 0 || i == 5) {
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
    // 水平表头*****************************************************************************
    QStringList headers;
    headers << "入库编号" << "入库时间" << "入库类别"
            << "入库名称" << "入库位置" << "入库数量";
    tableWidget01->setHorizontalHeaderLabels(headers);
    headerView01_row = tableWidget01->horizontalHeader();
    headerView01_row->setFont(*qfont03);
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
    tableWidget01->setFont(*qfont04);
    tableWidget01->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget01->resizeColumnsToContents();
    tableWidget01->setSortingEnabled(true);
    // 表属性*******************************************************************************
    // 入库表*******************************************************************************

    // 入库汇总*****************************************************************************
    // 清理以防止内存泄漏******************************************************************
    for (int row = 0; row < tableWidget02->rowCount(); ++row) {
        for (int col = 0; col < tableWidget02->columnCount(); ++col) {
            // 取出项**************************************************************************
            QTableWidgetItem* item = tableWidget02->takeItem(row, col);
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
    tableWidget02->clear();
    tableWidget02->sortItems(0, Qt::DescendingOrder);
    tableWidget02->setRowCount(0);
    tableWidget02->setColumnCount(5);
    query->exec(sqlgroup->at(1));
    row = 0;
    while (query->next()) {
        tableWidget02->insertRow(tableWidget02->rowCount());
        for(int i = 0; i < 5; i++) {
            if(i == 0 || i == 3 || i == 4) {
                int value = query->value(i).toInt();
                QTableWidgetItem *item= new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                item->setData(Qt::DisplayRole, value);
                tableWidget02->setItem(row, i, item);
            } else {
                QTableWidgetItem *item= new QTableWidgetItem(query->value(i).toString());
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                tableWidget02->setItem(row, i, item);
            }
        }
        ++row;
    }
    // 表格单元格***************************************************************************
    // 水平表头*****************************************************************************
    QStringList headers2;
    headers2 << "入库汇总编号" << "入库汇总类别" <<
                "入库汇总名称" << "入库汇总数量" << "当前库存数量";
    tableWidget02->setHorizontalHeaderLabels(headers2);
    headerView02_row = tableWidget02->horizontalHeader();
    headerView02_row->setFont(*qfont03);
    headerView02_row->setStyleSheet("");
    headerView02_row->setStyleSheet(
                "QHeaderView::up-arrow {image: none;}"
                "QHeaderView::down-arrow {image: none;}");
    // 水平表头*****************************************************************************
    // 垂直表头*****************************************************************************
    headerView02_column = tableWidget02->verticalHeader();
    headerView02_column->hide();
    // 垂直表头*****************************************************************************
    // 表属性*******************************************************************************
    tableWidget02->setFont(*qfont04);
    tableWidget02->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget02->resizeColumnsToContents();
    tableWidget02->setSortingEnabled(true);
    // 表属性*******************************************************************************
    // 入库汇总*****************************************************************************
}
void InRepo::RefreshInRepoTableSlot_DifferentSelect() {
    // 显示筛选的入库表********************************************************************
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
    tableWidget01->sortItems(0, Qt::DescendingOrder);
    tableWidget01->setRowCount(0);
    tableWidget01->setColumnCount(6);
    *whereclause = "";
    *whereclause += " AND 入库时间 > ? ";
    *whereclause += " AND 入库时间 < ? ";
    if (*IRsearchingrepo != "不选择") {
        *whereclause += " AND 入库位置 = ? ";
    }
    if (*IRsearchingproductcategory != "不选择") {
        *whereclause += " AND 入库类别 = ? ";
    }
    if (*IRsearchingproductname != "不选择") {
        *whereclause += " AND 入库名称 = ? ";
    }
    *whereclausesql = "SELECT 入库编号, 入库时间, 入库类别, 入库名称, 入库位置, 入库数量 "
                      "FROM 入库表 WHERE 1 = 1"
            + *whereclause +
            "ORDER BY 入库编号 DESC";
    /* ORDER BY 入库编号 DESC */
    query->prepare(*whereclausesql);
    query->addBindValue(IRsearchingdatetime->addDays(-1));
    query->addBindValue(*IRsearchingdatetime02);
    if (*IRsearchingrepo != "不选择") {
        query->addBindValue(*IRsearchingrepo);
    }
    if (*IRsearchingproductcategory != "不选择") {
        query->addBindValue(*IRsearchingproductcategory);
    }
    if (*IRsearchingproductname != "不选择") {
        query->addBindValue(*IRsearchingproductname);
    }
    query->exec();
    int row = 0;
    while (query->next()) {
        tableWidget01->insertRow(tableWidget01->rowCount());
        for(int i = 0; i < 6; i++) {
            if(i == 0 || i == 5) {
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
    // 水平表头*****************************************************************************
    QStringList headers;
    headers << "入库编号" << "入库时间" << "入库类别" <<
               "入库名称" << "入库位置" << "入库数量";
    tableWidget01->setHorizontalHeaderLabels(headers);
    headerView01_row = tableWidget01->horizontalHeader();
    headerView01_row->setFont(*qfont03);
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
    tableWidget01->setFont(*qfont04);
    tableWidget01->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget01->resizeColumnsToContents();
    tableWidget01->setSortingEnabled(true);
    // 表属性*******************************************************************************
    // 显示筛选的入库表********************************************************************

    // 显示筛选的入库汇总******************************************************************
    // 清理以防止内存泄漏******************************************************************
    for (int row = 0; row < tableWidget02->rowCount(); ++row) {
        for (int col = 0; col < tableWidget02->columnCount(); ++col) {
            // 取出项**************************************************************************
            QTableWidgetItem* item = tableWidget02->takeItem(row, col);
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
    tableWidget02->clear();
    tableWidget02->sortItems(0, Qt::DescendingOrder);
    tableWidget02->setRowCount(0);
    tableWidget02->setColumnCount(5);
    *whereclause = "";
    *whereclause += " AND 入库时间 > ? ";
    *whereclause += " AND 入库时间 < ? ";
    if (*IRsearchingrepo != "不选择") {
        *whereclause += " AND 入库位置 = ? ";
    }
    if (*IRsearchingproductcategory != "不选择") {
        *whereclause += " AND 入库类别 = ? ";
    }
    if (*IRsearchingproductname != "不选择") {
        *whereclause += " AND 入库名称 = ? ";
    }
    *whereclausesql = "SELECT 入库类别, 入库名称, 入库数量 FROM 入库表 WHERE 1 = 1"
            + *whereclause;
    query->prepare("WITH 入库汇总 AS ( "
                   "SELECT 临时表.入库类别 AS 入库汇总类别, "
                   "临时表.入库名称 AS 入库汇总名称, SUM(临时表.入库数量) AS 入库汇总数量 "
                   "FROM ("
                  + *whereclausesql +
                  ") AS 临时表 "
                  "GROUP BY 临时表.入库类别, 临时表.入库名称), "
                  "库存汇总 AS ( "
                  "SELECT 库存类别 AS 库存汇总类别, 库存名称 AS 库存汇总名称, "
                  "SUM(存放数量) AS 库存汇总数量 "
                  "FROM 库存表 "
                  "GROUP BY 库存类别, 库存名称) "
                  "SELECT ROW_NUMBER() OVER "
                  "(ORDER BY 入库汇总类别 DESC, 入库汇总名称 DESC) AS 入库汇总编号, "
                  "入库汇总类别, 入库汇总名称, 入库汇总数量, "
                  "COALESCE(库存汇总数量, 0) AS 当前库存数量 "
                  "FROM 入库汇总 LEFT JOIN 库存汇总 "
                  "ON 入库汇总.入库汇总类别 = 库存汇总.库存汇总类别 AND "
                  "入库汇总.入库汇总名称 = 库存汇总.库存汇总名称 "
                  "ORDER BY 入库汇总编号 DESC");
    /* ORDER BY 入库汇总编号 DESC */
    /* OVER (ORDER BY 入库汇总类别 DESC, 入库汇总名称 DESC) AS 入库汇总编号 */
    query->addBindValue(IRsearchingdatetime->addDays(-1));
    query->addBindValue(*IRsearchingdatetime02);
    if (*IRsearchingrepo != "不选择") {
        query->addBindValue(*IRsearchingrepo);
    }
    if (*IRsearchingproductcategory != "不选择") {
        query->addBindValue(*IRsearchingproductcategory);
    }
    if (*IRsearchingproductname != "不选择") {
        query->addBindValue(*IRsearchingproductname);
    }
    query->exec();
    row = 0;
    while (query->next()) {
        tableWidget02->insertRow(tableWidget02->rowCount());
        for(int i = 0; i < 5; i++) {
            if(i == 0 || i == 3 || i == 4) {
                int value = query->value(i).toInt();
                QTableWidgetItem *item= new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                item->setData(Qt::DisplayRole, value);
                tableWidget02->setItem(row, i, item);
            } else {
                QTableWidgetItem *item= new QTableWidgetItem(query->value(i).toString());
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                tableWidget02->setItem(row, i, item);
            }
        }
        ++row;
    }
    // 表格单元格***************************************************************************
    // 水平表头*****************************************************************************
    QStringList headers2;
    headers2 << "入库汇总编号" << "入库汇总类别" << "入库汇总名称" << "入库汇总数量"
             << "当前库存数量";
    tableWidget02->setHorizontalHeaderLabels(headers2);
    headerView02_row = tableWidget02->horizontalHeader();
    headerView02_row->setFont(*qfont03);
    headerView02_row->setStyleSheet("");
    headerView02_row->setStyleSheet(
                "QHeaderView::up-arrow {image: none;}"
                "QHeaderView::down-arrow {image: none;}");
    // 水平表头*****************************************************************************
    // 垂直表头*****************************************************************************
    headerView02_column = tableWidget02->verticalHeader();
    headerView02_column->hide();
    // 垂直表头*****************************************************************************
    // 表属性*******************************************************************************
    tableWidget02->setFont(*qfont04);
    tableWidget02->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget02->resizeColumnsToContents();
    tableWidget02->setSortingEnabled(true);
    // 表属性*******************************************************************************
    // 显示筛选的入库汇总******************************************************************
}
void InRepo::SaveFile() {
    QString currentProjectPath = QCoreApplication::applicationDirPath();
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("导出当前入库记录"),
                                                    currentProjectPath,
                                                    tr("Excel 文件 (*.xlsx);;所有文件 (*)"));
    if (!fileName.isEmpty()) {
        QXlsx::Document xlsx;
        // 入库表*****************************************************************************
        xlsx.write(1, 1, "入库编号");
        xlsx.write(1, 2, "入库时间");
        xlsx.write(1, 3, "入库类别");
        xlsx.write(1, 4, "入库名称");
        xlsx.write(1, 5, "入库位置");
        xlsx.write(1, 6, "入库数量");
        for (int row = 0; row < tableWidget01->rowCount(); ++row) {
            for (int col = 0; col < tableWidget01->columnCount(); ++col) {
                QTableWidgetItem *item = tableWidget01->item(row, col);
                if (item) {
                    QString text = item->text();
                    xlsx.write(row+2, col+1, text);
                }
            }
        }
        // 入库表*****************************************************************************
        // 入库汇总***************************************************************************
        int newrow = tableWidget01->rowCount();
        xlsx.write(newrow+5, 1, "入库汇总编号");
        xlsx.write(newrow+5, 2, "入库汇总类别");
        xlsx.write(newrow+5, 3, "入库汇总名称");
        xlsx.write(newrow+5, 4, "入库汇总数量");
        for (int row = 0; row < tableWidget02->rowCount(); ++row) {
            for (int col = 0; col < tableWidget02->columnCount(); ++col) {
                QTableWidgetItem *item = tableWidget02->item(row, col);
                if (item) {
                    QString text = item->text();
                    xlsx.write(newrow+row+6, col+1, text);
                }
            }
        }
        // 入库汇总***************************************************************************
        xlsx.saveAs(fileName);
    }
}
void InRepo::toggleTableVisibility() {
    // 下拉按钮****************************************************************************
    if (tableWidget02->isVisible()) {
        dropdowngradientbutton->setArrowType(Qt::UpArrow);
        tableWidget02->hide();
        // 恩，坏米饭*********************************************************************
        QEvent leaveEvent(QEvent::Leave);
        QCoreApplication::sendEvent(dropdowngradientbutton, &leaveEvent);
        // 恩，坏米饭*********************************************************************
    } else {
        dropdowngradientbutton->setArrowType(Qt::DownArrow);
        tableWidget02->show();
    }
    // 下拉按钮****************************************************************************
}
void InRepo::selectColumnOnHeaderClickForTable01(int column) {
    tableWidget01->clearSelection();
    for (int row = 0; row < tableWidget01->rowCount(); ++row)
    {
        tableWidget01->item(row, column)->setSelected(true);
    }
}
void InRepo::selectColumnOnHeaderClickForTable02(int column) {
    tableWidget02->clearSelection();
    for (int row = 0; row < tableWidget02->rowCount(); ++row)
    {
        tableWidget02->item(row, column)->setSelected(true);
    }
}
