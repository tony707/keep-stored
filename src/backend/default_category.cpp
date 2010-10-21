/**
 * \file category.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The default category class.
 */

#include "default_category.hpp"
#include "abstract_category.hpp"
#include "abstract_resource.hpp"
#include "string_tools.hpp"

#include <systools/xml_writer.hpp>
#include <systools/xml_node.hpp>
#include <systools/xml_xpath.hpp>

#include <boost/foreach.hpp>

DefaultCategory::DefaultCategory()
{
}

DefaultCategory::DefaultCategory(boost::shared_ptr<systools::xml::XmlNode> xml_node) :
	AbstractCategory(xml_node)
{
}

QList<boost::shared_ptr<AbstractResource> > DefaultCategory::resourceList()
{
	return d_resource_list;
}

void DefaultCategory::addResource(boost::shared_ptr<AbstractResource> resource)
{
	d_resource_list.push_back(resource);
}

void DefaultCategory::removeResource(int row)
{
	d_resource_list.removeAt(row);
}

