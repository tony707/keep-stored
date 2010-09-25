/**
 * \file category_list_view.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The category list view class.
 */

#include "category_list_view.hpp"

#include <QMenu>
#include <QScrollBar>
#include <QAction>
#include <QDebug>

CategoryListView::CategoryListView(QWidget* parent) :
	QListView(parent)
{
	setMinimumWidth(150);
	setMaximumWidth(horizontalScrollBar()->sizeHint().width() + 100);

	d_context_menu = new QMenu();
	d_delete_action = d_context_menu->addAction(tr("Delete category"));
	connect(d_delete_action, SIGNAL(triggered()), this, SLOT(deleteCategory()));
}

void CategoryListView::contextMenuEvent(QContextMenuEvent*)
{
	if (selectionModel()->hasSelection())
	{
		d_context_menu->exec(QCursor::pos());
	}
}

void CategoryListView::addCategory()
{
	model()->insertRows(model()->rowCount(), 1);
}

void CategoryListView::deleteCategory()
{
	int row = selectionModel()->selectedRows().front().row();
	model()->removeRows(row, 1);
}
