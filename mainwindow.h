#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ResearchAPI/ResearchDB.h"

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

private:
    Ui::MainWindow *ui;
    rsd::ResearchDB* researchDB = nullptr;
};
#endif // MAINWINDOW_H
