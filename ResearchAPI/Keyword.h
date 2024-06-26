#ifndef KEYWORD_H
#define KEYWORD_H
#include <QString>
#include <QList>
#include <QSqlQueryModel>

namespace rsd {
    class Keyword
    {
        unsigned int id = 0;
    public:
        Keyword();
        Keyword(const unsigned int& id);

        static unsigned int getKeywordIdByStr(const QString& keyword);

        unsigned int getId() const;

        void setId(const unsigned int& id);

        bool isValid() const;

        QString text() const;

        QList<unsigned int> getResearchIds();

        // delete the keyword
        void destroy();
    };
}

#endif // KEYWORD_H
