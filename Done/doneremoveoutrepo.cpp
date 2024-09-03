#include "doneremoveoutrepo.h"

DoneRemoveOutRepo::DoneRemoveOutRepo(QWidget *parent,
                                     QSqlDatabase *db,
                                     QSqlQuery *query,
                                     int *currentID,
                                     QDateTime *currentdatetime,
                                     QString *currentproductcategory,
                                     QString *currentproductname,
                                     int *currentproductnumber)
    : QDialog(parent),
      mainLayout(new QVBoxLayout(this)),
      inputZone(new QVBoxLayout()),
      buttonZone(new QHBoxLayout()),
      inputLabel(new QLabel("选择出库位置：", this)),
      messageLabel(new QLabel(this)),
      prompt(new QLabel(this)),
      confirmButton(new QPushButton("确定", this)),
      cancelButton(new QPushButton("取消", this)),
      db(db),
      query(query),
      sqlgroup(new QStringList()),
      currentID(currentID),
      currentdatetime(currentdatetime),
      currentproductcategory(currentproductcategory),
      currentproductname(currentproductname),
      currentproductnumber(currentproductnumber)
{
    // 数据库*******************************************************************************
    sqlgroup->append("SELECT 附表1仓库信息表.仓库名称, 库存表.存放数量 "
                     "FROM 附表1仓库信息表 JOIN 库存表 "
                     "ON 库存表.库存类别 = ? AND 库存表.库存名称 = ? "
                     "AND 库存表.存放位置 = 附表1仓库信息表.仓库名称");
    sqlgroup->append("DELETE FROM 已定表 WHERE 已定编号 = ?");
    sqlgroup->append("CREATE TABLE IF NOT EXISTS 临时已定表 ( "
                     "已定编号 INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "已定时间 DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP, "
                     "已定类别 TEXT NOT NULL, "
                     "已定名称 TEXT NOT NULL, "
                     "已定数量 INTEGER NOT NULL)");
    sqlgroup->append("INSERT INTO 临时已定表 "
                     "(已定时间, 已定类别, 已定名称, 已定数量) "
                     "SELECT 已定时间, 已定类别, 已定名称, 已定数量 FROM 已定表");
    sqlgroup->append("DROP TABLE 已定表");
    sqlgroup->append("ALTER TABLE 临时已定表 RENAME TO 已定表");
    sqlgroup->append("INSERT INTO 出库表 "
                     "(出库时间, 出库位置, 出库类别, 出库名称, 出库数量) "
                     "VALUES (?, ?, ?, ?, ?)");
    sqlgroup->append("SELECT 存放数量 FROM 库存表 "
                     "WHERE 存放位置 = ? AND 库存类别 = ? AND 库存名称 = ?");
    sqlgroup->append("DELETE FROM 库存表 "
                     "WHERE 存放位置 = ? AND 库存类别 = ? AND 库存名称 = ?");
    sqlgroup->append("UPDATE 库存表 SET 存放数量 = 存放数量 - ? "
                     "WHERE 存放位置 = ? AND 库存类别 = ? AND 库存名称 = ?");
    // 数据库*******************************************************************************
    setWindowIcon(QIcon(":/Image/BrokenRice.png"));
    setWindowTitle(" ");

    // 输入区*******************************************************************************
    inputLabel->setFont(QFont("楷体", 16));
    inputZone->addWidget(inputLabel);

    query->exec(sqlgroup->at(0));
    query->addBindValue(*currentproductcategory);
    query->addBindValue(*currentproductname);
    query->exec();
    QFont qfont00 = QFont("楷体", 16);
    while(query->next()) {
        InputZoneData inputZoneData;
        inputZoneData.layout = new QHBoxLayout();
        inputZoneData.label = new QLabel(this);
        inputZoneData.label->setText(query->value(0).toString() + "：");
        inputZoneData.label->setFont(qfont00);
        inputZoneData.spinBox = new QSpinBox(this);
        inputZoneData.spinBox->setMinimum(0);
        inputZoneData.spinBox->setMaximum(query->value(1).toInt());
        inputZoneData.spinBox->setValue(0);
        inputZoneData.spinBox->setMaximumHeight(30);
        inputZoneData.spinBox->setFont(qfont00);
        inputZoneData.label2 = new QLabel(this);
        inputZoneData.label2->setText("库存数量：" + query->value(1).toString());
        inputZoneData.label2->setFont(qfont00);
        inputZoneData.layout->addWidget(inputZoneData.label);
        inputZoneData.layout->addWidget(inputZoneData.spinBox, 1);
        inputZoneData.layout->addWidget(inputZoneData.label2);
        inputZone->addLayout(inputZoneData.layout);
        inputZones.append(inputZoneData);
    }
    mainLayout->addLayout(inputZone);
    // 输入区*******************************************************************************

    // 大段信息*****************************************************************************
    messageLabel->setFont(QFont("楷体", 16));
    messageLabel->setText(QString("待删除已定编号：%1\n"
                                  "待删除已定时间：%2\n"
                                  "待删除已定类别：%4\n"
                                  "待删除已定名称：%5\n"
                                  "待删除已定数量：%6\n"
                                  "确定删除该记录嘛？")
                          .arg(*currentID)
                          .arg(currentdatetime->toString("yyyy-MM-dd"))
                          .arg(*currentproductcategory)
                          .arg(*currentproductname)
                               .arg(*currentproductnumber));
    mainLayout->addWidget(messageLabel);
    // 大段信息*****************************************************************************

    // 提示信息*****************************************************************************
    QPalette palette = prompt->palette();
    palette.setColor(QPalette::WindowText, Qt::red);
    prompt->setPalette(palette);
    prompt->setVisible(false);
    prompt->setFont(qfont00);
    mainLayout->addWidget(prompt);
    // 提示信息*****************************************************************************

    // 按钮**********************************************************************************
    confirmButton->setFont(QFont("楷体", 16, QFont::Bold));
    cancelButton->setFont(QFont("楷体", 16, QFont::Bold));
    buttonZone->addWidget(confirmButton);
    buttonZone->addWidget(cancelButton);
    mainLayout->addLayout(buttonZone);
    // 按钮**********************************************************************************

    // 信号与槽函数*************************************************************************
    connect(confirmButton, &QPushButton::clicked, this,
            &DoneRemoveOutRepo::SubmitRemoveOperation);
    connect(cancelButton, &QPushButton::clicked, this, &DoneRemoveOutRepo::Close);
    // 信号与槽函数*************************************************************************
}
DoneRemoveOutRepo::~DoneRemoveOutRepo() {
    delete sqlgroup;
}
void DoneRemoveOutRepo::SubmitRemoveOperation() {
    // 检查*************************************************************************************
    int length = inputZones.size();
    int sum = 0;
    for(int i = 0; i < length; i++) {
        sum += inputZones[i].spinBox->value();
    }
    if(sum > *currentproductnumber) {
        prompt->setText("出库数量大于已定数量！");
        prompt->setVisible(true);
        return;
    } else if(sum < *currentproductnumber) {
        prompt->setText("出库数量小于已定数量！");
        prompt->setVisible(true);
        return;
    }
    // 检查*************************************************************************************
    // 更新数据表******************************************************************************
    // 更新已定表******************************************************************************
    query->prepare(sqlgroup->at(1));
    query->addBindValue(*currentID);
    query->exec();
    query->exec(sqlgroup->at(2));
    query->exec(sqlgroup->at(3));
    query->exec(sqlgroup->at(4));
    query->exec(sqlgroup->at(5));
    query->exec();
    for(int i = 0; i < length; i++) {
        if(inputZones[i].spinBox->value() == 0) {}
        else {
            QString currentrepo = inputZones[i].label->text();
            currentrepo.chop(1);
            int outnumber = inputZones[i].spinBox->value();
            // 更新出库表***********************************************************************
            query->prepare(sqlgroup->at(6));
            query->addBindValue(QDateTime::currentDateTime());
            query->addBindValue(currentrepo);
            query->addBindValue(*currentproductcategory);
            query->addBindValue(*currentproductname);
            query->addBindValue(outnumber);
            query->exec();
            // 更新出库表***********************************************************************
            // 更新库存表***********************************************************************
            query->prepare(sqlgroup->at(7));
            query->addBindValue(currentrepo);
            query->addBindValue(*currentproductcategory);
            query->addBindValue(*currentproductname);
            query->exec();
            query->next();
            if(outnumber == query->value(0).toInt()) {
                query->prepare(sqlgroup->at(8));
                query->addBindValue(currentrepo);
                query->addBindValue(*currentproductcategory);
                query->addBindValue(*currentproductname);
                query->exec();
                RefreshRepoTableID refreshid(db, query);
            } else {
                query->prepare(sqlgroup->at(9));
                query->addBindValue(outnumber);
                query->addBindValue(currentrepo);
                query->addBindValue(*currentproductcategory);
                query->addBindValue(*currentproductname);
                query->exec();
            }
            // 更新库存表***********************************************************************
        }
    }
    // 更新数据表******************************************************************************
    // 放出信号********************************************************************************
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
    // 放出信号********************************************************************************
    accept();
}
void DoneRemoveOutRepo::Close() {
    reject();
}
