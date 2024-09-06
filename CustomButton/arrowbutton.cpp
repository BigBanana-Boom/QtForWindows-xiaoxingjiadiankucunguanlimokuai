#include "arrowbutton.h"

ArrowButton::ArrowButton(QWidget* parent)
    : QToolButton(parent),
      normalBackgroundColor(QColor(240, 240, 240)),
      hoverBackgroundColor(QColor(192, 192, 192)),
      currentBackgroundColor(normalBackgroundColor),
      targetBackgroundColor(hoverBackgroundColor),
      normalBorderColor(QColor(192, 192, 192)),
      hoverBorderColor(QColor(128, 128, 128)),
      currentBorderColor(normalBorderColor),
      targetBorderColor(hoverBorderColor),
      gradientTimer(new QTimer(this)),
      transitionSteps(10),
      currentStep(0)
{
    // 颜色与样式************************************************************************
    setStyleSheet(QString("background-color: %1; border: 3px solid %2; ")
                  .arg(currentBackgroundColor.name())
                  .arg(currentBorderColor.name()));
    // 颜色与样式************************************************************************

    // 初始化定时器**********************************************************************
    gradientTimer->setInterval(16);
    // 初始化定时器**********************************************************************

    // 槽函数*****************************************************************************
    connect(gradientTimer, &QTimer::timeout, this,
            &ArrowButton::updateGradient);
    // 槽函数*****************************************************************************
}
ArrowButton::~ArrowButton() {}
void ArrowButton::setNormalFormat(
        const QColor &backgroundcolor, QColor &bordercolor) {
    normalBackgroundColor = backgroundcolor;
    normalBorderColor = bordercolor;
    currentBackgroundColor = normalBackgroundColor;
    currentBorderColor = normalBorderColor;
    gradientTimer->stop();
    setStyleSheet(QString("background-color: %1; border: 3px solid %2; ")
                  .arg(currentBackgroundColor.name())
                  .arg(currentBorderColor.name()));
}
void ArrowButton::setHoverFormat(
        const QColor &backgroundcolor, QColor &bordercolor) {
    hoverBackgroundColor = backgroundcolor;
    hoverBorderColor = bordercolor;
}
void ArrowButton::enterEvent(QEvent* event) {
    targetBackgroundColor = hoverBackgroundColor;
    targetBorderColor = hoverBorderColor;
    currentStep = 0;
    gradientTimer->start();
    QToolButton::enterEvent(event);
}
void ArrowButton::leaveEvent(QEvent* event) {
    targetBackgroundColor = normalBackgroundColor;
    targetBorderColor = normalBorderColor;
    currentStep = 0;
    gradientTimer->start();
    QToolButton::leaveEvent(event);
}
void ArrowButton::updateGradient() {
    // 停止*******************************************************************************
    if (currentStep >= transitionSteps) {
        gradientTimer->stop();
        return;
    }
    // 停止*******************************************************************************
    // 更新颜色***************************************************************************
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
    setStyleSheet(QString("background-color: %1; border: 3px solid %2; ")
                  .arg(currentBackgroundColor.name())
                  .arg(currentBorderColor.name()));
    // 更新颜色***************************************************************************
    ++currentStep;
}
