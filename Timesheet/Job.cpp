#include "Job.h"

Job::Job(Job* parent) : TreeItem(parent)
{
	itemData.resize(UsedColumns.size());

	hasCheckBox = true;
};

Job::Job(QDateTime _From, QDateTime _To, QDateTime _ModDate, QString _Company, QString _Project, QString _Comment, JobStatus _Status, QString _Owner, qint64 _ID) : Job()
{
	From = _From; 
	To = _To; 
	ModDate = _ModDate;
	Company = _Company; 
	Project = _Project; 
	Comment = _Comment; 
	Status = _Status; 
	Owner = _Owner;
	ID = _ID;
}

Job::~Job()
{
	qDebug() << "Usuwam Job!";
}

void Job::UpdateValues(QDateTime _From, QDateTime _To, QDateTime _ModDate, QString _Company, QString _Project, QString _Comment, JobStatus _Status, QString _Owner, qint64 _ID)
{
	From = _From;
	To = _To;
	ModDate = _ModDate;
	Company = _Company;
	Project = _Project;
	Comment = _Comment;
	Status = _Status;
	Owner = _Owner;
	ID = _ID;
}

int Job::columnCount() const
{
	return UsedColumns.size();
}
bool Job::setData(int column, const QVariant &value)
{

	if (column < 0 || column >= 5)
		return false;

	QString Value = value.toString();
	QDateTime F, T;
	QTime time;

	switch (column)
	{
	case 0:
		T = getTo(); F = getFrom();
		time = time.fromString(Value.mid(0, 5), TIMEFORMATSHORT);
		F.setTime(time);
		time = time.fromString(Value.mid(Value.indexOf(" to ") + 4, 5), TIMEFORMATSHORT);
		T.setTime(time);
		setFrom(F); setTo(T);
		break;
	case 1:
		// nothingto do - updates automatically, depending on From and To
		break;
	case 2:
		setCompany(Value);
		break;
	case 3:
		setProject(Value);
		break;
	case 4: setStatus(JobStatus(Value.toInt()));
	}

	return true;
}
QVariant Job::data(int column) const
{
	TimeSpan *ts = new TimeSpan;
	*ts = getDuration();
	QList<QVariant> List;
	List.append(getFrom());
	List.append(getTo());

	switch (column)
	{
	case 0:
		return QVariant::fromValue(List);
		break;
	case 1:
		return QVariant(qRegisterMetaType<TimeSpan>(), ts);
		break;
	case 2:
		return QVariant(getCompany());
		break;
	case 3:
		return QVariant(getProject());
		break;
	case 4:
        return QVariant(qRegisterMetaType<JobStatus>(), /*& CHECKME TOM */ & getStatus());
		break;
	case -1:
		QVariant var;
		var.setValue((Job*)this);
		return var;
		break;
	}
	return QVariant();
}
QDebug operator<< (QDebug d, const Job &item) {
	d << "--------------------" << endl;
	d << "Owner: " << item.getOwner() << endl;
	d << "From: " << item.getFrom() << endl;
	d << "To: " << item.getTo() << endl;
	d << "Company: " << item.getCompany() << endl;
	d << "Project: " << item.getProject() << endl;
	d << "Comment: " << item.getComment() << endl;
	d << "Status: " << item.getStatus().getStatusString() << endl;
	d << "Duration: " << item.getDuration() << endl;
	d << "ID: " << item.getID();

	return d;
}
QDataStream &operator<<(QDataStream &out, const Job &item) {
	out << (qint64)item.getID() << item.getOwner() << item.getComment() << item.getProject() << item.getCompany() << item.getFrom() << item.getTo() << (qint64)item.getStatus().toInt() << item.getModDate();
	return out;
}
QDataStream &operator>>(QDataStream &in, Job &item) {
	qint64 integer;
	QString str;
	QDateTime dt;
	in >> integer;
	item.setID(integer);
	in >> str;
	item.setOwner(str);
	in >> str;
	item.setComment(str);
	in >> str;
	item.setProject(str);
	in >> str;
	item.setCompany(str);
	in >> dt;
	item.setFrom(dt);
	in >> dt;
	item.setTo(dt);
	in >> integer;
	item.setStatus(JobStatus(integer));
	in >> dt;
	item.setModDate(dt);

	return in;
}
bool operator==(const Job& lhs, const Job& rhs)
{
	if (lhs.getComment() != rhs.getComment())
		return false;
	else if (lhs.getCompany() != rhs.getCompany())
		return false;
	else if (lhs.getFrom() != rhs.getFrom())
		return false;
	else if (lhs.getID() != rhs.getID())
		return false;
	else if (lhs.getModDate() != rhs.getModDate())
		return false;
	else if (lhs.getOwner() != rhs.getOwner())
		return false;
	else if (lhs.getProject() != rhs.getProject())
		return false;
	else if (lhs.getStatus().toInt() != rhs.getStatus().toInt())
		return false;
	else if (lhs.getTo() != rhs.getTo())
		return false;
	else
		return true;
}
