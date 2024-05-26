#ifndef RESEARCHDB_H
#define RESEARCHDB_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQueryModel>

namespace rsd {
    class ResearchDB : public QObject
    {
        Q_OBJECT
    public:
        explicit ResearchDB(QObject *parent = nullptr);

        QSqlDatabase getDB();

        QVariant getKeywordDefId(const QString& keyword);

        QSqlQueryModel* getSearchModel();

        void searchByKeyword(const QString& keyword);

        void searchResearchByTitle(QString title);
    signals:

    private:
        QSqlDatabase db;

        QSqlQueryModel* searchModel = nullptr;
    };
}

#endif // RESEARCHDB_H
