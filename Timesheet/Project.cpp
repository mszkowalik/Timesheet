#include "Project.h"



Project::Project(Project* parent) : TreeItem(parent)
{
}


Project::~Project()
{
	Jobs.clear(); // dont remove item, if you remove any of Jobs, you will also remove items from TreeView
	//but it is good idea to remove all project descendants;
	while(childItems.length())
	{
		delete childItems.takeLast();
	}
}

QStringList Project::ProjectsList(bool highest)
{

	QStringList ret;
	Project* proj;
	if (!childItems.length())
		ret.append(Name);
	else
		for (int i = 0; i < childItems.length(); i++)
		{
			proj = (Project*)childItems.at(i);
			foreach(QString name, proj->ProjectsList())
			{
				if (!highest)
					ret.append(Name + "/" + name);
				else
					ret.append(name);
			}
		}

	return ret;
}
qint64 Project::ProjectIndex(QString project)
{
	for (qint64 i = 0; i < childItems.length(); i++)
	{
		Project* proj = (Project*)childItems.at(i);
		if (proj->Name == project)
			return i;
	}
	return -1;
}
TimeSpan Project::getOverallTime()const
{
	TimeSpan t;
	Project* proj;
	if (childItems.length())
		for (int i = 0; i < childItems.length(); i++)
		{
			proj = (Project*)childItems.at(i);
			t += proj->getOverallTime();
		}
	else
		t = Time;
	return t;
}
void Project::addProject(Project* p)
{
	if (childItems.indexOf(p) == -1)
	{
		addChild(p);
	}
}
void Project::assignProject(Job* job, QString ProjectName)
{
	QString OrigProj;
	if (ProjectName == "")
		OrigProj = job->getProject();
	else OrigProj = ProjectName;

	QString RootProjectName = OrigProj.mid(0, OrigProj.indexOf("/"));
	Project* proj;


	int ProjIndex = ProjectIndex(RootProjectName);
	if (ProjIndex == -1)
	{
		proj = new Project;
		addProject(proj);
		proj->Name = RootProjectName;
		//proj->Time = job->getDuration(); // later on it will update itself
	}
	else
		proj = (Project*)childItems.at(ProjIndex);

	if (OrigProj == RootProjectName)
	{
		// there are no more subtasks, just add job to the list and return
		proj->Jobs.append(job);
		proj->Time += job->getDuration();
		return;
	}
	else
	{
		QString Assign = OrigProj.mid(OrigProj.indexOf("/") + 1, -1);
		//qDebug() << Assign;
		proj->assignProject(job, Assign);
		// we must go deeper. call "assign Project on proj, and pass everything after /, it will tahe care of creating new or appending them;
	}
}
QVariant Project::data(int column) const
{

	switch (column)
	{
	case 0:
		return QVariant::fromValue(Name);
		break;
	case 1:
		return QVariant::fromValue<TimeSpan>(getOverallTime());
		break;
	default:
		return QVariant();
	}
}
int Project::columnCount() const
{
	return 2;
}


QDebug operator<< (QDebug d, const Project &item) {
	d << endl << "--------------------" << endl;
	d << "Company: " << item.Name << endl;
	d << "Overall time " << item.getOverallTime() << endl;
	d << "Projects: " << endl;
	for (int i = 0; i < item.childItems.length(); i++)
	{
		Project *p = (Project*)item.childItems.at(i);
		d << "Name: " << p->Name << endl;
		d << "Jobs no.:" << p->Jobs.length() << endl;
		d << "Time :" << p->Time << endl;
	}

	return d;
}