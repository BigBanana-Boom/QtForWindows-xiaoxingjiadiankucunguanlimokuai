#include "modifyrepo.h"
#include <QLabel>
#include <QTableWidget>
#include <QSqlQuery>
#include <QVariant>
#include <QHeaderView>

ModifyRepo::ModifyRepo(QWidget *parent, QSqlDatabase *db, QSqlQuery *query)
    : QWidget{parent},
    qfont01(new QFont("楷体", 24, QFont::Bold)),
    qfont02(new QFont("楷体", 20, QFont::Bold)),
    qfont03(new QFont("楷体", 16, QFont::Bold)),
    qfont04(new QFont("楷体", 16)),
    mainLayout(new QVBoxLayout(this)),
    titleLayout(new QHBoxLayout()),
    contentLayout(new QHBoxLayout()),
    qlabel01(new QLabel("配 置", this))
{
    // 标题布局
    qlabel01->resize(100, 100);
    qlabel01->setFont(*qfont01);
    qlabel01->setAlignment(Qt::AlignCenter);

    titleLayout->addWidget(qlabel01);
    // 标题布局

    // 内容布局

    // 内容布局

    // 总布局
    mainLayout->addLayout(titleLayout);
    mainLayout->addStretch(1);
    mainLayout->addLayout(contentLayout);
    // 总布局

    // 窗口属性
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    // 窗口属性
}
ModifyRepo::~ModifyRepo() {
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete qfont04;
}
