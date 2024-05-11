#include "FileID.h"
#include <QSqlQuery>
#include <QSqlRecord>

using namespace rsd;

FileID::FileID() {}

FileID::FileID(const unsigned int& id)
{
    this->id = id;
}

void FileID::setId(const unsigned int& id)
{
    this->id = id;
}

unsigned int FileID::getId() const
{
    return id;
}

bool FileID::isValid() const
{
    // check if the file in the files table is valid id
    QSqlQuery query;
    query.prepare("SELECT file_id FROM files WHERE file_id = :file_id;");
    query.bindValue(":file_id", id);
    query.exec();
    bool isValid = false;
    while(query.next())
    {
        isValid = true;
    }
    return isValid;
}

QString FileID::getName() const
{
    QSqlQuery query;
    query.prepare("SELECT file_name FROM files WHERE file_id = :file_id;");
    query.bindValue(":file_id", id);
    query.exec();
    QString fileName = "";
    while(query.next())
    {
        fileName = query.record().value(0).toString();
    }
    return fileName;
}

QByteArray FileID::getData() const
{
    QSqlQuery query;
    query.prepare("SELECT file_data FROM files WHERE file_id = :file_id;");
    query.bindValue(":file_id", id);
    query.exec();
    QByteArray data;
    while(query.next())
    {
        data = query.record().value(0).toByteArray();
    }
    return data;
}

unsigned int FileID::getResearchID() const
{
    QSqlQuery query;
    query.prepare("SELECT research_id FROM files WHERE file_id = :file_id;");
    query.bindValue(":file_id", id);
    query.exec();
    unsigned int researchId = 0;
    while(query.next())
    {
        researchId = query.record().value(0).toUInt();
    }
    return researchId;
}
