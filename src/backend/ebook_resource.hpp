/**
 * \file ebook_resource.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The ebook resource class.
 */

#ifndef KEEP_STORED_EBOOK_RESOURCE_HPP
#define KEEP_STORED_EBOOK_RESOURCE_HPP

#include "abstract_resource.hpp"

class EbookResource : public AbstractResource
{
	public:
		EbookResource();

		EbookResource(boost::shared_ptr<systools::xml::XmlNode> xml_node);
};

#endif /* KEEP_STORED_EBOOK_RESOURCE_HPP */

