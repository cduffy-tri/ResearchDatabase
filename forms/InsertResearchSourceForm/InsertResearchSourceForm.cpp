#include "InsertResearchSourceForm.h"
#include "ui_InsertResearchSourceForm.h"
#include <QListWidget>
#include "ResearchAPI/ResearchID.h"

#include "mainwindow.h"

InsertResearchSourceForm::InsertResearchSourceForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InsertResearchSourceForm)
{
    ui->setupUi(this);

    // setup all of the options items in the listWidget
    this->ui->listWidget->addItem("General");

    // connect signals to slots
    connect(this->ui->listWidget, &QListWidget::itemClicked, this, &InsertResearchSourceForm::switchOptionMenu);
    //connect(this->ui->submitSourceButton, &QPushButton::clicked, this->parent(), &MainWindow::submitSource);

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

        // move stack widget to general page widget
        this->ui->mainStackedWidget->setCurrentIndex(this->ui->mainStackedWidget->addWidget(this->generalPageForm));
    }
}

bool InsertResearchSourceForm::isValid()
{
    if(this->generalPageForm->getTitle().isEmpty())
        return false;
    return true;
}

QString InsertResearchSourceForm::submitSource()
{
    QString error = "";

    if(this->generalPageForm->getTitle().isEmpty())
        error = "You must give the source a title";

    if(error.isEmpty())
    {
        // submit source
        rsd::ResearchID source = rsd::ResearchID::generateNewSource(this->generalPageForm->getTitle());
    }
    return error;
}

QPushButton* InsertResearchSourceForm::getCancelButton()
{

    return this->ui->cancelButton;
}

QPushButton* InsertResearchSourceForm::getSubmitButton()
{
    return this->ui->submitSourceButton;
}
