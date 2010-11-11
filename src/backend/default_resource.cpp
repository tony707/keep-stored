/**
 * \file default_resource.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The default resource class.
 */

#include "default_resource.hpp"

DefaultResource::DefaultResource() :
	AbstractResource()
{
	d_type = Default;
}

DefaultResource::DefaultResource(systools::xml::XmlNode& xml_node) :
	AbstractResource(xml_node)
{
	d_type = Default;
}
