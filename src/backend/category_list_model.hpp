/**
 * \file category_list_model.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The category list model class.
 */

#ifndef KEEP_STORED_CATEGORY_LIST_MODEL_HPP
#define KEEP_STORED_CATEGORY_LIST_MODEL_HPP

#include <QtGui>

#include <boost/shared_ptr.hpp>

#include <list>

class AbstractCategory;

class CategoryListModel : public QAbstractItemModel
{
	Q_OBJECT

	public:

		/**
		 * \brief Constructor.
		 */
		CategoryListModel(boost::shared_ptr<AbstractCategory> root_category, QObject *parent = 0);

		int rowCount(const QModelIndex &parent = QModelIndex()) const;

		int columnCount(const QModelIndex &parent = QModelIndex()) const;

		QVariant data(const QModelIndex &index, int role) const;

		Qt::ItemFlags flags(const QModelIndex &index) const;

		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

		QModelIndex parent(const QModelIndex &index) const;

    //bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

		bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());

		bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

		boost::shared_ptr<AbstractCategory> rootCategory();

		boost::shared_ptr<AbstractCategory> searchCategory();

	private:

		/**
		 * \brief The root category.
		 */
		boost::shared_ptr<AbstractCategory> d_root_category;

};

#endif /* KEEP_STORED_CATEGORY_LIST_MODEL_HPP */


