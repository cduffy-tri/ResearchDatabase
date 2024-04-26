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
    item.title = "Test2";
    item.insertKeyword("Testing Keywords");
    item.insertKeyword("Aliens");

    researchDB->insertResearchItem(item);
}

MainWindow::~MainWindow()
{
    delete ui;
}
