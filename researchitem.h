#ifndef RESEARCHITEM_H
#define RESEARCHITEM_H
#include <QString>
#include <QStringList>
#include <QDate>


class ResearchItem
{
public:
    unsigned int id = 0;
    QString title = "";
    QString author = "";
    QDate publicationDate;
    QString abstraction = "";
    QStringList keywords;
    QString doi = "";
    QString url = "";

    //ResearchItem();

    ResearchItem(const unsigned int& id = 0,
                 const QString& title = "",
                 const QString& author = "",
                 const QDate& publicationDate = QDate::currentDate(),
                 const QString& abstraction = "",
                 const QStringList& keywords = QStringList(),
                 const QString& doi = "",
                 const QString& url = "");

    QString isValid() const;
};

#endif // RESEARCHITEM_H
