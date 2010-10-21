/**
 * \file category.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The default category class.
 */

#ifndef KEEP_STORED_CATEGORY_HPP
#define KEEP_STORED_CATEGORY_HPP

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
		DefaultCategory(boost::shared_ptr<systools::xml::XmlNode> xml_node);

		/**
		 * \brief Get the resource list.
		 */
		QList<boost::shared_ptr<AbstractResource> > resourceList();

		void addResource(boost::shared_ptr<AbstractResource> resource);

		void removeResource(int row);

};

#endif /* KEEP_STORED_CATEGORY_HPP */


