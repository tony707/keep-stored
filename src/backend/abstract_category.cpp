/**
 * \file category.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract category class.
 */

#include "default_category.hpp"
#include "search_category.hpp"
#include "abstract_resource.hpp"
#include "string_tools.hpp"

#include <systools/xml_writer.hpp>
#include <systools/xml_node.hpp>
#include <systools/xml_xpath.hpp>

#include <boost/foreach.hpp>

#include <sstream>

#include <QDebug>

AbstractCategory* AbstractCategory::createFromXmlNode(systools::xml::XmlNode& xml_node)
{
	int int_type;
	std::istringstream iss(xml_node.xpath().evaluateAsString("string(ks:type)").toStdString());
	iss >> int_type;
	CategoryType type = static_cast<CategoryType>(int_type);

	AbstractCategory* category;

	switch(type)
	{
		case Default:
			category = new DefaultCategory(xml_node);
			break;
		case Search:
			category = new SearchCategory(xml_node);
			break;
		default:
			category = new DefaultCategory(xml_node);
			break;
	}
	return category;
}

void AbstractCategory::saveToXml(AbstractCategory* category, systools::xml::XmlWriter& xml_writer)
{
	if (category)
	{
		std::ostringstream oss;
		oss << category->type();

		xml_writer.startElement("category");
		xml_writer.writeElement("type", oss.str());
		xml_writer.writeElement("title", fromQString(category->title()));

		if (category->type() != AbstractCategory::Search)
		{
			BOOST_FOREACH(boost::shared_ptr<AbstractResource> resource, category->resourceList())
			{
				AbstractResource::saveToXml(resource, xml_writer);
			}
		}

		if (category->hasChildren())
		{
			BOOST_FOREACH(AbstractCategory* child_category, category->children())
			{
				saveToXml(child_category, xml_writer);
			}
		}

		xml_writer.endElement(); //category
	}
}

AbstractCategory::AbstractCategory() :
	d_resource_list(QList<boost::shared_ptr<AbstractResource> >()),
	d_children_categories(QList<AbstractCategory*>()),
	d_parent_category(NULL)
{
}

AbstractCategory::~AbstractCategory()
{
	qDeleteAll(d_children_categories);
}

AbstractCategory::AbstractCategory(systools::xml::XmlNode& xml_node):
	d_resource_list(QList<boost::shared_ptr<AbstractResource> >()),
	d_children_categories(QList<AbstractCategory* >()),
	d_parent_category(NULL)
{
	d_title = toQString(xml_node.xpath().evaluateAsString("string(ks:title)"));
	std::list<systools::xml::XmlNode> resource_list = xml_node.xpath().evaluate("ks:resource");

	BOOST_FOREACH(systools::xml::XmlNode resource, resource_list)
	{
		d_resource_list.push_back(AbstractResource::createFromXmlNode(resource));
	}
}

QString AbstractCategory::title()
{
	return d_title;
}

void AbstractCategory::setTitle(QString title)
{
	d_title = title;
}

AbstractCategory::CategoryType AbstractCategory::type()
{
	return d_type;
}

void AbstractCategory::setType(CategoryType type)
{
	d_type = type;
}

void AbstractCategory::prependChild(AbstractCategory* category)
{
	d_children_categories.prepend(category);
	category->setParent(const_cast<AbstractCategory*>(this));
}

void AbstractCategory::appendChild(AbstractCategory* category)
{
	d_children_categories.append(category);
	category->setParent(const_cast<AbstractCategory*>(this));
}

void AbstractCategory::removeChild(int row)
{
	d_children_categories.removeAt(row);
}

AbstractCategory* AbstractCategory::childAt(int row)
{
	return d_children_categories.at(row);
}

int AbstractCategory::childCount()
{
	return d_children_categories.count();
}

int AbstractCategory::columnCount()
{
	return 1;
}

int AbstractCategory::row()
{
	if (d_parent_category != NULL)
	{
		return d_parent_category->children().indexOf(const_cast<AbstractCategory*>(this));
	}
	return 0;
}

AbstractCategory* AbstractCategory::parent()
{
	return d_parent_category;
}

QList<AbstractCategory* > AbstractCategory::children()
{
	return d_children_categories;
}

void AbstractCategory::setParent(AbstractCategory* parent_category)
{
	d_parent_category = parent_category;
}

bool AbstractCategory::hasChildren()
{
	return (d_children_categories.size() > 0) ? true : false;
}

QList<boost::shared_ptr<AbstractResource> > AbstractCategory::resourceList()
{
	return d_resource_list;
}

void AbstractCategory::addResource(boost::shared_ptr<AbstractResource> resource)
{
	if (!d_resource_list.contains(resource))
	{
		d_resource_list.push_back(resource);
	}
}

void AbstractCategory::removeResource(int row)
{
	d_resource_list.removeAt(row);
}

void AbstractCategory::clearResourceList()
{
	d_resource_list.clear();
}

