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

class AbstractCategory;
class AbstractResource;

class AbstractResourceListModel : public QAbstractListModel
{
	Q_OBJECT

	public:

		static void prepareResourceAddition(AbstractResourceListModel*, QString path);

		/**
		 * \brief Constructor.
		 */
		AbstractResourceListModel(QObject *parent = 0);

		int rowCount(const QModelIndex &parent = QModelIndex()) const;

		int columnCount(const QModelIndex &parent = QModelIndex()) const;

		QVariant data(const QModelIndex &index, int role) const;

		Qt::ItemFlags flags(const QModelIndex &index) const;

		bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

		bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

		AbstractCategory* category();

		void setCategory(AbstractCategory* category);

		boost::shared_ptr<AbstractResource> resource(int row);

	public slots:

		void addResource(boost::shared_ptr<AbstractResource> resource);

		void addResource(const QMimeData* mime_data);

	private:

		/**
		 * \brief The category.
		 */
		AbstractCategory* d_category;

};

#endif /* KEEP_STORED_ABSTRACT_RESOURCE_LIST_MODEL_HPP */


