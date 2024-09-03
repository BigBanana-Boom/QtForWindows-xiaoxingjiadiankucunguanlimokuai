#include "inrepoaddname.h"

InRepoAddName::InRepoAddName(QWidget *parent,
                             QSqlDatabase *db,
                             QSqlQuery *query,
                             QString *category)
    : QDialog(parent),
      label0(new QLabel("当前入库类别：", this)),
      lineEdit0(new QLineEdit(this)),
      label(new QLabel("添加可选名称：", this)),
      lineEdit(new QLineEdit(this)),
      prompt(new QLabel(this)),
      okButton(new QPushButton("确定添加", this)),
      mainLayout(new QVBoxLayout(this)),
      inputZone0(new QHBoxLayout()),
      inputZone(new QHBoxLayout()),
      db(db),
      query(query),
      sqlgroup(new QStringList()),
      category(category)
{
    // 数据库*******************************************************************************
    sqlgroup->append("SELECT * FROM 附表2进货产品表 "
                     "WHERE 产品类别 = ? AND 产品名称 = '暂无'");
    sqlgroup->append("UPDATE 附表2进货产品表 SET 产品名称 = ? "
                     "WHERE 产品类别 = ? AND 产品名称 = '暂无'");
    sqlgroup->append("SELECT * FROM 附表2进货产品表 "
                     "WHERE 产品类别 = ? AND 产品名称 = ?");
    sqlgroup->append("INSERT INTO 附表2进货产品表 (产品类别, 产品名称) VALUES (?, ?)");
    // 数据库*******************************************************************************

    setWindowTitle("添加可选名称");
    setWindowIcon(QIcon(":/image/BrokenRice.png"));
    label0->setFont(QFont("Microsoft YaHei"));
    lineEdit0->setReadOnly(true);
    lineEdit0->setText(*category);
    lineEdit0->setFont(QFont("Microsoft YaHei"));
    inputZone0->addWidget(label0);
    inputZone0->addWidget(lineEdit0, 1);

    label->setFont(QFont("Microsoft YaHei"));
    lineEdit->setFont(QFont("Microsoft YaHei"));
    inputZone->addWidget(label);
    inputZone->addWidget(lineEdit, 1);
    mainLayout->addLayout(inputZone0);
    mainLayout->addLayout(inputZone);
    QPalette palette = prompt->palette();
    palette.setColor(QPalette::WindowText, Qt::red);
    prompt->setPalette(palette);
    prompt->setVisible(false);
    prompt->setFont(QFont("Microsoft YaHei"));
    okButton->setFont(QFont("Microsoft YaHei"));
    mainLayout->addWidget(prompt);
    mainLayout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, this, &InRepoAddName::SaveName);
}
InRepoAddName::~InRepoAddName() {
    delete sqlgroup;
}
void InRepoAddName::SaveName() {
    if(lineEdit->text() == "") {
        prompt->setText("输入框不能为空！");
        prompt->setVisible(true);
    } else {
        QSqlQuery query(*db);
        query.prepare(sqlgroup->at(0));
        query.addBindValue(lineEdit0->text());
        query.exec();
        if(query.next()) {
            query.prepare(sqlgroup->at(1));
            query.addBindValue(lineEdit->text());
            query.addBindValue(lineEdit0->text());
            query.exec();
            prompt->setText("添加"+lineEdit->text() + "到" + lineEdit0->text() + "成功！");
            prompt->setVisible(true);
        } else {
            query.prepare(sqlgroup->at(2));
            query.addBindValue(lineEdit0->text());
            query.addBindValue(lineEdit->text());
            query.exec();
            if(query.next()) {
                prompt->setText("不能重复添加！");
                prompt->setVisible(true);
            } else {
                query.prepare(sqlgroup->at(3));
                query.addBindValue(lineEdit0->text());
                query.addBindValue(lineEdit->text());
                query.exec();
                prompt->setText("添加"+lineEdit->text() + "到" + lineEdit0->text() + "成功！");
                prompt->setVisible(true);
            }
        }
    }
    emit RefreshInRepoAddSignal();
}
