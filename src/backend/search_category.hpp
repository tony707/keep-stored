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
		SearchCategory();

		/**
		 * \brief Constructor.
		 */
		SearchCategory(boost::shared_ptr<systools::xml::XmlNode> xml_node);

};

#endif /* KEEP_STORED_SEARCH_CATEGORY_HPP */


