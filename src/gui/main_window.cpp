/**
 * \file main_window.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The main window class.
 */

#include "main_window.hpp"

#include <QApplication>
#include <QtGui>

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent)
{
	setWindowTitle(tr("keep-stored"));
	show();
}

void MainWindow::buildFileMenu()
{
	//TODO: Implement this
}

void MainWindow::buildMenuBar()
{
	//TODO: Implement this
}

void MainWindow::buildWidgets()
{
	//TODO: Implement this
}

