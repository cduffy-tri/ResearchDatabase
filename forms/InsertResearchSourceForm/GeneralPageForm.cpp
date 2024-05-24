#include "GeneralPageForm.h"
#include "ui_GeneralPageForm.h"

GeneralPageForm::GeneralPageForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeneralPageForm)
{
    ui->setupUi(this);
}

GeneralPageForm::~GeneralPageForm()
{
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
    return this->ui->abstractionTextEdit->toHtml();
}
