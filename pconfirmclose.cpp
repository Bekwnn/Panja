#include "pconfirmclose.h"
#include "ui_pconfirmclose.h"

#include <QDialogButtonBox>

PConfirmClose::PConfirmClose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PConfirmClose)
{
    ui->setupUi(this);
}

PConfirmClose::~PConfirmClose()
{
    delete ui;
}

void PConfirmClose::on_pushButtonSave_clicked()
{
    done(QDialogButtonBox::Yes);
}

void PConfirmClose::on_pushButtonDiscard_clicked()
{
    done(QDialogButtonBox::No);
}

void PConfirmClose::on_pushButtonCancel_clicked()
{
    done(QDialogButtonBox::Cancel);
}
