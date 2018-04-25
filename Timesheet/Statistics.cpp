#include "Statistics.h"



Statistics::Statistics()
{
}


Statistics::~Statistics()
{
}

QStringList Statistics::GetCompaniesList()
{
	QStringList ret;
	for (int i = 0; i < Companies.length(); i++)
	{
		ret.append(Companies.at(i)->Name);
	}
	ret.removeAll("");
	return ret;
}
void Statistics::addPosition(Job *Item)
{
	model->layoutAboutToBeChanged();
	qint64 index = CompanyIndex(Item->getCompany()); //company index in list
	Project *Comp;
	if (index == -1) // if does not exist, create new company;
	{
		Comp = new Project; // create new company
		Comp->Name = Item->getCompany();
		Companies.append(Comp); // append to list
	}
	else
		Comp = Companies[index];

	Comp->assignProject(Item);// this makes sure, that project is added properly into subtasks;

	if (model->rootItem->childItems.indexOf(Comp) == -1)
	{
		model->rootItem->addChild(Comp);
	}
	model->layoutChanged();
	return;
}


qint64 Statistics::CompanyIndex(QString Company)
{
	for (qint64 i = 0; i < Companies.length(); i++)
	{
		if (Companies.at(i)->Name == Company)
		{
			return i;
		}
	}
	return -1;
}

void Statistics::setModel(TreeModel* _model)
{
	model = _model;
}