#pragma once
#include <QList>
#include <QWidget>
#include <QDate>
#include <QThread>
#include <QObject>
#include "Job.h"
#include "DayItem.h"
#include "TreeModel.h"
#include "Statistics.h"
#include "MySQLConn.h"
#include "Settings.h"

class Data : public QObject
{
	Q_OBJECT
public:


	Data(Settings* s = Q_NULLPTR,TreeModel* _TimesheetModel = Q_NULLPTR, TreeModel* _StatsModel = Q_NULLPTR);
	~Data();
	void updateStatistics();

signals:
	void addToQueue(Job*);
	void setMessage(QString);

public slots:
	DayItem* addJob(Job* job);
	DayItem* addJob(Job job);
	bool removeJob(Job* job);
	int jobsCount() const;
	Job* jobAt(int i) const;
	void sortJobs();
	void joinJobs(int s_difference);
	QList<Job*> getJobsToSave(int updatePeriod);

	DayItem* dayAt(int i);
	void updateDays();
	int findDay(QDate date);
	DayItem* assignDay(Job* job);
	void clearDays();

	void setModel(TreeModel* _TimesheetModel, TreeModel* _StatsModel) { Model = _TimesheetModel; stats.setModel(_StatsModel); };
	void clear();

	QStringList getCompaniesList();
	int companyIndex(QString Company);
	QStringList getProjectsList(QString Company);
	QStringList getUnpaidProjectsList(QString Company);

	Statistics getStats() { return stats; }


private:
	int indexOf(Job);
	//Settings settings;
	QList<Job*> JobList;
	QList<DayItem*> DayItemList;
	Statistics stats;
	TreeModel* Model;
};


QDebug operator<< (QDebug d, const Statistics &item);