/**
 * \file category_list_model.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The category list model class.
 */

#include "category_list_model.hpp"

#include "abstract_category.hpp"
#include "default_category.hpp"
#include "string_tools.hpp"

CategoryListModel::CategoryListModel(AbstractCategory* root_category, QObject *parent) :
	QAbstractItemModel(parent),
	d_root_category(root_category)
{
	d_root_category->setTitle("Categories");
}

CategoryListModel::~CategoryListModel()
{
	delete d_root_category;
}

int CategoryListModel::rowCount(const QModelIndex &parent) const
{
	AbstractCategory* parent_category;

	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
		parent_category = d_root_category;
	else
		parent_category = static_cast<AbstractCategory*>(parent.internalPointer());

	return parent_category->childCount();
}

int CategoryListModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
	{
		AbstractCategory* category = static_cast<AbstractCategory*>(parent.internalPointer());
		return category->columnCount();
	}
	else
	{
		return d_root_category->columnCount();
	}
}

QVariant CategoryListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	AbstractCategory* category = static_cast<AbstractCategory*>(index.internalPointer());

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		return category->title();
	}

	if (role == Qt::DecorationRole)
	{
		if (category->type() == AbstractCategory::Default)
		{
			return QIcon(":/resources/category.png");
		}
		else if(category->type() == AbstractCategory::Search)
		{
			return QIcon(":/resources/search_category.gif");
		}
	}

	return QVariant();
}


Qt::ItemFlags CategoryListModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;

}

QVariant CategoryListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	Q_UNUSED(section);

	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return d_root_category->title();

	return QVariant();
}


QModelIndex CategoryListModel::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
	{
		return QModelIndex();
	}

	AbstractCategory* parent_category;

	if (!parent.isValid())
	{
		parent_category = d_root_category;
	}
	else
	{
		parent_category = static_cast<AbstractCategory*>(parent.internalPointer());
	}

	AbstractCategory* child_category = parent_category->childAt(row);

	if (child_category)
	{
		return createIndex(row, column, child_category);
	}
	else
	{
		return QModelIndex();
	}

}

QModelIndex CategoryListModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return QModelIndex();
	}

	AbstractCategory* child_category = static_cast<AbstractCategory*>(index.internalPointer());
	AbstractCategory* parent_category = child_category->parent();

	if (d_root_category == parent_category)
	{
		return QModelIndex();
	}

	return createIndex(parent_category->row(), 0, parent_category);

}

bool CategoryListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (index.isValid() && role == Qt::EditRole)
	{
		AbstractCategory* category = static_cast<AbstractCategory*>(index.internalPointer());
		category->setTitle(value.toString());
		emit dataChanged(index, index);
		return true;
	}

	return false;
}

bool CategoryListModel::insertRows(int position, int rows, const QModelIndex &index)
{
	Q_UNUSED(rows);

	beginInsertRows(index, position, position);

	AbstractCategory* category;

	if (index.isValid())
	{
		category = static_cast<AbstractCategory*>(index.internalPointer());
	}
	else
	{
		category = d_root_category;
	}

	category->appendChild(new DefaultCategory("New Category"));

	endInsertRows();

	return true;
}

bool CategoryListModel::removeRows(int position, int rows, const QModelIndex &index)
{
	Q_UNUSED(rows);

	beginRemoveRows(index, position, position);

	AbstractCategory* category = static_cast<AbstractCategory*>(index.internalPointer());

	category->parent()->removeChild(category->row());

	endRemoveRows();

	return true;
}

AbstractCategory* CategoryListModel::rootCategory()
{
	return d_root_category;
}

AbstractCategory* CategoryListModel::searchCategory()
{
	AbstractCategory* search_category;

	BOOST_FOREACH(AbstractCategory* category, d_root_category->children())
	{
		if (category->type() == AbstractCategory::Search)
		{
			search_category = category;
			break;
		}
	}

	return search_category;
}
