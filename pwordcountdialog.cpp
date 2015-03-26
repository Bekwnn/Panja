#include "pwordcountdialog.h"
#include "ui_pwordcountdialog.h"

#include <QTextDocument>
#include <QChar>

PWordCountDialog::PWordCountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PWordCountDialog)
{
    ui->setupUi(this);
}

PWordCountDialog::~PWordCountDialog()
{
    delete ui;
}

void PWordCountDialog::processDocumentChanges(int position, int charsRemoved, int charsAdded)
{
    charCount -= charsRemoved;
    charCount += charsAdded;
    QTextDocument *doc = static_cast<QTextDocument*>(QObject::sender());
}
