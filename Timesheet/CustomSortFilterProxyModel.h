#pragma once

#include <QSortFilterProxyModel>

class CustomSortFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	CustomSortFilterProxyModel(QObject* parent = 0);
	~CustomSortFilterProxyModel();
	bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

};
