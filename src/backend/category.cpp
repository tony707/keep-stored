/**
 * \file category.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The category class.
 */

#include "category.hpp"
#include "abstract_resource.hpp"

#include <systools/xml_writer.hpp>
#include <systools/xml_node.hpp>
#include <systools/xml_xpath.hpp>

#include <boost/foreach.hpp>

#include <QDebug>

boost::shared_ptr<Category> Category::createFromXmlNode(boost::shared_ptr<systools::xml::XmlNode> xml_node)
{
	return boost::shared_ptr<Category>(new Category(xml_node));
}

void Category::saveToXml(boost::shared_ptr<Category> category, boost::shared_ptr<systools::xml::XmlWriter> xml_writer)
{
	assert(xml_writer);

	if (category)
	{
		xml_writer->startElement("category");
		xml_writer->writeAttribute("title", category->title());

		BOOST_FOREACH(boost::shared_ptr<AbstractResource> resource, category->resourceList())
		{
			AbstractResource::saveToXml(resource, xml_writer);
		}

		xml_writer->endElement(); //category
	}
}

Category::Category()
{
}

Category::Category(boost::shared_ptr<systools::xml::XmlNode> xml_node)
{
	assert(xml_node);

	d_title = xml_node->getAttributeValue("title");
	std::list<boost::shared_ptr<systools::xml::XmlNode> > resource_list = xml_node->getXPath()->evaluate("ks:resource");

	BOOST_FOREACH(boost::shared_ptr<systools::xml::XmlNode> resource, resource_list)
	{
		d_resource_list.push_back(AbstractResource::createFromXmlNode(resource));
	}
}

std::string Category::title()
{
	return d_title;
}

void Category::setTitle(std::string title)
{
	d_title = title;
}

QList<boost::shared_ptr<AbstractResource> > Category::resourceList()
{
	return d_resource_list;
}

void Category::addResource(boost::shared_ptr<AbstractResource> resource)
{
	d_resource_list.push_back(resource);
}

void Category::removeResource(int row)
{
	d_resource_list.removeAt(row);
}

