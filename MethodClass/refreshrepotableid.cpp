#include "refreshrepotableid.h"

RefreshRepoTableID::RefreshRepoTableID(QSqlDatabase *db, QSqlQuery *query)
    :db(db),
     query(query)
{
    query->exec("CREATE TABLE IF NOT EXISTS 临时库存表 ( \
               库存编号 INTEGER PRIMARY KEY AUTOINCREMENT, \
               库存类别 TEXT NOT NULL, \
               库存名称 TEXT NOT NULL, \
               存放位置 TEXT NOT NULL, \
               存放数量 INTEGER NOT NULL \
               );");
    query->exec("INSERT INTO 临时库存表 \
        (库存类别, 库存名称, 存放位置, 存放数量) \
            SELECT 库存类别, 库存名称, 存放位置, 存放数量 \
                FROM 库存表 ORDER BY 存放位置 DESC, 库存类别 DESC, 库存名称 DESC");
    query->exec("DROP TABLE 库存表;");
    query->exec("ALTER TABLE 临时库存表 RENAME TO 库存表;");
}
RefreshRepoTableID::~RefreshRepoTableID() {}
