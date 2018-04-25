#include <QtWidgets>

#include "treeitem.h"
#include "TreeModel.h"


TreeModel::TreeModel(QObject *parent,int columns)
	: QAbstractItemModel(parent)
{
	rootItem = new TreeItem();
	rootItem->itemData.resize(columns);
}
 
TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
}
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole&& role != Qt::CheckStateRole && role != 600)
        return QVariant();


    TreeItem *item = getItem(index);
	if (role == Qt::CheckStateRole && index.column() == 4 && item->hasCheckBox)
		return QVariant((item->data(index.column()).toInt() ? Qt::Checked : Qt::Unchecked));
	else if(role == Qt::CheckStateRole) 
		return QVariant();
	if (role == 600)
		return item->data(-1);

    return item->data(index.column());
}
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

	Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable| QAbstractItemModel::flags(index);

	TreeItem* item = getItem(index);
	if ((index.column() == 2 || index.column() == 3) && item->childCount() == 0)
		flags |= Qt::ItemIsEditable;

    return flags;
}
TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}
QVariant TreeModel::headerData(int section, Qt::Orientation orientation,int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    TreeItem *parentItem = getItem(parent);

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
QModelIndex TreeModel::getIndex(int row, int column, TreeItem* item)
{
	if (item)
	{
		return createIndex(row, column, item);
	}
	else
		return QModelIndex();
}
bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}
bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}
bool TreeModel::insertRows(TreeItem* parent, TreeItem*child)
{
	int row = rootItem->childItems.count();
	QModelIndex parentInd = getIndex(row, 0, rootItem);

	bool success;

	beginInsertRows(parentInd, row, row);
	success = true;
	rootItem->addChild(child);
	endInsertRows();

	return success;
}
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}
bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;
	//qDebug() << parent.data(0);
	//layoutAboutToBeChanged();
    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();
	//layoutChanged();
    return success;
}
int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}
bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}
bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}


