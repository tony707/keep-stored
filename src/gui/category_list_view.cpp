/**
 * \file category_list_view.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The category list view class.
 */

#include "category_list_view.hpp"
#include "../backend/category_list_model.hpp"
#include "../backend/abstract_category.hpp"

#include <boost/foreach.hpp>

#include <QMenu>
#include <QScrollBar>
#include <QAction>
#include <QDebug>
#include <QDragEnterEvent>
#include <QUrl>

CategoryListView::CategoryListView(QWidget* parent) :
	QTreeView(parent)
{
	setMinimumWidth(100);
	setMaximumWidth(horizontalScrollBar()->sizeHint().width() + 100);
	setAcceptDrops(true);
	setDropIndicatorShown(true);
	setDragDropMode(QAbstractItemView::DropOnly);

	d_context_menu = new QMenu();
	d_add_main_action = d_context_menu->addAction(tr("Add main category"));
	d_add_child_action = d_context_menu->addAction(tr("Add child category"));
	d_delete_action = d_context_menu->addAction(tr("Delete category"));

	connect(d_add_main_action, SIGNAL(triggered()), this, SLOT(addMainCategory()));
	connect(d_add_child_action, SIGNAL(triggered()), this, SLOT(addChildCategory()));
	connect(d_delete_action, SIGNAL(triggered()), this, SLOT(deleteCategory()));
}

void CategoryListView::contextMenuEvent(QContextMenuEvent*)
{
	d_add_child_action->setEnabled(false);
	d_delete_action->setEnabled(false);

	if (selectionModel()->hasSelection())
	{
		AbstractCategory* category = static_cast<AbstractCategory*>(selectionModel()->currentIndex().internalPointer());

		if (category->type() != AbstractCategory::Search)
		{
			d_add_child_action->setEnabled(true);
			d_delete_action->setEnabled(true);
		}
	}

	d_context_menu->exec(QCursor::pos());
}

void CategoryListView::addMainCategory()
{
	model()->insertRows(model()->rowCount(), 1);
}

void CategoryListView::addChildCategory()
{
	QModelIndex index = selectionModel()->currentIndex();
	AbstractCategory* category = static_cast<AbstractCategory*>(index.internalPointer());

	model()->insertRows(category->childCount(), 1, index);
}

void CategoryListView::deleteCategory()
{
	QModelIndex index = selectionModel()->currentIndex();
	AbstractCategory* category = static_cast<AbstractCategory*>(index.internalPointer());

	model()->removeRows(category->row(), 1, index);
}

void CategoryListView::dragEnterEvent(QDragEnterEvent *event)
{
	setBackgroundRole(QPalette::Highlight);
	event->acceptProposedAction();
}

void CategoryListView::dragMoveEvent(QDragMoveEvent *event)
{
	QModelIndex index = indexAt(event->pos());
	if (index.row() >= 0)
	{
		setCurrentIndex(index);
	}
	event->acceptProposedAction();
}

void CategoryListView::dropEvent(QDropEvent *event)
{
	emit resourceDropped(event->mimeData());
	event->acceptProposedAction();
}


