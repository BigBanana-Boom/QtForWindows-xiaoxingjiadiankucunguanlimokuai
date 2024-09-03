#include "chinesesort.h"

ChineseSort::ChineseSort(QStringList* list)
{
    if(list) {
        QCollator collator;
        collator.setLocale(QLocale::Chinese);
        std::sort(list->begin(), list->end(), [&collator](const QString& s1,
                  const QString& s2) {
            return collator.compare(s1, s2) < 0;
        });
    }
}
void ChineseSort::operator()(QStringList* list)
{
    QCollator collator;
    collator.setLocale(QLocale::Chinese);
    std::sort(list->begin(), list->end(), [&collator](const QString& s1,
              const QString& s2) {
        return collator.compare(s1, s2) < 0;
    });
}
