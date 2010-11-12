/**
 * \file abstract_resource_list_model.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The AbstractResource list model class.
 */

#include "abstract_resource_list_model.hpp"

#include "url_resource.hpp"
#include "ebook_resource.hpp"

#include "string_tools.hpp"
#include "abstract_category.hpp"
#include "abstract_resource.hpp"

void AbstractResourceListModel::prepareResourceAddition(AbstractResourceListModel* model, QString path)
{
	boost::shared_ptr<AbstractResource> resource;

	QUrl url = QUrl::fromUserInput(path);

	if (url.host().isEmpty())
	{
		resource.reset(new EbookResource());
		resource->setTitle(QFileInfo(url.path()).fileName());
	}
	else
	{
		resource.reset(new UrlResource());
		resource->setTitle(url.host());
	}

	resource->setLocation(url);
	model->addResource(resource);
}

AbstractResourceListModel::AbstractResourceListModel(QObject *parent) :
	QAbstractListModel(parent),
	d_category(0)
{
}

int AbstractResourceListModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	if (d_category)
	{
		return d_category->resourceList().count();
	}
	else
	{
		return 0;
	}
}

int AbstractResourceListModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return 4;
}

QVariant AbstractResourceListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	if (index.row() >= d_category->resourceList().size())
	{
		return QVariant();
	}

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		boost::shared_ptr<AbstractResource> resource = d_category->resourceList().at(index.row());

		switch(index.column())
		{
			case 0:
				return resource->title();
				break;
			case 1:
				return resource->author();
				break;
			case 2:
				return qStringListToQString(resource->tagList());
				break;
			case 3:
				if (resource->type() == AbstractResource::Ebook)
				{
					return resource->location().path();
				}
				else
				{
					return resource->location().toString();
				}
				break;
		}
	}

	return QVariant();
}

Qt::ItemFlags AbstractResourceListModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return Qt::ItemIsEnabled;
	}

	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool AbstractResourceListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (index.isValid() && role == Qt::EditRole)
	{
		switch(index.column())
		{
			case 0:
				d_category->resourceList().at(index.row())->setTitle(value.toString());
				break;
			case 1:
				d_category->resourceList().at(index.row())->setAuthor(value.toString());
				break;
			case 2:
				d_category->resourceList().at(index.row())->setTagList(qStringToQStringList(value.toString()));
				break;
			case 3:
				d_category->resourceList().at(index.row())->setLocation(QUrl::fromUserInput(value.toString()));
				break;
		}

		emit dataChanged(index, index);
		return true;
	}

	return false;
}

QVariant AbstractResourceListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
	{
		return QVariant();
	}

	if (orientation == Qt::Horizontal)
	{
		QString header;

		switch(section)
		{
			case 0:
				header = QString(tr("Title"));
				break;
			case 1:
				header = QString(tr("Author(s)"));
				break;
			case 2:
				header = QString(tr("Tags"));
				break;
			case 3:
				header = QString(tr("Location"));
				break;
		}
		return header;
	}
	else
	{
		return QVariant();
	}
}

bool AbstractResourceListModel::removeRows(int position, int rows, const QModelIndex &index)
{
	Q_UNUSED(index);

	beginRemoveRows(QModelIndex(), position, position+rows-1);

	for (int row = 0; row < rows; ++row)
	{
		d_category->removeResource(position);
	}

	endRemoveRows();

	return true;
}

AbstractCategory* AbstractResourceListModel::category()
{
	return d_category;
}

QModelIndex AbstractResourceListModel::categoryIndex()
{
	return d_category_index;
}

void AbstractResourceListModel::setCategoryIndex(QModelIndex category_index)
{
	beginResetModel();
	d_category_index = category_index;
	d_category = static_cast<AbstractCategory*>(category_index.internalPointer());
	endResetModel();
	emit categoryChanged();
}

boost::shared_ptr<AbstractResource> AbstractResourceListModel::resource(int row)
{
	return d_category->resourceList().at(row);
}

void AbstractResourceListModel::addResource(boost::shared_ptr<AbstractResource> resource)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount());

	d_category->addResource(resource);

	endInsertRows();
}

void AbstractResourceListModel::addResource(const QMimeData* mime_data)
{
	QList<QUrl> url_list;

	if (mime_data->hasText())
	{
		qDebug() << mime_data->text();
		url_list.push_back(QUrl::fromUserInput(mime_data->text()));
	}
	else if (mime_data->hasUrls())
	{
		url_list = mime_data->urls();
	}
	else
	{
		//TODO: MSGBOX
	}

	BOOST_FOREACH(QUrl url, url_list)
	{
		qDebug() << url.toString();

		boost::shared_ptr<AbstractResource> resource;

		if (url.host().isEmpty())
		{
			resource.reset(new EbookResource());
			resource->setTitle(QFileInfo(url.path()).fileName());
		}
		else
		{
			resource.reset(new UrlResource());
			resource->setTitle(url.host());
		}

		resource->setLocation(url);
		addResource(resource);
	}
}

