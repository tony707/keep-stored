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

