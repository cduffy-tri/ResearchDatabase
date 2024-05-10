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
    QString queryString = "INSERT INTO research (title) VALUES(:title);";
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

void ResearchID::insertKeyword(const QString keyword)
{
    // if the research_id is not valid then don't insert the keyword
    if(!this->isValid())
        return;

    // generate the keyword_def record if not already created
    QString keywordStr = keyword.toLower(); // prevent upper case from being stored
    QString queryString = "INSERT INTO keyword_def (keyword_def_str) VALUES(:keyword_def_str)";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":keyword_def_str", keywordStr);
    query.exec();

    QVariant lastKeywordID = query.lastInsertId();

    if(lastKeywordID.isValid())
    {
        // keyword fresh inserted

        // insert the new keyword_def_id into the keywords table with the research_id

        // check if the keyword_def_id is already in the table with the current research_id
        QSqlQuery checkQuery;
        QString checkQueryString = "SELECT * FROM keywords WHERE keyword_def_id = :keyword_def_id AND "
                                   "research_id = :research_id;";
        checkQuery.prepare(checkQueryString);
        checkQuery.bindValue(":keyword_def_id", lastKeywordID);
        checkQuery.bindValue(":research_id:", id);
        checkQuery.exec();
        bool alreadyInserted = false;
        while(checkQuery.next())
        {
            alreadyInserted = true;
        }

        if(!alreadyInserted)
        {
            QSqlQuery query;
            query.prepare("INSERT INTO keywords (keyword_def_id, research_id) VALUES(:keyword_def_id, :research_id);");
            query.bindValue(":keyword_def_id", lastKeywordID);
            query.bindValue(":research_id", id);
            query.exec();
        }
    }
    else
    {
        // keyword already exists
        /*QSqlQuery query;
        query.prepare("INSERT INTO keyword_def (keyword_def_str) :keyword_def_str;");
        query.bindValue(":keyword_def_str", keywordStr);
        query.exec();*/
        // insert the keyword into the keywords table

        // get the existing keyword id
        QSqlQuery existingKeywordQuery;
        existingKeywordQuery.prepare("SELECT keyword_def_id FROM keyword_def WHERE keyword_def_str = :keyword_def_str;");
        existingKeywordQuery.bindValue(":keyword_def_str", keywordStr);
        existingKeywordQuery.exec();
        QVariant existingKeywordDefID;
        while(existingKeywordQuery.next())
        {
            existingKeywordDefID = existingKeywordQuery.record().value(0);
        }

        //qDebug() << existingKeywordDefID;

        // check if the keyword is already inserted with the current research_id
        QSqlQuery checkQuery;
        QString checkQueryString = "SELECT * FROM keywords WHERE keyword_def_id = :keyword_def_id AND "
                                   "research_id = :research_id;";
        checkQuery.prepare(checkQueryString);
        checkQuery.bindValue(":keyword_def_id", existingKeywordDefID);
        checkQuery.bindValue(":research_id", id);
        checkQuery.exec();
        bool alreadyInserted = false;
        while(checkQuery.next())
        {
            alreadyInserted = true;
        }

        if(!alreadyInserted)
        {
            QSqlQuery keywordsQuery;
            keywordsQuery.prepare("INSERT INTO keywords (keyword_def_id, research_id) VALUES(:keyword_def_id, :research_id);");
            keywordsQuery.bindValue(":keyword_def_id", existingKeywordDefID);
            keywordsQuery.bindValue(":research_id", id);
            keywordsQuery.exec();
            qDebug() << keywordsQuery.lastInsertId();
        }
    }
}

bool ResearchID::attachFile(const QString& fileName, const QByteArray& data)
{
    // check if the id is valid
    if(!this->isValid())
        return false;

    // generate the new file record and tie it back to the research_id
    QSqlQuery generateFileQuery;
    generateFileQuery.prepare("INSERT INTO files (research_id, file_name, file_data) VALUES(:research_id, :file_name, :file_data);");
    generateFileQuery.bindValue(":research_id", id);
    generateFileQuery.bindValue(":file_name", fileName);
    generateFileQuery.bindValue(":file_data", data);
    generateFileQuery.exec();
    return true;
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

QList<FileID> ResearchID::getFiles() const
{
    // find all of the files that are acociated with this research source
    QSqlQuery fileQuery;
    fileQuery.prepare("SELECT file_id FROM files WHERE research_id = :research_id;");
    fileQuery.bindValue(":research_id", id);
    fileQuery.exec();
    QList<FileID> fileList;
    while(fileQuery.next())
    {
        fileList.append(FileID(fileQuery.record().value(0).toUInt()));
    }
    return fileList;
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
