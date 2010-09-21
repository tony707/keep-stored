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

class Category;

class CategoryListModel : public QAbstractListModel
{
	Q_OBJECT

	public:

		/**
		 * \brief Constructor.
		 */
		CategoryListModel(QList<boost::shared_ptr<Category> > category_list, QObject *parent = 0);

		int rowCount(const QModelIndex &parent = QModelIndex()) const;

		QVariant data(const QModelIndex &index, int role) const;

		QList<boost::shared_ptr<Category> > categoryList();

	private:

		/**
		 * \brief The category list.
		 */
		QList<boost::shared_ptr<Category> > d_category_list;

};

#endif /* KEEP_STORED_CATEGORY_LIST_MODEL_HPP */


