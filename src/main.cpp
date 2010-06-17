/**
 * \file main.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The program entry point.
 */

#include "gui/main_window.hpp"

#include <QApplication>

int main(int argc, char** argv)
{
	QApplication application(argc, argv);

	application.setApplicationName("keep-stored");

	// Create the main window.
	MainWindow mainWindow;

	return application.exec();
}
