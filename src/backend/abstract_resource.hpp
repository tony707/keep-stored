/**
 * \file abstract_resource.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract resource class.
 */

#ifndef KEEP_STORED_ABSTRACT_RESOURCE_HPP
#define KEEP_STORED_ABSTRACT_RESOURCE_HPP

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

enum ResourceType
{
	Default,
	Book,
	Ebook,
	Url
};

class AbstractResource
{
	public:

		/**
		 * \brief Constructor.
		 */
		AbstractResource();

		/**
		 * \brief Constructor.
		 */
		AbstractResource(boost::shared_ptr<systools::xml::XmlNode> xml_node);

		static boost::shared_ptr<AbstractResource> createFromXmlNode(boost::shared_ptr<systools::xml::XmlNode> xml_node);

		static void saveToXml(boost::shared_ptr<AbstractResource> resource, boost::shared_ptr<systools::xml::XmlWriter> xml_writer);

		static std::string resourceTypeToString(ResourceType type);

		ResourceType type();

		std::string title();

		std::string author();

		std::string location();

		void setTitle(std::string title);

		void setAuthor(std::string author);

		void setLocation(std::string location);

	private:

		/**
		 * \brief The type.
		 */
		ResourceType d_type;

		/**
		 * \brief The title.
		 */
		std::string d_title;

		/**
		 * \brief The author(s).
		 */
		std::string d_author;

		/**
		 * \brief The location.
		 */
		std::string d_location;

};

#endif /* KEEP_STORED_ABSTRACT_RESOURCE_HPP */

