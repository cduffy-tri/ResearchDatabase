#ifndef FILEID_H
#define FILEID_H
#include <QString>

namespace rsd {
    class FileID
    {
        unsigned int id = 0;
    public:
        FileID();
        FileID(const unsigned int& id);

        void setId(const unsigned int& id);

        unsigned int getId() const;

        bool isValid() const;

        QString getName() const;

        QByteArray getData() const;

        unsigned int getResearchID() const;
    };
}

#endif // FILEID_H
