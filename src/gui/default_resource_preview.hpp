/**
 * \file default_resource_preview.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract resource preview class.
 */

#ifndef KEEP_STORED_DEFAULT_RESOURCE_PREVIEW_HPP
#define KEEP_STORED_DEFAULT_RESOURCE_PREVIEW_HPP

#include "abstract_resource_preview.hpp"

class QLabel;

class DefaultResourcePreview : public AbstractResourcePreview
{
	public:

		/**
		 * \brief Constructor.
		 */
		DefaultResourcePreview(AbstractResourcePreview* parent = 0);

		void updateResourceInformation(boost::shared_ptr<AbstractResource> resource);

		void reset();

	private:

		QLabel* d_title;

};

#endif /* KEEP_STORED_DEFAULT_RESOURCE_PREVIEW_HPP */

