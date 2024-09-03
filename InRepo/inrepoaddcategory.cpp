#include "inrepoaddcategory.h"

InRepoAddCategory::InRepoAddCategory(QWidget *parent,
                                     QSqlDatabase *db,
                                     QSqlQuery *query)
    : QDialog(parent),
      label(new QLabel("添加可选类别：", this)),
      lineEdit(new QLineEdit(this)),
      prompt(new QLabel(this)),
      okButton(new QPushButton("确定添加", this)),
      mainLayout(new QVBoxLayout(this)),
      inputZone(new QHBoxLayout()),
      db(db),
      query(query),
      sqlgroup(new QStringList())
{
    // 数据库*******************************************************************************
    sqlgroup->append("SELECT * FROM 附表2进货产品表 WHERE 产品类别 = ?");
    sqlgroup->append("INSERT INTO 附表2进货产品表 (产品类别, 产品名称) "
                     "VALUES (?, '暂无')");
    // 数据库*******************************************************************************
    setWindowTitle("添加可选类别");
    setWindowIcon(QIcon(":/image/BrokenRice.png"));
    label->setFont(QFont("Microsoft YaHei"));
    lineEdit->setFont(QFont("Microsoft YaHei"));
    inputZone->addWidget(label);
    inputZone->addWidget(lineEdit, 1);
    mainLayout->addLayout(inputZone);
    QPalette palette = prompt->palette();
    palette.setColor(QPalette::WindowText, Qt::red);
    prompt->setPalette(palette);
    prompt->setVisible(false);
    prompt->setFont(QFont("Microsoft YaHei"));
    okButton->setFont(QFont("Microsoft YaHei"));
    mainLayout->addWidget(prompt);
    mainLayout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, this, &InRepoAddCategory::SaveCategory);
}
InRepoAddCategory::~InRepoAddCategory() {
    delete sqlgroup;
}
void InRepoAddCategory::SaveCategory() {
    if(lineEdit->text() == "") {
        prompt->setText("输入框不能为空！");
        prompt->setVisible(true);
    } else {
        QSqlQuery query(*db);
        query.prepare(sqlgroup->at(0));
        query.addBindValue(lineEdit->text());
        query.exec();
        if(query.next()) {
            prompt->setText("不能重复添加！");
            prompt->setVisible(true);
        } else {
            query.prepare(sqlgroup->at(1));
            query.addBindValue(lineEdit->text());
            query.exec();
            prompt->setText("添加"+lineEdit->text() + "成功！");
            prompt->setVisible(true);
        }
    }
    emit RefreshInRepoAddSignal();
}
