/**
 * \file book_resource.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The book resource class.
 */

#ifndef KEEP_STORED_BOOK_RESOURCE_HPP
#define KEEP_STORED_BOOK_RESOURCE_HPP

#include "abstract_resource.hpp"

class BookResource : public AbstractResource
{
	public:
		BookResource();

		BookResource(systools::xml::XmlNode& xml_node);
};

#endif /* KEEP_STORED_BOOK_RESOURCE_HPP */

