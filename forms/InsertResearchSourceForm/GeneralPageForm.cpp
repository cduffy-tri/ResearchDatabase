#include "GeneralPageForm.h"
#include "ui_GeneralPageForm.h"
#include <QHBoxLayout>

GeneralPageForm::GeneralPageForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeneralPageForm)
{
    ui->setupUi(this);

    QHBoxLayout* layout = new QHBoxLayout(this->ui->abstractionGroupBox);
    wordProcessorWidget->setParent(this->ui->abstractionGroupBox);

    layout->addWidget(wordProcessorWidget);
}

GeneralPageForm::~GeneralPageForm()
{
    delete wordProcessorWidget;
    delete ui;
}

QString GeneralPageForm::getTitle()
{
    return this->ui->titleLineEdit->text();
}

QString GeneralPageForm::getAuthor()
{
    return this->ui->authorLineEdit->text();
}

QDate GeneralPageForm::getPublicationDate()
{
    return this->ui->publicationDateEdit->date();
}

QString GeneralPageForm::getAbstraction()
{
    return this->wordProcessorWidget->getTextEdit()->toHtml();
}

QString GeneralPageForm::getDOI()
{
    return this->ui->doiLineEdit->text();
}

QString GeneralPageForm::getURL()
{
    return this->ui->urlLineEdit->text();
}
