/**
 * \file new_resource_view.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The new resource view class.
 */

#ifndef KEEP_STORED_RESOURCE_VIEW_HPP
#define KEEP_STORED_RESOURCE_VIEW_HPP

#include <QWidget>
#include <QModelIndex>

#include <boost/shared_ptr.hpp>

class QLineEdit;
class QPushButton;
class QComboBox;
class QItemSelection;
class AbstractResourceListModel;
class CategoryListModel;
class AbstractCategory;

class ResourceView : public QWidget
{
	Q_OBJECT

	public:

		/**
		 * \brief Constructor.
		 */
		ResourceView(CategoryListModel* category_list_model, AbstractResourceListModel* resource_list_model, QWidget* parent = 0);

		void setResourceListModel(AbstractResourceListModel* resource_list_model);

	protected:
		void showEvent(QShowEvent* event);

		void appendCategories(AbstractCategory* parent_category, const QModelIndex& parent = QModelIndex());

	private:

		QModelIndex d_index;

		QLineEdit* d_title_edit;
		QLineEdit* d_author_edit;
		QLineEdit* d_taglist_edit;
		QLineEdit* d_location_edit;
		QPushButton* d_submit_button;
		QComboBox* d_combo_category_list;

		CategoryListModel* d_category_list_model;
		AbstractResourceListModel* d_resource_list_model;

signals:
		void categoryChanged();

public slots:

	void save();

	void loadResource(QModelIndex);
};

Q_DECLARE_METATYPE(QModelIndex);

#endif /* KEEP_STORED_RESOURCE_VIEW_HPP */

