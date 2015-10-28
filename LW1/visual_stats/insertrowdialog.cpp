#include "insertrowdialog.h"
#include "ui_insertrowdialog.h"
#include <QPushButton>
InsertRowDialog::InsertRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertRowDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(onAccepted()));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
}

InsertRowDialog::~InsertRowDialog()
{
    delete ui;
}

void InsertRowDialog::onAccepted()
{
    emit rowReady(ui->editName->text(), ui->editValue->value());
}

void InsertRowDialog::on_editName_textChanged(const QString &)
{
    UpdateOkButtonState();
}

void InsertRowDialog::on_editValue_valueChanged(int)
{
    UpdateOkButtonState();
}

bool InsertRowDialog::IsTheDataAcceptable()
{
    return (!(ui->editName->text().isEmpty())
            && (ui->editValue->value() != 0));
}

void InsertRowDialog::UpdateOkButtonState()
{
    if (IsTheDataAcceptable())
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    }
}
