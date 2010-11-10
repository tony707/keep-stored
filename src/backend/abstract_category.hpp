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
#include <boost/enable_shared_from_this.hpp>

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

class AbstractCategory : public boost::enable_shared_from_this<AbstractCategory>
{

	public:

	enum CategoryType
	{
		Default,
		Search
	};

		static void saveToXml(boost::shared_ptr<AbstractCategory> category, boost::shared_ptr<systools::xml::XmlWriter> xml_writer);

		static boost::shared_ptr<AbstractCategory> createFromXmlNode(boost::shared_ptr<systools::xml::XmlNode> xml_node);

		/**
		 * \brief Constructor.
		 */
		AbstractCategory();

		/**
		 * \brief Constructor.
		 */
		AbstractCategory(boost::shared_ptr<systools::xml::XmlNode> xml_node);

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

		void prependChild(boost::shared_ptr<AbstractCategory> category);

		void appendChild(boost::shared_ptr<AbstractCategory> category);

		boost::shared_ptr<AbstractCategory> childAt(int row);

		int childCount();

		int columnCount();

		int row();

		boost::shared_ptr<AbstractCategory> parent();

		QList<boost::shared_ptr<AbstractCategory> > children();

		void setParent(boost::weak_ptr<AbstractCategory> parent_category);

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
		QList<boost::shared_ptr<AbstractCategory> > d_children_categories;

		/**
		 * \brief The parent category.
		 */
		boost::weak_ptr<AbstractCategory> d_parent_category;

};

#endif /* KEEP_STORED_ABSTRACT_CATEGORY_HPP */


