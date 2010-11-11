/**
 * \file abstract_resource.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract resource class.
 */

#ifndef KEEP_STORED_ABSTRACT_RESOURCE_HPP
#define KEEP_STORED_ABSTRACT_RESOURCE_HPP

#include <boost/shared_ptr.hpp>

#include <systools/string.hpp>
#include <systools/xml_node.hpp>
#include <systools/xml_writer.hpp>
#include <systools/xml_xpath.hpp>


#include <QList>
#include <QString>
#include <QUrl>

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
		AbstractResource(systools::xml::XmlNode& xml_node);

		static boost::shared_ptr<AbstractResource> createFromXmlNode(systools::xml::XmlNode& xml_node);

		static void saveToXml(boost::shared_ptr<AbstractResource> resource, systools::xml::XmlWriter& xml_writer);

		static QString resourceTypeToString(ResourceType type);

		ResourceType type();

		QString title();

		QString author();

		QUrl location();

		QList<QString> tagList();

		void setTitle(QString title);

		void setAuthor(QString author);

		void setLocation(QUrl location);

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
		QUrl d_location;

		/**
		 * \brief The tag list.
		 */
		QList<QString> d_tag_list;

};

#endif /* KEEP_STORED_ABSTRACT_RESOURCE_HPP */

