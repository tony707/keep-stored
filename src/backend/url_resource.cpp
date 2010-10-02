/**
 * \file url_resource.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The url resource class.
 */

#include "url_resource.hpp"

UrlResource::UrlResource() :
	AbstractResource()
{
	d_type = Url;
}

UrlResource::UrlResource(boost::shared_ptr<systools::xml::XmlNode> xml_node) :
	AbstractResource(xml_node)
{
	d_type = Url;
}
