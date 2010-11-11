/**
 * \file category_list_view.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The category list view class.
 */

#ifndef KEEP_STORED_CATEGORY_LIST_VIEW_HPP
#define KEEP_STORED_CATEGORY_LIST_VIEW_HPP

#include <QTreeView>

class QMenu;
class QAction;

class CategoryListView : public QTreeView
{
	Q_OBJECT

	public:

		/**
		 * \brief Constructor.
		 */
		CategoryListView(QWidget* parent = 0);

		void contextMenuEvent(QContextMenuEvent*);

	private:

		void dragEnterEvent(QDragEnterEvent *event);
		void dragMoveEvent(QDragMoveEvent *event);
		void dropEvent(QDropEvent *event);


		QMenu* d_context_menu;

		QItemSelectionModel* d_selection_model;

		QAction* d_add_main_action;

		QAction* d_add_child_action;

		QAction* d_delete_action;

		signals:

		void resourceDropped(const QMimeData* mime_data);

		public slots:

			void addChildCategory();

			void addMainCategory();

			void deleteCategory();
};

#endif /* KEEP_STORED_CATEGORY_LIST_VIEW_HPP */

