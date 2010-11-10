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
	QListView(parent)
{
	setMinimumWidth(150);
	setMaximumWidth(horizontalScrollBar()->sizeHint().width() + 100);
	setAcceptDrops(true);
	setDropIndicatorShown(true);
	setDragDropMode(QAbstractItemView::DropOnly);

	d_context_menu = new QMenu();
	d_delete_action = d_context_menu->addAction(tr("Delete category"));
	connect(d_delete_action, SIGNAL(triggered()), this, SLOT(deleteCategory()));
}

void CategoryListView::contextMenuEvent(QContextMenuEvent*)
{
	if (selectionModel()->hasSelection())
	{
		int row = selectionModel()->selectedRows().front().row();
		boost::shared_ptr<AbstractCategory> category = static_cast<CategoryListModel*>(this->model())->rootCategory()->children().at(row);

		if (category->type() != AbstractCategory::Search)
		{
			d_context_menu->exec(QCursor::pos());
		}
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


