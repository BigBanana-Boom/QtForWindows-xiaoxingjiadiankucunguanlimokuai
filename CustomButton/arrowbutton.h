#ifndef ARROWBUTTON_H
#define ARROWBUTTON_H

#include <QToolButton>
#include <QTimer>
#include <QColor>
#include <QCoreApplication>
#include <QDateTime>
#include <QEvent>

class ArrowButton : public QToolButton
{
    Q_OBJECT
public:
    explicit ArrowButton(QWidget *parent = nullptr);
    ~ArrowButton();

    // 设置背景颜色***********************************************************************
    void setNormalFormat(const QColor &backgroundcolor, QColor &bordercolor);
    void setHoverFormat(const QColor &backgroundcolor, QColor &bordercolor);
    // 设置背景颜色***********************************************************************
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
    QColor normalBackgroundColor;
    QColor hoverBackgroundColor;
    QColor currentBackgroundColor;
    QColor targetBackgroundColor;
    // 按钮背景颜色***********************************************************************

    // 按钮边框颜色***********************************************************************
    QColor normalBorderColor;
    QColor hoverBorderColor;
    QColor currentBorderColor;
    QColor targetBorderColor;
    // 按钮边框颜色***********************************************************************

    // 定时器与过渡次数*******************************************************************
    QTimer *gradientTimer;
    int transitionSteps;
    int currentStep;
    // 定时器与过渡次数*******************************************************************
};

#endif // ARROWBUTTON_H
