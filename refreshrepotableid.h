#ifndef REFRESHREPOTABLEID_H
#define REFRESHREPOTABLEID_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>

class RefreshRepoTableID
{
public:
    explicit RefreshRepoTableID(QSqlDatabase *db = nullptr,
                                      QSqlQuery *query = nullptr);
    ~RefreshRepoTableID();
private:
    QSqlDatabase *db;
    QSqlQuery *query;
};

#endif // REFRESHREPOTABLEID_H
