/**
 * \file category.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The default category class.
 */

#ifndef KEEP_STORED_DEFAULT_CATEGORY_HPP
#define KEEP_STORED_DEFAULT_CATEGORY_HPP

#include "abstract_category.hpp"

class DefaultCategory : public AbstractCategory
{
	public:

		/**
		 * \brief Constructor.
		 */
		DefaultCategory();

		/**
		 * \brief Constructor.
		 */
		DefaultCategory(QString title);

		/**
		 * \brief Constructor.
		 */
		DefaultCategory(systools::xml::XmlNode& xml_node);

};

#endif /* KEEP_STORED_DEFAULT_CATEGORY_HPP */


