#include "ptextedit.h"
#include <QDebug>

PTextEdit::PTextEdit()
{

}

PTextEdit::PTextEdit(QWidget *parent) : QTextEdit(parent)
{

}

PTextEdit::~PTextEdit()
{

}

void PTextEdit::setDocument(PTreeTextItem *item)
{
    QTextEdit::setDocument(item->getDocument());
    currentItem = item;
    documentLabel->setText(item->text(0));
}

void PTextEdit::setTextBold(bool b)
{
    if (b)  setFontWeight(QFont::Bold);
    else    setFontWeight(QFont::Normal);
}
