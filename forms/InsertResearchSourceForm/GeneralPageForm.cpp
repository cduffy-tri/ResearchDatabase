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
