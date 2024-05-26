#ifndef GENERALPAGEFORM_H
#define GENERALPAGEFORM_H

#include <QWidget>

namespace Ui {
class GeneralPageForm;
}

class GeneralPageForm : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralPageForm(QWidget *parent = nullptr);
    ~GeneralPageForm();

    QString getTitle();

    QString getAuthor();

    QDate getPublicationDate();

    QString getAbstraction();

private:
    Ui::GeneralPageForm *ui;


};

#endif // GENERALPAGEFORM_H