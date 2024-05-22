#ifndef INSERTRESEARCHSOURCEFORM_H
#define INSERTRESEARCHSOURCEFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include "GeneralPageForm.h"

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

    bool isValid();

    QPushButton* getCancelButton();

private:
    Ui::InsertResearchSourceForm *ui;

    GeneralPageForm* generalPageForm = new GeneralPageForm(this);
};

#endif // INSERTRESEARCHSOURCEFORM_H
