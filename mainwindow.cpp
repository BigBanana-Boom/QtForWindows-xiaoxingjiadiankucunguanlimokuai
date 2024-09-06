#include "mainwindow.h"

MainWindow::MainWindow(bool resizeEnable, bool shadowBorder,
                       bool winNativeEvent, QWidget *parent)
    : QFramelessMainWindow(parent, resizeEnable, shadowBorder, winNativeEvent),
      qfont01(new QFont("楷体", 24, QFont::Bold)),
      qfont02(new QFont("楷体", 26, QFont::Bold)),
      centralWidget(new QWidget(this)),
      centralWidgetVLayout(new QVBoxLayout()),
      titleWidget(new QWidget(this)),
      titleWidgetHLayout(new QHBoxLayout()),
      labelIcon(new QLabel(this)),
      labelTitle(new QLabel(this)),
      minimizedVLayout(new QVBoxLayout()),
      minimizedbutton(new GradientButton(this)),
      maximizedVLayout(new QVBoxLayout()),
      maximizedbutton(new GradientButton(this)),
      closeVLayout(new QVBoxLayout()),
      closebutton(new CloseButton(this)),
      line(new QFrame(this)),
      contentWidget(new QWidget(this)),
      contentWidgetHLayout(new QHBoxLayout()),
      leftContentLayout(new QVBoxLayout()),
      rightContentLayout(new QVBoxLayout()),
      gradientbutton01(new GradientButton(this)),
      gradientbutton02(new GradientButton(this)),
      gradientbutton03(new GradientButton(this)),
      gradientbutton04(new GradientButton(this)),
      gradientbutton05(new GradientButton(this)),
      stackedWidget(new QStackedWidget(this))
{
    // 中央器件**************************************************************************
    setCentralWidget(centralWidget);
    centralWidget->setLayout(centralWidgetVLayout);
    centralWidgetVLayout->setSpacing(0);
    centralWidgetVLayout->setContentsMargins(0, 0, 0, 0);
    // 中央器件**************************************************************************

    // 标题器件**************************************************************************
    titleWidget->setLayout(titleWidgetHLayout);
    centralWidgetVLayout->addWidget(titleWidget);
    // 左侧******************************************************************************
    QPixmap pixmap(":/Image/BrokenRice.png");
    // 变大小，保持原始宽高比，切换尽可能平滑*****************************************
    pixmap = pixmap.scaled(40, 40,
                           Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // 变大小，保持原始宽高比，切换尽可能平滑*****************************************
    // 为QLabel设置图像****************************************************************
    labelIcon->setPixmap(pixmap);
    // 为QLabel设置图像****************************************************************
    // 设置QLabel左右外边距，这样不紧贴左边，也不紧贴名称***************************
    labelIcon->setContentsMargins(20, 0, 20, 0);
    // 设置QLabel左右外边距，这样不紧贴左边，也不紧贴名称***************************
    labelTitle->setText("坏米饭");
    labelTitle->setFont(*qfont02);
    titleWidgetHLayout->addWidget(labelIcon);
    titleWidgetHLayout->addWidget(labelTitle);
    titleWidgetHLayout->addStretch(1);
    // 左侧******************************************************************************
    // 右侧******************************************************************************
    minimizedbutton->setIcon(QIcon(":/Image/minimized.png"));
    minimizedbutton->setIconSize(QSize(40, 40));
    minimizedbutton->setFixedSize(QSize(70, 53));
    maximizedbutton->setIcon(QIcon(":/Image/maximized.png"));
    maximizedbutton->setIconSize(QSize(40, 40));
    maximizedbutton->setFixedSize(QSize(70, 53));
    closebutton->setFixedSize(QSize(70, 53));
    minimizedVLayout->addWidget(minimizedbutton);
    minimizedVLayout->addStretch(1);
    maximizedVLayout->addWidget(maximizedbutton);
    maximizedVLayout->addStretch(1);
    closeVLayout->addWidget(closebutton);
    closeVLayout->addStretch(1);
    titleWidgetHLayout->addLayout(minimizedVLayout);
    titleWidgetHLayout->addLayout(maximizedVLayout);
    titleWidgetHLayout->addLayout(closeVLayout);
    // 右侧******************************************************************************
    // 设置固定高度，更加稳定**********************************************************
    titleWidget->setFixedHeight(60);
    // 设置固定高度，更加稳定**********************************************************
    titleWidgetHLayout->setSpacing(0);
    titleWidgetHLayout->setContentsMargins(0, 0, 0, 0);
    // 标题器件**************************************************************************

    // 标题器件与内容器件之间的分割线**************************************************
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setFixedHeight(2);
    line->setStyleSheet("QFrame { margin-top: 0px; margin-bottom: 0px; "
                        "border: 1px solid #bfbfbf; }");
    centralWidgetVLayout->addWidget(line);
    // 标题器件与内容器件之间的分割线**************************************************

    // 内容器件**************************************************************************
    contentWidget->setLayout(contentWidgetHLayout);
    // 左内容****************************************************************************
    gradientbutton01->setText("已定");
    gradientbutton01->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    gradientbutton01->setFont(*qfont01);
    gradientbutton01->setMinimumWidth(150);
    gradientbutton01->setNormalColor(QColor(255, 255, 255));
    gradientbutton02->setText("出库");
    gradientbutton02->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    gradientbutton02->setFont(*qfont01);
    gradientbutton02->setMinimumWidth(150);
    gradientbutton03->setText("入库");
    gradientbutton03->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    gradientbutton03->setFont(*qfont01);
    gradientbutton03->setMinimumWidth(150);
    gradientbutton04->setText("库存");
    gradientbutton04->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    gradientbutton04->setFont(*qfont01);
    gradientbutton04->setMinimumWidth(150);
    gradientbutton05->setText("配置");
    gradientbutton05->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    gradientbutton05->setFont(*qfont01);
    gradientbutton05->setMinimumWidth(150);
    leftContentLayout->addWidget(gradientbutton01);
    leftContentLayout->addWidget(gradientbutton02);
    leftContentLayout->addWidget(gradientbutton03);
    leftContentLayout->addWidget(gradientbutton04);
    leftContentLayout->addWidget(gradientbutton05);
    leftContentLayout->setSpacing(0);
    // 左内容****************************************************************************
    // 右内容****************************************************************************
    InitDatabase();
    doneWindow = new Done(stackedWidget, db, query);
    outRepoWindow = new OutRepo(stackedWidget, db, query);
    inRepoWindow = new InRepo(stackedWidget, db, query);
    modifyRepoWindow = new ModifyRepo(stackedWidget, db, query);
    repoWindow = new Repo(stackedWidget, db, query);
    stackedWidget->addWidget(doneWindow);
    stackedWidget->addWidget(outRepoWindow);
    stackedWidget->addWidget(inRepoWindow);
    stackedWidget->addWidget(repoWindow);
    stackedWidget->addWidget(modifyRepoWindow);
    stackedWidget->setCurrentWidget(doneWindow);
    rightContentLayout->addWidget(stackedWidget);
    // 右内容****************************************************************************
    // 内容******************************************************************************
    contentWidgetHLayout->addLayout(leftContentLayout);
    contentWidgetHLayout->addLayout(rightContentLayout);
    contentWidgetHLayout->setSpacing(0);
    contentWidgetHLayout->setContentsMargins(8, 0, 8, 8);
    // 内容******************************************************************************
    centralWidgetVLayout->addWidget(contentWidget);
    // 内容器件**************************************************************************

    // 窗口属性**************************************************************************
    framelessHelper()->setTitleBar(titleWidget);
    setGeometry(200, 120, 800, 600);
    setWindowIcon(QIcon(":/Image/BrokenRice.png"));
    // 窗口属性**************************************************************************

    // 信号与槽**************************************************************************
    // 右上方小大关按钮*****************************************************************
    connect(minimizedbutton, &QPushButton::clicked,
            this, &MainWindow::onMinimizedButtonClicked);
    connect(maximizedbutton, &QPushButton::clicked,
            this, &MainWindow::onMaximizedButtonClicked);
    connect(closebutton, &QPushButton::clicked,
            this, &MainWindow::onCloseButtonClicked);
    connect(framelessHelper(), &QFramelessHelper::maximizedChanged,
            this, &MainWindow::slotMaximizedChanged);
    // 右上方小大关按钮*****************************************************************
    // 左边按钮切换不同widget**********************************************************
    connect(gradientbutton01, &QPushButton::clicked, stackedWidget,
            [this](){
        stackedWidget->setCurrentWidget(doneWindow);
    });
    connect(gradientbutton02, &QPushButton::clicked, stackedWidget,
            [this](){
        stackedWidget->setCurrentWidget(outRepoWindow);
    });
    connect(gradientbutton03, &QPushButton::clicked, stackedWidget,
            [this](){
        stackedWidget->setCurrentWidget(inRepoWindow);
    });
    connect(gradientbutton04, &QPushButton::clicked, stackedWidget,
            [this](){
        stackedWidget->setCurrentWidget(repoWindow);
    });
    connect(gradientbutton05, &QPushButton::clicked, stackedWidget,
            [this](){
        stackedWidget->setCurrentWidget(modifyRepoWindow);
    });
    // 左边按钮切换不同widget**********************************************************
    // 不同widget设置左边按钮样式******************************************************
    connect(stackedWidget, &QStackedWidget::currentChanged, this,
            [this](int currentIndex) {
                gradientbutton01->setNormalColor(QColor(240, 240, 240));
                gradientbutton02->setNormalColor(QColor(240, 240, 240));
                gradientbutton03->setNormalColor(QColor(240, 240, 240));
                gradientbutton04->setNormalColor(QColor(240, 240, 240));
                gradientbutton05->setNormalColor(QColor(240, 240, 240));
        switch (currentIndex) {
            case 0: gradientbutton01->setNormalColor(QColor(255, 255, 255));
                        break;
            case 1: gradientbutton02->setNormalColor(QColor(255, 255, 255));
                        break;
            case 2: gradientbutton03->setNormalColor(QColor(255, 255, 255));
                        break;
            case 3: gradientbutton04->setNormalColor(QColor(255, 255, 255));
                        break;
            case 4: gradientbutton05->setNormalColor(QColor(255, 255, 255));
                        break;
        }
    });
    // 不同widget设置左边按钮样式******************************************************
    // 信号与槽*****************************************************************************
}
MainWindow::~MainWindow() {
    // 删除new对象**********************************************************************
    db->close();
    delete query;
    delete db;
    delete qfont01;
    delete qfont02;
    // 删除new对象*********************************************************************
}
void MainWindow::onMinimizedButtonClicked()
{
    // 窗口最小化************************************************************************
    showMinimized();
    // 窗口最小化************************************************************************
}
void MainWindow::onMaximizedButtonClicked()
{
    // 不同状态，选择最小化还是最大化**************************************************
    if (isMaximized()) {
        showNormal();
    }
    else {
        showMaximized();
        // 恩，坏米饭*********************************************************************
        QEvent leaveEvent(QEvent::Leave);
        QCoreApplication::sendEvent(maximizedbutton, &leaveEvent);
        // 恩，坏米饭*********************************************************************
    }
    // 不同状态，选择最小化还是最大化**************************************************
}
void MainWindow::onCloseButtonClicked()
{
    // 关闭窗口***************************************************************************
    close();
    // 关闭窗口***************************************************************************
}
void MainWindow::slotMaximizedChanged(bool bMax)
{
    QString strIcon = bMax ? ":/Image/normalized.png" : ":/Image/maximized.png";
    maximizedbutton->setIcon(QIcon(strIcon));
}
void MainWindow::InitDatabase()
{
    // 数据库配置***********************************************************************
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName("mydatabase.db");
    db->open();
    // 数据库配置***********************************************************************
    // 数据库连接***********************************************************************
    query = new QSqlQuery(*db);
    // 数据库连接***********************************************************************
    /*
    QFile file;
    QTextStream in;
    QString sqlQuery;
    // 建立已定表***********************************************************************
    file.setFileName(":/Sql/CreateDoneTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 建立已定表***********************************************************************
    // 初始化已定表*********************************************************************
    file.setFileName(":/Sql/InitDoneTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 初始化已定表*********************************************************************
    // 建立出库表***********************************************************************
    file.setFileName(":/Sql/CreateOutRepoTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 建立出库表***********************************************************************
    // 初始化出库表*********************************************************************
    file.setFileName(":/Sql/InitOutRepoTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 初始化出库表*********************************************************************
    // 建立入库表***********************************************************************
    file.setFileName(":/Sql/CreateInRepoTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 建立入库表***********************************************************************
    // 初始化入库表*********************************************************************
    file.setFileName(":/Sql/InitInRepoTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 初始化入库表*********************************************************************
    // 建立库存表***********************************************************************
    file.setFileName(":/Sql/CreateRepoTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 建立库存表***********************************************************************
    // 初始化库存表*********************************************************************
    file.setFileName(":/Sql/InitRepoTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 初始化库存表*********************************************************************
    // 整理库存表***********************************************************************
    RefreshRepoTableID refreshID(db, query);
    // 整理库存表***********************************************************************
    // 建立附表1仓库信息表*************************************************************
    file.setFileName(":/Sql/CreateRepoInfoTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 建立附表1仓库信息表*************************************************************
    // 初始化附表1仓库信息表***********************************************************
    file.setFileName(":/Sql/InitRepoInfoTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 初始化附表1仓库信息表***********************************************************
    // 建立附表2进货产品表*************************************************************
    file.setFileName(":/Sql/CreateInRepoInfoTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 建立附表2进货产品表*************************************************************
    // 初始化附表2进货产品表***********************************************************
    file.setFileName(":/Sql/InitInRepoInfoTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 初始化附表2进货产品表***********************************************************
    // 建立附表3库存调整表*************************************************************
    file.setFileName(":/Sql/CreateRepoChangeTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 建立附表3库存调整表*************************************************************
    // 初始化附表3库存调整表***********************************************************
    file.setFileName(":/Sql/InitRepoChangeTable.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&file);
    in.setCodec("UTF-8");
    sqlQuery = in.readAll();
    file.close();
    query->exec(sqlQuery);
    // 初始化附表3库存调整表***********************************************************
    */
}

/*
 * centralWidgetVLayout->setContentsMargins(0, 0, 0, 0);
 * 在应用于主窗口器件的布局中，设置了布局的外边距都为0
 * 设置布局的外边距都为0的原因是
 * 如果存在外边距，那么双击标题器件时，双击放大、双击缩小等，将无法正常工作
 * 所以设置主窗口器件的布局的外边距都为0
 * 接着又将内边距都设为了0
 * centralWidgetVLayout->setSpacing(0);
 * 这样做的原因是，如果不把内边距设置为0
 * 那么标题器件、标题器件与内容器件之间的分割线、内容器件之间，将会存在空隙
 * 而如果鼠标处在标题器件与标题器件与内容期间之间的分割线之间的空隙时
 * 双击放大与双击缩小将无法正常工作
 * 所以设置主窗口器件的布局的内边距为0
 * 虽然将主窗口部件的布局的外边距设置为了0，整体就没有缓冲，不舒服
 * 但依然可以通过设置标题部件的内外边距、内容部件的内外边距，进一步设置缓冲
 * 强化视觉效果
 */

/*
 * titleWidgetHLayout->setSpacing(0);
 * 标题器件的内边距被设置为了0
 * 这是因为，标题器件右上角将会有三个小按钮，最小化、最大化/正常化以及关闭
 * 只有设置内边距为0之后，标题器件右上角的三个小按钮才会紧密排列在一起
 * 否则将不会紧密排列在一起
 * titleWidgetHLayout->setContentsMargins(0, 0, 0, 0);
 * 标题器件的布局也将左上右下外边距设置为了0
 * 将左上右下外边距设置为0，跟centralWidgetVLayout保持了一致
 * 这就使得双击放大与双击缩小能够更好地正常工作
 */
