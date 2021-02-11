#include "TreeItem.h"
#include <QStringList>

TreeItem::TreeItem(TreeItem *parent)
{
	parentItem = parent;
}
TreeItem::~TreeItem()
{
	qDebug() << "Usuwam TreeItem!";
	if (parentItem)
	{
		parentItem->childItems.removeAll(this);
		for (int i = 0; i < childItems.length(); i++)
		{
			childItems[i]->setParentItem(parentItem);
		}
	}

}

TreeItem *TreeItem::child(int number)
{
	return childItems.value(number);
}

void TreeItem::addChild(TreeItem* Child)
{
	Child->setParentItem(this);
	childItems.append(Child);
}

int TreeItem::childCount() const
{
	return childItems.count();
}

int TreeItem::childNumber() const //row()
{
	if (parentItem)
		return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

	return 0;
}

int TreeItem::columnCount() const
{
	return itemData.count();
}

QVariant TreeItem::data(int column) const
{
	return itemData.value(column);
}

bool TreeItem::insertChildren(int position, int count, int columns)
{
	if (position < 0 || position > childItems.size())
		return false;

	for (int row = 0; row < count; ++row) {

		TreeItem *item = new TreeItem(this);

		childItems.insert(position, item);
	}

	return true;
}

bool TreeItem::insertColumns(int position, int columns)
{
	if (position < 0 || position > columnCount())
		return false;

	for (int column = 0; column < columns; ++column)
		itemData.insert(position, QVariant());

	foreach(TreeItem *child, childItems)
		child->insertColumns(position, columns);

	return true;
}

TreeItem *TreeItem::parent()
{
	return parentItem;
}

bool TreeItem::removeChildren(int position, int count)
{
	if (position < 0 || position + count >= childItems.size())
		return false;

	for (int row = 0; row < count; ++row)
		delete childItems.takeAt(position);

	return true;
}

bool TreeItem::removeColumns(int position, int columns)
{
	if (position < 0 || position + columns > itemData.size())
		return false;

	for (int column = 0; column < columns; ++column)
		itemData.remove(position);

	foreach(TreeItem *child, childItems)
		child->removeColumns(position, columns);

	return true;
}

bool TreeItem::setData(int column, const QVariant &value)
{
	if (column < 0 || column >= itemData.size())
		return false;

	itemData[column] = value;
	return true;
}

void TreeItem::addChildren(QList<TreeItem*>List)
{
	for (qint64 i = 0; i < List.length(); i++)
	{
		addChild(List.at(i));
	}
}
