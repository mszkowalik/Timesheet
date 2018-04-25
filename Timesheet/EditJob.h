#pragma once

#include <QDialog>
#include <ui_EditJob.h>
#include "Data.h"
#include "TreeModel.h"
class EditJob : public QDialog
{
	Q_OBJECT

public:
	EditJob(QWidget *parent = Q_NULLPTR);
	EditJob(Job* _job, Data* _JobData,QWidget *parent = Q_NULLPTR);

	~EditJob();

public slots:
	void on_OK_pushButton_clicked();
	void on_Cancel_pushButton_clicked();
	void on_Company_comboBox_currentIndexChanged(QString index);

private:
	Ui::EditJob ui;
	Job *job;
	Data *JobData;
};
