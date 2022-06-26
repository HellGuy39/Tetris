#include "database/Database.h"

Database::Database()
{
    db = QSqlDatabase::addDatabase(DRIVER);
    db.setHostName(HOST_NAME);
    db.setDatabaseName(DATABASE_NAME);
    db.setUserName(USER_NAME);
    db.open();

    QString query = "CREATE TABLE player_scores"
                    "(id integer, score integer, level integer, lines integer);";

    QSqlQuery qry;

    qry.exec(query);
}

QSqlQueryModel* Database::getModel()
{
    QSqlQueryModel *qryModel = new QSqlQueryModel;

    qryModel->setQuery("SELECT * "
                       "FROM player_scores "
                       "ORDER BY score DESC "
                       "LIMIT 0, 10");

    qryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Score"));
    qryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Level"));
    qryModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Lines"));

    return qryModel;
}

void Database::insertScore(int id, int score, int level, int lines)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO player_scores"
                "(ID, Score, Level, Lines)"
                "VALUES(?, ?, ?, ?);");

    qry.addBindValue(id);
    qry.addBindValue(score);
    qry.addBindValue(level);
    qry.addBindValue(lines);

    qry.exec();
}

void Database::clearDatabase()
{
    QString query = "DELETE FROM player_scores";
    QSqlQuery qry;

    qry.exec(query);
}
