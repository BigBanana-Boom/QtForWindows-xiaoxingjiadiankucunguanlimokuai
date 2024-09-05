#ifndef DONEREMOVEDIALOG2_H
#define DONEREMOVEDIALOG2_H

#include "qframelessdialog.h"
#include "../MethodClass/refreshrepotableid.h"
#include "../CustomButton/dialoggradientbutton.h"
#include "../CustomButton/exitgradientbutton.h"
#include "../CustomStruct/inputzone.h"
#include "../CustomStruct/repoandcurrentnum.h"
#include "../CustomStruct/repoandnumber.h"
#include <QDialog>
#include <QFile>
#include <QLabel>
#include <QTextEdit>
#include <QApplication>
#include <QComboBox>
#include <QDateTime>
#include <QDebug>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidget>
#include <QVector>
#include <QVBoxLayout>

class DoneRemoveDialog2 : public QFramelessDialog
{
    Q_OBJECT
public:
    explicit DoneRemoveDialog2(bool resizeEnable = true,
                               bool shadowBorder = true,
                               bool winNativeEvent = true,
                               QWidget *parent = nullptr,
                               int reponum = 0,
                               int currentproductnumber = 0,
                               QVector<RepoAndCurrentNum> *ret = nullptr);
    ~DoneRemoveDialog2();
    void setDoneRemove2ID(QString id);
    void setDoneRemove2DateTime(QString datetime);
    void setDoneRemove2Category(QString category);
    void setDoneRemove2Name(QString name);
    void setDoneRemove2Number(QString number);
    void setDoneRemove2Repo(QVector<RepoAndNumber> repoandnumberv);
private slots:
    void onCloseButtonClicked();
private:
    // 字体********************************************************************************
    QFont *qfont01;
    QFont *qfont02;
    QFont *qfont03;
    QFont *qfont04;
    // 字体********************************************************************************

    // 总布局******************************************************************************
    QVBoxLayout *TotalVLayout;
    // 总布局******************************************************************************

    // 标题器件及内容*********************************************************************
    QWidget *titleWidget;
    QHBoxLayout *titleWidgetHLayout;
    QLabel *labelIcon;
    QLabel *labelTitle;
    // 右上方小大关按钮布局**************************************************************
    QVBoxLayout *closeVLayout;
    ExitGradientButton *closebutton;
    // 右上方小大关按钮布局**************************************************************
    // 标题器件及内容*********************************************************************

    // 标题器件与内容器件之间的分割线****************************************************
    QFrame *line;
    // 标题器件与内容器件之间的分割线****************************************************

    // 内容器件及内容**********************************************************************
    QWidget *contentWidget;
    QVBoxLayout *contentWidgetVLayout;
    // 标题*********************************************************************************
    QLabel *contentWidgetTitle;
    // 标题*********************************************************************************
    // 第一行******************************************************************************
    QLabel *rowOneLabel;
    QLabel *rowOneContent;
    QHBoxLayout *rowOneHLayout;
    // 第一行******************************************************************************
    // 第二行******************************************************************************
    QLabel *rowTwoLabel;
    QLabel *rowTwoContent;
    QHBoxLayout *rowTwoHLayout;
    // 第二行******************************************************************************
    // 第三行******************************************************************************
    QLabel *rowThreeLabel;
    QLabel *rowThreeContent;
    QHBoxLayout *rowThreeHLayout;
    // 第三行******************************************************************************
    // 第四行******************************************************************************
    QLabel *rowFourLabel;
    QLabel *rowFourContent;
    QHBoxLayout *rowFourHLayout;
    // 第四行******************************************************************************
    // 第五行******************************************************************************
    QLabel *rowFiveLabel;
    QLabel *rowFiveContent;
    QHBoxLayout *rowFiveHLayout;
    // 第五行******************************************************************************
    // 第六行及之后***********************************************************************
    QLabel *rowSixLabel;
    // 这里使用了一个自定义的结构体*****************************************************
    QVector<InputZone> inputZones;
    // 这里使用了一个自定义的结构体*****************************************************
    // 第六行及之后***********************************************************************
    // 倒数第二行*************************************************************************
    QLabel *rowLastTwoLabel;
    // 倒数第二行*************************************************************************
    // 倒数第一行**************************************************************************
    QLabel *rowLastOneLabel;
    // 倒数第一行**************************************************************************
    // 内容器件及内容*********************************************************************

    // 内容器件与按钮器件之间的分割线****************************************************
    QFrame *line2;
    // 内容器件与按钮器件之间的分割线****************************************************

    // 按钮器件及内容**********************************************************************
    QWidget *buttonWidget;
    QHBoxLayout *ButtonHLayout;
    DialogGradientButton *AcceptButton;
    DialogGradientButton *CancelButton;
    // 按钮器件及内容**********************************************************************
};

#endif // DONEREMOVEDIALOG2_H
