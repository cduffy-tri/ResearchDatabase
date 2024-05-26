#ifndef INSERTRESEARCHSOURCEFORM_H
#define INSERTRESEARCHSOURCEFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include "GeneralPageForm.h"
#include "KeywordsPageForm.h"

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

    QPushButton* getSubmitButton();

    QString submitSource();

private:
    Ui::InsertResearchSourceForm *ui;

    GeneralPageForm* generalPageForm = new GeneralPageForm();

    KeywordsPageForm* keywordsPageForm = new KeywordsPageForm();
};

#endif // INSERTRESEARCHSOURCEFORM_H
