/**
 * \file resource_list_view.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The resource list view class.
 */

#include "resource_list_view.hpp"

#include "../backend/abstract_resource_list_model.hpp"
#include "../backend/abstract_resource.hpp"

#include "boost/foreach.hpp"

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
	setAcceptDrops(true);
	setDropIndicatorShown(true);
	setDragDropMode(QAbstractItemView::DropOnly);

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

void ResourceListView::dragEnterEvent(QDragEnterEvent *event)
{
	event->acceptProposedAction();
}

void ResourceListView::dragMoveEvent(QDragMoveEvent *event)
{
	event->acceptProposedAction();
}

void ResourceListView::dropEvent(QDropEvent *event)
{
	QString url_string;

	const QMimeData *mimeData = event->mimeData();
	if (mimeData->hasText())
	{
		url_string = mimeData->text();
		qDebug() << url_string;

	} else if (mimeData->hasUrls())
	{
		QList<QUrl> url_list = mimeData->urls();
		BOOST_FOREACH(QUrl url, url_list)
		{
			url_string = url.path();
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
