#include "KeywordsPageForm.h"
#include "ui_KeywordsPageForm.h"
#include <QMessageBox>
#include <QListWidgetItem>
#include <QPushButton>

KeywordsPageForm::KeywordsPageForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::KeywordsPageForm)
{
    ui->setupUi(this);

    connect(this->ui->insertKeywordButton, &QPushButton::clicked, this, &KeywordsPageForm::insertKeyword);
    connect(this->ui->removeKeywordButton, &QPushButton::clicked, this, &KeywordsPageForm::removeKeyword);
}

KeywordsPageForm::~KeywordsPageForm()
{
    delete ui;
}

QString KeywordsPageForm::getEnteredKeyword()
{
    return this->ui->keywordLineEdit->text();
}

void KeywordsPageForm::insertKeyword()
{
    if(getEnteredKeyword().isEmpty())
        return;
    QString keyword = getEnteredKeyword().toLower();
    if(keywords.contains(keyword))
    {
        QMessageBox::warning(this, "Keyword Error", "Keyword Already Inserted");
        return;
    }

    this->ui->listWidget->addItem(keyword);
    keywords.insert(keyword);
}

void KeywordsPageForm::removeKeyword()
{
    keywords.remove(this->ui->listWidget->currentItem()->text());
    this->ui->listWidget->takeItem(this->ui->listWidget->currentRow());
}

QList<QString> KeywordsPageForm::getKeywords()
{
    QList<QString> list;
    for(const QString& keyword : this->keywords)
    {
        list.append(keyword);
    }
    return list;
}
