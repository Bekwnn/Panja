#ifndef PCONFIRMCLOSE_H
#define PCONFIRMCLOSE_H

#include <QDialog>

namespace Ui {
class PConfirmClose;
}

class PConfirmClose : public QDialog
{
    Q_OBJECT

public:
    explicit PConfirmClose(QWidget *parent = 0);
    ~PConfirmClose();

private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonDiscard_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::PConfirmClose *ui;
};

#endif // PCONFIRMCLOSE_H
