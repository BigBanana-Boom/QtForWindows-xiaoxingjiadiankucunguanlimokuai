#include "modifyrepo.h"
#include <QLabel>
#include <QTableWidget>
#include <QSqlQuery>
#include <QVariant>
#include <QHeaderView>

ModifyRepo::ModifyRepo(QWidget *parent,
                       QSqlDatabase *db,
                       QSqlQuery *query)
    : QWidget{parent},
    qfont01(new QFont("楷体", 24, QFont::Bold)),
    qfont02(new QFont("楷体", 20, QFont::Bold)),
    qfont03(new QFont("楷体", 18, QFont::Bold)),
    qfont04(new QFont("楷体", 18)),
    mainLayout(new QVBoxLayout(this)),
    titleLayout(new QHBoxLayout()),
    contentLayout(new QGridLayout()),
    qlabel01(new QLabel("配 置", this)),
    db(db),
    query(query),
    sqlgroup(new QStringList()),
    whereclause(new QString()),
    whereclausesql(new QString()),
    qpushbutton01(new QPushButton("进货产品表新增", this)),
    qpushbutton02(new QPushButton("仓库信息表新增", this)),
    qpushbutton03(new QPushButton("库存表批量新增", this)),
    qpushbutton04(new QPushButton("出库表批量删除", this)),
    qpushbutton05(new QPushButton("入库表批量删除", this)),
    qpushbutton06(new QPushButton("本地数据库备份", this)),
    qpushbutton07(new QPushButton("读取本地数据库", this)),
    qpushbutton08(new QPushButton("云端数据库备份", this)),
    qpushbutton09(new QPushButton("读取云端数据库", this)),
    line(new QFrame(this))
{
    // 标题布局
    qlabel01->resize(100, 100);
    qlabel01->setFont(*qfont01);
    qlabel01->setAlignment(Qt::AlignCenter);
    titleLayout->addWidget(qlabel01);
    // 标题布局

    // 内容布局
    qpushbutton01->setFont(*qfont03);
    qpushbutton02->setFont(*qfont03);
    qpushbutton03->setFont(*qfont03);
    qpushbutton04->setFont(*qfont03);
    qpushbutton05->setFont(*qfont03);
    qpushbutton06->setFont(*qfont03);
    qpushbutton07->setFont(*qfont03);
    qpushbutton08->setFont(*qfont03);
    qpushbutton09->setFont(*qfont03);
    contentLayout->addWidget(qpushbutton01, 0, 0);
    contentLayout->addWidget(qpushbutton02, 0, 1);
    contentLayout->addWidget(qpushbutton03, 0, 2);
    contentLayout->addWidget(qpushbutton04, 1, 0);
    contentLayout->addWidget(qpushbutton05, 1, 1);
    contentLayout->addWidget(qpushbutton06, 1, 2);
    contentLayout->addWidget(qpushbutton07, 2, 0);
    contentLayout->addWidget(qpushbutton08, 2, 1);
    contentLayout->addWidget(qpushbutton09, 2, 2);
    // 内容布局

    // 总布局
    mainLayout->addLayout(titleLayout);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("QFrame { color: grey; }");
    mainLayout->addWidget(line);
    mainLayout->addLayout(contentLayout);
    mainLayout->addStretch(1);
    // 总布局

    // 窗口属性
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    // 窗口属性
}
ModifyRepo::~ModifyRepo() {
    // 删除new对象*************************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete qfont04;
    delete sqlgroup;
    delete whereclause;
    delete whereclausesql;
    // 删除new对象*************************************************************************
}
