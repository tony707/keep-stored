/**
 * \file abstract_resource.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract resource class.
 */

#ifndef KEEP_STORED_ABSTRACT_RESOURCE_HPP
#define KEEP_STORED_ABSTRACT_RESOURCE_HPP

#include <boost/shared_ptr.hpp>

#include <systools/string.hpp>

#include <QList>

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

		systools::String title();

		systools::String author();

		systools::String location();

		QList<systools::String> tagList();

		void setTitle(systools::String title);

		void setAuthor(systools::String author);

		void setLocation(systools::String location);

		void setTagList(QList<systools::String> tag_list);

	protected:

		/**
		 * \brief The type.
		 */
		ResourceType d_type;

		/**
		 * \brief The title.
		 */
		systools::String d_title;

		/**
		 * \brief The author(s).
		 */
		systools::String d_author;

		/**
		 * \brief The location.
		 */
		systools::String d_location;

		/**
		 * \brief The tag list.
		 */
		QList<systools::String> d_tag_list;

};

#endif /* KEEP_STORED_ABSTRACT_RESOURCE_HPP */

