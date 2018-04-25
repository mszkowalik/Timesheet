#include "DayItem.h"


DayItem::DayItem()
{
}


DayItem::~DayItem()
{
	//qDebug() << "Usuwam DayItem!";
	
}

void DayItem::addJob(Job* job)
{
	if (Jobs.indexOf(job) == -1)
	{
		Jobs.append(job);
		addChild(job);
	}
	UpdateStats();
}
QVariant DayItem::data(int column) const
{
	switch (column)
	{

	case 0:
		return QVariant(getDate());
		break;
	case 1:
		return QVariant::fromValue<TimeSpan>(timespan);
		break;
	default:
		return QVariant();
	}

}
void DayItem::UpdateStats()
{
	timespan = TimeSpan();
	for (qint64 i = 0; i < Jobs.length(); i++)
	{
		timespan += Jobs[i]->getDuration();
	}
}
bool DayItem::setData(int column, const QVariant &value)
{
	return false;
}
int DayItem::columnCount() const
{
	return 2;
}

