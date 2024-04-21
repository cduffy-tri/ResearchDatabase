#include "researchdb.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include "filetools.h"
ResearchDB::ResearchDB(QWidget *parent)
    : QWidget{parent}
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("research.db");
    db.open();
    QSqlError error = db.lastError();
    if(error.isValid())
    {
        QMessageBox::warning(this, "DB Error", "Error: "+error.text());
    }
    else
    {
        qDebug() << "Connnected to database";
    }

    // create the research table
    QSqlQuery(FileTools::readFile(":/sql/createResearchTable.sql"));

    // create the files table
    QSqlQuery(FileTools::readFile(":/sql/createFilesTable.sql"));

    // create keyword definition table
    QSqlQuery(FileTools::readFile(":/sql/createKeywordDefinitionsTable.sql"));

    // create keywords table
    QSqlQuery(FileTools::readFile(":/sql/createKeywordsTable.sql"));
}

QSqlDatabase ResearchDB::getDB()
{
    return db;
}

bool ResearchDB::inesrtResearchItem(const ResearchItem& item)
{
    // make a query to the datbase and load it with the data.
    QString errorStr = item.isValid();

    if(errorStr.isEmpty())
    {
        // process the item into the research table
        QSqlQuery researchTableQuery;
        researchTableQuery.prepare(FileTools::readFile(":/sql/insertIntoResearchTable.sql"));
        researchTableQuery.bindValue(":title", item.title);
        researchTableQuery.bindValue(":author", item.author);
        researchTableQuery.bindValue("publication_date:", item.publicationDate);
        researchTableQuery.bindValue(":abstraction", item.abstraction);
        researchTableQuery.bindValue(":doi", item.doi);
        researchTableQuery.bindValue(":url", item.url);
        researchTableQuery.exec();

        QVariant researchId = researchTableQuery.record().field(0).value();
        qDebug() << researchId;

        // if there is any keywords then process them into the database
        if(!item.keywords.empty())
        {
            for(const QString& keyword : item.keywords)
            {
                // insert keyword def if not already created
                QSqlQuery keywordDefQuery;
                keywordDefQuery.prepare(FileTools::readFile(":/sql/insertKeywordDef.sql"));
                keywordDefQuery.bindValue(":keyword_def", keyword.toLower());
                keywordDefQuery.exec();

                QVariant keywordDefId = keywordDefQuery.record().field(0).value();

                // insert the keyword under the keywords table with the research ID.
                QSqlQuery keywordsQuery;
                keywordsQuery.prepare(FileTools::readFile(":/sql/insertIntoKeywordsTable.sql"));
                keywordsQuery.bindValue(":keyword_def_id", keywordDefId);
                keywordsQuery.bindValue(":research_id", researchId);
                keywordsQuery.exec();
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "Input Error", errorStr);
    }

    return (!errorStr.isEmpty());
}
