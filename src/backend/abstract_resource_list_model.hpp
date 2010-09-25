/**
 * \file abstract_resource_list_model.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The AbstractResource list model class.
 */

#ifndef KEEP_STORED_ABSTRACT_RESOURCE_LIST_MODEL_HPP
#define KEEP_STORED_ABSTRACT_RESOURCE_LIST_MODEL_HPP

#include <QtGui>

#include <boost/shared_ptr.hpp>

#include <list>

class Category;
class AbstractResource;

class AbstractResourceListModel : public QAbstractListModel
{
	Q_OBJECT

	public:

		/**
		 * \brief Constructor.
		 */
		AbstractResourceListModel(boost::shared_ptr<Category> category, QObject *parent = 0);

		int rowCount(const QModelIndex &parent = QModelIndex()) const;

		int columnCount(const QModelIndex &parent = QModelIndex()) const;

		QVariant data(const QModelIndex &index, int role) const;

		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

		bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

		boost::shared_ptr<Category> category();

		boost::shared_ptr<AbstractResource> resource(int row);

		void addResource(boost::shared_ptr<AbstractResource> resource);

	private:

		/**
		 * \brief The category.
		 */
		boost::shared_ptr<Category> d_category;

};

#endif /* KEEP_STORED_ABSTRACT_RESOURCE_LIST_MODEL_HPP */


