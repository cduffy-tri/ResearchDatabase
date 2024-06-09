#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QWidget>

class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit CustomLineEdit(QWidget* parent = nullptr);

signals:
    void doubleClicked();

    void lostFocus();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void focusOutEvent(QFocusEvent* event) override;
};

#endif // CUSTOMLINEEDIT_H
