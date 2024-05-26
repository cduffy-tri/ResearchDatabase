#include "ResearchAPI/ResearchDB.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include "filetools.h"
using namespace rsd;

ResearchDB::ResearchDB(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("research.db");
    db.open();
    QSqlError error = db.lastError();
    if(error.isValid())
    {
        //QMessageBox::warning(this, "DB Error", "Error: "+error.text());
    }
    else
    {
        //qDebug() << "Connnected to database";
    }

    // create the research table
    QSqlQuery(FileTools::readFile(":/sql/createResearchTable.sql"));

    // create the files table
    QSqlQuery(FileTools::readFile(":/sql/createFilesTable.sql"));

    // create keyword definition table
    QSqlQuery(FileTools::readFile(":/sql/createKeywordDefinitionsTable.sql"));

    // create keywords table
    QSqlQuery(FileTools::readFile(":/sql/createKeywordsTable.sql"));


    searchModel = new QSqlQueryModel(this);
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

QSqlQueryModel* ResearchDB::getSearchModel()
{
    return searchModel;
}

void ResearchDB::searchByKeyword(const QString& keyword)
{
    // use the keyword to make a sqlquery on the query model
    QString queryText = QString(FileTools::readFile(":/sql/search/searchByKeyword.sql")).arg(keyword);
    this->searchModel->setQuery(queryText);
}

void ResearchDB::searchResearchByTitle(QString title)
{
    QString queryText = "SELECT title, research_id FROM research "
                        "WHERE title LIKE '%%1%'";
    queryText = queryText.arg(title);
    searchModel->setHeaderData(0, Qt::Horizontal, tr("Title"));
    searchModel->setQuery(queryText);
}
