#include "CustomSortFilterProxyModel.h"
#include <QDebug>
#include <QDate>
#include "Constants.h"
CustomSortFilterProxyModel::CustomSortFilterProxyModel(QObject* parent) : QSortFilterProxyModel(parent)
{
}

CustomSortFilterProxyModel::~CustomSortFilterProxyModel()
{
}
bool CustomSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
	if (left.data().canConvert<QDateTime>())
	{
		return left.data().toDateTime() < right.data().toDateTime();
	}
	else  if (left.data().canConvert<QString>())
	{
		return left.data().toString() < right.data().toString();
	}
	else {
		return false;
	}

}