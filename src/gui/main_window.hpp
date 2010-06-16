/**
 * \file main_window.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The main window class.
 */

#ifndef KEEP_STORED_MAIN_WINDOW_HPP
#define KEEP_STORED_MAIN_WINDOW_HPP

#include <QMainWindow>

class ConfigurationWindow;

class QTimer;
class QAction;

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
		 * \brief Build Application's File Menu.
		 */
		 void buildFileMenu();

		/**
		 * \brief Build Application's Menu Bar.
		 */
		 void buildMenuBar();

		/**
		 * \brief Build MainWindows Widgets.
		 */
		 void buildWidgets();

};

#endif /* KEEP_STORED_MAIN_WINDOW_HPP */
