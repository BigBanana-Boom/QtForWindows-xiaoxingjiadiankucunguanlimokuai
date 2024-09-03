#include "exitgradientbutton.h"

ExitGradientButton::ExitGradientButton(QWidget* parent)
    : QPushButton(parent),
      gradientTimer(new QTimer(this)),
      // 总步数与当前步数***************************************************************
      transitionSteps(10),
      currentStep(0)
    // 总步数与当前步数***************************************************************
{
    // 默认颜色**************************************************************************
    normalColor = QColor(240, 240, 240);
    hoverColor = QColor(200, 0, 0);
    normalIconColor = QColor(0, 0, 0);
    hoverIconColor = QColor(255, 255, 255);
    currentColor = normalColor;
    currentIconColor = normalIconColor;
    // 默认颜色**************************************************************************
    // 应用配置**************************************************************************
    setStyleSheet(QString("border: none; background-color: %1")
                  .arg(currentColor.name()));
    setIconSize(QSize(25, 25));
    updateIcon();
    // 应用配置**************************************************************************
    // 初始化定时器**********************************************************************
    gradientTimer->setInterval(16);
    // 初始化定时器**********************************************************************
    // 槽函数*****************************************************************************
    connect(gradientTimer, &QTimer::timeout,
            this, &ExitGradientButton::updateGradient);
    // 槽函数*****************************************************************************
}
void ExitGradientButton::enterEvent(QEvent* event) {
    targetColor = hoverColor;
    targetIconColor = hoverIconColor;
    currentStep = 0;
    gradientTimer->start();
    QPushButton::enterEvent(event);
}
void ExitGradientButton::leaveEvent(QEvent* event) {
    targetColor = normalColor;
    targetIconColor = normalIconColor;
    currentStep = 0;
    gradientTimer->start();
    QPushButton::leaveEvent(event);
}
void ExitGradientButton::updateGradient() {
    if (currentStep >= transitionSteps) {
        gradientTimer->stop();
        return;
    }
    qreal ratio = static_cast<qreal>(currentStep) / transitionSteps;

    // 更新背景颜色***********************************************************************
    int red = targetColor.red() * ratio + currentColor.red() * (1 - ratio);
    int green = targetColor.green() * ratio + currentColor.green() * (1 - ratio);
    int blue = targetColor.blue() * ratio + currentColor.blue() * (1 - ratio);
    currentColor = QColor(red, green, blue);
    setStyleSheet(QString("border: none; background-color: %1")
                  .arg(currentColor.name()));
    // 更新背景颜色***********************************************************************

    // 更新图标颜色***********************************************************************
    red = targetIconColor.red() * ratio + currentIconColor.red() * (1 - ratio);
    green = targetIconColor.green() * ratio + currentIconColor.green() * (1 - ratio);
    blue = targetIconColor.blue() * ratio + currentIconColor.blue() * (1 - ratio);
    currentIconColor = QColor(red, green, blue);
    updateIcon();
    // 更新图标颜色***********************************************************************

    ++currentStep;
}
void ExitGradientButton::updateIcon() {
    QPixmap pixmap(iconSize());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPen pen(currentIconColor);
    pen.setWidth(3);
    painter.setPen(pen);
    // 绘制 "X" 形状的两条对角线***********************************************************
    painter.drawLine(pixmap.rect().topLeft(), pixmap.rect().bottomRight());
    painter.drawLine(pixmap.rect().topRight(), pixmap.rect().bottomLeft());
    // 绘制 "X" 形状的两条对角线***********************************************************
    painter.end();
    setIcon(QIcon(pixmap));
}
