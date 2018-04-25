#include "CustomDelegate.h"
#include <qdebug.h>
#include <qapplication.h>
#include <QDateTime>
#include "Constants.h"
#include "JobStatus.h"

CustomDelegate::CustomDelegate(QObject *parent)
	: QItemDelegate(parent)
{
}

CustomDelegate::~CustomDelegate()
{
}

void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	if (index.data().canConvert<TimeSpan>())
	{
		QVariant var = index.data();
		TimeSpan ts = var.value<TimeSpan>();
		QStyleOptionViewItemV4 myOption = option;
		myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;
		QString text = ts.toString();
		if (index.child(0, 0).isValid()) // if not end-element of tree, it means that value is sum of children
		{
			text.prepend(" ");
			text.prepend(QChar(0x03A3));

		}

		myOption.text = text;
		drawDisplay(painter, myOption, myOption.rect, text);
		drawFocus(painter, myOption, myOption.rect);
	}
	else if (index.data().canConvert<JobStatus>())
	{
		QVariant var = index.data();
		JobStatus ts = var.value<JobStatus>();
		QStyleOptionViewItemV4 myOption = option;
		myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;
		QString text = ts.getStatusString();
		myOption.text = text;

		drawDisplay(painter, myOption, myOption.rect, text);
		drawFocus(painter, myOption, myOption.rect);
	}
	else if (index.data().type() == QVariant::List)
	{
		QList<QVariant> List = index.data().toList();
		if (List.size() == 2)
		{
			QString text;
			if (List.at(1).toDate() > List.at(0).toDate())
				text = List.at(0).toDateTime().time().toString(TIMEFORMATSHORT) + " to " + List.at(1).toDateTime().time().toString(TIMEFORMATSHORT) + " " + NEXT_DAY;
			else
				text = List.at(0).toDateTime().time().toString(TIMEFORMATSHORT) + " to " + List.at(1).toDateTime().time().toString(TIMEFORMATSHORT);


			QStyleOptionViewItemV4 myOption = option;
			myOption.displayAlignment = Qt::AlignLeft | Qt::AlignHCenter;
			myOption.text = text;

			drawDisplay(painter, myOption, myOption.rect, text);
			drawFocus(painter, myOption, myOption.rect);
		}
	}
	else if (index.data().type() == QVariant::Date)
	{
		QString text = index.data().toDate().toString(DATEFORMAT);
		QStyleOptionViewItemV4 myOption = option;
		myOption.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;
		myOption.text = text;

		drawDisplay(painter, myOption, myOption.rect, text);
		drawFocus(painter, myOption, myOption.rect);
	}
	else if (index.data().type() == QVariant::String)
	{
		QString text = index.data().toString();
		QStyleOptionViewItemV4 myOption = option;
		if (index.column() == 0)
			myOption.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;
		else if (index.column() == 3)
			myOption.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;
		else
			myOption.displayAlignment = Qt::AlignCenter;
		myOption.text = text;
		drawDisplay(painter, myOption, myOption.rect, text);
		drawFocus(painter, myOption, myOption.rect);
	}
	else // it's just a common column. Live it in default way
		QItemDelegate::paint(painter, option, index);
}
