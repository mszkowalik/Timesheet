#pragma once

#include <QStandardItem>
#include "TreeItem.h"
#include <qdatetime.h>
#include <QDebug>
#include "Constants.h"
#include "TimeSpan.h"
#include "JobStatus.h"
#include <QObject>

class Job : public TreeItem
{

public:
	Job(Job* parent = 0);
	Job(QDateTime _From, QDateTime _To, QDateTime _ModDate, QString _Company, QString _Project, QString _Comment, JobStatus _Status, QString _Owner, qint64 _ID);
	~Job();
	static bool lessThan(const Job* lhs, const Job* rhs)
	{
		bool ret = lhs->getFrom() < rhs->getFrom();
		//qDebug() << "operator Called" << endl << lhs->getFrom().toString(DATETIMEFORMAT) << endl << rhs->getFrom().toString(DATETIMEFORMAT) << endl << ret;

		return ret;
	};

	QDateTime getFrom()		const { return From; };
	QDateTime getTo()		const { return To; };
	QDateTime getModDate()		const { return ModDate; };
	QString getCompany()	const { return Company; };
	QString getProject()	const { return Project; };
	QString getComment()	const { return Comment; };
    JobStatus const & getStatus()	const { return Status; };
	QString getOwner()		const { return Owner; };
	qint64 getID()			const { return ID; };
	TimeSpan getDuration()	const { return TimeSpan(getFrom().secsTo(getTo())); };


	void setFrom(QDateTime _From) { From = _From; };
	void setModDate(QDateTime _ModDate) { ModDate = _ModDate; };
	void setTo(QDateTime _To) { To = _To; };
	void setCompany(QString _Company) {Company = _Company; };
	void setProject(QString _Project) { Project = _Project; };
	void setComment(QString _Comment) { Comment = _Comment; };
	void setStatus(JobStatus _Status) { Status = _Status; };
	void setOwner(QString _Owner) { Owner =  _Owner; };
	void setID(qint64 _ID) {ID = _ID; };

	void UpdateValues(QDateTime _From, QDateTime _To, QDateTime _ModDate, QString _Company, QString _Project, QString _Comment, JobStatus _Status, QString _Owner, qint64 _ID);


	void clear() { From = QDateTime(); To = QDateTime(); Status = JobStatus(); ID = 0; Owner.clear(); Company.clear(); Comment.clear(); Project.clear(); };
	//functions needed for tree view

	QVariant data(int column) const override;
	bool setData(int column, const QVariant &value) override;
	int columnCount() const  override;

	friend QDataStream &operator<<(QDataStream &out, const Job &item);
	friend QDataStream &operator>>(QDataStream &in, Job &item);
	QStringList UsedColumns = { "FromTo","Duration","Company","Project", "Status" };


private:
	JobStatus Status;
	qint64 ID = 0;
	QString Owner = "";
	QString Comment = "";
	QString Project = "";
	QString Company = "";
	QDateTime From, To, ModDate;

};


Q_DECLARE_METATYPE(Job);
Q_DECLARE_METATYPE(Job*);
QDebug operator<< (QDebug d, const Job &item);
bool operator==(const Job& lhs, const Job& rhs);
