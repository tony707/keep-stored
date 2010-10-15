/**
 * \file abstract_resource.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract resource class.
 */

#include "abstract_resource.hpp"

#include "default_resource.hpp"
#include "book_resource.hpp"
#include "ebook_resource.hpp"
#include "url_resource.hpp"

#include <systools/xml_node.hpp>
#include <systools/xml_writer.hpp>
#include <systools/xml_xpath.hpp>

#include <boost/foreach.hpp>

#include <sstream>
#include <QDebug>

boost::shared_ptr<AbstractResource> AbstractResource::createFromXmlNode(boost::shared_ptr<systools::xml::XmlNode> xml_node)
{
	int int_type;
	std::istringstream iss(xml_node->getAttributeValue("type").toStdString());
	iss >> int_type;
	ResourceType type = static_cast<ResourceType>(type);

	boost::shared_ptr<AbstractResource> resource;

	switch(type)
	{
		case Default:
			resource.reset(new DefaultResource(xml_node));
			break;
		case Book:
			resource.reset(new BookResource(xml_node));
			break;
		case Ebook:
			resource.reset(new EbookResource(xml_node));
			break;
		case Url:
			resource.reset(new UrlResource(xml_node));
			break;

	}
	return resource;
}

AbstractResource::AbstractResource()
{
}

AbstractResource::AbstractResource(boost::shared_ptr<systools::xml::XmlNode> xml_node)
{
	assert(xml_node);

	d_title = xml_node->xpath()->evaluateAsString("string(ks:title)");
	d_author = xml_node->xpath()->evaluateAsString("string(ks:author)");
	d_location = xml_node->xpath()->evaluateAsString("string(ks:location)");

	std::list<boost::shared_ptr<systools::xml::XmlNode> > tag_list = xml_node->xpath()->evaluate("ks:tagList/ks:tag");

	BOOST_FOREACH(boost::shared_ptr<systools::xml::XmlNode> tag, tag_list)
	{
		d_tag_list.push_back(tag->content());
	}

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
		xml_writer->startElement("tagList");

		BOOST_FOREACH(systools::String tag, resource->tagList())
		{
			xml_writer->writeElement("tag", tag);
		}

		xml_writer->endElement(); //tagList
		xml_writer->endElement(); //resource
	}
}

std::string AbstractResource::resourceTypeToString(ResourceType type)
{
	std::string str_type;

	switch(type)
	{
		case Default:
			str_type = "Default";
			break;
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

systools::String AbstractResource::title()
{
	return d_title;
}

systools::String AbstractResource::author()
{
	return d_author;
}

systools::String AbstractResource::location()
{
	return d_location;
}

QList<systools::String> AbstractResource::tagList()
{
	return d_tag_list;
}

void AbstractResource::setTitle(systools::String title)
{
	d_title = title;
}

void AbstractResource::setAuthor(systools::String author)
{
	d_author = author;
}

void AbstractResource::setLocation(systools::String location)
{
	d_location = location;
}

void AbstractResource::setTagList(QList<systools::String> tag_list)
{
	d_tag_list = tag_list;
}
