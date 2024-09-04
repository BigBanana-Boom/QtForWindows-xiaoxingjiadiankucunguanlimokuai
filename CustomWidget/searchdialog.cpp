#include "searchdialog.h"

SearchDialog::SearchDialog(bool resizeEnable,
                           bool shadowBorder,
                           bool winNativeEvent,
                           QWidget *parent,
                           QSqlDatabase *db,
                           QSqlQuery *query,
                           int *returnid)
    : QFramelessDialog(parent, resizeEnable, shadowBorder, winNativeEvent),
      qfont01(new QFont("楷体", 20, QFont::Bold)),
      qfont02(new QFont("楷体", 18, QFont::Bold)),
      qfont03(new QFont("楷体", 16, QFont::Bold)),
      qfont04(new QFont("楷体", 16)),
      TotalVLayout(new QVBoxLayout()),
      titleWidget(new QWidget(this)),
      titleWidgetHLayout(new QHBoxLayout()),
      labelIcon(new QLabel(this)),
      labelTitle(new QLabel(this)),
      closeVLayout(new QVBoxLayout()),
      closebutton(new ExitGradientButton(this)),
      line(new QFrame(this)),
      contentWidget(new QWidget(this)),
      contentWidgetVLayout(new QVBoxLayout()),
      contentWidgetTitle(new QLabel(this)),
      qlineedit(new QLineEdit(this)),
      yesbutton(new DialogGradientButton(this)),
      rowOneHLayout(new QHBoxLayout()),
      qtablewidget(new QTableWidget(this)),
      line2(new QFrame(this)),
      buttonWidget(new QWidget(this)),
      ButtonHLayout(new QHBoxLayout()),
      AcceptButton(new DialogGradientButton(this)),
      db(db),
      query(query),
      sqlgroup(new QStringList()),
      whereclause(new QString()),
      whereclausesql(new QString()),
      tablename(new QString())
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT * FROM 已定表 ORDER BY 已定编号 DESC");
    /* ORDER BY 已定编号 DESC */
    sqlgroup->append("SELECT * FROM 出库表 ORDER BY 出库编号 DESC");
    /* ORDER BY 出库编号 DESC */
    sqlgroup->append("SELECT * FROM 入库表 ORDER BY 入库编号 DESC");
    /* ORDER BY 入库编号 DESC */
    sqlgroup->append("SELECT * FROM 库存表 ORDER BY 库存编号 DESC");
    /* ORDER BY 库存编号 DESC */
    sqlgroup->append("SELECT * FROM 附表2进货产品表 ORDER BY 产品编号 DESC");
    /* ORDER BY 产品编号 DESC */
    // 数据库语句***************************************************************************

    // 总布局****************************************************************************
    setLayout(TotalVLayout);
    TotalVLayout->setSpacing(0);
    TotalVLayout->setContentsMargins(0, 0, 0, 0);
    // 总布局****************************************************************************

    // 标题器件**************************************************************************
    titleWidget->setLayout(titleWidgetHLayout);
    TotalVLayout->addWidget(titleWidget);
    // 左侧******************************************************************************
    QPixmap pixmap(":/Image/BrokenRice.png");
    // 变大小，保持原始宽高比，切换尽可能平滑*****************************************
    pixmap = pixmap.scaled(30, 30,
                           Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // 变大小，保持原始宽高比，切换尽可能平滑*****************************************
    // 为QLabel设置图像****************************************************************
    labelIcon->setPixmap(pixmap);
    // 为QLabel设置图像****************************************************************
    // 设置QLabel左右外边距，这样不紧贴左边，也不紧贴名称***************************
    labelIcon->setContentsMargins(16, 0, 16, 0);
    // 设置QLabel左右外边距，这样不紧贴左边，也不紧贴名称***************************
    labelTitle->setText("坏米饭");
    labelTitle->setFont(*qfont01);
    titleWidgetHLayout->addWidget(labelIcon);
    titleWidgetHLayout->addWidget(labelTitle);
    titleWidgetHLayout->addStretch(1);
    // 左侧******************************************************************************
    // 右侧******************************************************************************
    // closebutton用的是专有的类，只这样设置就行************************************
    closebutton->setFixedSize(QSize(60, 43));
    // closebutton用的是专有的类，只这样设置就行************************************
    closeVLayout->addWidget(closebutton);
    closeVLayout->addStretch(1);
    titleWidgetHLayout->addLayout(closeVLayout);
    // 右侧******************************************************************************
    // 设置固定高度，更加稳定**********************************************************
    titleWidget->setFixedHeight(50);
    // 设置固定高度，更加稳定**********************************************************
    titleWidgetHLayout->setSpacing(0);
    titleWidgetHLayout->setContentsMargins(0, 0, 0, 0);
    // 标题器件**************************************************************************

    // 标题器件与内容器件之间的分割线**************************************************
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setFixedHeight(2);
    QFile file(":/Qss/SeperateLine.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    QString stylesheet = in.readAll();
    line->setStyleSheet(stylesheet);
    file.close();
    TotalVLayout->addWidget(line);
    // 标题器件与内容器件之间的分割线**************************************************

    // 内容器件**************************************************************************
    contentWidget->setLayout(contentWidgetVLayout);
    TotalVLayout->addWidget(contentWidget);
    // 标题******************************************************************************
    contentWidgetTitle->setText("新 增 已 定");
    contentWidgetTitle->setFont(*qfont02);
    contentWidgetTitle->setAlignment(Qt::AlignCenter);
    contentWidgetVLayout->addWidget(contentWidgetTitle);
    // 标题******************************************************************************
    // 第一行****************************************************************************
    qlineedit->setFont(*qfont04);
    yesbutton->setText("确定");
    yesbutton->setFont(*qfont03);
    yesbutton->setFixedHeight(40);
    rowOneHLayout->addWidget(qlineedit, 1);
    rowOneHLayout->addWidget(yesbutton);
    contentWidgetVLayout->addLayout(rowOneHLayout);
    // 第一行****************************************************************************
    // 表格******************************************************************************
    if(*tablename == "已定表") {
        RefreshDoneTable();
    } else if(*tablename == "出库表") {
        RefreshOutRepoTable();
    } else if(*tablename == "入库表") {
        RefreshInRepoTable();
    } else if(*tablename == "库存表") {
        RefreshRepoTable();
    } else {
        RefreshInRepoInfoTable();
    }
    contentWidgetVLayout->addWidget(qtablewidget);
    // 表格******************************************************************************
    // 跟该Pro的其它保持一致***********************************************************
    contentWidgetVLayout->setSpacing(8);
    contentWidgetVLayout->setContentsMargins(20, 8, 20, 8);
    // 跟该Pro的其它保持一致***********************************************************
    contentWidget->setMinimumHeight(490);
    // 内容器件**************************************************************************

    // 内容器件与按钮器件之间的分割线**************************************************
    TotalVLayout->addSpacing(20);
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    line2->setFixedHeight(2);
    file.setFileName(":/Qss/SeperateLine.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    in.setDevice(&file);
    line2->setStyleSheet(in.readAll());
    file.close();
    TotalVLayout->addWidget(line2);
    // 内容器件与按钮器件之间的分割线**************************************************

    // 按钮器件**************************************************************************
    buttonWidget->setLayout(ButtonHLayout);
    TotalVLayout->addWidget(buttonWidget);
    AcceptButton->setFont(*qfont02);
    AcceptButton->setText("确定");
    AcceptButton->setFixedHeight(40);
    AcceptButton->setFixedWidth(200);
    ButtonHLayout->addStretch(1);
    ButtonHLayout->addWidget(AcceptButton);
    // 按钮器件**************************************************************************

    // 窗口属性**************************************************************************
    framelessHelper()->setTitleBar(titleWidget);
    setMinimumWidth(900);
    setMinimumHeight(629);
    setWindowIcon(QIcon(":/Image/BrokenRice.png"));
    // 窗口属性**************************************************************************

    // 信号与槽**************************************************************************
    connect(closebutton, &QPushButton::clicked,
            this, &SearchDialog::onCloseButtonClicked);
    connect(AcceptButton, &QPushButton::clicked, this, [this]() {
        accept();
    });
    // 信号与槽**************************************************************************
}
SearchDialog::~SearchDialog() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete qfont04;
    delete sqlgroup;
    delete whereclause;
    delete whereclausesql;
    delete tablename;
    // 删除new对象*************************************************************************
}
void SearchDialog::onCloseButtonClicked()
{
    // 关闭窗口***************************************************************************
    close();
    // 关闭窗口***************************************************************************
}
void SearchDialog::setTableName(QString name) {
    *tablename = name;
    if(*tablename == "已定表") {
        RefreshDoneTable();
    } else if(*tablename == "出库表") {
        RefreshOutRepoTable();
    } else if(*tablename == "入库表") {
        RefreshInRepoTable();
    } else if(*tablename == "库存表") {
        RefreshRepoTable();
    } else {
        RefreshInRepoInfoTable();
    }
}
void SearchDialog::RefreshDoneTable() {
    // 清理以防止内存泄漏******************************************************************
    for (int row = 0; row < qtablewidget->rowCount(); ++row) {
        for (int col = 0; col < qtablewidget->columnCount(); ++col) {
            // 取出项**************************************************************************
            QTableWidgetItem* item = qtablewidget->takeItem(row, col);
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
    qtablewidget->clear();
    qtablewidget->sortItems(0, Qt::DescendingOrder);
    qtablewidget->setRowCount(0);
    qtablewidget->setColumnCount(5);
    query->exec(sqlgroup->at(0));
    int row = 0;
    while (query->next()) {
        qtablewidget->insertRow(qtablewidget->rowCount());
        for(int i = 0; i < 5; i++) {
            if(i == 0 || i == 4) {
                int value = query->value(i).toInt();
                QTableWidgetItem *item= new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                item->setData(Qt::DisplayRole, value);
                qtablewidget->setItem(row, i, item);
            } else {
                QTableWidgetItem *item= new QTableWidgetItem(query->value(i).toString());
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                qtablewidget->setItem(row, i, item);
            }
        }
        ++row;
    }
    // 表格单元格***************************************************************************
    // 水平表头*****************************************************************************
    QStringList headers;
    headers << "已定编号" << "已定时间" << "已定类别" << "已定名称" << "已定数量";
    qtablewidget->setHorizontalHeaderLabels(headers);
    headerView01_row = qtablewidget->horizontalHeader();
    headerView01_row->setFont(*qfont03);
    headerView01_row->setStyleSheet("");
    headerView01_row->setStyleSheet(
                "QHeaderView::up-arrow {image: none;}"
                "QHeaderView::down-arrow {image: none;}");
    // 水平表头*****************************************************************************
    // 垂直表头*****************************************************************************
    headerView01_column = qtablewidget->verticalHeader();
    headerView01_column->hide();
    // 垂直表头*****************************************************************************
    // 表属性*******************************************************************************
    qtablewidget->setFont(*qfont04);
    qtablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qtablewidget->resizeColumnsToContents();
    qtablewidget->setSortingEnabled(true);
    // 表属性*******************************************************************************
}
void SearchDialog::RefreshOutRepoTable() {
    // 清理以防止内存泄漏******************************************************************
    for (int row = 0; row < qtablewidget->rowCount(); ++row) {
        for (int col = 0; col < qtablewidget->columnCount(); ++col) {
            // 取出项**************************************************************************
            QTableWidgetItem* item = qtablewidget->takeItem(row, col);
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
    qtablewidget->clear();
    qtablewidget->sortItems(0, Qt::DescendingOrder);
    qtablewidget->setRowCount(0);
    qtablewidget->setColumnCount(6);
    query->exec(sqlgroup->at(1));
    int row = 0;
    while (query->next()) {
        qtablewidget->insertRow(qtablewidget->rowCount());
        for(int i = 0; i < 6; i++) {
            if(i == 0 || i == 5) {
                int value = query->value(i).toInt();
                QTableWidgetItem *item= new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                item->setData(Qt::DisplayRole, value);
                qtablewidget->setItem(row, i, item);
            } else {
                QTableWidgetItem *item= new QTableWidgetItem(query->value(i).toString());
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                qtablewidget->setItem(row, i, item);
            }
        }
        ++row;
    }
    // 表格单元格***************************************************************************
    // 水平表头*****************************************************************************
    QStringList headers;
    headers << "出库编号" << "出库时间" << "出库类别" <<
               "出库名称" << "出库位置" << "出库数量";
    qtablewidget->setHorizontalHeaderLabels(headers);
    headerView01_row = qtablewidget->horizontalHeader();
    headerView01_row->setFont(*qfont03);
    headerView01_row->setStyleSheet("");
    headerView01_row->setStyleSheet(
                "QHeaderView::up-arrow {image: none;}"
                "QHeaderView::down-arrow {image: none;}");
    // 水平表头*****************************************************************************
    // 垂直表头*****************************************************************************
    headerView01_column = qtablewidget->verticalHeader();
    headerView01_column->hide();
    // 垂直表头*****************************************************************************
    // 表属性*******************************************************************************
    qtablewidget->setFont(*qfont04);
    qtablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qtablewidget->resizeColumnsToContents();
    qtablewidget->setSortingEnabled(true);
    // 表属性*******************************************************************************
}
void SearchDialog::RefreshInRepoTable() {
    // 清理以防止内存泄漏******************************************************************
    for (int row = 0; row < qtablewidget->rowCount(); ++row) {
        for (int col = 0; col < qtablewidget->columnCount(); ++col) {
            // 取出项**************************************************************************
            QTableWidgetItem* item = qtablewidget->takeItem(row, col);
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
    qtablewidget->clear();
    qtablewidget->sortItems(0, Qt::DescendingOrder);
    qtablewidget->setRowCount(0);
    qtablewidget->setColumnCount(6);
    query->exec(sqlgroup->at(2));
    int row = 0;
    while (query->next()) {
        qtablewidget->insertRow(qtablewidget->rowCount());
        for(int i = 0; i < 6; i++) {
            if(i == 0 || i == 5) {
                int value = query->value(i).toInt();
                QTableWidgetItem *item= new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                item->setData(Qt::DisplayRole, value);
                qtablewidget->setItem(row, i, item);
            } else {
                QTableWidgetItem *item= new QTableWidgetItem(query->value(i).toString());
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                qtablewidget->setItem(row, i, item);
            }
        }
        ++row;
    }
    // 表格单元格***************************************************************************
    // 水平表头*****************************************************************************
    QStringList headers;
    headers << "入库编号" << "入库时间" << "入库类别"
            << "入库名称" << "入库位置" << "入库数量";
    qtablewidget->setHorizontalHeaderLabels(headers);
    headerView01_row = qtablewidget->horizontalHeader();
    headerView01_row->setFont(*qfont03);
    headerView01_row->setStyleSheet("");
    headerView01_row->setStyleSheet(
                "QHeaderView::up-arrow {image: none;}"
                "QHeaderView::down-arrow {image: none;}");
    // 水平表头*****************************************************************************
    // 垂直表头*****************************************************************************
    headerView01_column = qtablewidget->verticalHeader();
    headerView01_column->hide();
    // 垂直表头*****************************************************************************
    // 表属性*******************************************************************************
    qtablewidget->setFont(*qfont04);
    qtablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qtablewidget->resizeColumnsToContents();
    qtablewidget->setSortingEnabled(true);
    // 表属性*******************************************************************************
}
void SearchDialog::RefreshRepoTable() {
    // 清理以防止内存泄漏******************************************************************
    for (int row = 0; row < qtablewidget->rowCount(); ++row) {
        for (int col = 0; col < qtablewidget->columnCount(); ++col) {
            // 取出项**************************************************************************
            QTableWidgetItem* item = qtablewidget->takeItem(row, col);
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
    qtablewidget->clear();
    qtablewidget->sortItems(0, Qt::DescendingOrder);
    qtablewidget->setRowCount(0);
    qtablewidget->setColumnCount(5);
    query->exec(sqlgroup->at(3));
    int row = 0;
    while (query->next()) {
        qtablewidget->insertRow(qtablewidget->rowCount());
        for(int i = 0; i < 5; i++) {
            if(i == 0 || i == 4) {
                int value = query->value(i).toInt();
                QTableWidgetItem *item= new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                item->setData(Qt::DisplayRole, value);
                qtablewidget->setItem(row, i, item);
            } else {
                QTableWidgetItem *item= new QTableWidgetItem(query->value(i).toString());
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                qtablewidget->setItem(row, i, item);
            }
        }
        ++row;
    }
    // 表格单元格***************************************************************************
    // 水平表头*****************************************************************************
    QStringList headers;
    headers << "库存编号" << "库存类别" << "库存名称" << "存放位置" << "存放数量";
    qtablewidget->setHorizontalHeaderLabels(headers);
    headerView01_row = qtablewidget->horizontalHeader();
    headerView01_row->setFont(*qfont03);
    headerView01_row->setStyleSheet("");
    headerView01_row->setStyleSheet(
                "QHeaderView::up-arrow {image: none;}"
                "QHeaderView::down-arrow {image: none;}");
    // 水平表头*****************************************************************************
    // 垂直表头*****************************************************************************
    headerView01_column = qtablewidget->verticalHeader();
    headerView01_column->hide();
    // 垂直表头*****************************************************************************
    // 表属性*******************************************************************************
    qtablewidget->setFont(*qfont04);
    qtablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qtablewidget->resizeColumnsToContents();
    qtablewidget->setSortingEnabled(true);
    // 表属性*******************************************************************************
}
void SearchDialog::RefreshInRepoInfoTable() {
    // 清理以防止内存泄漏******************************************************************
    for (int row = 0; row < qtablewidget->rowCount(); ++row) {
        for (int col = 0; col < qtablewidget->columnCount(); ++col) {
            // 取出项**************************************************************************
            QTableWidgetItem* item = qtablewidget->takeItem(row, col);
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
    qtablewidget->clear();
    qtablewidget->sortItems(0, Qt::DescendingOrder);
    qtablewidget->setRowCount(0);
    qtablewidget->setColumnCount(3);
    query->exec(sqlgroup->at(4));
    int row = 0;
    while (query->next()) {
        qtablewidget->insertRow(qtablewidget->rowCount());
        for(int i = 0; i < 3; i++) {
            if(i == 0 ) {
                int value = query->value(i).toInt();
                QTableWidgetItem *item= new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                item->setData(Qt::DisplayRole, value);
                qtablewidget->setItem(row, i, item);
            } else {
                QTableWidgetItem *item= new QTableWidgetItem(query->value(i).toString());
                item->setTextAlignment(Qt::AlignmentFlag(Qt::AlignCenter));
                qtablewidget->setItem(row, i, item);
            }
        }
        ++row;
    }
    // 表格单元格***************************************************************************
    // 水平表头*****************************************************************************
    QStringList headers;
    headers << "产品编号" << "产品类别" << "产品名称";
    qtablewidget->setHorizontalHeaderLabels(headers);
    headerView01_row = qtablewidget->horizontalHeader();
    headerView01_row->setFont(*qfont03);
    headerView01_row->setStyleSheet("");
    headerView01_row->setStyleSheet(
                "QHeaderView::up-arrow {image: none;}"
                "QHeaderView::down-arrow {image: none;}");
    // 水平表头*****************************************************************************
    // 垂直表头*****************************************************************************
    headerView01_column = qtablewidget->verticalHeader();
    headerView01_column->hide();
    // 垂直表头*****************************************************************************
    // 表属性*******************************************************************************
    qtablewidget->setFont(*qfont04);
    qtablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qtablewidget->resizeColumnsToContents();
    qtablewidget->setSortingEnabled(true);
    // 表属性*******************************************************************************
}
void SearchDialog::setDialogTitle(QString title) {
    contentWidgetTitle->setText(title);
}
