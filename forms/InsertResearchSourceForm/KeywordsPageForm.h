#ifndef KEYWORDSPAGEFORM_H
#define KEYWORDSPAGEFORM_H

#include <QWidget>
#include <QSet>
#include <QList>

namespace Ui {
class KeywordsPageForm;
}

class KeywordsPageForm : public QWidget
{
    Q_OBJECT

public:
    explicit KeywordsPageForm(QWidget *parent = nullptr);
    ~KeywordsPageForm();

public slots:
    void insertKeyword();

    void removeKeyword();

    QList<QString> getKeywords();

private:
    Ui::KeywordsPageForm *ui;

    QSet<QString> keywords;

    QString getEnteredKeyword();
};

#endif // KEYWORDSPAGEFORM_H
