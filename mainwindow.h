#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ResearchAPI/ResearchDB.h"
#include "forms/InsertResearchSourceForm/InsertResearchSourceForm.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void search();

    void searchByTitle();

    void searchByKeyword();

    void researchRecordSelected();

    void loadInsertResearchSourceForm();

    void removeInsertResearchSourceForm();

    void submitSource();

private:
    Ui::MainWindow *ui;
    rsd::ResearchDB* researchDB = nullptr;

    InsertResearchSourceForm* insertForm = nullptr;
};
#endif // MAINWINDOW_H
