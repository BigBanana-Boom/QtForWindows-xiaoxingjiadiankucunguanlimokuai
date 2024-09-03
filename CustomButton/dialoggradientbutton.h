#ifndef DIALOGGRADIENTBUTTON_H
#define DIALOGGRADIENTBUTTON_H

#include <QPushButton>
#include <QTimer>
#include <QColor>
#include <QDateTime>

class DialogGradientButton : public QPushButton
{
    Q_OBJECT
public:
    // 构造函数***************************************************************************
    explicit DialogGradientButton(QWidget *parent = nullptr);
    // 构造函数***************************************************************************
    // 设置背景颜色***********************************************************************
    void setNormalColor(const QColor &color);
    void setHoverColor(const QColor &color);
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
    QColor normalColor;
    QColor hoverColor;
    QColor currentColor;
    int transitionSteps;
    int currentStep;
    QColor targetColor;
};

#endif // DIALOGGRADIENTBUTTON_H
