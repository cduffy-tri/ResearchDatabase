#ifndef RESEARCHDB_H
#define RESEARCHDB_H

#include <QWidget>
#include <QSqlDatabase>
#include "researchitem.h"

class ResearchDB : public QWidget
{
    Q_OBJECT
public:
    explicit ResearchDB(QWidget *parent = nullptr);

    QSqlDatabase getDB();

signals:

public slots:
    bool inesrtResearchItem(const ResearchItem& item);

private:
    QSqlDatabase db;
};

#endif // RESEARCHDB_H
