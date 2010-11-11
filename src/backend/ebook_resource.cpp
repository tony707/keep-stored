/**
 * \file ebook_resource.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The ebook resource class.
 */

#include "ebook_resource.hpp"

EbookResource::EbookResource() :
	AbstractResource()
{
	d_type = Ebook;
}

EbookResource::EbookResource(systools::xml::XmlNode& xml_node) :
	AbstractResource(xml_node)
{
	d_type = Ebook;
}
