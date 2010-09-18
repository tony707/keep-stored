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
	resize(900, 600);

	buildMenuBar();
	buildToolBar();
	buildWidgets();

	show();
}

void MainWindow::buildMenuBar()
{
	//TODO: Implement this
}

void MainWindow::buildToolBar()
{
	QToolBar *handlingToolBar = addToolBar("Handling");

	QLineEdit* search_widget = new QLineEdit();
	search_widget->setFixedWidth(200);
	QPushButton* search_button = new QPushButton(tr("Search"));
	QWidget* spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	d_add_action = handlingToolBar->addAction(tr("Add a resource"));
	d_edit_action = handlingToolBar->addAction(tr("Edit a resource"));
	d_remove_action = handlingToolBar->addAction(tr("Remove a resource"));

	handlingToolBar->addWidget(spacer);
	handlingToolBar->addWidget(search_widget);
	handlingToolBar->addWidget(search_button);
}

void MainWindow::buildWidgets()
{
	d_category_list = new QTreeView;
	d_resource_list = new QListView;
	d_resource_preview = new QWidget;

	QSplitter* vsplitter = new QSplitter(Qt::Vertical);
	vsplitter->addWidget(d_resource_list);
	vsplitter->addWidget(d_resource_preview);

	QSplitter* hsplitter = new QSplitter(Qt::Horizontal);
	hsplitter->addWidget(d_category_list);
	hsplitter->addWidget(vsplitter);

	setCentralWidget(hsplitter);
}

