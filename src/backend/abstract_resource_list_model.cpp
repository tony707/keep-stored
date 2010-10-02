/**
 * \file abstract_resource_list_model.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The AbstractResource list model class.
 */

#include "abstract_resource_list_model.hpp"

#include "url_resource.hpp"
#include "ebook_resource.hpp"

#include "string_tools.hpp"
#include "category.hpp"
#include "abstract_resource.hpp"

void AbstractResourceListModel::prepareResourceAddition(AbstractResourceListModel* model, QString path)
{
	boost::shared_ptr<AbstractResource> resource;
	QUrl url = QUrl(path);

	if (url.isValid())
	{
		resource.reset(new UrlResource());
	}
	else
	{
		resource.reset(new EbookResource());
	}

	resource->setTitle(fromQString(path));
	resource->setLocation(fromQString(path));

	model->addResource(resource);
}

AbstractResourceListModel::AbstractResourceListModel(boost::shared_ptr<Category> category, QObject *parent) :
	QAbstractListModel(parent),
	d_category(category)
{
}

int AbstractResourceListModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return d_category->resourceList().count();
}

int AbstractResourceListModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return 3;
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

	if (role == Qt::DisplayRole)
	{
		switch(index.column())
		{
			case 0:
				return toQString(d_category->resourceList().at(index.row())->title());
				break;
			case 1:
				return toQString(d_category->resourceList().at(index.row())->author());
				break;
			case 2:
				return toQString(d_category->resourceList().at(index.row())->location());
				break;
		}
	}

	return QVariant();
}

bool AbstractResourceListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (index.isValid() && role == Qt::EditRole)
	{
		QByteArray utf8_value = value.toString().toUtf8();
		std::string value = std::string(utf8_value.constData(), utf8_value.size());

		switch(index.column())
		{
			case 0:
				d_category->resourceList().at(index.row())->setTitle(value);
				break;
			case 1:
				d_category->resourceList().at(index.row())->setAuthor(value);
				break;
			case 2:
				d_category->resourceList().at(index.row())->setLocation(value);
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
				header = QString(tr("Location"));
				break;
			default:
				header = QString(tr("Other"));
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

boost::shared_ptr<Category> AbstractResourceListModel::category()
{
	return d_category;
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

