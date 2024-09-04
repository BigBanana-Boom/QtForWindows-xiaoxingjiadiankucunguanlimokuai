#ifndef INPUTZONE_H
#define INPUTZONE_H

#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>

struct InputZone {
    QHBoxLayout* layout;
    QLabel* label;
    QSpinBox* spinBox;
    QLabel* label2;
};

#endif // INPUTZONE_H
