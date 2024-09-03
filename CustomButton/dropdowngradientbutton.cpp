#include "dropdowngradientbutton.h"

DropDownGradientButton::DropDownGradientButton(QWidget* parent)
    : QToolButton(parent),
      gradientTimer(new QTimer(this)),
      transitionSteps(10),
      currentStep(0)
{
    // 默认颜色**************************************************************************
    normalBackgroundColor = QColor(240, 240, 240);
    normalBorderColor = QColor(192, 192, 192);
    hoverBackgroundColor = QColor(192, 192, 192);
    hoverBorderColor = QColor(128, 128, 128);
    currentBackgroundColor = normalBackgroundColor;
    currentBorderColor = normalBorderColor;
    setStyleSheet(QString("background-color: %1; border: 3px solid %2; ")
                  .arg(currentBackgroundColor.name())
                  .arg(currentBorderColor.name()));
    // 默认颜色**************************************************************************
    // 初始化定时器**********************************************************************
    gradientTimer->setInterval(16);
    // 初始化定时器**********************************************************************
    // 槽函数*****************************************************************************
    connect(gradientTimer, &QTimer::timeout, this,
            &DropDownGradientButton::updateGradient);
    // 槽函数*****************************************************************************
}
void DropDownGradientButton::setNormalFormat(
        const QColor &backgroundcolor, QColor &bordercolor) {
    normalBackgroundColor = backgroundcolor;
    normalBorderColor = bordercolor;
    currentBackgroundColor = normalBackgroundColor;
    currentBorderColor = normalBorderColor;
    /* 恩，嗯，坏米饭*/
    gradientTimer->stop();
    setStyleSheet(QString("background-color: %1; border: 3px solid %2; ")
                  .arg(currentBackgroundColor.name())
                  .arg(currentBorderColor.name()));
    /* 恩，嗯，坏米饭*/
}
void DropDownGradientButton::setHoverFormat(
        const QColor &backgroundcolor, QColor &bordercolor) {
    hoverBackgroundColor = backgroundcolor;
    hoverBorderColor = bordercolor;
}
void DropDownGradientButton::enterEvent(QEvent* event) {
    // 设置目标颜色为悬停颜色***********************************************************
    targetBackgroundColor = hoverBackgroundColor;
    targetBorderColor = hoverBorderColor;
    // 设置目标颜色为悬停颜色***********************************************************
    currentStep = 0;
    // 开始渐变到悬停颜色***************************************************************
    gradientTimer->start();
    // 开始渐变到悬停颜色***************************************************************
    // 继续QToolButton父类的enterEvent***********************************************
    QToolButton::enterEvent(event);
    // 继续QToolButton父类的enterEvent***********************************************
}
void DropDownGradientButton::leaveEvent(QEvent* event) {
    // 设置目标颜色为正常颜色************************************************************
    targetBackgroundColor = normalBackgroundColor;
    targetBorderColor = normalBorderColor;
    // 设置目标颜色为正常颜色************************************************************
    currentStep = 0;
    // 开始渐变到正常颜色****************************************************************
    gradientTimer->start();
    // 开始渐变到正常颜色****************************************************************
    // 继续QToolButton父类的leaveEvent***********************************************
    QToolButton::leaveEvent(event);
    // 继续QToolButton父类的leaveEvent***********************************************
}
void DropDownGradientButton::updateGradient() {
    // 停止*******************************************************************************
    if (currentStep >= transitionSteps) {
        gradientTimer->stop();
        return;
    }
    // 停止*******************************************************************************
    // 计算当前颜色***********************************************************************
    qreal ratio = static_cast<qreal>(currentStep) / transitionSteps;
    int red = targetBackgroundColor.red() * ratio +
            currentBackgroundColor.red() * (1 - ratio);
    int green = targetBackgroundColor.green() * ratio +
            currentBackgroundColor.green() * (1 - ratio);
    int blue = targetBackgroundColor.blue() * ratio +
            currentBackgroundColor.blue() * (1 - ratio);
    currentBackgroundColor = QColor(red, green, blue);

    red = targetBorderColor.red() * ratio +
            currentBorderColor.red() * (1 - ratio);
    green = targetBorderColor.green() * ratio +
            currentBorderColor.green() * (1 - ratio);
    blue = targetBorderColor.blue() * ratio +
            currentBorderColor.blue() * (1 - ratio);
    currentBorderColor = QColor(red, green, blue);
    // 计算当前颜色***********************************************************************
    // 应用当前颜色***********************************************************************
    setStyleSheet(QString("background-color: %1; border: 3px solid %2; ")
                  .arg(currentBackgroundColor.name())
                  .arg(currentBorderColor.name()));
    // 应用当前颜色***********************************************************************
    // 步进********************************************************************************
    ++currentStep;
    // 步进********************************************************************************
}
