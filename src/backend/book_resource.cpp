/**
 * \file book_resource.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The book resource class.
 */

#include "book_resource.hpp"

BookResource::BookResource() :
	AbstractResource()
{
	d_type = Book;
}

BookResource::BookResource(systools::xml::XmlNode& xml_node) :
	AbstractResource(xml_node)
{
	d_type = Book;
}
