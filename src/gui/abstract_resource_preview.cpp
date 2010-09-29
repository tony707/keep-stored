/**
 * \file abstract_resource_preview.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract resource preview class.
 */

#include "abstract_resource_preview.hpp"

AbstractResourcePreview::AbstractResourcePreview(QWidget* parent) :
	QWidget(parent),
	d_resource_model_list(NULL),
	d_current_row(-1)
{
}
