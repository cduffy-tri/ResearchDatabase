#ifndef RESEARCHID_H
#define RESEARCHID_H
#include <QString>
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

    // get the title of the research reecord
    QString getTitle() const;

    // get the author of the research record
    QString getAuthor() const;

    // get the summary/abstraction from the research id
    QString getAbstraction() const;

    // get doi
    QString getDOI() const;

    // get the url
    QString getURL() const;

    // get the keywords for this research source
    QStringList getKeywords() const;

    // get a list of the file names of that are attached to the source
    QStringList getAttachedFileNames() const;

    // get the data of a file by file name
    QByteArray getFileData(const QString& fileName);
};

#endif // RESEARCHID_H
