/**
 * \file search_category.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The search category class.
 */

#ifndef KEEP_STORED_SEARCH_CATEGORY_HPP
#define KEEP_STORED_SEARCH_CATEGORY_HPP

#include "abstract_category.hpp"

class SearchCategory : public AbstractCategory
{
	public:

		/**
		 * \brief Constructor.
		 */
		SearchCategory(QString title);

		/**
		 * \brief Constructor.
		 */
		SearchCategory(systools::xml::XmlNode& xml_node);

};

#endif /* KEEP_STORED_SEARCH_CATEGORY_HPP */


