#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "researchitem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("Research Database");

    researchDB = new ResearchDB(this);

    ResearchItem item;
    item.title = "Test";
    item.keywords.append("Aliens");
    item.keywords.append("Space");


    researchDB->inesrtResearchItem(item);
}

MainWindow::~MainWindow()
{
    delete ui;
}
