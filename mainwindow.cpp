#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "InsertResearchSourceForm.h"
#include "ResearchAPI/FileID.h"
#include "ResearchAPI/ResearchID.h"
#include "ResearchAPI/Keyword.h"
#include <QListView>
#include <QAbstractItemView>

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
    //QSqlQueryModel* model = new QSqlQueryModel(this);
    //rsd::Keyword(1).queryForResearch(model);

    //qDebug() << model->record();
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
MainWindow::~MainWindow()
{
    delete ui;
}
