#include "configdialog.h"
#include "global/global.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);

    ui->lineEdit_server_address->setText(GL.getAddress());
    ui->check_notify_send->setChecked(GL.notifySend());
    ui->check_notify_recv->setChecked(GL.notifyRecv());
}

ConfigDialog::~ConfigDialog()
{
    if (result() == Accepted) {
        GL.setAddress(ui->lineEdit_server_address->text());
        GL.setNotifySend(ui->check_notify_send->isChecked());
        GL.setNotifyRecv(ui->check_notify_recv->isChecked());
    }

    delete ui;
}
