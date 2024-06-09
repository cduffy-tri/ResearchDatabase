#include "CustomLineEdit.h"

CustomLineEdit::CustomLineEdit(QWidget* parent) : QLineEdit(parent)
{

}

void CustomLineEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit doubleClicked();
    QLineEdit::mouseDoubleClickEvent(event);

    if(this->isReadOnly())
    {
        this->setReadOnly(false);
    }
}

void CustomLineEdit::focusOutEvent(QFocusEvent* event)
{
    emit lostFocus();
    QLineEdit::focusOutEvent(event);

    if(!this->isReadOnly())
    {
        this->setReadOnly(true);
    }
}
