#pragma once

#include <QDialog>
#include "ui_SalaryPaid.h"
#include "Data.h"

class SalaryPaid : public QDialog
{
	Q_OBJECT

public:
	SalaryPaid(QWidget *parent = Q_NULLPTR);
	SalaryPaid(Data* _data, QWidget *parent = Q_NULLPTR);
	~SalaryPaid();
	public slots:
	void on_OK_pushButton_clicked();
	void on_Cancel_pushButton_clicked();
	void on_Company_comboBox_currentIndexChanged(QString index);
	void on_AllPaid_checkBox_stateChanged(int state);
private:
	Ui::SalaryPaid ui;
	Data* data;
};
