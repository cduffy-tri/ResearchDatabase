#ifndef GENERALPAGEFORM_H
#define GENERALPAGEFORM_H

#include <QWidget>
#include "../WordProcessorWidget.h"

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

    QString getDOI();

    QString getURL();

private:
    Ui::GeneralPageForm *ui;

    WordProcessorWidget* wordProcessorWidget = new WordProcessorWidget();
};

#endif // GENERALPAGEFORM_H
