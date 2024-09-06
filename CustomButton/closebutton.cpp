#include "closebutton.h"

CloseButton::CloseButton(QWidget* parent)
    : QPushButton(parent),
      normalColor(QColor(240, 240, 240)),
      hoverColor(QColor(200, 0, 0)),
      currentColor(normalColor),
      targetColor(hoverColor),
      normalIconColor(QColor(0, 0, 0)),
      hoverIconColor(QColor(255, 255, 255)),
      currentIconColor(normalIconColor),
      targetIconColor(hoverIconColor),
      gradientTimer(new QTimer(this)),
      transitionSteps(10),
      currentStep(0)
{
    // 颜色与样式***********************************************************************
    setStyleSheet(QString("border: none; background-color: %1")
                  .arg(currentColor.name()));
    setIconSize(QSize(30, 30));
    updateIcon();
    // 颜色与样式***********************************************************************

    // 初始化定时器**********************************************************************
    gradientTimer->setInterval(16);
    // 初始化定时器**********************************************************************

    // 槽函数*****************************************************************************
    connect(gradientTimer, &QTimer::timeout,
            this, &CloseButton::updateGradient);
    // 槽函数*****************************************************************************
}
CloseButton::~CloseButton() {}
void CloseButton::enterEvent(QEvent* event) {
    targetColor = hoverColor;
    targetIconColor = hoverIconColor;
    currentStep = 0;
    gradientTimer->start();
    QPushButton::enterEvent(event);
}
void CloseButton::leaveEvent(QEvent* event) {
    targetColor = normalColor;
    targetIconColor = normalIconColor;
    currentStep = 0;
    gradientTimer->start();
    QPushButton::leaveEvent(event);
}
void CloseButton::updateGradient() {
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
    // 更新图标颜色***********************************************************************
    // 绘制图标****************************************************************************
    updateIcon();
    // 绘制图标****************************************************************************
    ++currentStep;
}
void CloseButton::updateIcon() {
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
