#include "ResearchID.h"
#include <QSqlQuery>
#include <QSqlRecord>

ResearchID::ResearchID()
{
    id = 0;
}

ResearchID::ResearchID(const unsigned int& id)
{
    this->id = id;
}

ResearchID ResearchID::generateNewSource(const QString& sourceTitle)
{
    // generate a new research ID record
    ResearchID researchItem;

    // generate record
    QString queryString = "INSERT INTO research title VALUES(:title);";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":title", sourceTitle);
    query.exec();
    researchItem.setId(query.lastInsertId().toUInt());
    return researchItem;
}

void ResearchID::setId(unsigned int newId)
{
    id = newId;
}

unsigned int ResearchID::getId() const
{
    return id;
}

// get if the id is a valid database record
bool ResearchID::isValid() const
{
    QString queryString = "SELECT * FROM research WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":research_id", id);
    query.exec();
    bool isValid = false;
    while(query.next())
    {
        isValid = true;
    }
    return isValid;
}

// set title
void ResearchID::setTitle(const QString& title)
{
    QString queryString = "UPDATE research SET title = :title WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":title", title);
    query.bindValue(":research_id", id);
    query.exec();
}

// get the title of the research reecord
QString ResearchID::getTitle() const
{
    QString queryString = "SELECT title FROM research WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":research_id", id);
    query.exec();
    QString title = "";
    while(query.next())
    {
        title = query.record().value(0).toString();
    }
    return title;
}

// get the author of the research record
QString ResearchID::getAuthor() const
{
    QString queryString = "SELECT author FROM research WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":research_id", id);
    query.exec();
    QString author = "";
    while(query.next())
    {
        author = query.record().value(0).toString();
    }
    return author;
}

// get doi
QString ResearchID::getDOI() const
{
    QString queryString = "SELECT doi FROM research WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":research_id", id);
    QString doi = "";
    while(query.next())
    {
        doi = query.record().value(0).toString();
    }
    return doi;
}

// get the url
QString ResearchID::getURL() const
{
    QString queryString = "SELECT url FROM research WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":research_id", id);
    QString url = "";
    while(query.next())
    {
        url = query.record().value(0).toString();
    }
    return url;
}

// get the keywords for this research source
QStringList ResearchID::getKeywords() const
{
    QString queryString = "SELECT keyword_def_str FROM keyword_def "
                          "INNER JOIN keywords ON keywords.keyword_def_id = keyword_def.keyword_def_id "
                          "WHERE keywords.research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":research_id", id);
    query.exec();
    QStringList keywords;
    while(query.next())
    {
        keywords.append(query.record().value(0).toString());
    }
    return keywords;
}

// get the summary/abstraction from the research id
QString ResearchID::getAbstraction() const
{
    QString queryString = "SELECT abstraction FROM research WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":research_id", id);
    query.exec();
    QString abstraction = "";
    while(query.next())
    {
        abstraction = query.record().value(0).toString();
    }
    return abstraction;
}

// get a list of the file names of that are attached to the source
QStringList ResearchID::getAttachedFileNames() const
{
    QString queryString = "SELECT file_name FROM files WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":research_id", id);
    query.exec();
    QStringList fileNames;
    while(query.next())
    {
        fileNames.append(query.record().value(0).toString());
    }
    return fileNames;
}

// get the data of a file by file name
QByteArray ResearchID::getFileData(const QString& fileName)
{
    QString queryString = "SELECT file_data FROM files WHERE research_id = :research_id AND file_name = :file_name;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":research_id", id);
    query.bindValue(":file_name", fileName);
    query.exec();
    QByteArray data;
    while(query.next())
    {
        data = query.record().value(0).toByteArray();
    }
    return data;
}
