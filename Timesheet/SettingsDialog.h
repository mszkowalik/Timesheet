#pragma once

#include <QDialog>
#include "ui_SettingsDialog.h"
#include "Settings.h"

class SettingsDialog : public QDialog
{
	Q_OBJECT

public:
	SettingsDialog(QWidget *parent = Q_NULLPTR);
	SettingsDialog(Settings _s, QWidget* parent= Q_NULLPTR);
	~SettingsDialog();
	void closeEvent(QCloseEvent *event);
	Settings settings;
	public slots:
	void on_cancel_pushButton_clicked();
	void on_ok_pushButton_clicked();

private:
	Ui::SettingsDialog ui;
};
