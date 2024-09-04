#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include "qframelessdialog.h"
#include "CustomButton/dialoggradientbutton.h"
#include "CustomButton/exitgradientbutton.h"
#include <QDialog>
#include <QFile>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>

class SearchDialog : public QFramelessDialog
{
    Q_OBJECT
public:
    explicit SearchDialog(bool resizeEnable = true,
                          bool shadowBorder = true,
                          bool winNativeEvent = true,
                          QWidget *parent = nullptr);
    ~SearchDialog();
    void setDialogContent(QString content);
private slots:
    void onCloseButtonClicked();
private:
    // 字体********************************************************************************
    QFont *qfont01;
    QFont *qfont02;
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
    // 第一行******************************************************************************
    QLabel *rowOneLabel;
    // 第一行******************************************************************************
    // 内容器件及内容**********************************************************************

    // 内容器件与按钮器件之间的分割线****************************************************
    QFrame *line2;
    // 内容器件与按钮器件之间的分割线****************************************************

    // 按钮器件及内容**********************************************************************
    QWidget *buttonWidget;
    QHBoxLayout *ButtonHLayout;
    DialogGradientButton *AcceptButton;
    // 按钮器件及内容**********************************************************************
};

#endif // SEARCHDIALOG_H
