#ifndef FILETOOLS_H
#define FILETOOLS_H
#include <QString>
#include <QByteArray>
#include <QFile>

class FileTools
{
    FileTools();
public:
    static QString readFile(const QString& fileName);
    static QByteArray readData(const QString& fileName);
};

#endif // FILETOOLS_H
