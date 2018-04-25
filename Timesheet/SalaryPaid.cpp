#include "SalaryPaid.h"

SalaryPaid::SalaryPaid(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

SalaryPaid::SalaryPaid(Data * _data, QWidget * parent): SalaryPaid(parent)
{
	data = _data;
	ui.Company_comboBox->addItems(data->getCompaniesList());
}

SalaryPaid::~SalaryPaid()
{
}

void SalaryPaid::on_Cancel_pushButton_clicked()
{
	close();
}
void SalaryPaid::on_OK_pushButton_clicked()
{
	QStringList PL;
	for (int i = 0; i < ui.Projects_listWidget->count(); i++)
	{
		QListWidgetItem* item = ui.Projects_listWidget->item(i);
		if (item->checkState() == Qt::Checked)
			PL.append(item->text());

	}

	PL.sort();
	PL.removeDuplicates();

	for (int i = 0; i < data->jobsCount(); i++)
	{
		Job* job = data->jobAt(i);
		if(job->getCompany() == ui.Company_comboBox->currentText())
			if (PL.indexOf(job->getProject()) >= 0)
			{
				job->setStatus(JobStatus::Paid);
			}
	}


	close();
}
void SalaryPaid::on_Company_comboBox_currentIndexChanged(QString index)
{
	QStringList projects = data->getUnpaidProjectsList(index);
	projects.removeDuplicates();
	projects.sort();

	ui.Projects_listWidget->clear();
	for (int i = 0; i < projects.count(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem(projects.at(i), ui.Projects_listWidget);
		item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
		item->setCheckState(Qt::Unchecked); // AND initialize check state
	}
	//ui.Project_comboBox->clear();
	//ui.Project_comboBox->addItems(projects);
}

void SalaryPaid::on_AllPaid_checkBox_stateChanged(int state)
{
	for (int i = 0; i < ui.Projects_listWidget->count(); i++)
		ui.Projects_listWidget->item(i)->setCheckState((Qt::CheckState)state);
}
