/**
 * \file default_resource_preview.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract resource preview class.
 */

#ifndef KEEP_STORED_DEFAULT_RESOURCE_PREVIEW_HPP
#define KEEP_STORED_DEFAULT_RESOURCE_PREVIEW_HPP

#include "abstract_resource_preview.hpp"

class QLabel;
class QPushButton;

class DefaultResourcePreview : public AbstractResourcePreview
{
	public:

		/**
		 * \brief Constructor.
		 */
		DefaultResourcePreview(AbstractResourcePreview* parent = 0);

		void updateResourceInformation(AbstractResourceListModel* model, int row);

		void reset();

	private:

		QLabel* d_title_label;
		QLabel* d_author_label;
		QLabel* d_taglist_label;
		QLabel* d_location_label;

		QLabel* d_title;
		QLabel* d_author;
		QLabel* d_taglist;
		QLabel* d_location;

		QPushButton* d_open_button;

		public slots:
			void open();
};

#endif /* KEEP_STORED_DEFAULT_RESOURCE_PREVIEW_HPP */

