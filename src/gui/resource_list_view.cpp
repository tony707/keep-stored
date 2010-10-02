/**
 * \file resource_list_view.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The resource list view class.
 */

#include "resource_list_view.hpp"

#include "../backend/abstract_resource_list_model.hpp"
#include "../backend/abstract_resource.hpp"

#include <QMenu>
#include <QScrollBar>
#include <QAction>
#include <QHeaderView>

ResourceListView::ResourceListView(QWidget* parent) :
	QTableView(parent)
{
	verticalHeader()->hide();
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setSortingEnabled(true);
	horizontalHeader()->setResizeMode(QHeaderView::Stretch);

	d_context_menu = new QMenu();
	d_edit_action = d_context_menu->addAction(tr("Edit resource"));
	d_delete_action = d_context_menu->addAction(tr("Delete resource"));

	connect(d_edit_action, SIGNAL(triggered()), this, SLOT(editResource()));
	connect(d_delete_action, SIGNAL(triggered()), this, SLOT(deleteResource()));
}

void ResourceListView::contextMenuEvent(QContextMenuEvent*)
{
	if (selectionModel()->hasSelection())
	{
		d_context_menu->exec(QCursor::pos());
	}
}

void ResourceListView::editResource()
{
	int row = selectionModel()->selectedRows().front().row();
	resourceAboutToEdit(row);
}

void ResourceListView::deleteResource()
{
	int row = selectionModel()->selectedRows().front().row();
	model()->removeRows(row, 1);
}

