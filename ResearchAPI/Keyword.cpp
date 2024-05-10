#include "ResearchAPI/Keyword.h"
#include <QSqlQuery>
#include <QSqlRecord>

Keyword::Keyword()
{
    id = 0;
}

Keyword::Keyword(const unsigned int& id)
{
    this->id = id;
}

unsigned int Keyword::getKeywordIdByStr(const QString& keyword)
{
    QSqlQuery query;
    query.prepare("SELECT keyword_def_id FROM keyword_def WHERE keyword_def_str = :keyword_def_str;");
    query.bindValue(":keyword_def_str", keyword);
    query.exec();
    unsigned int keyword_def_id = 0;
    while(query.next())
    {
        keyword_def_id = query.record().value(0).toUInt();
    }
    return keyword_def_id;
}

unsigned int Keyword::getId() const
{
    return id;
}

void Keyword::setId(const unsigned int& id)
{
    this->id = id;
}

bool Keyword::isValid() const
{
    QSqlQuery query;
    query.prepare("SELECT keyword_def_id FROM keyword_def WHERE keyword_def_id = :keyword_def_id;");
    query.bindValue(":keyword_def_id", id);
    query.exec();
    bool isValid = false;
    while(query.next())
    {
        isValid = true;
    }
    return isValid;
}

QString Keyword::text() const
{
    QSqlQuery query;
    query.prepare("SELECT keyword_def_str FROM keyword_def WHERE keyword_def_id = :keyword_def_id;");
    query.bindValue(":keyword_def_id", id);
    query.exec();
    QString text = "";
    while(query.next())
    {
        text = query.record().value(0).toString();
    }
    return text;
}

QList<unsigned int> Keyword::getResearchIds()
{
    QSqlQuery query;
    query.prepare("SELECT research_id FROM keywords WHERE keyword_def_id = :keyword_def_id;");
    query.bindValue(":keyword_def_id", id);
    query.exec();
    QList<unsigned int> researchIds;
    while(query.next())
    {
        researchIds.append(query.record().value(0).toUInt());
    }
    return researchIds;
}
