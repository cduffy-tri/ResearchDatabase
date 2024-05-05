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


    queryModel = new QSqlQueryModel(this);
}

QSqlDatabase ResearchDB::getDB()
{
    return db;
}

QVariant ResearchDB::getKeywordDefId(const QString& keyword)
{
    // query for the id of the keyword_def_id
    QString qText = QString("SELECT keyword_def_id FROM keyword_def WHERE keyword_def_str='%1'").arg(keyword)+";";
    //qDebug() << qText;
    qDebug() << qText;
    QSqlQuery queryForKeywordID;
    queryForKeywordID.prepare(qText);
    queryForKeywordID.exec();
    QSqlError error = queryForKeywordID.lastError();
    if(error.isValid())
    {
        qDebug() << error.text();
    }

    QVariant keyword_def_id;
    while (queryForKeywordID.next())
    {
        keyword_def_id = queryForKeywordID.record().field(0).value();
    }
    return keyword_def_id;
}

bool ResearchDB::insertResearchItem(const ResearchItem& item)
{
    // make a query to the datbase and load it with the data.
    QString errorStr = item.isValid();

    if(errorStr.isEmpty())
    {
        QSqlQuery researchTableQuery;
        researchTableQuery.prepare(FileTools::readFile(":/sql/insertIntoResearchTable.sql"));
        researchTableQuery.bindValue(":title", item.title);
        researchTableQuery.bindValue(":author", item.author);
        researchTableQuery.bindValue("publication_date:", item.publicationDate);
        researchTableQuery.bindValue(":abstraction", item.abstraction);
        researchTableQuery.bindValue(":doi", item.doi);
        researchTableQuery.bindValue(":url", item.url);
        researchTableQuery.exec();

        QVariant researchId = researchTableQuery.lastInsertId();
        //qDebug() << researchId;

        // if there is any keywords then process them into the database
        if(!item.getKeywords().empty())
        {
            for(const QString& keyword : item.getKeywords())
            {
                // insert keyword def if not already created
                QSqlQuery keywordDefQuery;
                keywordDefQuery.prepare(FileTools::readFile(":/sql/insertKeywordDef.sql"));
                keywordDefQuery.bindValue(":keyword_def_str", keyword.toLower());
                keywordDefQuery.exec();
                QVariant keywordDefId = keywordDefQuery.lastInsertId();
                //qDebug() << keywordDefId;

                if(keywordDefId.isValid())
                {
                    // insert the keyword under the keywords table with the research ID.
                    QSqlQuery keywordsQuery;
                    keywordsQuery.prepare(FileTools::readFile(":/sql/insertIntoKeywordsTable.sql"));
                    keywordsQuery.bindValue(":keyword_def_id", keywordDefId);
                    keywordsQuery.bindValue(":research_id", researchId);
                    keywordsQuery.exec();
                }
                else
                {
                    //qDebug() << keyword_def_id;
                    QVariant keyword_def_id = getKeywordDefId(keyword);
                    qDebug() << keyword_def_id;

                    if(keyword_def_id.isValid())
                    {
                        // insert the keyword under the keywords table with the current research ID
                        QSqlQuery keywordsQuery;
                        keywordsQuery.prepare(FileTools::readFile(":/sql/insertIntoKeywordsTable.sql"));
                        keywordsQuery.bindValue(":keyword_def_id", keyword_def_id);
                        keywordsQuery.bindValue(":research_id", researchId);
                        keywordsQuery.exec();
                    }
                }
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "Input Error", errorStr);
    }

    return (!errorStr.isEmpty());
}

QSqlQueryModel* ResearchDB::getQueryModel()
{
    return queryModel;
}

void ResearchDB::searchByTitle(const QString& title)
{
    // set the query to the database using the qSqlQueryModel
    QString queryText = QString(FileTools::readFile(":/sql/search/searchByTitle.sql"));
    queryModel->setQuery(queryText.arg(title));
}
