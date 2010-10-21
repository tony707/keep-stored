/**
 * \file category.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract category class.
 */

#include "abstract_category.hpp"
#include "default_category.hpp"
//#include "search_category.hpp"
#include "abstract_resource.hpp"
#include "string_tools.hpp"

#include <systools/xml_writer.hpp>
#include <systools/xml_node.hpp>
#include <systools/xml_xpath.hpp>

#include <boost/foreach.hpp>

#include <sstream>

boost::shared_ptr<AbstractCategory> AbstractCategory::createFromXmlNode(boost::shared_ptr<systools::xml::XmlNode> xml_node)
{
	int int_type;
	std::istringstream iss(xml_node->getAttributeValue("type").toStdString());
	iss >> int_type;
	CategoryType type = static_cast<CategoryType>(type);

	boost::shared_ptr<AbstractCategory> category;

	switch(type)
	{
		case Default:
			category.reset(new DefaultCategory(xml_node));
			break;
		default:
			category.reset(new DefaultCategory(xml_node));
			break;
		//case Search:
		//	category.reset(new SearchCategory(xml_node));
		//	break;
	}
	return category;
}

void AbstractCategory::saveToXml(boost::shared_ptr<AbstractCategory> category, boost::shared_ptr<systools::xml::XmlWriter> xml_writer)
{
	assert(xml_writer);

	if (category)
	{
		std::ostringstream oss;
		oss << category->type();

		xml_writer->startElement("category");
		xml_writer->writeAttribute("type", oss.str());
		xml_writer->writeAttribute("title", fromQString(category->title()));

		BOOST_FOREACH(boost::shared_ptr<AbstractResource> resource, category->resourceList())
		{
			AbstractResource::saveToXml(resource, xml_writer);
		}

		xml_writer->endElement(); //category
	}
}

AbstractCategory::AbstractCategory()
{
}

AbstractCategory::AbstractCategory(boost::shared_ptr<systools::xml::XmlNode> xml_node)
{
	assert(xml_node);

	d_title = toQString(xml_node->getAttributeValue("title"));
	std::list<boost::shared_ptr<systools::xml::XmlNode> > resource_list = xml_node->xpath()->evaluate("ks:resource");

	BOOST_FOREACH(boost::shared_ptr<systools::xml::XmlNode> resource, resource_list)
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


QList<boost::shared_ptr<AbstractResource> > AbstractCategory::resourceList()
{
	return QList<boost::shared_ptr<AbstractResource> >();
}
