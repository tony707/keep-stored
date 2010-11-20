/**
 * \file main.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The program entry point.
 */

#include "gui/main_window.hpp"

#include <QApplication>
#include <QMessageBox>
#include <QPlastiqueStyle>

#include <systools/os.hpp>

int main(int argc, char** argv)
{
	QApplication application(argc, argv);

#ifdef LINUX
	application.setStyle(new QPlastiqueStyle);
#endif

	application.setApplicationName("keep-stored");

	// Create the main window.
	MainWindow mainWindow;

	int result = 0;

	try
	{
		result = application.exec();
	}
	catch (std::exception& ex)
	{
		QMessageBox::critical(NULL, QObject::tr("Ooops!"), QObject::tr("An unexpected exception was thrown. The program must now terminate.\n\nWe apologize for the inconvenience. You may report this problem by writing to tinou@tinou.fr.\n\nThe error was:\n\n%1").arg(QString(ex.what())));
	}

	return result;
}
