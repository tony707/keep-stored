/**
 * \file abstract_resource.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract resource class.
 */

#include "abstract_resource.hpp"

#include <systools/xml_node.hpp>
#include <systools/xml_writer.hpp>
#include <systools/xml_xpath.hpp>

#include <boost/foreach.hpp>

#include <sstream>

boost::shared_ptr<AbstractResource> AbstractResource::createFromXmlNode(boost::shared_ptr<systools::xml::XmlNode> xml_node)
{
	return boost::shared_ptr<AbstractResource>(new AbstractResource(xml_node));
}

AbstractResource::AbstractResource()
{
}

AbstractResource::AbstractResource(boost::shared_ptr<systools::xml::XmlNode> xml_node)
{
	assert(xml_node);

	int tmp_type;
	std::istringstream iss(xml_node->getAttributeValue("type"));
	iss >> tmp_type;
	d_type = (ResourceType)tmp_type;
	d_title = xml_node->getXPath()->evaluateAsString("string(ks:title)");
	d_author = xml_node->getXPath()->evaluateAsString("string(ks:author)");
	d_location = xml_node->getXPath()->evaluateAsString("string(ks:location)");

}

void AbstractResource::saveToXml(boost::shared_ptr<AbstractResource> resource, boost::shared_ptr<systools::xml::XmlWriter> xml_writer)
{
	assert(xml_writer);

	if (resource)
	{
		std::ostringstream oss;
		oss << resource->type();

		xml_writer->startElement("resource");
		xml_writer->writeAttribute("type", oss.str());
		xml_writer->writeElement("title", resource->title());
		xml_writer->writeElement("author", resource->author());
		xml_writer->writeElement("location", resource->location());
		xml_writer->endElement(); //resource
	}
}

std::string AbstractResource::resourceTypeToString(ResourceType type)
{
	std::string str_type;

	switch(type)
	{
		case Book:
			str_type = "Book";
			break;
		case Ebook:
			str_type = "Ebook";
			break;
		case Url:
			str_type = "Url";
			break;
	}

	return str_type;
}

ResourceType AbstractResource::type()
{
	return d_type;
}

std::string AbstractResource::title()
{
	return d_title;
}

std::string AbstractResource::author()
{
	return d_author;
}

std::string AbstractResource::location()
{
	return d_location;
}

void AbstractResource::setTitle(std::string title)
{
	d_title = title;
}

void AbstractResource::setAuthor(std::string author)
{
	d_author = author;
}

void AbstractResource::setLocation(std::string location)
{
	d_location = location;
}

