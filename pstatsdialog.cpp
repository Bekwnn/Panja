#include "pstatsdialog.h"
#include "ui_pstatsdialog.h"

#include <QDebug>

PStatsDialog::PStatsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PStatsDialog)
{
    ui->setupUi(this);
}

PStatsDialog::PStatsDialog(PTreeTextItem *mainview, QList<PTreeTextItem *> allCountedDocuments, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PStatsDialog)
{
    ui->setupUi(this);
    setStats(mainview, allCountedDocuments);
}

PStatsDialog::~PStatsDialog()
{
    delete ui;
}

void PStatsDialog::setStats(PTreeTextItem *mainview, QList<PTreeTextItem*> allCountedDocuments)
{
    PDocumentStats mainstats  = calculateStats(mainview);
    ui->labelIntCurrentChar->setText(QString::number(mainstats.charCount));
    ui->labelIntCurrentCharWS->setText(QString::number(mainstats.wsCharCount));
    ui->labelIntCurrentParagraph->setText(QString::number(mainstats.blockCount));
    ui->labelIntCurrentWC->setText(QString::number(mainstats.wordCount));

    //PDocumentStats totalstats = calculateStats(allCountedDocuments);
}

PDocumentStats PStatsDialog::calculateStats(PTreeTextItem* item)
{
    qDebug() << "Running!";
    QTextDocument* doc = item->getDocument();
    QString docString = doc->toPlainText().append(" "); //append space to make sure last word is counted
    PDocumentStats itemStats;
    for (int i = 0; i < docString.length(); i++)
    {
        if (!docString[i].isSpace())
        {
            itemStats.charCount++;
            bIsWord = true;
        }
        else
        {
            if (bIsWord)
            {
                itemStats.wordCount++;
                bIsWord = false;
            }
        }
        itemStats.wsCharCount++;
    }
    itemStats.wsCharCount--;    //correcting for the appended space
    return itemStats;
}

PDocumentStats PStatsDialog::calculateStats(QList<PTreeTextItem*> items)
{
    PDocumentStats total;
    for (PTreeTextItem* item : items)
    {
        total = total + calculateStats(item);
    }
    return total;
}

void PStatsDialog::on_buttonClose_clicked()
{
    close();
}
