#include "gradientbutton.h"

GradientButton::GradientButton(QWidget* parent)
    : QPushButton(parent),
      normalColor(QColor(240, 240, 240)),
      hoverColor(QColor(255, 255, 255)),
      currentColor(normalColor),
      targetColor(hoverColor),
      buttonstyle(new QString("border: none; ")),
      gradientTimer(new QTimer(this)),
      transitionSteps(10),
      currentStep(0)
{
    // 颜色与样式************************************************************************
    setStyleSheet(*buttonstyle + QString("background-color: %1")
                  .arg(currentColor.name()));
    // 颜色与样式************************************************************************

    // 初始化定时器**********************************************************************
    gradientTimer->setInterval(16);
    // 初始化定时器**********************************************************************

    // 槽函数*****************************************************************************
    connect(gradientTimer, &QTimer::timeout, this, &GradientButton::updateGradient);
    // 槽函数*****************************************************************************
}
GradientButton::~GradientButton() {
    delete buttonstyle;
}
void GradientButton::setCustomStyle(QString customstyle) {
    *buttonstyle = customstyle;
    setStyleSheet(*buttonstyle + QString("background-color: %1")
                 .arg(currentColor.name()));
}
void GradientButton::setNormalColor(const QColor& color) {
    normalColor = color;
    currentColor = color;
    gradientTimer->stop();
    setStyleSheet(*buttonstyle + QString("background-color: %1")
                 .arg(currentColor.name()));
}
void GradientButton::setHoverColor(const QColor& color) {
    hoverColor = color;
}
void GradientButton::enterEvent(QEvent* event) {
    targetColor = hoverColor;
    currentStep = 0;
    gradientTimer->start();
    QPushButton::enterEvent(event);
}
void GradientButton::leaveEvent(QEvent* event) {
    targetColor = normalColor;
    currentStep = 0;
    gradientTimer->start();
    QPushButton::leaveEvent(event);
}
void GradientButton::updateGradient() {
    // 停止*******************************************************************************
    if (currentStep >= transitionSteps) {
        gradientTimer->stop();
        return;
    }
    // 停止*******************************************************************************
    // 更新背景颜色***********************************************************************
    qreal ratio = static_cast<qreal>(currentStep) / transitionSteps;
    int red = targetColor.red() * ratio + currentColor.red() * (1 - ratio);
    int green = targetColor.green() * ratio + currentColor.green() * (1 - ratio);
    int blue = targetColor.blue() * ratio + currentColor.blue() * (1 - ratio);
    currentColor = QColor(red, green, blue);
    setStyleSheet(*buttonstyle + QString("background-color: %1")
                  .arg(currentColor.name()));
    // 更新背景颜色***********************************************************************
    ++currentStep;
}
