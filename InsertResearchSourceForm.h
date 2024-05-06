#ifndef INSERTRESEARCHSOURCEFORM_H
#define INSERTRESEARCHSOURCEFORM_H

#include <QWidget>
#include <QListWidgetItem>
namespace Ui {
class InsertResearchSourceForm;
}

class InsertResearchSourceForm : public QWidget
{
    Q_OBJECT

public:
    explicit InsertResearchSourceForm(QWidget *parent = nullptr);
    ~InsertResearchSourceForm();

public slots:
    // switchOptionMenu
    void switchOptionMenu(QListWidgetItem* item);

private:
    Ui::InsertResearchSourceForm *ui;
};

#endif // INSERTRESEARCHSOURCEFORM_H
