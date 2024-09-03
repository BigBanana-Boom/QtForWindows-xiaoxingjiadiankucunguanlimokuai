#ifndef GRADIENTBUTTONWITHSIMPLEICON_H
#define GRADIENTBUTTONWITHSIMPLEICON_H

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

class GradientButtonWithSimpleIcon : public QPushButton
{
    Q_OBJECT
public:
    explicit GradientButtonWithSimpleIcon(QWidget *parent = nullptr);

    // 设置颜色****************************************************************************
    void setNormalColor(const QColor &color);
    void setHoverColor(const QColor &color);
    void setNormalIconColor(const QColor &color);
    void setHoverIconColor(const QColor &color);
    // 设置颜色***************************************************************************
    // 更新Icon***************************************************************************
    void updateIcon();
    // 更新Icon***************************************************************************
protected:
    // 重载以加动画***********************************************************************
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    // 重载以加动画***********************************************************************
private slots:
    // 极其频繁调用***********************************************************************
    void updateGradient();
    // 极其频繁调用***********************************************************************
private:
    QTimer *gradientTimer;
    QColor normalColor;
    QColor hoverColor;
    QColor normalIconColor;
    QColor hoverIconColor;
    QColor currentColor;
    QColor currentIconColor;
    int transitionSteps;
    int currentStep;
    QColor targetColor;
    QColor targetIconColor;
};

#endif // GRADIENTBUTTONWITHSIMPLEICON_H
