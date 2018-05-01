#include "Data.h"




Data::Data(Settings* s, TreeModel* _TimesheetModel, TreeModel* _StatsModel) : QObject()
{
	Model = _TimesheetModel;
	stats.setModel(_StatsModel);
}
Data::~Data()
{

}
void Data::updateStatistics()
{
	//while (stats.Companies.length())
	//{
	//	delete stats.Companies.takeLast();
	//	
	//}

	//for (int i = 0; i < JobList.count(); i++)
	//{

	//	stats.addPosition(JobList.at(i));
	//}
}
void Data::clearDays()
{
	while (DayItemList.length())
		DayItemList.removeLast();
}
void Data::sortJobs()
{
	if (Model)
	{
		Model->layoutAboutToBeChanged();
		Model->rootItem->removeChildren(0, Model->rootItem->childCount());
		clearDays();
		std::sort(JobList.begin(), JobList.end(), Job::lessThan);

		for (int i = 0; i < JobList.length(); i++)
			assignDay(JobList.at(i));

		std::sort(DayItemList.begin(), DayItemList.end(), DayItem::lessThan);

		for (int i = 0; i < DayItemList.length(); i++)
			Model->rootItem->addChild(DayItemList.at(i));

		//for (int i = 0; i < JobList.length(); i++)
			//qDebug() << *JobList.at(i);
		Model->layoutChanged();
	}
}
void Data::joinJobs(int s_difference)
{
	sortJobs();
	qint64 difference;
	bool sameCompany, sameProject;
	Job* job;
	if (Model)
	{
		Model->layoutAboutToBeChanged();
		Model->rootItem->removeChildren(0, Model->rootItem->childCount());
	}
	clearDays();


	for (int i = 1; i < JobList.length() - 1; i++)
	{
		difference = JobList.at(i)->getFrom().toSecsSinceEpoch() - JobList.at(i - 1)->getTo().toSecsSinceEpoch();
		sameCompany = JobList.at(i - 1)->getCompany() == JobList.at(i)->getCompany();
		sameProject = JobList.at(i - 1)->getProject() == JobList.at(i)->getProject();
		if (difference < s_difference && sameCompany && sameProject)
		{
			job = new Job(JobList.at(i - 1)->getFrom(), JobList.at(i)->getTo(), JobList.at(i)->getModDate(), JobList.at(i)->getCompany(), JobList.at(i)->getProject(), JobList.at(i - 1)->getComment() + JobList.at(i)->getComment(), JobList.at(i)->getStatus(), JobList.at(i)->getOwner(), 0);
			JobList.takeAt(i - 1);
			JobList.takeAt(i - 1);
			JobList.append(job);
			qDebug() << *job;
			i = 0;
		}
	}

	for (int i = 0; i < JobList.length(); i++)
		assignDay(JobList.at(i));

	std::sort(DayItemList.begin(), DayItemList.end(), DayItem::lessThan);

	for (int i = 0; Model && i < DayItemList.length(); i++)
		Model->rootItem->addChild(DayItemList.at(i));
	if (Model)
		Model->layoutChanged();

}
DayItem* Data::addJob(Job* job)
{
	if (job)
	{
		if (Model)
			Model->layoutAboutToBeChanged();

		JobList.append(job);
		stats.addPosition(job);

		
		
		
		
		DayItem* D = assignDay(job);
		if (Model && Model->rootItem->childItems.indexOf(D) == -1)
		{
			Model->rootItem->addChild(D);	
			//Model->insertRows(Model->rootItem, D);
		}

		if (Model)
			Model->layoutChanged();
		// if job hasn't got ID or status is not unpaid try to ask server to assign one

		emit(addToQueue(job));

		return D;
	}
	return Q_NULLPTR;
}
DayItem* Data::addJob(Job job)
{
	Job* newJob;
	newJob = new Job(job);
	if (Model)
		Model->layoutAboutToBeChanged();

	JobList.append(newJob);
	stats.addPosition(newJob);

	DayItem* D = assignDay(newJob);
	if (Model && Model->rootItem->childItems.indexOf(D) == -1)
	{
		Model->rootItem->addChild(D);
	}

	if (Model)
		Model->layoutChanged();
	// if job hasn't got ID or status is not unpaid try to ask server to assign one

	emit(addToQueue(newJob));

	return D;

}

Job* Data::jobAt(int i) const
{
	if (i < JobList.length())
		return JobList[i];
	else return Q_NULLPTR;
}
bool Data::removeJob(Job* job)
{
	if (job)
	{
		TreeItem* parent = job->parentItem;
		int jobItemRow = parent->childItems.indexOf(job);
		QModelIndex jobItemIndex = Model->getIndex(jobItemRow, 0, job);
		int dayItemRow = Model->rootItem->childItems.indexOf(parent);

		QModelIndex dayItemtIndex = Model->getIndex(dayItemRow, 0, parent);

		int index = JobList.indexOf(job);

		Model->removeRow(jobItemRow, jobItemIndex.parent());
		JobList.takeAt(index);

		if (parent)
		{
			//int count = parent->childItems.count();
			//if (count == 0)
			{
				//index = DayItemList.indexOf(static_cast<DayItem*>(parent));
				//DayItemList.takeAt(index);
				//Model->removeRow(dayItemRow, dayItemtIndex.parent());
			}
		}


		return true;
	}
	return false;
}
void Data::updateDays()
{
	while (DayItemList.length() > 0)
	{
		delete DayItemList.takeFirst();
	}
	for (int i = 0; i < JobList.length(); i++)
	{
		assignDay(JobList.at(i));
	}

}
DayItem* Data::dayAt(int i)
{
	if (i < DayItemList.length())
		return DayItemList[i];
	else return Q_NULLPTR;
}
int Data::jobsCount() const
{
	return JobList.length();
};
int Data::findDay(QDate date)
{
	DayItem *Item;
	for (int i = 0; i < DayItemList.length(); i++)
	{
		Item = DayItemList.at(i);
		if (Item->getDate() == date)
		{
			return i;
		}
	}
	return -1;
}
DayItem* Data::assignDay(Job* job)
{
	int index = -1;
	index = findDay(job->getFrom().date());
	if (index != -1)
	{
		DayItemList.at(index)->addJob(job);
		return	DayItemList.at(index);
	}
	else
	{
		DayItem *dayItem = new DayItem;
		dayItem->setDate(job->getFrom().date());
		dayItem->addJob(job);
		DayItemList.append(dayItem);
		return dayItem;
	}
}
void Data::clear()
{
	while (DayItemList.length() > 0)
	{
		delete DayItemList.takeFirst();
	}
	while (JobList.length() > 0)
	{
		delete JobList.takeFirst();
	}
	while (stats.Companies.length())
	{
		delete stats.Companies.takeLast();
	}
}


QStringList Data::getProjectsList(QString Company)
{
	int index = stats.CompanyIndex(Company);
	if (index >= 0 && index < stats.Companies.length())
		return stats.Companies[index]->ProjectsList(true);
	else
		return QStringList();
}
QStringList Data::getUnpaidProjectsList(QString Company)
{
	QStringList ret;
	int index = stats.CompanyIndex(Company);
	if (index >= 0 && index < stats.Companies.length())
	{
		for (int i = 0; i < JobList.count(); i++)
			if (JobList.at(i)->getStatus().toInt() == JobStatus::Unpaid && JobList.at(i)->getCompany() == Company)
				ret.append(JobList.at(i)->getProject());

		return ret;
	}
	else
		return QStringList();;
}
int Data::indexOf(Job j)
{
	for (int i = 0; i < JobList.length(); i++)
	{
		if (*JobList.at(i) == j)
		{

		}
	}
	return 0;
}
QStringList Data::getCompaniesList()
{
	return stats.GetCompaniesList();
};

int Data::companyIndex(QString Company)
{
	return stats.CompanyIndex(Company);
};
QList<Job*> Data::getJobsToSave(int updatePeriod)
{
	QList<Job*> ret;
	for each (Job* job in JobList)
	{
		//if (job->getStatus().toInt() == 0 || job->getFrom() > QDateTime::currentDateTime().addDays(-updatePeriod))
		{
			ret.append(job);
		}
	}
	return ret;
}
QDebug operator<< (QDebug d, const Statistics &item)
{
	for (int i = 0; i < item.Companies.length(); i++)
	{
		d << *item.Companies.at(i);
	}
	return d;
}
