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
#include "string_tools.hpp"

#include <boost/foreach.hpp>

#include <sstream>

#include <QDebug>

boost::shared_ptr<AbstractResource> AbstractResource::createFromXmlNode(systools::xml::XmlNode& xml_node)
{
	int int_type;
	std::istringstream iss(xml_node.xpath().evaluateAsString("string(ks:type)").toStdString());
	iss >> int_type;
	ResourceType type = static_cast<ResourceType>(int_type);

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

AbstractResource::AbstractResource(systools::xml::XmlNode& xml_node)
{
	d_title = toQString(xml_node.xpath().evaluateAsString("string(ks:title)"));
	d_author = toQString(xml_node.xpath().evaluateAsString("string(ks:author)"));
	d_location = QUrl::fromUserInput(toQString(xml_node.xpath().evaluateAsString("string(ks:location)")));

	std::list<systools::xml::XmlNode> tag_list = xml_node.xpath().evaluate("ks:tagList/ks:tag");

	BOOST_FOREACH(systools::xml::XmlNode tag, tag_list)
	{
		d_tag_list.push_back(toQString(tag.content()));
	}

}

void AbstractResource::saveToXml(boost::shared_ptr<AbstractResource> resource, systools::xml::XmlWriter& xml_writer)
{
	if (resource)
	{
		std::ostringstream oss;
		oss << resource->type();

		xml_writer.startElement("resource");
		xml_writer.writeElement("type", oss.str());
		xml_writer.writeElement("title", fromQString(resource->title()));
		xml_writer.writeElement("author", fromQString(resource->author()));
		xml_writer.writeElement("location", fromQString(resource->location().toString()));
		xml_writer.startElement("tagList");

		BOOST_FOREACH(QString tag, resource->tagList())
		{
			xml_writer.writeElement("tag", fromQString(tag));
		}

		xml_writer.endElement(); //tagList
		xml_writer.endElement(); //resource
	}
}

QString AbstractResource::resourceTypeToString(ResourceType type)
{
	QString str_type;

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

AbstractResource::ResourceType AbstractResource::type()
{
	return d_type;
}

QString AbstractResource::title()
{
	return d_title;
}

QString AbstractResource::author()
{
	return d_author;
}

QUrl AbstractResource::location()
{
	return d_location;
}

QList<QString> AbstractResource::tagList()
{
	return d_tag_list;
}

void AbstractResource::setTitle(QString title)
{
	d_title = title;
}

void AbstractResource::setAuthor(QString author)
{
	d_author = author;
}

void AbstractResource::setLocation(QUrl location)
{
	d_location = location;
}

void AbstractResource::setTagList(QList<QString> tag_list)
{
	d_tag_list = tag_list;
}
