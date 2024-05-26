#include "SelectKeywordsDialog.h"
#include "ui_SelectKeywordsDialog.h"


SelectKeywordsDialog::SelectKeywordsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SelectKeywordsDialog)
{
    ui->setupUi(this);

    this->ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QString queryString("SELECT keyword_def_str FROM keyword_def");
    keywordModel->setQuery(queryString);

    this->ui->listView->setModel(keywordModel);
}

SelectKeywordsDialog::~SelectKeywordsDialog()
{
    delete ui;
}

QItemSelectionModel* SelectKeywordsDialog::getSelectionModel()
{
    return this->ui->listView->selectionModel();
}
