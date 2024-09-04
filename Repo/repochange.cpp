/*
 *
 * on... Changed();不用连锁所有的
 * Refresh...();需要更新所有的
 *
 */
#include "repochange.h"

RepoChange::RepoChange(QWidget *parent,
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
      qlabel01(new QLabel("待修改库存编号：", this)),
      qlabel02(new QLabel("待修改库存类别：", this)),
      qlabel03(new QLabel("待修改库存名称：", this)),
      qlabel04(new QLabel("待修改库存位置：", this)),
      qlabel05(new QLabel("待修改库存数量：", this)),
      qlabel06(new QLabel("修改后库存数量：", this)),
      qcombobox01(new QComboBox(this)),
      searchbutton(new QPushButton(this)),
      qreadonlylineedit01(new QLineEdit(this)),
      qreadonlylineedit02(new QLineEdit(this)),
      qreadonlylineedit03(new QLineEdit(this)),
      qreadonlylineedit04(new QLineEdit(this)),
      qspinbox01(new QSpinBox(this)),
      yeschange(new QPushButton("确定修改该记录", this)),
      db(db),
      query(query),
      sqlgroup(new QStringList()),
      currentdatetime(new QString(
                          QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))),
      currentID(new int),
      currentproductcategory(new QString()),
      currentproductname(new QString()),
      currentrepo(new QString()),
      currentproductnumber(new int),
      changedproductnumber(new int)
{
    // 数据库语句***************************************************************************
    sqlgroup->append("SELECT 库存编号 FROM 库存表 "
                     "ORDER BY 库存编号 DESC");
    /* ORDER BY 库存编号 DESC */
    sqlgroup->append("SELECT 库存类别 FROM 库存表 WHERE 库存编号 = ?");
    /* WHERE ...编号 = ?，很精确了，不用再排序 */
    sqlgroup->append("SELECT 库存名称 FROM 库存表 WHERE 库存编号 = ?");
    /* WHERE ...编号 = ?，很精确了，不用再排序 */
    sqlgroup->append("SELECT 存放位置 FROM 库存表 WHERE 库存编号 = ?");
    /* WHERE ...编号 = ?，很精确了，不用再排序 */
    sqlgroup->append("SELECT 存放数量 FROM 库存表 WHERE 库存编号 = ?");
    /* WHERE ...编号 = ?，很精确了，不用再排序 */
    sqlgroup->append("UPDATE 库存表 SET 存放数量 = ? WHERE 库存编号 = ?");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("DELETE FROM 库存表 WHERE 库存编号 = ?");
    /* 数据库操作语句，不需要排序 */
    sqlgroup->append("INSERT INTO 附表3库存调整表 "
                     "(调库时间, 库存位置, 库存类别, 库存名称, 库存变化) VALUES (?, ?, ?, ?, ?)");
    /* 数据库操作语句，不需要排序 */
    // 数据库语句***************************************************************************

    // 左区域*******************************************************************************
    // 待修改库存编号***********************************************************************
    qlabel01->setFont(*qfont01);
    qcombobox01->setFont(*qfont02);
    qcombobox01->setEditable(false);
    searchbutton->setIcon(QIcon(":/Image/search.png"));
    searchbutton->setIconSize(QSize(32, 32));
    searchbutton->setFixedSize(QSize(40, 40));
    // 样式**********************************************************************************
    // 填充内容*****************************************************************************
    qcombobox01->clear();
    query->exec(sqlgroup->at(0));
    if(!query->next()) {
        qcombobox01->addItem("暂无");
        *currentID = 0;
     } else {
        qcombobox01->addItem(query->value(0).toString());
        while (query->next()) {
            qcombobox01->addItem(query->value(0).toString());
        }
        *currentID = qcombobox01->currentText().toInt();
    }
    // 填充内容*****************************************************************************
    // 待修改库存编号***********************************************************************
    // 待修改库存类别***********************************************************************
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
        qreadonlylineedit01->setText("暂无");
        *currentproductcategory = "暂无";
    } else {
        while(query->next()) {
            qreadonlylineedit01->setText(query->value(0).toString());
            *currentproductcategory = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 待修改库存类别***********************************************************************
    // 待修改库存名称***********************************************************************
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
        qreadonlylineedit02->setText("暂无");
        *currentproductname = "暂无";
    } else {
        while(query->next()) {
            qreadonlylineedit02->setText(query->value(0).toString());
            *currentproductname = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 待修改库存名称***********************************************************************
    // 待修改存放位置***********************************************************************
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
        qreadonlylineedit03->setText("暂无");
        *currentrepo = "暂无";
    } else {
        while(query->next()) {
            qreadonlylineedit03->setText(query->value(0).toString());
            *currentrepo = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 待修改存放位置***********************************************************************
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
    // 左区域*******************************************************************************

    // 右区域*******************************************************************************
    // 待修改存放数量***********************************************************************
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
        qreadonlylineedit04->setText("暂无");
        *currentproductnumber = 0;
    } else {
        while(query->next()) {
            qreadonlylineedit04->setText(query->value(0).toString());
            *currentproductnumber = query->value(0).toInt();
        }
    }
    // 填充内容*****************************************************************************
    // 待修改存放数量***********************************************************************
    // 修改后存放数量***********************************************************************
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
        qspinbox01->setMinimum(0);
        qspinbox01->setMaximum(9999);
        qspinbox01->setValue(*currentproductnumber);
        *changedproductnumber = qspinbox01->value();
    }
    // 填充内容*****************************************************************************
    // 修改后存放数量***********************************************************************
    // 修改提交按钮*************************************************************************
    yeschange->setFont(*qfont01);
    // 修改提交按钮*************************************************************************
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
    // 右区域*******************************************************************************

    // 总区域*******************************************************************************
    mainLayout->addLayout(zone);
    // 总区域*******************************************************************************

    // 信号与槽函数*************************************************************************
    connect(searchbutton, &QPushButton::clicked,
            this, &RepoChange::onSearchButtonClicked);
    connect(qcombobox01, &QComboBox::currentTextChanged,
            this, &RepoChange::onChangedIDChanged);
    using SpinBoxSignal = void (QSpinBox::*)(int);
    SpinBoxSignal spinBoxSignal = &QSpinBox::valueChanged;
    connect(qspinbox01, spinBoxSignal, this, &RepoChange::onChangedValueChanged);
    connect(yeschange, &QPushButton::clicked, this, &RepoChange::showMessage);
    // 信号与槽函数*************************************************************************
}
RepoChange::~RepoChange() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete sqlgroup;
    delete currentdatetime;
    delete currentID;
    delete currentrepo;
    delete currentproductnumber;
    delete currentproductcategory;
    delete currentproductname;
    delete changedproductnumber;
    // 删除new对象*************************************************************************
}
void RepoChange::onChangedIDChanged(const QString &text) {
    // 记录更新*****************************************************************************
    *currentID = text.toInt();
    // 记录更新*****************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit01->clear();
    query->prepare(sqlgroup->at(1));
    query->addBindValue(*currentID);
    query->exec();
    if(*currentID == 0) {
        qreadonlylineedit01->setText("暂无");
        *currentproductcategory = "暂无";
    } else {
        while(query->next()) {
            qreadonlylineedit01->setText(query->value(0).toString());
            *currentproductcategory = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit02->clear();
    query->prepare(sqlgroup->at(2));
    query->addBindValue(*currentID);
    query->exec();
    if(*currentID == 0) {
        qreadonlylineedit02->setText("暂无");
        *currentproductname = "暂无";
    } else {
        while(query->next()) {
            qreadonlylineedit02->setText(query->value(0).toString());
            *currentproductname = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit03->clear();
    query->prepare(sqlgroup->at(3));
    query->addBindValue(*currentID);
    query->exec();
    if(*currentID == 0) {
        qreadonlylineedit03->setText("暂无");
        *currentrepo = "暂无";
    } else {
        while(query->next()) {
            qreadonlylineedit03->setText(query->value(0).toString());
            *currentrepo = query->value(0).toString();
        }
    }
    // 填充内容*****************************************************************************
    // 填充内容*****************************************************************************
    qreadonlylineedit04->clear();
    query->prepare(sqlgroup->at(4));
    query->addBindValue(*currentID);
    query->exec();
    if(*currentID == 0) {
        qreadonlylineedit04->setText("暂无");
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
        qspinbox01->setMaximum(9999);
        qspinbox01->setValue(*currentproductnumber);
        *changedproductnumber = qspinbox01->value();
    }
    // 填充内容*****************************************************************************
    // 开信号*******************************************************************************
    qspinbox01->blockSignals(false);
    // 开信号*******************************************************************************
    // 启槽函数*****************************************************************************
    onChangedValueChanged(*changedproductnumber);
    // 启槽函数*****************************************************************************
}
void RepoChange::onChangedValueChanged(int value) {
    // 记录更新*****************************************************************************
    *changedproductnumber = value;
    // 记录更新*****************************************************************************
}
void RepoChange::showMessage()
{
    QMessageBox messageBox(this);
    messageBox.setWindowTitle("修改库存");
    if(*currentID == 0) {
        // 新对象****************************************************************************
        simpledialog = new SimpleDialog(false, true, true, this);
        simpledialog->setDialogContent("库存表中暂无记录，无法修改");
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
        simpledialog->setDialogContent("库存表无变化，修改无效");
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
        repochangedialog = new RepoChangeDialog(false, true, true, this);
        repochangedialog->setRepoChangeID(
                    QString::number(*currentID));
        repochangedialog->setRepoChangeCategory(*currentproductcategory);
        repochangedialog->setRepoChangeName(*currentproductname);
        repochangedialog->setRepoChangeRepo(*currentrepo);
        repochangedialog->setRepoChangeOldNumber(
                    QString::number(*currentproductnumber));
        repochangedialog->setRepoChangeNewNumber(
                    QString::number(*changedproductnumber));
        // 新对象****************************************************************************
        // 新对象的信号与槽*****************************************************************
        connect(repochangedialog, &RepoChangeDialog::accepted, this, [this]() {
            SubmitChangeOperation();
        });
        // 新对象的信号与槽*****************************************************************
        // 嗯，坏米饭************************************************************************
        // 调整位置**************************************************************************
        QRect parentGeometry = this->window()->window()->geometry();
        int dialogWidth = repochangedialog->width();
        int dialogHeight = repochangedialog->height();
        int x = (parentGeometry.width() - dialogWidth) / 2 + parentGeometry.x();
        int y = (parentGeometry.height() - dialogHeight) / 2 + parentGeometry.y();
        // 调整位置**************************************************************************
        // 移动对话框***********************************************************************
        repochangedialog->move(x, y);
        // 移动对话框***********************************************************************
        // 嗯，坏米饭************************************************************************
        repochangedialog->exec();
        delete repochangedialog;
    }
}
void RepoChange::SubmitChangeOperation() {
    // 更新数据表***************************************************************************
    // 更新调库表***************************************************************************
    query->prepare(sqlgroup->at(7));
    query->addBindValue(*currentdatetime);
    query->addBindValue(*currentrepo);
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    if(*changedproductnumber > *currentproductnumber) {
        QString result;
        QTextStream stream(&result);
        stream << "+" << *changedproductnumber - *currentproductnumber;
        query->addBindValue(result);
    } else if(*changedproductnumber <  *currentproductnumber) {
        QString result;
        QTextStream stream(&result);
        stream << "-" << *currentproductnumber - *changedproductnumber;
        query->addBindValue(result);
    }
    query->exec();
    // 更新调库表***************************************************************************
    // 更新库存表***************************************************************************
    if(*changedproductnumber == 0) {
        query->prepare(sqlgroup->at(6));
        query->addBindValue(*currentID);
        query->exec();
    } else {
        query->prepare(sqlgroup->at(5));
        query->addBindValue(*changedproductnumber);
        query->addBindValue(*currentID);
        query->exec();
    }
    // 更新库存表***************************************************************************
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
    RefreshRepoChangeSlot();
    // 更新自己**************************************************************************
}
void RepoChange::RefreshRepoChangeSlot() {
    // 更新日期*****************************************************************************
    *currentdatetime = QDateTime::currentDateTime()
            .toString("yyyy-MM-dd hh:mm:ss");
    // 更新日期*****************************************************************************
    // 关信号****************************************************************************
    qcombobox01->blockSignals(true);
    // 关信号****************************************************************************
    // 填充内容*****************************************************************************
    qcombobox01->clear();
    query->exec(sqlgroup->at(0));
    if(!query->next()) {
        qcombobox01->addItem("暂无");
        *currentID = 0;
     } else {
        qcombobox01->addItem(query->value(0).toString());
        while (query->next()) {
            qcombobox01->addItem(query->value(0).toString());
        }
        *currentID = qcombobox01->currentText().toInt();
    }
    // 填充内容*****************************************************************************
    // 开信号****************************************************************************
    qcombobox01->blockSignals(false);
    // 开信号****************************************************************************
    // 启槽函数**************************************************************************
    onChangedIDChanged(QString::number(*currentID));
    // 启槽函数**************************************************************************
}
void RepoChange::onSearchButtonClicked() {
    // 新对象****************************************************************************
    searchdialog = new SearchDialog(true, true, true, this, db, query, returnid);
    searchdialog->setDialogTitle("库 存 修 改 · 查 找");
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
    delete searchdialog;
}
