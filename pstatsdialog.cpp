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

    PDocumentStats totalstats = calculateStats(allCountedDocuments);
    ui->labelIntTotalChar->setText(QString::number(totalstats.charCount));
    ui->labelIntTotalCharWS->setText(QString::number(totalstats.wsCharCount));
    ui->labelIntTotalParagraph->setText(QString::number(totalstats.blockCount));
    ui->labelIntTotalWC->setText(QString::number(totalstats.wordCount));
}

PDocumentStats PStatsDialog::calculateStats(PTreeTextItem* item)
{
    QTextDocument* doc = item->getDocument();
    QString docString = doc->toPlainText().append("\n"); //append newline to make sure last word and block are counted
    PDocumentStats itemStats;
    for (int i = 0; i < docString.length(); i++)
    {
        if (!docString[i].isSpace())
        {
            itemStats.charCount++;
            bIsWord = true;
            bIsBlock = true;
        }
        else
        {
            if (bIsWord)
            {
                itemStats.wordCount++;
                bIsWord = false;
            }
            if (bIsBlock && docString[i] == '\n')
            {
                itemStats.blockCount++;
                bIsBlock = false;
            }
        }
        itemStats.wsCharCount++;
    }
    itemStats.wsCharCount--;    //correcting for the appended newline
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
