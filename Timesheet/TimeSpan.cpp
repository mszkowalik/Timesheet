#include "TimeSpan.h"

TimeSpan::TimeSpan()
{
	qRegisterMetaType<TimeSpan>("TimeSpan");
}

TimeSpan::TimeSpan(qint64 seconds)
{
	Hours = seconds / 3600;
	seconds -= Hours * 3600;
	Minutes = seconds / 60;
	seconds -= Minutes * 60;
	Seconds = seconds;

}

TimeSpan::~TimeSpan()
{
}

QString TimeSpan::toString() const
{
	QString ret;
	QString minutes = QString("%1").arg(Minutes, 2, 10, QChar('0'));
	//QString seconds = QString("%1").arg(Seconds, 2, 10, QChar('0'));
	QString hours = QString("%1").arg(Hours, 2, 10, QChar('0'));
	ret = hours + ":" + minutes;// +":" + seconds;
	return ret;
}
QString TimeSpan::toStringSec() const
{
	QString ret;
	QString minutes = QString("%1").arg(Minutes, 2, 10, QChar('0'));
	QString seconds = QString("%1").arg(Seconds, 2, 10, QChar('0'));
	QString hours = QString("%1").arg(Hours, 2, 10, QChar('0'));
	ret = hours + ":" + minutes +":" + seconds;
	return ret;
}
QDebug operator<< (QDebug d, const TimeSpan &item)
{
	QString Minutes = QString("%1").arg(item.Minutes, 2, 10, QChar('0'));
	QString Seconds = QString("%1").arg(item.Seconds, 2, 10, QChar('0'));
	QString Hours = QString("%1").arg(item.Hours, 2, 10, QChar('0'));
	d << Hours << "Hours " << Minutes << " Minutes " << Seconds << " Seconds";
	return d;
}