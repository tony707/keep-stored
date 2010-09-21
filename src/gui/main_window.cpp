/**
 * \file main_window.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The main window class.
 */

#include "main_window.hpp"
#include "../backend/configuration.hpp"
#include "../backend/category_list_model.hpp"

#include <QApplication>
#include <QtGui>

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	d_configuration(new Configuration())
{
	setWindowTitle(tr("Welcome on KeepStored"));
	resize(900, 600);

	QList<boost::shared_ptr<Category> > category_list = d_configuration->loadConfigurationFile();
	d_category_list_model = new CategoryListModel(category_list);

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
	QPushButton* search_button = new QPushButton(QIcon(":/resources/search.png"), tr("Search"));
	QWidget* spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	d_add_action = handlingToolBar->addAction(QIcon(":/resources/add.png"), tr("Add"));
	d_edit_action = handlingToolBar->addAction(QIcon(":/resources/edit.png"), tr("Edit"));
	d_remove_action = handlingToolBar->addAction(QIcon(":/resources/delete.png"), tr("Delete"));

	handlingToolBar->addWidget(spacer);
	handlingToolBar->addWidget(search_widget);
	handlingToolBar->addWidget(search_button);
}

void MainWindow::buildWidgets()
{
	d_category_list_view = new QTreeView;
	d_category_list_view->setModel(d_category_list_model);
	d_resource_list_view = new QListView;
	d_resource_preview = new QWidget;

	QSplitter* vsplitter = new QSplitter(Qt::Vertical);
	vsplitter->addWidget(d_resource_list_view);
	vsplitter->addWidget(d_resource_preview);

	QSplitter* hsplitter = new QSplitter(Qt::Horizontal);
	hsplitter->addWidget(d_category_list_view);
	hsplitter->addWidget(vsplitter);

	setCentralWidget(hsplitter);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	d_configuration->saveConfigurationFile(d_category_list_model->categoryList());

	QMainWindow::closeEvent(event);
}
