#ifndef RESEARCHDB_H
#define RESEARCHDB_H

#include <QWidget>
#include <QSqlDatabase>
#include "researchitem.h"
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
signals:

public slots:
    bool insertResearchItem(const ResearchItem& item);

private:
    QSqlDatabase db;

    QSqlQueryModel* queryModel = nullptr;
};

#endif // RESEARCHDB_H
