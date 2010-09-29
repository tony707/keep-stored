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
class AbstractResourceListModel;

class AbstractResourcePreview : public QWidget
{
	Q_OBJECT

	public:

		/**
		 * \brief Constructor.
		 */
		AbstractResourcePreview(QWidget* parent = 0);

		virtual void updateResourceInformation(AbstractResourceListModel* model, int row) = 0;

		virtual void reset() = 0;

	protected:

		AbstractResourceListModel* d_resource_model_list;
		int d_current_row;

	public slots:

		virtual void open() = 0;

};

#endif /* KEEP_STORED_ABSTRACT_RESOURCE_PREVIEW_HPP */

