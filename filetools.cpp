#include "filetools.h"

FileTools::FileTools() {}

QString FileTools::readFile(const QString& fileName)
{
    QFile file(fileName);
    QString content = "";
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(file.isOpen())
    {
        content = file.readAll();
        file.close();
    }
    return content;
}

QByteArray FileTools::readData(const QString& fileName)
{
    QFile file(fileName);
    QByteArray data;
    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
    {
        data = file.readAll();
        file.close();
    }
    return data;
}
