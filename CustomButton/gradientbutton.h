#ifndef GRADIENTBUTTON_H
#define GRADIENTBUTTON_H

#include <QPushButton>
#include <QTimer>
#include <QColor>
#include <QDateTime>
#include <QEvent>

class GradientButton : public QPushButton
{
    Q_OBJECT
public:
    // 构造函数***************************************************************************
    explicit GradientButton(QWidget *parent = nullptr);
    ~GradientButton();
    // 构造函数***************************************************************************

    // 设置背景颜色***********************************************************************
    void setNormalColor(const QColor &color);
    void setHoverColor(const QColor &color);
    // 设置背景颜色***********************************************************************

    // 设置样式***************************************************************************
    void setCustomStyle(QString customstyle);
    // 设置样式***************************************************************************
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

    // 按钮样式***************************************************************************
    QString *buttonstyle;
    // 按钮样式***************************************************************************

    // 定时器与过渡次数*******************************************************************
    QTimer *gradientTimer;
    int transitionSteps;
    int currentStep;
    // 定时器与过渡次数*******************************************************************
};

#endif // GRADIENTBUTTON_H
