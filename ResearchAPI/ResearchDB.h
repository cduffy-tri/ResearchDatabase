#ifndef RESEARCHDB_H
#define RESEARCHDB_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQueryModel>

class ResearchDB : public QWidget
{
    Q_OBJECT
public:
    explicit ResearchDB(QWidget *parent = nullptr);

    QSqlDatabase getDB();

    QVariant getKeywordDefId(const QString& keyword);

    QSqlQueryModel* getQueryModel();

    void searchByTitle(const QString& title);

    void searchByKeyword(const QString& keyword);
signals:

private:
    QSqlDatabase db;

    QSqlQueryModel* queryModel = nullptr;
};

#endif // RESEARCHDB_H
