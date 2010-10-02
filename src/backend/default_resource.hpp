/**
 * \file default_resource.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The default resource class.
 */

#ifndef KEEP_STORED_DEFAULT_RESOURCE_HPP
#define KEEP_STORED_DEFAULT_RESOURCE_HPP

#include "abstract_resource.hpp"

class DefaultResource : public AbstractResource
{
	public:
		DefaultResource();

		DefaultResource(boost::shared_ptr<systools::xml::XmlNode> xml_node);
};

#endif /* KEEP_STORED_DEFAULT_RESOURCE_HPP */

