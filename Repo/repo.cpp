#include "repo.h"
#include <QLabel>
#include <QTableWidget>
#include <QSqlQuery>
#include <QVariant>
#include <QHeaderView>

Repo::Repo(QWidget *parent,
           QSqlDatabase *db,
           QSqlQuery *query)
    : QWidget{parent},
    qfont01(new QFont("楷体", 24, QFont::Bold)),
    qfont02(new QFont("楷体", 20, QFont::Bold)),
    qfont03(new QFont("楷体", 16, QFont::Bold)),
    qfont04(new QFont("楷体", 16)),
    mainLayout(new QVBoxLayout(this)),
    titleLayout(new QHBoxLayout()),
    contentLayout(new QVBoxLayout()),
    tableLayout(new QVBoxLayout()),
    qlabel01(new QLabel("库 存", this)),
    db(db),
    query(query),
    sqlgroup(new QStringList()),
    whereclause(new QString()),
    whereclausesql(new QString()),
    Rsearchingrepo(new QString()),
    Rsearchingproductcategory(new QString()),
    Rsearchingproductname(new QString()),
    fivebutton(new QHBoxLayout()),
    stackedWidget(new QStackedWidget(this)),
    repoModifyWindow(new RepoModify(stackedWidget, db, query)),
    repoAdjustWindow(new RepoAdjust(stackedWidget, db, query)),
    repoChangeWindow(new RepoChange(stackedWidget, db, query)),
    repoSearchWindow(new RepoSearch(stackedWidget, db, query,
                                    Rsearchingproductcategory,
                                    Rsearchingproductname,
                                    Rsearchingrepo)),
    repomodify(new NormalGradientButton(this)),
    repoadjust(new NormalGradientButton(this)),
    repochange(new NormalGradientButton(this)),
    reposearch(new NormalGradientButton(this)),
    repoexport(new NormalGradientButton(this)),
    line(new QFrame(this)),
    tableWidget01(new QTableWidget(this)),
    dropdowngradientbutton(new DropDownGradientButton(this)),
    tableWidget02(new QTableWidget(this))
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT 库存编号, 库存类别, 库存名称, "
                     "存放位置, 存放数量 FROM 库存表 "
                     "ORDER BY 库存编号 DESC");
    /* ORDER BY 库存编号 DESC */
    sqlgroup->append("SELECT 调库编号, 调库时间, 库存类别, 库存名称, 库存位置, 库存变化 "
                     "FROM 附表3库存调整表 "
                     "ORDER BY 调库编号 DESC");
    /* ORDER BY 调库编号 DESC */
    // 数据库语句***************************************************************************

    // 标题布局******************************************************************************
    qlabel01->resize(100, 100);
    qlabel01->setFont(*qfont01);
    qlabel01->setAlignment(Qt::AlignCenter);
    titleLayout->addWidget(qlabel01);
    // 标题布局******************************************************************************

    // 内容布局******************************************************************************
    // 五个顶栏按钮*************************************************************************
    repomodify->setText("库存盘点");
    repomodify->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    repomodify->setFont(*qfont02);
    repoadjust->setText("库存转存");
    repoadjust->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    repoadjust->setFont(*qfont02);
    repochange->setText("库存修改");
    repochange->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    repochange->setFont(*qfont02);
    reposearch->setText("库存查找");
    reposearch->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    reposearch->setFont(*qfont02);
    repoexport->setText("库存导出");
    repoexport->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    repoexport->setFont(*qfont02);
    fivebutton->addWidget(repomodify);
    fivebutton->addWidget(repoadjust);
    fivebutton->addWidget(repochange);
    fivebutton->addWidget(reposearch);
    fivebutton->addWidget(repoexport);
    contentLayout->addLayout(fivebutton);
    // 五个顶栏按钮*************************************************************************
    // stackedWidget**********************************************************************
    stackedWidget->addWidget(repoModifyWindow);
    stackedWidget->addWidget(repoAdjustWindow);
    stackedWidget->addWidget(repoChangeWindow);
    stackedWidget->addWidget(repoSearchWindow);
    stackedWidget->setStyleSheet(
        "QStackedWidget {"
        "   border: 1px solid #999999;"
        "}"
    );
    contentLayout->addWidget(stackedWidget);
    stackedWidget->setVisible(false);
    // stackedWidget**********************************************************************
    // 两个表格和下拉按钮******************************************************************
    RefreshRepoTableSlot();
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
    // 盘库存*******************************************************************************
    connect(repomodify, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == repoModifyWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(295);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(repoModifyWindow);
        }
    });
    // 盘库存*******************************************************************************
    // 调库存*******************************************************************************
    connect(repoadjust, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == repoAdjustWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(332);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(repoAdjustWindow);
        }
    });
    // 调库存*******************************************************************************
    // 改库存*******************************************************************************
    connect(repochange, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == repoChangeWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(217);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(repoChangeWindow);
        }
    });
    // 改库存*******************************************************************************
    // 查库存*******************************************************************************
    connect(reposearch, &QPushButton::clicked, this, [this]() {
        if(stackedWidget->isVisible() &&
                stackedWidget->currentWidget() == repoSearchWindow) {
            stackedWidget->setVisible(false);
        } else {
            stackedWidget->setFixedHeight(130);
            stackedWidget->setVisible(true);
            stackedWidget->setCurrentWidget(repoSearchWindow);
        }
    });
    // 查库存*******************************************************************************
    // 导库存*******************************************************************************
    connect(repoexport, &QPushButton::clicked, this, &Repo::SaveFile);
    // 导库存*******************************************************************************
    // 下拉框*******************************************************************************
    connect(dropdowngradientbutton, &QToolButton::clicked,
            this, &Repo::toggleTableVisibility);
    // 下拉框*******************************************************************************
    // 调库表表头***************************************************************************
    connect(headerView02_row, &QHeaderView::sortIndicatorChanged, this,
            &Repo::onSortIndicatorChanged);
    // 调库表表头***************************************************************************
    // 选中表1******************************************************************************
    connect(headerView01_row, &QHeaderView::sectionClicked,
             this, &Repo::selectColumnOnHeaderClickForTable01);
    // 选中表1******************************************************************************
    // 选中表2******************************************************************************
    connect(headerView02_row, &QHeaderView::sectionClicked,
             this, &Repo::selectColumnOnHeaderClickForTable02);
    // 选中表2******************************************************************************
    // 信号与槽*****************************************************************************

    // 窗口属性*****************************************************************************
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    // 窗口属性*****************************************************************************
}
Repo::~Repo() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete qfont04;
    delete sqlgroup;
    delete whereclause;
    delete whereclausesql;
    delete Rsearchingrepo;
    delete Rsearchingproductcategory;
    delete Rsearchingproductname;
    // 删除new对象*************************************************************************
}
void Repo::RefreshRepoTableSlot() {
    // 显示库存表***************************************************************************
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
    headers << "库存编号" << "库存类别" << "库存名称" << "存放位置" << "存放数量";
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
    // 显示库存表***************************************************************************

    // 显示调库表***************************************************************************
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
    tableWidget02->setColumnCount(6);
    query->exec(sqlgroup->at(1));
    row = 0;
    while (query->next()) {
        tableWidget02->insertRow(tableWidget02->rowCount());
        for(int i = 0; i < 6; i++) {
            if(i == 0) {
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
    headers2 << "调库编号" << "调库时间" << "库存类别" <<
                "库存名称" << "库存位置" << "库存变化";
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
    // 显示调库表***************************************************************************
}
void Repo::RefreshRepoTableSlot_DifferentSelect() {
    // 显示筛选的库存表*********************************************************************
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
    if (*Rsearchingrepo != "不选择") {
        *whereclause += " AND 存放位置 = ? ";
    }
    if (*Rsearchingproductcategory != "不选择") {
        *whereclause += " AND 库存类别 = ? ";
    }
    if (*Rsearchingproductname != "不选择") {
        *whereclause += " AND 库存名称 = ? ";
    }
    *whereclausesql = "SELECT 库存编号, 库存类别, 库存名称, "
                      "存放位置 存放数量 FROM 库存表 WHERE 1 = 1"
            +*whereclause+
            "ORDER BY 库存编号 DESC";
    /* ORDER BY 库存编号 DESC */
    query->prepare(*whereclausesql);
    if (*Rsearchingrepo != "不选择") {
        query->addBindValue(*Rsearchingrepo);
    }
    if (*Rsearchingproductcategory != "不选择") {
        query->addBindValue(*Rsearchingproductcategory);
    }
    if (*Rsearchingproductname != "不选择") {
        query->addBindValue(*Rsearchingproductname);
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
    headers << "库存编号" << "库存类别" << "库存名称" << "存放位置" << "存放数量";
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
    // 显示筛选的库存表*********************************************************************
}
void Repo::SaveFile() {
    QString currentProjectPath = QCoreApplication::applicationDirPath();
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("导出当前库存记录"),
                                                    currentProjectPath,
                                                    tr("Excel 文件 (*.xlsx);;所有文件 (*)"));
    if (!fileName.isEmpty()) {
        QXlsx::Document xlsx;
        // 库存表*****************************************************************************
        xlsx.write(1, 1, "库存编号");
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
        // 库存表*****************************************************************************
        // 调库表*****************************************************************************
        int newrow = tableWidget01->rowCount();
        xlsx.write(newrow+5, 1, "调库编号");
        xlsx.write(newrow+5, 2, "调库时间");
        xlsx.write(newrow+5, 3, "库存类别");
        xlsx.write(newrow+5, 4, "库存名称");
        xlsx.write(newrow+5, 5, "库存位置");
        xlsx.write(newrow+5, 6, "库存变化");
        for (int row = 0; row < tableWidget02->rowCount(); ++row) {
            for (int col = 0; col < tableWidget02->columnCount(); ++col) {
                QTableWidgetItem *item = tableWidget02->item(row, col);
                if (item) {
                    QString text = item->text();
                    xlsx.write(newrow+row+6, col+1, text);
                }
            }
        }
        // 调库表*****************************************************************************
        xlsx.saveAs(fileName); // 使用实际的文件名变量
    }
}
void Repo::toggleTableVisibility() {
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
void Repo::onSortIndicatorChanged(int column, Qt::SortOrder order) {
    if(column == 5) {
        tableWidget02->setSortingEnabled(false);
        CustomSort(order);
    } else {
        tableWidget02->setSortingEnabled(true);
    }
}
void Repo::CustomSort(Qt::SortOrder order) {
    int rowCount = tableWidget02->rowCount();
    int columnCount = tableWidget02->columnCount();
    // 整数值和行索引对*******************************************************************
    QVector<QPair<int, int>> intData;
    // 整数值和行索引对*******************************************************************
    // 记录表全部内容*********************************************************************
    QVector<QVector<QString>> textVector;
    // 记录表全部内容*********************************************************************
    // 填充QVector***********************************************************************
    for(int row = 0; row < rowCount; ++row) {
        QString text = tableWidget02->item(row, 5)->text();
        int number = convertToInt(text);
        intData.append(qMakePair(number, row));

        QVector<QString> rowData;
        for (int column = 0; column < columnCount; ++column) {
            QTableWidgetItem *item = tableWidget02->item(row, column);
            rowData.append(item->text());
        }
        textVector.append(rowData);
    }
    // 填充QVector***********************************************************************
    // 根据整数排序***********************************************************************
    std::sort(intData.begin(), intData.end(),
              [order](const QPair<int, int>& a, const QPair<int, int>& b) {
        return order == Qt::AscendingOrder ? a.first < b.first : a.first > b.first;
    });
    // 根据整数排序***********************************************************************
    // 调整表格行顺序*********************************************************************
    tableWidget02->clearContents();
    tableWidget02->setRowCount(0);
    tableWidget02->setColumnCount(6);
    for(int row = 0; row < rowCount; ++row) {
        tableWidget02->insertRow(tableWidget02->rowCount());
        int sourceRow = intData[row].second;
        for(int column = 0; column < columnCount; ++column) {
            QTableWidgetItem *item =
                    new QTableWidgetItem(textVector[sourceRow][column]);
            item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
            tableWidget02->setItem(row, column, item);
        }
    }
    // 调整表格行顺序*********************************************************************
}
int Repo::convertToInt(const QString text) {
    bool isPositive = text.startsWith("+");
    int number = text.mid(1).toInt();
    return isPositive ? number : -number;
}
void Repo::selectColumnOnHeaderClickForTable01(int column) {
    tableWidget01->clearSelection();
    for (int row = 0; row < tableWidget01->rowCount(); ++row)
    {
        tableWidget01->item(row, column)->setSelected(true);
    }
}
void Repo::selectColumnOnHeaderClickForTable02(int column) {
    tableWidget02->clearSelection();
    for (int row = 0; row < tableWidget02->rowCount(); ++row)
    {
        tableWidget02->item(row, column)->setSelected(true);
    }
}
