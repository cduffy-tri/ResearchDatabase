#include "ResearchID.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

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

void ResearchID::setAuthor(const QString& author)
{
    QString queryString = "UPDATE research SET author = :author WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":author", author);
    query.bindValue(":research_id", id);
    query.exec();
}

void ResearchID::setPublicationDate(const QDate& publication_date)
{
    QString queryString = "UPDATE research SET publication_date = :publication_date WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":publication_date", publication_date);
    query.bindValue(":research_id", id);
    query.exec();
}

void ResearchID::setAbstraction(const QString& abstraction)
{
    QString queryString = "UPDATE research SET abstraction = :abstraction WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":abstraction", abstraction);
    query.bindValue(":research_id", id);
    query.exec();
}

void ResearchID::setDOI(const QString& doi)
{
    QString queryString = "UPDATE research SET doi = :doi WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":doi", doi);
    query.bindValue(":research_id", id);
    query.exec();
}

void ResearchID::setURL(const QString& url)
{
    QString queryString = "UPDATE research SET url = :url WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":url", url);
    query.bindValue(":research_id", id);
    query.exec();
}

/*void ResearchID::insertKeyword(const QString keyword)
{
    // generate the keyword_def record if not already created
    QString keywordStr = keyword.toLower(); // prevent upper case from being stored
    QString queryString = "INSERT INTO keyword_def (keyword_def_str) VALUES(:keyword)";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":keyword", keywordStr);
    query.exec();

    QVariant lastKeywordID = query.lastInsertId();
    if(lastKeywordID.isValid())
    {
        // insert the new keyword_def_id into the keywords table with the research_id
        QSqlQuery query;
        query.prepare("INSERT INTO keywords (keyword_def_id, research_id) VALUES(:keyword_def_id, :research_id);");
        query.bindValue(":keyword_def_id", lastKeywordID);
        query.bindValue(":research_id", id);
        query.exec();
    }
    else
    {
        // create the new keyword_def record
        QSqlQuery query;
        query.prepare("INSERT INTO keyword_def (keyword_def_str) :keyword_def_str;");
        query.bindValue(":keyword_def_str", keywordStr);
        query.exec();

        QVariant lastKeywordID = query.lastInsertId();
        // insert the keyword into the keywords table
        if(lastKeywordID.isValid())
        {
            QSqlQuery keywordsQuery;
            keywordsQuery.prepare("INSERT INTO keywords (keyword_def_id, research_id) VALUES(:keyword_def_id, :research_id);");
            keywordsQuery.bindValue(":keyword_def_id", lastKeywordID);
            keywordsQuery.bindValue(":research_id", id);
            keywordsQuery.exec();
        }
    }
}*/

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

QDate ResearchID::getPublicationDate() const
{
    QString queryString = "SELECT publication_date FROM research WHERE research_id = :research_id;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":research_id", id);
    query.exec();
    QDate publicationDate;
    while(query.next())
    {
        publicationDate = query.record().value(0).toDate();
    }
    return publicationDate;
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
