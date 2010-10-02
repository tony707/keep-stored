/**
 * \file category_list_view.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The category list view class.
 */

#include "category_list_view.hpp"

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
	const QMimeData *mimeData = event->mimeData();
	if (mimeData->hasText())
	{
		qDebug() << mimeData->text();
		emit resourceDropped(mimeData->text());
	} else if (mimeData->hasUrls())
	{
		QList<QUrl> url_list = mimeData->urls();
		BOOST_FOREACH(QUrl url, url_list)
		{
			QString url_string = url.path();
			qDebug() << url_string;
			emit resourceDropped(url_string);
		}
	} else
	{
		qDebug() << "This mime type can't be dropped!";
		//TODO: MSGBOX
	}
	event->acceptProposedAction();
}


