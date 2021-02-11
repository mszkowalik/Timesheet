#pragma once
#include <qwidget.h>
class JobStatus
{
public:
	JobStatus(int i = 0) {status = i;};
	~JobStatus();
    int toInt() const { return status; };
    QString getStatusString() const { return Statuses.at(status); };
	void setStatus(int i) { if (i < Statuses.length()) status = i; };
	QStringList Statuses = { "Unpaid","Paid","Pending" };
	enum StatusesEnum
	{
		Unpaid=0,
		Paid,
		Pending
	};

private:

	int status = 0;
};


Q_DECLARE_METATYPE(JobStatus);
