/**
 * \file category.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The category class.
 */

#ifndef KEEP_STORED_CATEGORY_HPP
#define KEEP_STORED_CATEGORY_HPP

#include <QMetaType>

#include <boost/shared_ptr.hpp>

#include <list>
#include <string>

namespace systools
{
	namespace xml
	{
		class XmlNode;
		class XmlWriter;
	}
}

class AbstractResource;

class Category
{
	public:

		static void saveToXml(boost::shared_ptr<Category> category, boost::shared_ptr<systools::xml::XmlWriter> xml_writer);

		static boost::shared_ptr<Category> createFromXmlNode(boost::shared_ptr<systools::xml::XmlNode> xml_node);

		/**
		 * \brief Constructor.
		 */
		Category();

		/**
		 * \brief Constructor.
		 */
		Category(boost::shared_ptr<systools::xml::XmlNode> xml_node);

		/**
		 * \brief Get the title.
		 */
		std::string title();

		/**
		 * \brief Get the resource list.
		 */
		std::list<boost::shared_ptr<AbstractResource> > resourceList();

	private:

		/**
		 * \brief The title.
		 */
		std::string d_title;

		/**
		 * \brief The associated resource list.
		 */
		std::list<boost::shared_ptr<AbstractResource> > d_resource_list;

};

Q_DECLARE_METATYPE(Category)

#endif /* KEEP_STORED_CATEGORY_HPP */


