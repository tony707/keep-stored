/**
 * \file main_window.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The main window class.
 */

#include "main_window.hpp"
#include "category_list_view.hpp"
#include "resource_list_view.hpp"
#include "resource_view.hpp"

#include "../backend/abstract_resource.hpp"
#include "../backend/category.hpp"
#include "../backend/configuration.hpp"
#include "../backend/category_list_model.hpp"
#include "../backend/abstract_resource_list_model.hpp"
#include "../backend/abstract_resource_list_model.hpp"

#include <QApplication>
#include <QtGui>

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	d_configuration(new Configuration())
{
	setWindowTitle(tr("Welcome on KeepStored"));

	buildMenuBar();
	buildWidgets();
	buildToolBar();
	setupActions();

	show();
}

void MainWindow::buildMenuBar()
{
	//TODO: Implement this
}

void MainWindow::buildWidgets()
{
	QList<boost::shared_ptr<Category> > category_list = d_configuration->loadConfigurationFile();
	d_category_list_model = new CategoryListModel(category_list);

	d_category_list_view = new CategoryListView();
	d_category_list_view->setModel(d_category_list_model);
	d_resource_list_view = new ResourceListView();
	d_resource_view = new ResourceView(category_list);
	d_resource_preview = new QWidget;

	QSplitter* vsplitter = new QSplitter(Qt::Vertical);
	vsplitter->addWidget(d_resource_list_view);
	vsplitter->addWidget(d_resource_preview);

	QSplitter* hsplitter = new QSplitter(Qt::Horizontal);
	hsplitter->addWidget(d_category_list_view);
	hsplitter->addWidget(vsplitter);

	setCentralWidget(hsplitter);
}

void MainWindow::buildToolBar()
{
	QToolBar *handlingToolBar = addToolBar("ToolBar");

	QLineEdit* search_widget = new QLineEdit();
	search_widget->setFixedWidth(200);

	QWidget* spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	d_add_action = handlingToolBar->addAction(QIcon(":/resources/add.png"), tr("Add"));
	d_setting_action = handlingToolBar->addAction(QIcon(":/resources/settings.png"), tr("Settings"));
	d_add_menu = new QMenu();
	d_add_category = d_add_menu->addAction(tr("Add a category"));
	d_add_resource = d_add_menu->addAction(tr("Add a resource"));
	d_add_action->setMenu(d_add_menu);

	handlingToolBar->addWidget(spacer);
	handlingToolBar->addWidget(search_widget);
	d_search_action = handlingToolBar->addAction(QIcon(":/resources/search.png"), tr("Search"));

}

void MainWindow::setupActions()
{
	connect(d_add_category, SIGNAL(triggered()), d_category_list_view, SLOT(addCategory()));
	connect(d_add_resource, SIGNAL(triggered()), d_resource_view, SLOT(show()));
	connect(d_add_action, SIGNAL(triggered()), this, SLOT(showAddMenu()));

	connect(d_category_list_view->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(updateResourceList(const QItemSelection &, const QItemSelection &)));
	connect(d_resource_list_view, SIGNAL(resourceEdited(int)), this, SLOT(editResource(int)));
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	d_configuration->saveConfigurationFile(d_category_list_model->categoryList());

	QMainWindow::closeEvent(event);
}

//SLOTS
void MainWindow::showAddMenu()
{
	d_add_menu->exec(QCursor::pos());
}

void MainWindow::updateResourceList(const QItemSelection & selected, const QItemSelection & deselected)
{
	Q_UNUSED(deselected);

	QModelIndex selected_index = selected.indexes().front();

	QSortFilterProxyModel *filterModel = new QSortFilterProxyModel();
	d_resource_list_model = new AbstractResourceListModel(d_category_list_model->categoryList().at(selected_index.row()));
	filterModel->setSourceModel(d_resource_list_model);
	d_resource_list_view->setModel(filterModel);
	d_resource_list_view->resizeColumnsToContents();
	d_resource_list_view->resizeRowsToContents();
	d_resource_list_view->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	connect(d_resource_view, SIGNAL(resourceAdded(boost::shared_ptr<Category>, boost::shared_ptr<AbstractResource>)), this, SLOT(addResource(boost::shared_ptr<Category>, boost::shared_ptr<AbstractResource>)), Qt::UniqueConnection);
}

void MainWindow::addResource(boost::shared_ptr<Category> category, boost::shared_ptr<AbstractResource> resource)
{

	if (d_resource_list_model->category() == category)
	{
		d_resource_list_model->addResource(resource);
	}
	else
	{
		category->addResource(resource);
	}
}

void MainWindow::editResource(int row)
{
	d_resource_view->loadResource(d_resource_list_model->resource(row), d_resource_list_model->category());
}
