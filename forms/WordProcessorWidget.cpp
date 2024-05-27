#include "WordProcessorWidget.h"
#include "ui_WordProcessorWidget.h"
#include <QIcon>
#include <QFont>
#include <QPushButton>
#include <QSpinBox>
#include <QAbstractSpinBox>
#include <QFontComboBox>

WordProcessorWidget::WordProcessorWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WordProcessorWidget)
{
    ui->setupUi(this);

    this->ui->boldButton->setIcon(QIcon(":/icons/bold-icon.png"));
    this->ui->italicButton->setIcon(QIcon(":/icons/italic-icon.png"));
    this->ui->underlineButton->setIcon(QIcon(":/icons/underline-icon.png"));

    // setup the point size spin box
    QFont font = getTextEdit()->currentFont();
    font.setPointSize(this->ui->pointSizeSpinBox->value());

    getTextEdit()->setCurrentFont(font);

    updateFont();


    //connect signals to slots
    connect(this->ui->boldButton, &QPushButton::clicked, this, &WordProcessorWidget::toggleBold);
    connect(this->ui->italicButton, &QPushButton::clicked, this, &WordProcessorWidget::toggleItalic);
    connect(this->ui->underlineButton, &QPushButton::clicked, this, &WordProcessorWidget::toggleUnderline);
    connect(this->ui->pointSizeSpinBox, &QSpinBox::editingFinished, this, &WordProcessorWidget::updatePointSize);
    connect(this->ui->fontComboBox, &QFontComboBox::currentFontChanged, this, &WordProcessorWidget::updateFont);
}

WordProcessorWidget::~WordProcessorWidget()
{
    delete ui;
}

QTextEdit* WordProcessorWidget::getTextEdit()
{
    return this->ui->textEdit;
}

void WordProcessorWidget::toggleBold()
{
    QFont font = getTextEdit()->currentFont();
    if(font.bold())
        font.setBold(false);
    else
        font.setBold(true);

    getTextEdit()->setCurrentFont(font);
}

void WordProcessorWidget::toggleItalic()
{
    QFont font = getTextEdit()->currentFont();
    if(font.italic())
        getTextEdit()->setFontItalic(false);
    else
        getTextEdit()->setFontItalic(true);

    //getTextEdit()->setCurrentFont(font);
}

void WordProcessorWidget::toggleUnderline()
{
    if(getTextEdit()->fontUnderline())
        getTextEdit()->setFontUnderline(false);
    else
        getTextEdit()->setFontUnderline(true);
}

void WordProcessorWidget::updatePointSize()
{
    QFont font = getTextEdit()->currentFont();
    font.setPointSize(this->ui->pointSizeSpinBox->value());

    getTextEdit()->setCurrentFont(font);
}

void WordProcessorWidget::updateFont()
{
    QFont font = getTextEdit()->currentFont();
    font.setFamily(this->ui->fontComboBox->currentText());
    getTextEdit()->setCurrentFont(font);
}
