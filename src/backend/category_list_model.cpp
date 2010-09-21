/**
 * \file category_list_model.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The category list model class.
 */

#include "category_list_model.hpp"

#include "Category.hpp"

CategoryListModel::CategoryListModel(QList<boost::shared_ptr<Category> > category_list, QObject *parent) :
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

	if (role == Qt::DisplayRole)
	{
		return QString::fromStdString(d_category_list.at(index.row())->title());
	}
	else
	{
		return QVariant();
	}

}

QList<boost::shared_ptr<Category> > CategoryListModel::categoryList()
{
	return d_category_list;
}
