/**
 * \file category_list_model.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The category list model class.
 */

#include "category_list_model.hpp"

#include "abstract_category.hpp"
#include "default_category.hpp"
#include "string_tools.hpp"

CategoryListModel::CategoryListModel(QList<boost::shared_ptr<AbstractCategory> > category_list, QObject *parent) :
	QAbstractListModel(parent),
	d_category_list(category_list)
{
}

int CategoryListModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return d_category_list.size();
}

QVariant CategoryListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	if (index.row() >= d_category_list.size())
	{
		return QVariant();
	}

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		return d_category_list.at(index.row())->title();
	}

	if (role == Qt::DecorationRole)
	{
		return QIcon(":/resources/category.png");
	}


	return QVariant();
}


Qt::ItemFlags CategoryListModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return Qt::ItemIsEnabled;
	}

	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CategoryListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (index.isValid() && role == Qt::EditRole)
	{
		d_category_list.at(index.row())->setTitle(value.toString());
		emit dataChanged(index, index);
		return true;
	}

	return false;
}

bool CategoryListModel::insertRows(int position, int rows, const QModelIndex &index)
{
	Q_UNUSED(index);

	beginInsertRows(QModelIndex(), position, position+rows-1);

	for (int row = 0; row < rows; ++row)
	{
		d_category_list.insert(position, boost::shared_ptr<AbstractCategory>(new DefaultCategory()));
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
		boost::shared_ptr<AbstractCategory> category = d_category_list.at(position);

		if (category->resourceList().count() > 0)
		{
			//TODO: Popup msgbox, Please delete all attached resources of this category before deleting it.
		}
		else
		{
			d_category_list.removeAt(position);
		}
	}

	endRemoveRows();

	return true;
}

QList<boost::shared_ptr<AbstractCategory> > CategoryListModel::categoryList()
{
	return d_category_list;
}
