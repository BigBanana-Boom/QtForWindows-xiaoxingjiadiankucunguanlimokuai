#include "inrepoadddialog.h"

InRepoAddDialog::InRepoAddDialog(bool resizeEnable,
                                 bool shadowBorder,
                                 bool winNativeEvent,
                                 QWidget *parent)
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
      closebutton(new CloseButton(this)),
      line(new QFrame(this)),
      contentWidget(new QWidget(this)),
      contentWidgetVLayout(new QVBoxLayout()),
      contentWidgetTitle(new QLabel(this)),
      rowOneLabel(new QLabel(this)),
      rowOneContent(new QLabel(this)),
      rowOneHLayout(new QHBoxLayout()),
      rowTwoLabel(new QLabel(this)),
      rowTwoContent(new QLabel(this)),
      rowTwoHLayout(new QHBoxLayout()),
      rowThreeLabel(new QLabel(this)),
      rowThreeContent(new QLabel(this)),
      rowThreeHLayout(new QHBoxLayout()),
      rowFourLabel(new QLabel(this)),
      rowFourContent(new QLabel(this)),
      rowFourHLayout(new QHBoxLayout()),
      rowFiveLabel(new QLabel(this)),
      line2(new QFrame(this)),
      buttonWidget(new QWidget(this)),
      ButtonHLayout(new QHBoxLayout()),
      AcceptButton(new GradientButton(this)),
      CancelButton(new GradientButton(this))
{
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
    closebutton->setIconSize(QSize(25, 25));
    closebutton->setFixedSize(QSize(60, 43));
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
    contentWidgetTitle->setText("新 增 入 库");
    contentWidgetTitle->setFont(*qfont02);
    contentWidgetTitle->setAlignment(Qt::AlignCenter);
    contentWidgetVLayout->addWidget(contentWidgetTitle);
    // 标题******************************************************************************
    // 第一行****************************************************************************
    rowOneLabel->setText("待新增入库类别：");
    rowOneLabel->setFont(*qfont03);
    // 让外类通过公有方法设置rowOneContent的内容***********************************
    rowOneContent->setFont(*qfont04);
    rowOneHLayout->addWidget(rowOneLabel);
    rowOneHLayout->addWidget(rowOneContent, 1);
    contentWidgetVLayout->addLayout(rowOneHLayout);
    // 第一行****************************************************************************
    // 第二行****************************************************************************
    rowTwoLabel->setText("待新增入库名称：");
    rowTwoLabel->setFont(*qfont03);
    // 让外类通过公有方法设置rowTwoContent的内容***********************************
    rowTwoContent->setFont(*qfont04);
    rowTwoHLayout->addWidget(rowTwoLabel);
    rowTwoHLayout->addWidget(rowTwoContent, 1);
    contentWidgetVLayout->addLayout(rowTwoHLayout);
    // 第二行****************************************************************************
    // 第三行****************************************************************************
    rowThreeLabel->setText("待新增入库位置：");
    rowThreeLabel->setFont(*qfont03);
    // 让外类通过公有方法设置rowThreeContent的内容*********************************
    rowThreeContent->setFont(*qfont04);
    rowThreeHLayout->addWidget(rowThreeLabel);
    rowThreeHLayout->addWidget(rowThreeContent, 1);
    contentWidgetVLayout->addLayout(rowThreeHLayout);
    // 第三行****************************************************************************
    // 第四行****************************************************************************
    rowFourLabel->setText("待新增入库数量：");
    rowFourLabel->setFont(*qfont03);
    // 让外类通过公有方法设置rowFourContent的内容**********************************
    rowFourContent->setFont(*qfont04);
    rowFourHLayout->addWidget(rowFourLabel);
    rowFourHLayout->addWidget(rowFourContent, 1);
    contentWidgetVLayout->addLayout(rowFourHLayout);
    // 第四行****************************************************************************
    // 第五行****************************************************************************
    rowFiveLabel->setText("确定新增该记录嘛？");
    rowFiveLabel->setFont(*qfont03);
    contentWidgetVLayout->addWidget(rowFiveLabel);
    // 第五行****************************************************************************
    // 跟该Pro的其它保持一致***********************************************************
    contentWidgetVLayout->setSpacing(8);
    contentWidgetVLayout->setContentsMargins(20, 8, 20, 8);
    // 跟该Pro的其它保持一致***********************************************************
    contentWidget->setFixedHeight(280);
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
    AcceptButton->setFont(*qfont03);
    AcceptButton->setText("确定");
    AcceptButton->setFixedHeight(40);
    ButtonHLayout->addWidget(AcceptButton);
    CancelButton->setFont(*qfont03);
    CancelButton->setText("取消");
    CancelButton->setFixedHeight(40);
    ButtonHLayout->addWidget(CancelButton);
    // 按钮器件**************************************************************************

    // 窗口属性**************************************************************************
    framelessHelper()->setTitleBar(titleWidget);
    setFixedWidth(940);
    setFixedHeight(414);
    setWindowIcon(QIcon(":/Image/BrokenRice.png"));
    // 窗口属性**************************************************************************

    // 信号与槽**************************************************************************
    connect(closebutton, &QPushButton::clicked,
            this, &InRepoAddDialog::onCloseButtonClicked);
    connect(AcceptButton, &QPushButton::clicked, this, [this]() {
        accept();
    });
    connect(CancelButton, &QPushButton::clicked, this, [this]() {
        reject();
    });
    // 信号与槽**************************************************************************
}
InRepoAddDialog::~InRepoAddDialog()
{
    // 删除new对象**********************************************************************
    delete qfont01;
    delete qfont02;
    delete qfont03;
    delete qfont04;
    // 删除new对象*********************************************************************
}
void InRepoAddDialog::onCloseButtonClicked()
{
    // 关闭窗口***************************************************************************
    close();
    // 关闭窗口***************************************************************************
}
void InRepoAddDialog::setInRepoAddCategory(QString category) {
    rowOneContent->setText(category);
}
void InRepoAddDialog::setInRepoAddName(QString name) {
    rowTwoContent->setText(name);
}
void InRepoAddDialog::setInRepoAddRepo(QString repo) {
    rowThreeContent->setText(repo);
}
void InRepoAddDialog::setInRepoAddNumber(QString number) {
    rowFourContent->setText(number);
}
/*
 * TotalVLayout->setContentsMargins(0, 0, 0, 0);
 * 设置了主布局的外边距都为0，这样做的原因是
 * 使得标题器件与内容器件之间的分割线能从左边开始，一直延伸到最右边
 * 所以设置主布局的外边距都为0
 * 接着又将内边距都设为了0
 * TotalVLayout->setSpacing(0);
 * 这样做的原因是，如果不把内边距设置为0
 * 标题器件与分割线，分割线与内容器件之间将会有无法说明的空隙
 * 而这一点是不想要的
 * 所以设置主窗口器件的布局的内边距为0
 * 虽然将主窗口部件的布局的外边距设置为了0，整体就没有缓冲，不舒服
 * 但依然可以通过设置标题部件的内外边距、内容部件的内外边距，进一步设置缓冲
 * 强化视觉效果
 */

/*
 * titleWidgetHLayout->setSpacing(0);
 * 标题器件的内边距被设置为了0
 * 这是因为，标题器件左上角有icon和大标题
 * 只有设置内边距为0之后，标题器件左上角的icon和大标题才会默认紧密排列在一起
 * 这为进一步调整标题器件左上角的icon和大标题之间的空隙提供了便利
 * titleWidgetHLayout->setContentsMargins(0, 0, 0, 0);
 * 标题器件的布局也将左上右下外边距设置为了0
 * 将左上右下外边距设置为0，跟centralWidgetVLayout保持了一致
 * 这就使得标题器件与分割线之间，没有无法说明的空隙
 */
