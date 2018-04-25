#pragma once
#include "treeitem.h"
#include "Job.h"
#include <QDate>
#include "TimeSpan.h"

class DayItem :	public TreeItem
{
public:

	DayItem();
	~DayItem();
	void addJob(Job* job);
	QDate getDate() const { return date; };
	void setDate(QDate _date) { date = _date; };
	void UpdateStats();
	static bool lessThan(const DayItem* lhs, const DayItem* rhs)
	{
		return lhs->getDate() < rhs->getDate();
	}
	// TreeItem Specific:


	QVariant data(int column) const override;
	bool setData(int column, const QVariant &value) override;
	int columnCount() const  override;


private:
	QList<Job*> Jobs;
	QDate date;
	TimeSpan timespan;
};


Q_DECLARE_METATYPE(DayItem);