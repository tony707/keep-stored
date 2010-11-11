/**
 * \file url_resource.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The url resource class.
 */

#ifndef KEEP_STORED_URL_RESOURCE_HPP
#define KEEP_STORED_URL_RESOURCE_HPP

#include "abstract_resource.hpp"

class UrlResource : public AbstractResource
{
	public:
		UrlResource();

		UrlResource(systools::xml::XmlNode& xml_node);
};

#endif /* KEEP_STORED_URL_RESOURCE_HPP */

