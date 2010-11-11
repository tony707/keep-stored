/**
 * \file search_category.cpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The search category class.
 */

#include "search_category.hpp"
#include "abstract_category.hpp"
#include "abstract_resource.hpp"
#include "string_tools.hpp"

#include <systools/xml_writer.hpp>
#include <systools/xml_node.hpp>
#include <systools/xml_xpath.hpp>

#include <boost/foreach.hpp>

SearchCategory::SearchCategory(QString title) :
	AbstractCategory()
{
	d_title = title;
	d_type = Search;
}

SearchCategory::SearchCategory(systools::xml::XmlNode& xml_node) :
	AbstractCategory(xml_node)
{
	d_type = Search;
}

