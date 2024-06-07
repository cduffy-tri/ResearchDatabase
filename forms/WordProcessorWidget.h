#ifndef WORDPROCESSORWIDGET_H
#define WORDPROCESSORWIDGET_H

#include <QWidget>
#include <QTextEdit>

namespace Ui {
class WordProcessorWidget;
}

class WordProcessorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WordProcessorWidget(QWidget *parent = nullptr);
    ~WordProcessorWidget();

    QTextEdit* getTextEdit();

public slots:
    void toggleBold();

    void toggleItalic();

    void toggleUnderline();

    void updatePointSize();

    void updateUiBoxes();

    void updateFont();

private:
    Ui::WordProcessorWidget *ui;
};

#endif // WORDPROCESSORWIDGET_H
