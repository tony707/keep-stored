/**
 * \file resource_list_view.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The resource list view class.
 */

#ifndef KEEP_STORED_RESOURCE_LIST_VIEW_HPP
#define KEEP_STORED_RESOURCE_LIST_VIEW_HPP

#include <QTableView>

#include <boost/shared_ptr.hpp>

class QMenu;
class QAction;
class AbstractResource;

class ResourceListView : public QTableView
{
	Q_OBJECT

	public:

		/**
		 * \brief Constructor.
		 */
		ResourceListView(QWidget* parent = 0);

		void contextMenuEvent(QContextMenuEvent*);

		void dragEnterEvent(QDragEnterEvent *event);
		void dragMoveEvent(QDragMoveEvent *event);
		void dropEvent(QDropEvent *event);

	private:

		QMenu* d_context_menu;

		QAction* d_edit_action;

		QAction* d_delete_action;

	signals:
		void resourceAboutToEdit(QModelIndex);
		void resourceSelected(boost::shared_ptr<AbstractResource> resource);
		void resourceDropped(const QMimeData* mime_data);

	public slots:

		void editResource();
		void deleteResource();
};

#endif /* KEEP_STORED_RESOURCE_LIST_VIEW_HPP */

