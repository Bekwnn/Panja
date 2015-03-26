#ifndef PTEXTEDIT_H
#define PTEXTEDIT_H

#include <QTextEdit>
#include <QLabel>
#include "ptreetextitem.h"

class PTextEdit : public QTextEdit
{
protected:
    PTreeTextItem* currentItem;
    void setDocument(QTextDocument *doc);   //hiding setDocument(QTextDocument*), use setDocument(PTreeTextItem*) instead
public:
    PTreeTextItem* getItem() { return currentItem; }
    void setDocument(PTreeTextItem *item);
    QLabel* documentLabel;
    PTextEdit();
    PTextEdit(QWidget*);
    ~PTextEdit();
public slots:
    void setTextBold(bool b);
};

#endif // PTEXTEDIT_H
