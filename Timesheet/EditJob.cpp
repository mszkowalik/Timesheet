#include "EditJob.h"
#include <QLineEdit>

EditJob::EditJob(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}


EditJob::EditJob(Job* _job, Data* _JobData, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);


	job = _job;
	JobData = _JobData;

	JobStatus js;
	ui.Status_comboBox->addItems(js.Statuses);

	ui.From_dateTimeEdit->setDateTime(job->getFrom());
	ui.To_dateTimeEdit->setDateTime(job->getTo());
	ui.Comment_textEdit->setText(job->getComment());

	ui.Company_comboBox->clear();
	ui.Company_comboBox->addItems(JobData->getCompaniesList());
	ui.Company_comboBox->setCurrentText(job->getCompany());
	on_Company_comboBox_currentIndexChanged(job->getCompany());

	ui.Status_comboBox->setCurrentText(job->getStatus().getStatusString());
}


EditJob::~EditJob()
{
}

void EditJob::on_OK_pushButton_clicked()
{
	qDebug() << "OK";

	job->setComment(ui.Comment_textEdit->toPlainText());
	job->setCompany(ui.Company_comboBox->currentText());
	job->setFrom(ui.From_dateTimeEdit->dateTime());
	job->setTo(ui.To_dateTimeEdit->dateTime());
	job->setProject(ui.Project_comboBox->currentText());
	job->setStatus(ui.Status_comboBox->currentIndex());

	close();
}

void EditJob::on_Cancel_pushButton_clicked()
{
	close();
}

void EditJob::on_Company_comboBox_currentIndexChanged(QString index)
{
	


	QStringList projects = JobData->getProjectsList(index);
	projects.removeDuplicates();
	projects.sort();
	ui.Project_comboBox->clear();
	ui.Project_comboBox->addItems(projects);
	if (job->getCompany() == index)
		ui.Project_comboBox->setCurrentText(job->getProject());
	
}