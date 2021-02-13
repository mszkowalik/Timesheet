#pragma once
#include <QList>
#include <qdebug.h>
#include <QVariant>
#include <QVector>

class TreeItem
{
public:
	TreeItem(TreeItem *parent = 0);
    ~TreeItem();

    TreeItem *child(int number);
    int childCount() const;
    virtual int columnCount() const;
    virtual QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    TreeItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    virtual bool setData(int column, const QVariant &value);
	void setParentItem(TreeItem* parent) { parentItem = parent; };
	void addChild(TreeItem* Child);
	void addChildren(QList<TreeItem*>List);
	bool hasCheckBox = false;


    QList<TreeItem*> childItems;
	QVector<QVariant> itemData;
    TreeItem *parentItem;
};
Q_DECLARE_METATYPE(TreeItem*);