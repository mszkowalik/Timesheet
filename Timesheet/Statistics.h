#pragma once
#include <qwidget.h>
#include "Job.h"
#include "DayItem.h"
#include "Project.h"
#include "TreeModel.h"

class Statistics
{
public:
	Statistics();
	~Statistics();
	void setModel(TreeModel* _model);
	void addPosition(Job *Item);
	QStringList GetCompaniesList();
	qint64 CompanyIndex(QString Company);


	QList<Project*> Companies;
	TreeModel* model;
};

