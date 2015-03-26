#ifndef PSTATSDIALOG_H
#define PSTATSDIALOG_H

#include <QDialog>
#include <QList>
#include <QMap>

#include "ptreetextitem.h"

namespace Ui {
class PStatsDialog;
}

struct PDocumentStats {
    quint32 wsCharCount;   //char count with whitespace
    quint32 charCount;
    quint32 wordCount;
    quint32 blockCount;

    PDocumentStats() : wsCharCount(0), charCount(0), wordCount(0), blockCount(0)
    {
    }

    const PDocumentStats& operator+(const PDocumentStats& rhs)
    {
        PDocumentStats result;
        result.wsCharCount = this->wsCharCount + rhs.wsCharCount;
        result.charCount   = this->charCount   + rhs.charCount;
        result.wordCount   = this->wordCount   + rhs.wordCount;
        result.blockCount  = this->blockCount  + rhs.blockCount;
        return result;
    }
};

class PStatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PStatsDialog(PTreeTextItem* mainview, QList<PTreeTextItem*> allCountedDocuments, QWidget *parent = 0);
    ~PStatsDialog();
private slots:
    void on_buttonClose_clicked();

private:
    void setStats(PTreeTextItem* mainview, QList<PTreeTextItem*> allCountedDocuments);
    PDocumentStats calculateStats(PTreeTextItem* item);
    PDocumentStats calculateStats(QList<PTreeTextItem*> items);
    explicit PStatsDialog(QWidget *parent = 0);
    Ui::PStatsDialog *ui;
    bool bIsWord;
    bool bIsBlock;
    QMap<QString, int> wordFreqMap;
};

#endif // PSTATSDIALOG_H
