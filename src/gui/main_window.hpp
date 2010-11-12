/**
 * \file main_window.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The main window class.
 */

#ifndef KEEP_STORED_MAIN_WINDOW_HPP
#define KEEP_STORED_MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QItemSelection>

#include <boost/shared_ptr.hpp>

class Category;
class Configuration;
class QTableView;
class CategoryListView;
class ResourceListView;
class CategoryListModel;
class AbstractCategory;
class AbstractResource;
class AbstractResourceListModel;
class ResourceView;
class QStackedWidget;
class QLineEdit;

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:

		/**
		 * \brief Constructor.
		 * \param parent The parent widget.
		 */
		MainWindow(QWidget* parent = NULL);

		public slots:

			void updateResourceList(const QItemSelection & selected, const QItemSelection & deselected);

		void updateCategorySelection();

		void updateResourcePreview(const QItemSelection &, const QItemSelection &);

		void findResources();

		void showAddMenu();

	private:
		/**
		 * \brief Build Application's Menu Bar.
		 */
		void buildMenuBar();

		/**
		 * \brief Build Application's Tool Bar.
		 */
		void buildToolBar();

		/**
		 * \brief Build MainWindows Widgets.
		 */
		void buildWidgets();

		void setupActions();

		void closeEvent(QCloseEvent* event);

		void findCategoryResources(AbstractCategory* parent_category, QString pattern, const QModelIndex& parent = QModelIndex());

	private:

		/**
		 * \brief The category list.
		 */
		CategoryListView* d_category_list_view;

		/**
		 * \brief The resource list.
		 */
		ResourceListView* d_resource_list_view;

		/**
		 * \brief The word list.
		 */
		CategoryListModel* d_category_list_model;

		/**
		 * \brief The resource list model.
		 */
		AbstractResourceListModel* d_resource_list_model;

		/**
		 * \brief The resource preview.
		 */
		QStackedWidget* d_resource_preview;

		/**
		 * \brief The configuration.
		 */
		boost::shared_ptr<Configuration> d_configuration;

		/**
		 * \brief The resource view (new/edit).
		 */
		ResourceView* d_resource_view;

		/**
		 * \brief The resource view (new/edit).
		 */
		AbstractCategory* d_search_category;

	private:

		QMenu* d_add_menu;

		QAction* d_setting_action;

		QAction* d_search_action;

		QLineEdit* d_search_edit;

		QAction* d_add_action;

		QAction* d_add_category;

		QAction* d_add_resource;


};

#endif /* KEEP_STORED_MAIN_WINDOW_HPP */
