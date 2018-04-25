#pragma once

#include <QItemDelegate>
#include "TimeSpan.h"

class CustomDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	CustomDelegate(QObject *parent=0);
	~CustomDelegate();
	void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	//virtual  QSize QAbstractItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
