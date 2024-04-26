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

    QVariant getKeywordDefId(const QString& keyword);

signals:

public slots:
    bool insertResearchItem(const ResearchItem& item);

private:
    QSqlDatabase db;
};

#endif // RESEARCHDB_H
