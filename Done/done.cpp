#include "done.h"

Done::Done(QWidget *parent, QSqlDatabase *db, QSqlQuery *query)
    : QWidget{parent},
      qfont01(new QFont("楷体", 24, QFont::Bold)),
      qfont02(new QFont("楷体", 20, QFont::Bold)),
      qfont03(new QFont("楷体", 16, QFont::Bold)),
      qfont04(new QFont("楷体", 16)),
      mainLayout(new QVBoxLayout(this)),
      titleLayout(new QHBoxLayout()),
      contentLayout(new QVBoxLayout()),
      tableLayout(new QVBoxLayout()),
      qlabel01(new QLabel("已 定", this)),
      db(db),
      query(query),
      sqlgroup(new QStringList()),
      whereclause(new QString()),
      whereclausesql(new QString()),
      Dsearchingdatetime(new QDateTime()),
      Dsearchingdatetime02(new QDateTime()),
      Dsearchingproductcategory(new QString()),
      Dsearchingproductname(new QString()),
      fivebutton(new QHBoxLayout()),
      stackedWidget(new QStackedWidget(this)),
      doneAddWindow(new DoneAdd(stackedWidget, db, query)),
      doneRemoveWindow(new DoneRemove(stackedWidget, db, query)),
      doneChangeWindow(new DoneChange(stackedWidget, db, query)),
      doneSearchWindow(new DoneSearch(stackedWidget,
                                        db, query,
                                        Dsearchingdatetime,
                                        Dsearchingdatetime02,
                                        Dsearchingproductcategory,
                                        Dsearchingproductname)),
      doneadd(new GradientButton(this)),
      doneremove(new GradientButton(this)),
      donechange(new GradientButton(this)),
      donesearch(new GradientButton(this)),
      doneexport(new GradientButton(this)),
      line(new QFrame(this)),
      tableWidget01(new QTableWidget(this)),
      dropdowngradientbutton(new ArrowButton(this)),
      tableWidget02(new QTableWidget(this))
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT 已定编号, 已定时间, 已定类别, 已定名称, 已定数量 "
                     "FROM 已定表 "
                     "ORDER BY 已定编号 DESC");
    /* ORDER BY 已定编号 DESC */
    sqlgroup->append("WITH 已定汇总 AS ( "
                     "SELECT 已定类别 AS 已定汇总类别, 已定名称 AS 已定汇总名称, "
                     "SUM(已定数量) AS 已定汇总数量 "
                     "FROM 已定表 "
                     "GROUP BY 已定类别, 已定名称), "
                     "库存汇总 AS ( "
                     "SELECT 库存类别, 库存名称, SUM(存放数量) AS 库存总量 "
                     "FROM 库存表 "
                     "GROUP BY 库存类别, 库存名称) "
                     "SELECT ROW_NUMBER() OVER "
                     "(ORDER BY 已定汇总类别 DESC, 已定汇总名称 DESC) AS 已定汇总编号, "
                     "已定汇总类别, 已定汇总名称, 已定汇总数量, 库存总量 "
                     "FROM 已定汇总 LEFT JOIN 库存汇总 "
                     "ON 已定汇总类别 = 库存类别 AND 已定汇总名称 = 库存名称 "
                     "ORDER BY 已定汇总编号 DESC");
    /* ORDER BY 已定汇总编号 DESC */
    /* ... OVER (ORDER BY 已定汇总类别 DESC, 已定汇总名称 DESC) AS 已定汇总编号 */
    // 数据库语句***************************************************************************

    // 标题布局*****************************************************************************
    qlabel01->resize(100, 100);
    qlabel01->setFont(*qfont01);
    qlabel01->setAlignment(Qt::AlignCenter);
    titleLayout->addWidget(qlabel01);
    // 标题布局*****************************************************************************

    // 内容布局*****************************************************************************
    // 五个顶栏按钮*************************************************************************
    doneadd->setText("新增已定");
    doneadd->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    doneadd->setFont(*qfont02);
    doneadd->setHoverColor(QColor(240, 240, 240));
    doneadd->setNormalColor(QColor(255, 255, 255));
    doneadd->setCustomStyle("");
    doneremove->setText("删除已定");
    doneremove->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    doneremove->setFont(*qfont02);
    doneremove->setHoverColor(QColor(240, 240, 240));
    doneremove->setNormalColor(QColor(255, 255, 255));
    doneremove->setCustomStyle("");
    donechange->setText("修改已定");
    donechange->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    donechange->setFont(*qfont02);
    donechange->setHoverColor(QColor(240, 240, 240));
    donechange->setNormalColor(QColor(255, 255, 255));
    donechange->setCustomStyle("");
    donesearch->setText("查找已定");
    donesearch->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    donesearch->setFont(*qfont02);
    donesearch->setHoverColor(QColor(240, 240, 240));
    donesearch->setNormalColor(QColor(255, 255, 255));
    donesearch->setCustomStyle("");
    doneexport->setText("导出已定");
    doneexport->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    doneexport->setFont(*qfont02);
    doneexport->setHoverColor(QColor(240, 240, 240));
    doneexport->setNormalColor(QColor(255, 255, 255));
    doneexport->setCustomStyle("");
    fivebutton->addWidget(doneadd);
    fivebutton->addWidget(doneremove);
    fivebutton->addWidget(donechange);
    fivebutton->addWidget(donesearch);
    fivebutton->addWidget(doneexport);
    contentLayout->addLayout(fivebutton);
    // 五个顶栏按钮*************************************************************************
    // stackedWidget**********************************************************************
    stackedWidget->addWidget(doneAddWindow);
    stackedWidget->addWidget(doneRemoveWindow);
    stackedWidget->addWidget(doneChangeWindow);
    stackedWidget->addWidget(doneSearchWindow);
    stackedWidget->setCurrentWidget(doneAddWindow);
    stackedWidget->setStyleSheet(
        "QStackedWidget {"
        "   border: 1px solid #999999;"
        "}"
    );
    stackedWidget->setVisible(false);
    contentLayout->addWidget(stackedWidget);
    // stackedWidget**********************************************************************
    // 两个表格和下拉按钮******************************************************************
    RefreshDoneTableSlot();
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
    // 已定增*******************************************************************************
    connect(doneadd, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == doneAddWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(280);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(doneAddWindow);
        }
    });
    // 已定增*******************************************************************************
    // 已定删*******************************************************************************
    connect(doneremove, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == doneRemoveWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(330);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(doneRemoveWindow);
        }
    });
    // 已定删*******************************************************************************
    // 已定改*******************************************************************************
    connect(donechange, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == doneChangeWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(380);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(doneChangeWindow);
        }
    });
    // 已定改*******************************************************************************
    // 已定查*******************************************************************************
    connect(donesearch, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == doneSearchWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(180);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(doneSearchWindow);
        }
    });
    // 已定查*******************************************************************************
    // 已定导*******************************************************************************
    connect(doneexport, &QPushButton::clicked, this, &Done::SaveFile);
    // 已定导*******************************************************************************
    // 下拉框*******************************************************************************
    connect(dropdowngradientbutton, &QToolButton::clicked,
            this, &Done::toggleTableVisibility);
    // 下拉框*******************************************************************************
    // 选中表1******************************************************************************
    connect(headerView01_row, &QHeaderView::sectionClicked,
             this, &Done::selectColumnOnHeaderClickForTable01);
    // 选中表1******************************************************************************
    // 选中表2******************************************************************************
    connect(headerView02_row, &QHeaderView::sectionClicked,
             this, &Done::selectColumnOnHeaderClickForTable02);
    // 选中表2******************************************************************************
    // 信号与槽*****************************************************************************

    // 窗口属性*****************************************************************************
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    // 窗口属性*****************************************************************************
}
Done::~Done() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete qfont04;
    delete sqlgroup;
    delete whereclause;
    delete whereclausesql;
    delete Dsearchingdatetime;
    delete Dsearchingdatetime02;
    delete Dsearchingproductcategory;
    delete Dsearchingproductname;
    // 删除new对象*************************************************************************
}
void Done::RefreshDoneTableSlot() {
    // 显示已定表***************************************************************************
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
    tableWidget01->setColumnCount(5);
    query->exec(sqlgroup->at(0));
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
    // 水平表头*****************************************************************************
    QStringList headers;
    headers << "已定编号" << "已定时间" << "已定类别" << "已定名称" << "已定数量";
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
    // 显示已定表***************************************************************************

    // 显示已定汇总*************************************************************************
    // 清理以防止内存泄漏******************************************************************
    for (int row = 0; row < tableWidget02->rowCount(); ++row) {
        for (int col = 0; col < tableWidget02->columnCount(); ++col) {
            // 取出项*************************************************************************
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
                if(i == 4 && query->value(4).toInt() < query->value(3).toInt()) {
                    item->setForeground(QBrush(Qt::red));
                }
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
    headers2 << "已定汇总编号" << "已定汇总类别" <<
                "已定汇总名称" << "已定汇总数量" << "库存数量";
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
    // 显示已定汇总*************************************************************************
}
void Done::RefreshDoneTableSlot_DifferentSelect() {
    // 显示筛选的已定表*********************************************************************
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
    tableWidget01->setColumnCount(5);
    *whereclause = "";
    *whereclause += " AND 已定时间 > ? ";
    *whereclause += " AND 已定时间 < ? ";
    if (*Dsearchingproductcategory != "不选择") {
        *whereclause += " AND 已定类别 = ? ";
    }
    if (*Dsearchingproductname != "不选择") {
        *whereclause += " AND 已定名称 = ? ";
    }
    *whereclausesql = "SELECT 已定编号, 已定时间, 已定位置, 已定类别, 已定名称, 已定数量 "
                      "FROM 已定表 WHERE 1 = 1"
            + *whereclause +
            "ORDER BY 已定编号 DESC";
    /* ORDER BY 已定编号 DESC */
    query->prepare(*whereclausesql);
    query->addBindValue(Dsearchingdatetime->addDays(-1));
    query->addBindValue(*Dsearchingdatetime02);
    if (*Dsearchingproductcategory != "不选择") {
        query->addBindValue(*Dsearchingproductcategory);
    }
    if (*Dsearchingproductname != "不选择") {
        query->addBindValue(*Dsearchingproductname);
    }
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
    // 水平表头*****************************************************************************
    QStringList headers;
    headers << "已定编号" << "已定时间" << "已定类别" << "已定名称" << "已定数量";
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
    // 显示筛选的已定表*********************************************************************

    // 显示筛选的已定汇总*******************************************************************
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
    *whereclause += " AND 已定时间 > ? ";
    *whereclause += " AND 已定时间 < ? ";
    if (*Dsearchingproductcategory != "不选择") {
        *whereclause += " AND 已定类别 = ? ";
    }
    if (*Dsearchingproductname != "不选择") {
        *whereclause += " AND 已定名称 = ? ";
    }
    *whereclausesql = "SELECT 已定类别, 已定名称, 已定数量 "
                      "FROM 已定表 WHERE 1 = 1" + *whereclause;
    query->prepare("WITH 已定汇总 AS ( "
                   "SELECT 临时表.已定类别 AS 已定汇总类别, "
                   "临时表.已定名称 AS 已定汇总名称, SUM(临时表.已定数量) AS 已定汇总数量 "
                   "FROM ("
                  + *whereclausesql +
                  ") AS 临时表 "
                  "GROUP BY 临时表.已定类别, 临时表.已定名称), "
                  "库存汇总 AS ( "
                  "SELECT 库存类别, 库存名称, SUM(存放数量) AS 库存总量 "
                  "FROM 库存表 "
                  "GROUP BY 库存类别, 库存名称) "
                  "SELECT ROW_NUMBER() OVER "
                  "(ORDER BY 已定汇总类别 DESC, 已定汇总名称 DESC) AS 已定汇总编号, "
                  "已定汇总类别, 已定汇总名称, 已定汇总数量, 库存总量 "
                  "FROM 已定汇总 LEFT JOIN 库存汇总 "
                  "ON 已定汇总类别 = 库存类别 AND 已定汇总名称 = 库存名称 "
                  "ORDER BY 已定汇总编号 DESC");
    /* ORDER BY 已定汇总编号 DESC */
    /* OVER (ORDER BY 已定汇总类别 DESC, 已定汇总名称 DESC) AS 已定汇总编号 */
    query->addBindValue(Dsearchingdatetime->addDays(-1));
    query->addBindValue(*Dsearchingdatetime02);
    if (*Dsearchingproductcategory != "不选择") {
        query->addBindValue(*Dsearchingproductcategory);
    }
    if (*Dsearchingproductname != "不选择") {
        query->addBindValue(*Dsearchingproductname);
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
                if(i == 4 && query->value(4).toInt() < query->value(3).toInt()) {
                    item->setForeground(QBrush(Qt::red));
                }
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
    headers2 << "已定汇总编号" << "已定汇总类别" <<
                "已定汇总名称" << "已定汇总数量" << "库存数量";
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
    // 显示筛选的已定汇总******************************************************************
}
void Done::SaveFile() {
    QString currentProjectPath = QCoreApplication::applicationDirPath();
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("导出当前已定记录"),
                                                    currentProjectPath,
                                                    tr("Excel 文件 (*.xlsx);;所有文件 (*)"));
    if (!fileName.isEmpty()) {
        QXlsx::Document xlsx;
        // 已定表*****************************************************************************
        xlsx.write(1, 1, "已定编号");
        xlsx.write(1, 2, "已定时间");
        xlsx.write(1, 3, "已定类别");
        xlsx.write(1, 4, "已定名称");
        xlsx.write(1, 5, "已定数量");
        for (int row = 0; row < tableWidget01->rowCount(); ++row) {
            for (int col = 0; col < tableWidget01->columnCount(); ++col) {
                QTableWidgetItem *item = tableWidget01->item(row, col);
                if (item) {
                    QString text = item->text();
                    xlsx.write(row+2, col+1, text);
                }
            }
        }
        // 已定表*****************************************************************************
        // 已定汇总***************************************************************************
        int newrow = tableWidget01->rowCount();
        xlsx.write(newrow+5, 1, "已定汇总编号");
        xlsx.write(newrow+5, 2, "已定汇总类别");
        xlsx.write(newrow+5, 3, "已定汇总名称");
        xlsx.write(newrow+5, 4, "已定汇总数量");
        xlsx.write(newrow+5, 5, "库存数量");
        for (int row = 0; row < tableWidget02->rowCount(); ++row) {
            for (int col = 0; col < tableWidget02->columnCount(); ++col) {
                QTableWidgetItem *item = tableWidget02->item(row, col);
                if (item) {
                    QString text = item->text();
                    xlsx.write(newrow+row+6, col+1, text);
                }
            }
        }
        // 已定汇总***************************************************************************
        xlsx.saveAs(fileName);
    }
}
void Done::toggleTableVisibility() {
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
void Done::selectColumnOnHeaderClickForTable01(int column) {
    tableWidget01->clearSelection();
    for (int row = 0; row < tableWidget01->rowCount(); ++row)
    {
        tableWidget01->item(row, column)->setSelected(true);
    }
}
void Done::selectColumnOnHeaderClickForTable02(int column) {
    tableWidget02->clearSelection();
    for (int row = 0; row < tableWidget02->rowCount(); ++row)
    {
        tableWidget02->item(row, column)->setSelected(true);
    }
}
