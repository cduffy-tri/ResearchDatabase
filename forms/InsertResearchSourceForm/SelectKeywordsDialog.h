#ifndef SELECTKEYWORDSDIALOG_H
#define SELECTKEYWORDSDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QItemSelectionModel>

namespace Ui {
class SelectKeywordsDialog;
}

class SelectKeywordsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectKeywordsDialog(QWidget *parent = nullptr);
    ~SelectKeywordsDialog();

    QItemSelectionModel* getSelectionModel();

    QSqlQueryModel* keywordModel = new QSqlQueryModel(this);

private:
    Ui::SelectKeywordsDialog *ui;
};

#endif // SELECTKEYWORDSDIALOG_H
