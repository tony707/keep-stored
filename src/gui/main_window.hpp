/**
 * \file main_window.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The main window class.
 */

#ifndef KEEP_STORED_MAIN_WINDOW_HPP
#define KEEP_STORED_MAIN_WINDOW_HPP

#include <QMainWindow>

class ConfigurationWindow;

class QTreeView;
class QListView;

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

		 /**
			* \brief The category list.
			*/
		 QTreeView* d_category_list;

		 /**
			* \brief The resource list.
			*/
		 QListView* d_resource_list;

		 /**
			* \brief The resource list.
			*/
		 QWidget* d_resource_preview;

		 QAction* d_add_action;
		 QAction* d_edit_action;
		 QAction* d_remove_action;

};

#endif /* KEEP_STORED_MAIN_WINDOW_HPP */
