#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlTableModel>

class Database: public QObject
{
        Q_OBJECT
    public:
        Database();
        ~Database() { db.close(); }
        void insertScore(int id, int score, int level, int lines);
        void clearDatabase();
        QSqlQueryModel* getModel();


    private:
        QSqlDatabase db;
        const QString DRIVER = "QSQLITE";
        const QString HOST_NAME = "host";
        const QString DATABASE_NAME = "score_table.sqlite";
        const QString USER_NAME = "player";

};

#endif // DATABASE_H
