#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H

#include <QPushButton>
#include <QTimer>
#include <QColor>
#include <QDebug>
#include <QDateTime>
#include <QElapsedTimer>
#include <QEvent>
#include <QIcon>
#include <QPixmap>
#include <QPainter>

class CloseButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CloseButton(QWidget *parent = nullptr);
    ~CloseButton();
protected:
    // 重载函数****************************************************************************
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    // 重载函数****************************************************************************
private slots:
    // 动画过渡***************************************************************************
    void updateGradient();
    // 动画过渡***************************************************************************
private:
    // 按钮背景颜色***********************************************************************
    QColor normalColor;
    QColor hoverColor;
    QColor currentColor;
    QColor targetColor;
    // 按钮背景颜色***********************************************************************

    // 按钮Icon颜色***********************************************************************
    QColor normalIconColor;
    QColor hoverIconColor;
    QColor currentIconColor;
    QColor targetIconColor;
    // 按钮Icon颜色***********************************************************************

    // 定时器与过渡次数*******************************************************************
    QTimer *gradientTimer;
    int transitionSteps;
    int currentStep;
    // 定时器与过渡次数*******************************************************************

    // 函数*********************************************************************************
    void updateIcon();
    // 函数*********************************************************************************
};

#endif // CLOSEBUTTON_H
