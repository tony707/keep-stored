/**
 * \file abstract_resource_preview.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The abstract resource preview class.
 */

#include "default_resource_preview.hpp"

#include "../backend/abstract_resource.hpp"
#include "../backend/abstract_resource_list_model.hpp"

#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QUrl>
#include <QDesktopServices>

DefaultResourcePreview::DefaultResourcePreview(AbstractResourcePreview* parent) :
	AbstractResourcePreview(parent),
	d_title_label(new QLabel(tr("Title :"))),
	d_author_label(new QLabel(tr("Author(s) :"))),
	d_taglist_label(new QLabel(tr("Tags :"))),
	d_location_label(new QLabel(tr("Location :"))),
	d_title(new QLabel("")),
	d_author(new QLabel("")),
	d_taglist(new QLabel("")),
	d_location(new QLabel("")),
	d_open_button(new QPushButton("Open Resource"))
{
	QVBoxLayout* vlayout = new QVBoxLayout();

	QFormLayout* form_layout = new QFormLayout();

	form_layout->addRow(d_title_label, d_title);
	form_layout->addRow(d_author_label, d_author);
	form_layout->addRow(d_taglist_label, d_taglist);
	form_layout->addRow(d_location_label, d_location);

	vlayout->addLayout(form_layout);
	vlayout->addWidget(d_open_button);

	setLayout(vlayout);

	connect(d_open_button, SIGNAL(clicked()), this, SLOT(open()));
}

void DefaultResourcePreview::updateResourceInformation(AbstractResourceListModel* model, int row)
{
	d_resource_model_list = model;
	d_current_row = row;
	d_title->setText(model->data(model->index(row, 0), Qt::DisplayRole).toString());
	d_author->setText(model->data(model->index(row, 1), Qt::DisplayRole).toString());
	d_taglist->setText(model->data(model->index(row, 2), Qt::DisplayRole).toString());
	d_location->setText(model->data(model->index(row, 3), Qt::DisplayRole).toString());
}

void DefaultResourcePreview::reset()
{
	d_title->setText("");
	d_author->setText("");
	d_taglist->setText("");
	d_location->setText("");
	d_resource_model_list = NULL;
}

void DefaultResourcePreview::open()
{
	if (d_current_row >= 0)
	{
		QString url_string = d_resource_model_list->data(d_resource_model_list->index(d_current_row, 3), Qt::DisplayRole).toString();

		QDesktopServices::openUrl(url_string);
	}
}
