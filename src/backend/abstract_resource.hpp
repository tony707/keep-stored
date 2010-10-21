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
#include <QString>

namespace systools
{
	namespace xml
	{
		class XmlNode;
		class XmlWriter;
	}
}


class AbstractResource
{

	public:

	enum ResourceType
	{
		Default,
		Book,
		Ebook,
		Url
	};

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

		QString title();

		QString author();

		QString location();

		QList<QString> tagList();

		void setTitle(QString title);

		void setAuthor(QString author);

		void setLocation(QString location);

		void setTagList(QList<QString> tag_list);

	protected:

		/**
		 * \brief The type.
		 */
		ResourceType d_type;

		/**
		 * \brief The title.
		 */
		QString d_title;

		/**
		 * \brief The author(s).
		 */
		QString d_author;

		/**
		 * \brief The location.
		 */
		QString d_location;

		/**
		 * \brief The tag list.
		 */
		QList<QString> d_tag_list;

};

#endif /* KEEP_STORED_ABSTRACT_RESOURCE_HPP */

