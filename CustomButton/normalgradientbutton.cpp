#include "normalgradientbutton.h"

NormalGradientButton::NormalGradientButton(QWidget* parent)
    : QPushButton(parent),
      gradientTimer(new QTimer(this)),
      transitionSteps(10),
      currentStep(0)
{
    // 默认颜色**************************************************************************
    normalColor = QColor(255, 255, 255);
    hoverColor = QColor(240, 240, 240);
    currentColor = normalColor;
    setStyleSheet(QString("background-color: %1").arg(currentColor.name()));
    // 默认颜色**************************************************************************
    // 初始化定时器**********************************************************************
    gradientTimer->setInterval(16);
    // 初始化定时器**********************************************************************
    // 槽函数*****************************************************************************
    connect(gradientTimer, &QTimer::timeout, this,
            &NormalGradientButton::updateGradient);
    // 槽函数*****************************************************************************
}
void NormalGradientButton::setNormalColor(const QColor& color) {
    normalColor = color;
    currentColor = color;
    /* 恩，嗯，坏米饭*/
    gradientTimer->stop();
    setStyleSheet(QString("background-color: %1").arg(currentColor.name()));
    /* 恩，嗯，坏米饭*/
}
void NormalGradientButton::setHoverColor(const QColor& color) {
    hoverColor = color;
}
void NormalGradientButton::enterEvent(QEvent* event) {
    // 设置目标颜色为悬停颜色***********************************************************
    targetColor = hoverColor;
    // 设置目标颜色为悬停颜色***********************************************************
    currentStep = 0;
    // 开始渐变到悬停颜色***************************************************************
    gradientTimer->start();
    // 开始渐变到悬停颜色***************************************************************
    // 继续QPushButton父类的enterEvent***********************************************
    QPushButton::enterEvent(event);
    // 继续QPushButton父类的enterEvent***********************************************
}
void NormalGradientButton::leaveEvent(QEvent* event) {
    // 设置目标颜色为正常颜色************************************************************
    targetColor = normalColor;
    // 设置目标颜色为正常颜色************************************************************
    currentStep = 0;
    // 开始渐变到正常颜色****************************************************************
    gradientTimer->start();
    // 开始渐变到正常颜色****************************************************************
    // 继续QPushButton父类的leaveEvent***********************************************
    QPushButton::leaveEvent(event);
    // 继续QPushButton父类的leaveEvent***********************************************
}
void NormalGradientButton::updateGradient() {
    // 停止*******************************************************************************
    if (currentStep >= transitionSteps) {
        gradientTimer->stop();
        return;
    }
    // 停止*******************************************************************************
    // 计算当前颜色***********************************************************************
    qreal ratio = static_cast<qreal>(currentStep) / transitionSteps;
    int red = targetColor.red() * ratio + currentColor.red() * (1 - ratio);
    int green = targetColor.green() * ratio + currentColor.green() * (1 - ratio);
    int blue = targetColor.blue() * ratio + currentColor.blue() * (1 - ratio);
    currentColor = QColor(red, green, blue);
    // 计算当前颜色***********************************************************************
    // 应用当前颜色***********************************************************************
    setStyleSheet(QString("background-color: %1").arg(currentColor.name()));
    // 应用当前颜色***********************************************************************
    // 步进********************************************************************************
    ++currentStep;
    // 步进********************************************************************************
}
