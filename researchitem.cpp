#include "researchitem.h"

//ResearchItem::ResearchItem() {}


ResearchItem::ResearchItem(const unsigned int& id,
             const QString& title,
             const QString& author,
             const QDate& publicationDate,
             const QString& abstraction,
             const QStringList& keywords,
             const QString& doi,
             const QString& url)
{
    this->id = id;
    this->title = title;
    this->author = author;
    this->publicationDate = publicationDate;
    this->abstraction = abstraction;
    this->keywords = keywords;
    this->doi = doi;
    this->url = url;
}

QString ResearchItem::isValid() const
{
    // check if the title is empty
    if(title.isEmpty())
    {
        return "You must enter a title";
    }

    return "";
}
