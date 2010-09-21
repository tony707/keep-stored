/**
 * \file main_window.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The main window class.
 */

#ifndef KEEP_STORED_MAIN_WINDOW_HPP
#define KEEP_STORED_MAIN_WINDOW_HPP

#include <QMainWindow>

#include <boost/shared_ptr.hpp>

class Configuration;
class QTreeView;
class QListView;
class CategoryListModel;

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:

		/**
		 * \brief Constructor.
		 * \param parent The parent widget.
		 */
		MainWindow(QWidget* parent = NULL);

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

		 void closeEvent(QCloseEvent* event);

		 /**
			* \brief The category list.
			*/
		 QTreeView* d_category_list_view;

		 /**
			* \brief The resource list.
			*/
		 QListView* d_resource_list_view;

		 /**
			* \brief The resource list.
			*/
		 CategoryListModel* d_category_list_model;

		 /**
			* \brief The resource list.
			*/
		 QWidget* d_resource_preview;

		 QAction* d_add_action;

		 QAction* d_edit_action;

		 QAction* d_remove_action;

		 boost::shared_ptr<Configuration> d_configuration;

};

#endif /* KEEP_STORED_MAIN_WINDOW_HPP */
