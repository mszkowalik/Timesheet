#pragma once
#include <qwidget.h>
#include "TimeSpan.h"
#include "Job.h"
#include "TreeItem.h"
#include <QStringList>
class Project : public TreeItem
{
public:
	Project(Project* parent=0);
	~Project();
    QVariant data(int column) const;
	int columnCount() const  override;

	void assignProject(Job* job, QString ProjectName="");
	TimeSpan getOverallTime()const;
	QStringList ProjectsList(bool highest = false);
	void addProject(Project* project);
	qint64 ProjectIndex(QString project);

	QString Name;
	TimeSpan Time;
	QList<Job*> Jobs;
	//QList <Project*> childItems; // subtasks

};

QDebug operator<< (QDebug d, const Project &item);
