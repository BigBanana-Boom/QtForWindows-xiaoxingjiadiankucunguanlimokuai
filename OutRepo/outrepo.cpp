#include "outrepo.h"

OutRepo::OutRepo(QWidget *parent, QSqlDatabase *db, QSqlQuery *query)
    : QWidget{parent},
    qfont01(new QFont("楷体", 24, QFont::Bold)),
    qfont02(new QFont("楷体", 20, QFont::Bold)),
    qfont03(new QFont("楷体", 16, QFont::Bold)),
    qfont04(new QFont("楷体", 16)),
    mainLayout(new QVBoxLayout(this)),
    titleLayout(new QHBoxLayout()),
    contentLayout(new QVBoxLayout()),
    tableLayout(new QVBoxLayout()),
    qlabel01(new QLabel("出 库", this)),
    db(db),
    query(query),
    sqlgroup(new QStringList()),
    whereclause(new QString()),
    whereclausesql(new QString()),
    ORsearchingdatetime(new QDateTime()),
    ORsearchingdatetime02(new QDateTime()),
    ORsearchingrepo(new QString()),
    ORsearchingproductcategory(new QString()),
    ORsearchingproductname(new QString()),
    fivebutton(new QHBoxLayout()),
    stackedWidget(new QStackedWidget(this)),
    outRepoAddWindow(new OutRepoAdd(stackedWidget, db, query)),
    outRepoRemoveWindow(new OutRepoRemove(stackedWidget, db, query)),
    outRepoChangeWindow(new OutRepoChange(stackedWidget, db, query)),
    outRepoSearchWindow(new OutRepoSearch(stackedWidget, db, query,
                                            ORsearchingdatetime,
                                            ORsearchingdatetime02,
                                            ORsearchingproductcategory,
                                            ORsearchingproductname,
                                            ORsearchingrepo)),
    outrepoadd(new GradientButton(this)),
    outreporemove(new GradientButton(this)),
    outrepochange(new GradientButton(this)),
    outreposearch(new GradientButton(this)),
    outrepoexport(new GradientButton(this)),
    line(new QFrame(this)),
    tableWidget01(new QTableWidget(this)),
    dropdowngradientbutton(new ArrowButton(this)),
    tableWidget02(new QTableWidget(this))
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT 出库编号, 出库时间, 出库类别, 出库名称, 出库位置, 出库数量 "
                     "FROM 出库表 "
                     "ORDER BY 出库编号 DESC");
    /* ORDER BY 出库编号 DESC */
    sqlgroup->append("WITH 出库汇总 AS ( "
                     "SELECT 出库类别 AS 出库汇总类别, 出库名称 AS 出库汇总名称, "
                     "SUM(出库数量) AS 出库汇总数量 "
                     "FROM 出库表 "
                     "GROUP BY 出库类别, 出库名称), "
                     "库存汇总 AS ( "
                     "SELECT 库存类别 AS 库存汇总类别, 库存名称 AS 库存汇总名称, "
                     "SUM(存放数量) AS 库存汇总数量 "
                     "FROM 库存表 "
                     "GROUP BY 库存类别, 库存名称) "
                     "SELECT ROW_NUMBER() OVER "
                     "(ORDER BY 出库汇总类别 DESC, 出库汇总名称 DESC) AS 出库汇总编号, "
                     "出库汇总类别, 出库汇总名称, 出库汇总数量, "
                     "COALESCE(库存汇总数量, 0) AS 当前库存数量 "
                     "FROM 出库汇总 LEFT JOIN 库存汇总 "
                     "ON 出库汇总.出库汇总类别 = 库存汇总.库存汇总类别 AND "
                     "出库汇总.出库汇总名称 = 库存汇总.库存汇总名称 "
                     "ORDER BY 出库汇总编号 DESC");
    /* ORDER BY 出库汇总编号 DESC */
    /* OVER (ORDER BY 出库汇总类别 DESC, 出库汇总名称 DESC) AS 出库汇总编号 */
    // 数据库语句***************************************************************************

    // 标题布局*****************************************************************************
    qlabel01->resize(100, 100);
    qlabel01->setFont(*qfont01);
    qlabel01->setAlignment(Qt::AlignCenter);
    titleLayout->addWidget(qlabel01);
    // 标题布局*****************************************************************************

    // 内容布局*****************************************************************************
    // 五个顶栏按钮*************************************************************************
    outrepoadd->setText("新增出库");
    outrepoadd->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    outrepoadd->setFont(*qfont02);
    outrepoadd->setHoverColor(QColor(240, 240, 240));
    outrepoadd->setNormalColor(QColor(255, 255, 255));
    outrepoadd->setCustomStyle("");
    outreporemove->setText("删除出库");
    outreporemove->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    outreporemove->setFont(*qfont02);
    outreporemove->setHoverColor(QColor(240, 240, 240));
    outreporemove->setNormalColor(QColor(255, 255, 255));
    outreporemove->setCustomStyle("");
    outrepochange->setText("修改出库");
    outrepochange->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    outrepochange->setFont(*qfont02);
    outrepochange->setHoverColor(QColor(240, 240, 240));
    outrepochange->setNormalColor(QColor(255, 255, 255));
    outrepochange->setCustomStyle("");
    outreposearch->setText("查找出库");
    outreposearch->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    outreposearch->setFont(*qfont02);
    outreposearch->setHoverColor(QColor(240, 240, 240));
    outreposearch->setNormalColor(QColor(255, 255, 255));
    outreposearch->setCustomStyle("");
    outrepoexport->setText("导出出库");
    outrepoexport->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    outrepoexport->setFont(*qfont02);
    outrepoexport->setHoverColor(QColor(240, 240, 240));
    outrepoexport->setNormalColor(QColor(255, 255, 255));
    outrepoexport->setCustomStyle("");
    fivebutton->addWidget(outrepoadd);
    fivebutton->addWidget(outreporemove);
    fivebutton->addWidget(outrepochange);
    fivebutton->addWidget(outreposearch);
    fivebutton->addWidget(outrepoexport);
    contentLayout->addLayout(fivebutton);
    // 五个顶栏按钮*************************************************************************
    // stackedWidget**********************************************************************
    stackedWidget->addWidget(outRepoAddWindow);
    stackedWidget->addWidget(outRepoRemoveWindow);
    stackedWidget->addWidget(outRepoChangeWindow);
    stackedWidget->addWidget(outRepoSearchWindow);
    stackedWidget->setCurrentWidget(outRepoAddWindow);
    stackedWidget->setStyleSheet(
        "QStackedWidget {"
        "   border: 1px solid #999999;"
        "}"
    );
    contentLayout->addWidget(stackedWidget);
    stackedWidget->setVisible(false);
    // stackedWidget**********************************************************************
    // 两个表格和下拉按钮******************************************************************
    RefreshOutRepoTableSlot();
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
    // 出库增*******************************************************************************
    connect(outrepoadd, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == outRepoAddWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(295);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(outRepoAddWindow);
        }
    });
    // 出库增*******************************************************************************
    // 出库删*******************************************************************************
    connect(outreporemove, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == outRepoRemoveWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(332);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(outRepoRemoveWindow);
        }
    });
    // 出库删*******************************************************************************
    // 出库改*******************************************************************************
    connect(outrepochange, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == outRepoChangeWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(332);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(outRepoChangeWindow);
        }
    });
    // 出库改*******************************************************************************
    // 出库查*******************************************************************************
    connect(outreposearch, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == outRepoSearchWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(180);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(outRepoSearchWindow);
        }
    });
    // 出库查*******************************************************************************
    // 出库导*******************************************************************************
    connect(outrepoexport, &QPushButton::clicked, this, &OutRepo::SaveFile);
    // 出库导*******************************************************************************
    // 下拉框*******************************************************************************
    connect(dropdowngradientbutton, &QToolButton::clicked,
            this, &OutRepo::toggleTableVisibility);
    // 下拉框*******************************************************************************
    // 选中表1******************************************************************************
    connect(headerView01_row, &QHeaderView::sectionClicked,
             this, &OutRepo::selectColumnOnHeaderClickForTable01);
    // 选中表1******************************************************************************
    // 选中表2******************************************************************************
    connect(headerView02_row, &QHeaderView::sectionClicked,
             this, &OutRepo::selectColumnOnHeaderClickForTable02);
    // 选中表2******************************************************************************
    // 信号与槽*****************************************************************************
    // 窗口属性*****************************************************************************
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    // 窗口属性*****************************************************************************
}
OutRepo::~OutRepo() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete qfont04;
    delete sqlgroup;
    delete whereclause;
    delete whereclausesql;
    delete ORsearchingdatetime;
    delete ORsearchingdatetime02;
    delete ORsearchingrepo;
    delete ORsearchingproductcategory;
    delete ORsearchingproductname;
    // 删除new对象*************************************************************************
}
void OutRepo::RefreshOutRepoTableSlot() {
    // 显示出库表***************************************************************************
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
    headers << "出库编号" << "出库时间" << "出库类别" <<
               "出库名称" << "出库位置" << "出库数量";
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
    // 显示出库表***************************************************************************

    // 显示出库汇总*************************************************************************
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
    headers2 << "出库汇总编号" << "出库汇总类别" << "出库汇总名称" << "出库汇总数量"
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
    // 显示出库汇总*************************************************************************
}
void OutRepo::RefreshOutRepoTableSlot_DifferentSelect() {
    // 显示筛选的出库表*********************************************************************
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
    *whereclause += " AND 出库时间 > ? ";
    *whereclause += " AND 出库时间 < ? ";
    if (*ORsearchingrepo != "不选择") {
        *whereclause += " AND 出库位置 = ? ";
    }
    if (*ORsearchingproductcategory != "不选择") {
        *whereclause += " AND 出库类别 = ? ";
    }
    if (*ORsearchingproductname != "不选择") {
        *whereclause += " AND 出库名称 = ? ";
    }
    *whereclausesql = "SELECT 出库编号, 出库时间, 出库类别, 出库名称, 出库位置, 出库数量 "
                      "FROM 出库表 WHERE 1 = 1"
            + *whereclause +
            "ORDER BY 出库编号 DESC";
    /* ORDER BY 出库编号 DESC */
    query->prepare(*whereclausesql);
    query->addBindValue(ORsearchingdatetime->addDays(-1));
    query->addBindValue(*ORsearchingdatetime02);
    if (*ORsearchingrepo != "不选择") {
        query->addBindValue(*ORsearchingrepo);
    }
    if (*ORsearchingproductcategory != "不选择") {
        query->addBindValue(*ORsearchingproductcategory);
    }
    if (*ORsearchingproductname != "不选择") {
        query->addBindValue(*ORsearchingproductname);
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
    headers << "出库编号" << "出库时间" << "出库类别" <<
               "出库名称" << "出库位置" << "出库数量";
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
    // 显示筛选的出库表*********************************************************************

    // 显示筛选的出库汇总*******************************************************************
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
    *whereclause += " AND 出库时间 > ? ";
    *whereclause += " AND 出库时间 < ? ";
    if (*ORsearchingrepo != "不选择") {
        *whereclause += " AND 出库位置 = ? ";
    }
    if (*ORsearchingproductcategory != "不选择") {
        *whereclause += " AND 出库类别 = ? ";
    }
    if (*ORsearchingproductname != "不选择") {
        *whereclause += " AND 出库名称 = ? ";
    }
    *whereclausesql = "SELECT 出库类别, 出库名称, 出库数量 "
                      "FROM 出库表 WHERE 1 = 1" + *whereclause;
    query->prepare("WITH 出库汇总 AS ( "
                   "SELECT 临时表.出库类别 AS 出库汇总类别, "
                   "临时表.出库名称 AS 出库汇总名称, SUM(临时表.出库数量) AS 出库汇总数量 "
                   "FROM ("
                  + *whereclausesql +
                  ") AS 临时表 "
                  "GROUP BY 临时表.出库类别, 临时表.出库名称), "
                  "库存汇总 AS ( "
                  "SELECT 库存类别 AS 库存汇总类别, 库存名称 AS 库存汇总名称, "
                  "SUM(存放数量) AS 库存汇总数量 "
                  "FROM 库存表 "
                  "GROUP BY 库存类别, 库存名称) "
                  "SELECT ROW_NUMBER() OVER "
                  "(ORDER BY 出库汇总类别 DESC, 出库汇总名称 DESC) AS 出库汇总编号, "
                  "出库汇总类别, 出库汇总名称, 出库汇总数量, "
                  "COALESCE(库存汇总数量, 0) AS 当前库存数量 "
                  "FROM 出库汇总 LEFT JOIN 库存汇总 "
                  "ON 出库汇总.出库汇总类别 = 库存汇总.库存汇总类别 AND "
                  "出库汇总.出库汇总名称 = 库存汇总.库存汇总名称 "
                  "ORDER BY 出库汇总编号 DESC");
    /* ORDER BY 出库汇总编号 DESC */
    /* OVER (ORDER BY 出库汇总类别 DESC, 出库汇总名称 DESC) AS 出库汇总编号 */
    query->addBindValue(ORsearchingdatetime->addDays(-1));
    query->addBindValue(*ORsearchingdatetime02);
    if (*ORsearchingrepo != "不选择") {
        query->addBindValue(*ORsearchingrepo);
    }
    if (*ORsearchingproductcategory != "不选择") {
        query->addBindValue(*ORsearchingproductcategory);
    }
    if (*ORsearchingproductname != "不选择") {
        query->addBindValue(*ORsearchingproductname);
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
    headers2 << "出库汇总编号" << "出库汇总类别" << "出库汇总名称" << "出库汇总数量"
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
    // 显示筛选的出库汇总*******************************************************************
}
void OutRepo::SaveFile() {
    QString currentProjectPath = QCoreApplication::applicationDirPath();
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("导出当前出库记录"),
                                                    currentProjectPath,
                                                    tr("Excel 文件 (*.xlsx);;所有文件 (*)"));
    if (!fileName.isEmpty()) {
        QXlsx::Document xlsx;
        // 出库表*****************************************************************************
        xlsx.write(1, 1, "出库编号");
        xlsx.write(1, 2, "出库时间");
        xlsx.write(1, 3, "出库类别");
        xlsx.write(1, 4, "出库名称");
        xlsx.write(1, 5, "出库位置");
        xlsx.write(1, 6, "出库数量");
        for (int row = 0; row < tableWidget01->rowCount(); ++row) {
            for (int col = 0; col < tableWidget01->columnCount(); ++col) {
                QTableWidgetItem *item = tableWidget01->item(row, col);
                if (item) {
                    QString text = item->text();
                    xlsx.write(row+2, col+1, text);
                }
            }
        }
        // 出库表*****************************************************************************
        // 出库汇总***************************************************************************
        int newrow = tableWidget01->rowCount();
        xlsx.write(newrow+5, 1, "出库汇总编号");
        xlsx.write(newrow+5, 2, "出库汇总类别");
        xlsx.write(newrow+5, 3, "出库汇总名称");
        xlsx.write(newrow+5, 4, "出库汇总数量");
        for (int row = 0; row < tableWidget02->rowCount(); ++row) {
            for (int col = 0; col < tableWidget02->columnCount(); ++col) {
                QTableWidgetItem *item = tableWidget02->item(row, col);
                if (item) {
                    QString text = item->text();
                    xlsx.write(newrow+row+6, col+1, text);
                }
            }
        }
        // 出库汇总***************************************************************************
        xlsx.saveAs(fileName);
    }
}
void OutRepo::toggleTableVisibility() {
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
void OutRepo::selectColumnOnHeaderClickForTable01(int column) {
    tableWidget01->clearSelection();
    for (int row = 0; row < tableWidget01->rowCount(); ++row)
    {
        tableWidget01->item(row, column)->setSelected(true);
    }
}
void OutRepo::selectColumnOnHeaderClickForTable02(int column) {
    tableWidget02->clearSelection();
    for (int row = 0; row < tableWidget02->rowCount(); ++row)
    {
        tableWidget02->item(row, column)->setSelected(true);
    }
}
