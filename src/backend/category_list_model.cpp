/**
 * \file category_list_model.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The category list model class.
 */

#include "category_list_model.hpp"

#include "abstract_category.hpp"
#include "default_category.hpp"
#include "string_tools.hpp"

CategoryListModel::CategoryListModel(boost::shared_ptr<AbstractCategory> root_category, QObject *parent) :
	QAbstractItemModel(parent),
	d_root_category(root_category)
{
}

int CategoryListModel::rowCount(const QModelIndex &parent) const
{
	boost::shared_ptr<AbstractCategory> parent_category;

	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
		parent_category = d_root_category;
	else
		parent_category = boost::shared_ptr<AbstractCategory>(static_cast<AbstractCategory*>(parent.internalPointer()));

	return parent_category->childCount();
}

int CategoryListModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
	{
		boost::shared_ptr<AbstractCategory> category = boost::shared_ptr<AbstractCategory>(static_cast<AbstractCategory*>(parent.internalPointer()));
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

	boost::shared_ptr<AbstractCategory> category = boost::shared_ptr<AbstractCategory>(static_cast<AbstractCategory*>(index.internalPointer()));

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
	{
		return Qt::ItemIsEnabled;
	}

	//return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
	return QAbstractItemModel::flags(index);
}

QModelIndex CategoryListModel::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
	{
		return QModelIndex();
	}

	boost::shared_ptr<AbstractCategory> parent_category;

	if (!parent.isValid())
	{
		parent_category = d_root_category;
	}
	else
	{
		parent_category = boost::shared_ptr<AbstractCategory>(static_cast<AbstractCategory*>(parent.internalPointer()));
	}

	boost::shared_ptr<AbstractCategory> child_category = parent_category->childAt(row);

	if (child_category)
	{
		return createIndex(row, column, child_category.get());
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

	boost::shared_ptr<AbstractCategory> child_category = boost::shared_ptr<AbstractCategory>(static_cast<AbstractCategory*>(index.internalPointer()));

	boost::shared_ptr<AbstractCategory> parent_category = child_category->parent();

	if (child_category == parent_category)
	{
		return QModelIndex();
	}

	return createIndex(parent_category->row(), 0, parent_category.get());

}

//bool CategoryListModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//	if (index.isValid() && role == Qt::EditRole)
//	{
//		d_category_list.at(index.row())->setTitle(value.toString());
//		emit dataChanged(index, index);
//		return true;
//	}
//
//	return false;
//}

bool CategoryListModel::insertRows(int position, int rows, const QModelIndex &index)
{
	Q_UNUSED(index);

	beginInsertRows(QModelIndex(), position, position+rows-1);

	for (int row = 0; row < rows; ++row)
	{
		//d_category_list.insert(position, boost::shared_ptr<AbstractCategory>(new DefaultCategory()));
	}

	endInsertRows();

	return true;
}

bool CategoryListModel::removeRows(int position, int rows, const QModelIndex &index)
{
	Q_UNUSED(index);

	beginRemoveRows(QModelIndex(), position, position+rows-1);

	for (int row = 0; row < rows; ++row)
	{
		//boost::shared_ptr<AbstractCategory> category = d_category_list.at(position);

		//if (category->resourceList().count() > 0)
		//{
		//	QMessageBox::information(NULL, tr("Information"), tr("Please delete all attached resources before deleting this category."));
		//}
		//else
		//{
		//	d_category_list.removeAt(position);
		//}
	}

	endRemoveRows();

	return true;
}

boost::shared_ptr<AbstractCategory> CategoryListModel::rootCategory()
{
	return d_root_category;
}

boost::shared_ptr<AbstractCategory> CategoryListModel::searchCategory()
{
	boost::shared_ptr<AbstractCategory> search_category;

	BOOST_FOREACH(boost::shared_ptr<AbstractCategory> category, d_root_category->children())
	{
		if (category->type() == AbstractCategory::Search)
		{
			search_category = category;
			break;
		}
	}

	return search_category;
}
