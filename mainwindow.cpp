#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "researchitem.h"
#include "InsertResearchSourceForm.h"
#include "ResearchID.h"
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

    researchDB = new ResearchDB(this);

    InsertResearchSourceForm* insertResearchSourceForm = new InsertResearchSourceForm(this);
    this->setCentralWidget(insertResearchSourceForm);

    this->showMaximized();

    // connect signals to slots
    connect(this->ui->searchButton, &QPushButton::clicked, this, &MainWindow::search);
    //qDebug()<<ResearchID(1).getKeywords();
    //ResearchID newSource = ResearchID::generateNewSource("Aliens");


    //qDebug() << newSource.getTitle();
}

void MainWindow::search()
{
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

    // make a query for the title
    this->researchDB->searchByTitle(title);

    this->ui->listView->setModel(this->researchDB->getQueryModel());
}

void MainWindow::searchByKeyword()
{
    QString keyword = this->ui->searchLineEdit->text();
    this->researchDB->searchByKeyword(keyword);
    this->ui->listView->setModel(this->researchDB->getQueryModel());
}

MainWindow::~MainWindow()
{
    delete ui;
}
