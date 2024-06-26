#ifndef RESEARCHID_H
#define RESEARCHID_H
#include <QString>
#include <QDate>
#include <QSqlRecord>
#include <QList>
#include "FileID.h"

namespace rsd {
    class ResearchID
    {
        unsigned int id;
    public:
        ResearchID();
        ResearchID(const unsigned int& id);

        static ResearchID generateNewSource(const QString& sourceTitle);

        void setId(unsigned int newId);
        unsigned int getId() const;

        // get if the id is a valid database record
        bool isValid() const;

        // set title
        void setTitle(const QString& title);

        void setAuthor(const QString& author);

        void setPublicationDate(const QDate& publication_date);

        void setAbstraction(const QString& abstraction);

        void setDOI(const QString& doi);

        void setURL(const QString& url);

        void insertKeyword(const QString keyword);

        bool attachFile(const QString& fileName, const QByteArray& data);

        // get the title of the research reecord
        QString getTitle() const;

        // get the author of the research record
        QString getAuthor() const;

        QDate getPublicationDate() const;

        // get the summary/abstraction from the research id
        QString getAbstraction() const;

        // get doi
        QString getDOI() const;

        // get the url
        QString getURL() const;

        // get the keywords for this research source
        QStringList getKeywords() const;

        QList<unsigned int> getKeywordIds() const;

        QList<FileID> getFiles() const;

        void destroy();
    };
}


#endif // RESEARCHID_H
