#ifndef CHINESESORT_H
#define CHINESESORT_H

#include <QStringList>
#include <QCollator>
class ChineseSort
{
public:
    explicit ChineseSort(QStringList* list = nullptr);
    void operator()(QStringList* list);
};

#endif // CHINESESORT_H
