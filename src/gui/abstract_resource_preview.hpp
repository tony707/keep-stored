/**
 * \file abstract_resource_preview.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract resource preview class.
 */

#ifndef KEEP_STORED_ABSTRACT_RESOURCE_PREVIEW_HPP
#define KEEP_STORED_ABSTRACT_RESOURCE_PREVIEW_HPP

#include <QWidget>

#include <boost/shared_ptr.hpp>

class AbstractResource;

class AbstractResourcePreview : public QWidget
{
	Q_OBJECT

	public:

		/**
		 * \brief Constructor.
		 */
		AbstractResourcePreview(QWidget* parent = 0);

		virtual void updateResourceInformation(boost::shared_ptr<AbstractResource> resource) = 0;

		virtual void reset() = 0;

	private:

};

#endif /* KEEP_STORED_ABSTRACT_RESOURCE_PREVIEW_HPP */

