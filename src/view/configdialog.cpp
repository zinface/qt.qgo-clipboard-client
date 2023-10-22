#include "configdialog.h"
#include "global.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);

    ui->lineEdit_server_address->setText(GL.getAddress());
}

ConfigDialog::~ConfigDialog()
{
    GL.setAddress(ui->lineEdit_server_address->text());

    delete ui;
}
