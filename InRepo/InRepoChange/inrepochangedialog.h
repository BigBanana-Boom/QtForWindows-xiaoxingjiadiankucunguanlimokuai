#ifndef INREPOCHANGEDIALOG_H
#define INREPOCHANGEDIALOG_H

#include "qframelessdialog.h"
#include "../CustomButton/dialoggradientbutton.h"
#include "../CustomButton/exitgradientbutton.h"
#include <QDialog>
#include <QFile>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>

class InRepoChangeDialog : public QFramelessDialog
{
    Q_OBJECT
public:
    InRepoChangeDialog(bool resizeEnable = true,
                       bool shadowBorder = true,
                       bool winNativeEvent = true,
                       QWidget *parent = nullptr);
    ~InRepoChangeDialog();
    void setInRepoChangeTitle(QString title);
    void setInRepoChangeID(QString id);
    void setInRepoChangeDateTime(QString datetime);
    void setInRepoChangeCategory(QString category);
    void setInRepoChangeName(QString name);
    void setInRepoChangeRepo(QString repo);
    void setInRepoOriginalNumber(QString number);
    void setInRepoChangeNumber(QString number);
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
    // 第六行******************************************************************************
    QLabel *rowSixLabel;
    QLabel *rowSixContent;
    QHBoxLayout *rowSixHLayout;
    // 第六行******************************************************************************
    // 第七行******************************************************************************
    QLabel *rowSevenLabel;
    QLabel *rowSevenContent;
    QHBoxLayout *rowSevenHLayout;
    // 第七行******************************************************************************
    // 第八行******************************************************************************
    QLabel *rowEightLabel;
    // 第八行******************************************************************************
    // 内容器件及内容**********************************************************************

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

#endif // INREPOCHANGEDIALOG_H