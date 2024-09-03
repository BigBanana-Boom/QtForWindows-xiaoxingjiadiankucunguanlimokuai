#ifndef DROPDOWNGRADIENTBUTTON_H
#define DROPDOWNGRADIENTBUTTON_H

#include <QToolButton>
#include <QTimer>
#include <QColor>
#include <QCoreApplication>
#include <QDateTime>
#include <QEvent>

class DropDownGradientButton : public QToolButton
{
    Q_OBJECT
public:
    // 构造函数***************************************************************************
    explicit DropDownGradientButton(QWidget *parent = nullptr);
    // 构造函数***************************************************************************
    // 设置背景颜色***********************************************************************
    void setNormalFormat(const QColor &backgroundcolor, QColor &bordercolor);
    void setHoverFormat(const QColor &backgroundcolor, QColor &bordercolor);
    // 设置背景颜色***********************************************************************
protected:
    // 重载以加动画***********************************************************************
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    // 重载以加动画***********************************************************************
private slots:
    void updateGradient();
private:
    QTimer *gradientTimer;
    QColor normalBackgroundColor;
    QColor normalBorderColor;
    QColor hoverBackgroundColor;
    QColor hoverBorderColor;
    QColor currentBackgroundColor;
    QColor currentBorderColor;
    int transitionSteps;
    int currentStep;
    QColor targetBackgroundColor;
    QColor targetBorderColor;
};

#endif // DROPDOWNGRADIENTBUTTON_H
