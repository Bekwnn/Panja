#ifndef PWORDCOUNTDIALOG_H
#define PWORDCOUNTDIALOG_H

#include <QDialog>
#include <cstdint>

namespace Ui {
class PWordCountDialog;
}

class PWordCountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PWordCountDialog(QWidget *parent = 0);
    ~PWordCountDialog();

private:
    Ui::PWordCountDialog *ui;
    uint32_t charCount;
    uint32_t wordCount;
    uint32_t blockCount;
    QMap<QString, int> wordFrequencyMap;


public slots:
    void processDocumentChanges(int position, int charsRemoved, int charsAdded);
};

#endif // PWORDCOUNTDIALOG_H
