/**
 * \file main_window.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The main window class.
 */

#include "main_window.hpp"
#include "category_list_view.hpp"
#include "resource_list_view.hpp"
#include "resource_view.hpp"
#include "abstract_resource_preview.hpp"
#include "default_resource_preview.hpp"

#include "../backend/abstract_resource.hpp"
#include "../backend/abstract_category.hpp"
#include "../backend/configuration.hpp"
#include "../backend/category_list_model.hpp"
#include "../backend/abstract_resource_list_model.hpp"
#include "../backend/abstract_resource_list_model.hpp"

#include <boost/foreach.hpp>

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
	AbstractCategory* root_category = d_configuration->loadConfigurationFile();

	d_category_list_model = new CategoryListModel(root_category);
	d_search_category = d_category_list_model->searchCategory();

	d_resource_list_model = new AbstractResourceListModel();
	QSortFilterProxyModel *filterModel = new QSortFilterProxyModel();
	filterModel->setSourceModel(d_resource_list_model);

	d_category_list_view = new CategoryListView();
	d_category_list_view->setModel(d_category_list_model);

	d_resource_list_view = new ResourceListView();
	d_resource_list_view->setModel(filterModel);

	d_resource_view = new ResourceView(d_category_list_model, d_resource_list_model);

	// Put each resource type in stack
	d_resource_preview = new QStackedWidget;
	d_resource_preview->addWidget(new DefaultResourcePreview());
	d_resource_preview->addWidget(new DefaultResourcePreview());
	d_resource_preview->addWidget(new DefaultResourcePreview());
	d_resource_preview->addWidget(new DefaultResourcePreview());

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

	d_search_edit = new QLineEdit();
	d_search_edit->setFixedWidth(200);

	QWidget* spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	d_add_action = handlingToolBar->addAction(QIcon(":/resources/add.png"), tr("Add"));
	d_setting_action = handlingToolBar->addAction(QIcon(":/resources/settings.png"), tr("Settings"));

	d_add_menu = new QMenu();
	d_add_category = d_add_menu->addAction(tr("Add main category"));
	d_add_resource = d_add_menu->addAction(tr("Add a resource"));
	d_add_action->setMenu(d_add_menu);


	handlingToolBar->addWidget(spacer);
	handlingToolBar->addWidget(d_search_edit);
	d_search_action = handlingToolBar->addAction(QIcon(":/resources/search.png"), tr("Search"));

}

void MainWindow::setupActions()
{
	connect(d_add_category, SIGNAL(triggered()), d_category_list_view, SLOT(addMainCategory()));
	connect(d_add_resource, SIGNAL(triggered()), d_resource_view, SLOT(show()));
	connect(d_add_action, SIGNAL(triggered()), this, SLOT(showAddMenu()));

	connect(d_search_action, SIGNAL(triggered()), this, SLOT(findResources()));

	connect(d_resource_list_model, SIGNAL(categoryChanged()), this, SLOT(updateCategorySelection()));

	connect(d_category_list_view->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(updateResourceList(const QItemSelection &, const QItemSelection &)));
	connect(d_resource_list_view, SIGNAL(resourceAboutToEdit(QModelIndex)), d_resource_view, SLOT(loadResource(QModelIndex)));
	connect(d_category_list_view, SIGNAL(resourceDropped(const QMimeData*)), d_resource_list_model, SLOT(addResource(const QMimeData*)));
	connect(d_resource_list_view->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(updateResourcePreview(const QItemSelection &, const QItemSelection &)));
	connect(d_resource_list_view, SIGNAL(resourceDropped(const QMimeData*)), d_resource_list_model, SLOT(addResource(const QMimeData*)));
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	d_configuration->saveConfigurationFile(d_category_list_model->rootCategory());

	QMainWindow::closeEvent(event);
}

void MainWindow::showAddMenu()
{
  d_add_menu->exec(QCursor::pos());
}


void MainWindow::updateResourceList(const QItemSelection & selected, const QItemSelection & deselected)
{
	Q_UNUSED(deselected);

	QModelIndex selected_index;

	if (selected.indexes().count() > 0)
	{
		selected_index = selected.indexes().front();
	}
	else
	{
		selected_index = d_category_list_view->currentIndex();
	}

	if (selected_index.row() >= 0)
	{
		d_resource_list_model->setCategoryIndex(selected_index);
	}
}

void MainWindow::updateCategorySelection()
{
		d_resource_list_view->resizeRowsToContents();
		static_cast<AbstractResourcePreview*>(d_resource_preview->currentWidget())->reset();
		d_resource_view->setResourceListModel(d_resource_list_model);

		if (d_resource_list_model->categoryIndex() != d_category_list_view->currentIndex())
		{
			d_category_list_view->setCurrentIndex(d_resource_list_model->categoryIndex());
		}
}

void MainWindow::updateResourcePreview(const QItemSelection & selected, const QItemSelection & deselected)
{
	Q_UNUSED(deselected);

	QModelIndex selected_index;

	if (selected.indexes().count() > 0)
	{
		selected_index = selected.indexes().front();
	}
	else
	{
		selected_index = d_resource_list_view->currentIndex();
	}

	if (selected_index.row() >= 0)
	{
		boost::shared_ptr<AbstractResource> resource = d_resource_list_model->resource(selected_index.row());
		d_resource_preview->setCurrentIndex((int)resource->type());
		static_cast<AbstractResourcePreview*>(d_resource_preview->currentWidget())->updateResourceInformation(d_resource_list_model, selected_index.row());
	}
}

void MainWindow::findResources()
{
	QString pattern = d_search_edit->text();

	if (!pattern.isEmpty())
	{
		d_category_list_view->setCurrentIndex(QModelIndex());
		d_search_category->clearResourceList();

		findCategoryResources(d_category_list_model->rootCategory(), pattern);

		d_category_list_view->setCurrentIndex(d_category_list_model->index(d_category_list_model->rootCategory()->children().indexOf(d_search_category), 0));
	}
}

void MainWindow::findCategoryResources(AbstractCategory* parent_category, QString pattern, const QModelIndex& parent)
{
	if (parent_category->hasChildren())
	{
		BOOST_FOREACH(AbstractCategory* category, parent_category->children())
		{
			QModelIndex index = d_category_list_model->index(category->row(), 0, parent);

			d_resource_list_model->setCategoryIndex(index);

			QModelIndexList modelIndexes = d_resource_list_model->match(d_resource_list_model->index(0, 0), Qt::DisplayRole, pattern, -1, Qt::MatchFlags(Qt::MatchContains | Qt::MatchWrap));

			BOOST_FOREACH(QModelIndex index, modelIndexes)
			{
				d_search_category->addResource(d_resource_list_model->resource(index.row()));
			}

			findCategoryResources(category, pattern, index);
		}
	}
}

