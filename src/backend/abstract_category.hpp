/**
 * \file category.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract category class.
 */

#ifndef KEEP_STORED_ABSTRACT_CATEGORY_HPP
#define KEEP_STORED_ABSTRACT_CATEGORY_HPP

#include <QList>
#include <QString>

#include <boost/smart_ptr.hpp>

#include <list>

namespace systools
{
	namespace xml
	{
		class XmlNode;
		class XmlWriter;
	}
}


class AbstractResource;

class AbstractCategory
{

	public:

	enum CategoryType
	{
		Default,
		Search
	};

		static void saveToXml(AbstractCategory* category, systools::xml::XmlWriter& xml_writer);

		static AbstractCategory* createFromXmlNode(systools::xml::XmlNode& xml_node);

		/**
		 * \brief Constructor.
		 */
		AbstractCategory();

		/**
		 * \brief Constructor.
		 */
		~AbstractCategory();

		/**
		 * \brief Constructor.
		 */
		AbstractCategory(systools::xml::XmlNode& xml_node);

		/**
		 * \brief Get the title.
		 */
		QString title();

		/**
		 * \brief Set the title.
		 */
		void setTitle(QString title);

		/**
		 * \brief Get the title.
		 */
		CategoryType type();

		/**
		 * \brief Set the title.
		 */
		void setType(CategoryType type);

		void prependChild(AbstractCategory* category);

		void appendChild(AbstractCategory* category);

		void removeChild(int row);

		AbstractCategory* childAt(int row);

		int childCount();

		int columnCount();

		int row();

		AbstractCategory* parent();

		QList<AbstractCategory*> children();

		void setParent(AbstractCategory* parent_category);

		bool hasChildren();

		/**
		 * \brief Get the resource list.
		 */
		virtual QList<boost::shared_ptr<AbstractResource> > resourceList();

		virtual void addResource(boost::shared_ptr<AbstractResource> resource);

		virtual void removeResource(int row);

		virtual void clearResourceList();

	protected:

		/**
		 * \brief The title.
		 */
		QString d_title;

		/**
		 * \brief The type.
		 */
		CategoryType d_type;

		/**
		 * \brief The associated resource list.
		 */
		QList<boost::shared_ptr<AbstractResource> > d_resource_list;

		/**
		 * \brief The children categories.
		 */
		QList<AbstractCategory*> d_children_categories;

		/**
		 * \brief The parent category.
		 */
		AbstractCategory* d_parent_category;

};

#endif /* KEEP_STORED_ABSTRACT_CATEGORY_HPP */


