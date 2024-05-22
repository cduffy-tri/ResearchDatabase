#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "forms/InsertResearchSourceForm/InsertResearchSourceForm.h"
#include "ResearchAPI/FileID.h"
#include "ResearchAPI/ResearchID.h"
#include "ResearchAPI/Keyword.h"
#include <QListView>
#include <QAbstractItemView>
#include "filetools.h"
#include <QPushButton>
#include <QList>

//#include "filetools.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("Research Database");

    this->ui->searchByComboBox->insertItem(0, "Title");
    this->ui->searchByComboBox->insertItem(1, "Keyword");

    QFont font = this->font();
    font.setPointSize(15);
    this->setFont(font);

    researchDB = new rsd::ResearchDB(this);

    //InsertResearchSourceForm* insertResearchSourceForm = new InsertResearchSourceForm(this);
    //this->setCentralWidget(insertResearchSourceForm);

    this->showMaximized();

    // connect signals to slots
    connect(this->ui->searchButton, &QPushButton::clicked, this, &MainWindow::search);
    connect(this->ui->listView, &QAbstractItemView::clicked, this, &MainWindow::researchRecordSelected);
    connect(this->ui->actionInsert_New_Source, &QAction::triggered, this, &MainWindow::loadInsertResearchSourceForm);
}

void MainWindow::search()
{
    if(this->ui->searchLineEdit->text().isEmpty())
        return;
    if(this->ui->searchByComboBox->currentText() == "Title")
    {
        searchByTitle();
    }
    else if(this->ui->searchByComboBox->currentText() == "Keyword")
    {
        searchByKeyword();
    }
}

void MainWindow::searchByTitle()
{
    // capture what is entered into the search bar
    QString title = this->ui->searchLineEdit->text();

    this->researchDB->searchResearchByTitle(title);

    this->ui->listView->setModel(this->researchDB->getSearchModel());
}

void MainWindow::searchByKeyword()
{
    QString keyword = this->ui->searchLineEdit->text();
    this->researchDB->searchByKeyword(keyword);
    this->ui->listView->setModel(this->researchDB->getSearchModel());
}

void MainWindow::researchRecordSelected()
{
    rsd::ResearchID source(this->researchDB->getSearchModel()->record(this->ui->listView->currentIndex().row()).value(1).toUInt());
    qDebug() << source.getKeywords();
}

void MainWindow::loadInsertResearchSourceForm()
{
    if(!insertForm)
    {
        // create a InsertResearchSourceForm widget object
        insertForm = new InsertResearchSourceForm();
        QPushButton* button = insertForm->getCancelButton();
        connect(button, &QPushButton::clicked, this, &MainWindow::removeInsertResearchSourceForm);

        // attach this widget to a full screen view on the screen
        //this->ui->mainStackedWidget->insertWidget(0, insertForm);
        this->ui->mainStackedWidget->setCurrentIndex(this->ui->mainStackedWidget->addWidget(insertForm));
    }
}

void MainWindow::removeInsertResearchSourceForm()
{
    //delete and detach this menu from view if the insertSourceForm Validates Correctly
    if(insertForm->isValid())
    {
        this->ui->mainStackedWidget->setCurrentIndex(0);
        this->ui->mainStackedWidget->removeWidget(insertForm);
        delete insertForm;
        insertForm = nullptr;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
