/**
 * \file abstract_resource_preview.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract resource preview class.
 */

#include "default_resource_preview.hpp"

#include "../backend/abstract_resource.hpp"

#include <QLabel>
#include <QVBoxLayout>

DefaultResourcePreview::DefaultResourcePreview(AbstractResourcePreview* parent) :
	AbstractResourcePreview(parent),
	d_title(new QLabel())
{
	QVBoxLayout* layout = new QVBoxLayout();

	layout->addWidget(d_title);

	setLayout(layout);
}

void DefaultResourcePreview::updateResourceInformation(boost::shared_ptr<AbstractResource> resource)
{
	d_title->setText(QString::fromUtf8(resource->title().c_str()));
}

void DefaultResourcePreview::reset()
{
	d_title->setText("");
}
