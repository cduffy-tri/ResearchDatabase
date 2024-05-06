#include "InsertResearchSourceForm.h"
#include "ui_InsertResearchSourceForm.h"
#include <QListWidget>

InsertResearchSourceForm::InsertResearchSourceForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InsertResearchSourceForm)
{
    ui->setupUi(this);

    // setup all of the options items in the listWidget
    this->ui->listWidget->addItem("General");

    // connect signals to slots
    connect(this->ui->listWidget, &QListWidget::itemClicked, this, &InsertResearchSourceForm::switchOptionMenu);

    // set the general page as the first displaying page when this widget is first loaded.
    this->ui->listWidget->setCurrentItem(this->ui->listWidget->item(0));
    switchOptionMenu(this->ui->listWidget->item(0));
}

InsertResearchSourceForm::~InsertResearchSourceForm()
{
    delete ui;
}

void InsertResearchSourceForm::switchOptionMenu(QListWidgetItem* item)
{
    if(item->text() == "General")
    {
        // switch to the General Widget
        qDebug() << "Switching to General page";
    }
}
