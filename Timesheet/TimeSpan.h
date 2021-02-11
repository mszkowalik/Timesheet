#pragma once
#include <QWidget>
#include <QDebug>
#include <iomanip>
class TimeSpan
{
public:
	TimeSpan();
	TimeSpan(qint64 seconds);
	~TimeSpan();

	qint16 Hours = 0;
	qint8 Minutes = 0;
	qint8 Seconds = 0;
	QString toString() const;
	QString toStringSec() const;
	TimeSpan& operator+=(const TimeSpan& item) 
	{
		if (Seconds + item.Seconds >= 60)
		{
			Minutes += (Seconds + item.Seconds) / 60;
		}

		if (Minutes + item.Minutes >= 60)
		{
			Hours += (Minutes + item.Minutes) / 60;
		}
		Minutes = (Minutes + item.Minutes) % 60;

		Hours += item.Hours;
		return *this; // return the result by reference
	}
	//const int id = qRegisterMetaType<TimeSpan>("TimeSpan");
};


QDebug operator<< (QDebug d, const TimeSpan &item);
Q_DECLARE_METATYPE(TimeSpan);
