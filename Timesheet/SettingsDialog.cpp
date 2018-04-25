#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

SettingsDialog::SettingsDialog(Settings _s, QWidget* parent)
	: QDialog(parent)
{
	settings = _s;
	ui.setupUi(this);
	if (_s.SyncWithServer)
	{
		ui.Username_lineEdit->setText(_s.MySQL_Username);
		ui.Adress_lineEdit->setText(_s.MySQL_Server);
		ui.Port_lineEdit->setText(QString::number(_s.MySQL_Port, 10));
		ui.updatePeriod_spinBox->setValue(_s.UpdatePeriod);
		ui.Sync_checkBox->setChecked(_s.SyncWithServer);
	}
}

SettingsDialog::~SettingsDialog()
{
}
void SettingsDialog::closeEvent(QCloseEvent *event)
{

}

void SettingsDialog::on_cancel_pushButton_clicked()
{
	close();
}

void SettingsDialog::on_ok_pushButton_clicked()
{
	if (ui.Sync_checkBox->isChecked())
	{
		settings.MySQL_Username = ui.Username_lineEdit->text();
		settings.MySQL_Port = ui.Port_lineEdit->text().toInt(0, 10);
		settings.MySQL_Server = ui.Adress_lineEdit->text();
		settings.UpdatePeriod = ui.updatePeriod_spinBox->value();
		//settings.SyncWithServer = ui.Sync_checkBox->isChecked();
	}
	close();
}
