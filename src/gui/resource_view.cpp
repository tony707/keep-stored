/**
 * \file new_resource_view.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The new resource view class.
 */

#include "resource_view.hpp"

#include "../backend/abstract_resource.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>

ResourceView::ResourceView(QWidget* parent) :
	QWidget(parent),
	d_title_edit(new QLineEdit()),
	d_author_edit(new QLineEdit()),
	d_location_edit(new QLineEdit()),
	d_submit_button(new QPushButton(tr("Submit")))
{
	setWindowTitle(tr("Add a resource"));

	QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Title")), d_title_edit);
  layout->addRow(new QLabel(tr("Author(s)")), d_author_edit);
  layout->addRow(new QLabel(tr("Location")), d_location_edit);
  layout->addRow(d_submit_button);

	d_resource.reset();

	connect(d_submit_button, SIGNAL(clicked()), this, SLOT(save()));

  setLayout(layout);
}

void ResourceView::loadResource(boost::shared_ptr<AbstractResource> resource)
{
	d_resource = resource;

	d_title_edit->setText(QString::fromStdString(d_resource->title()));
	d_author_edit->setText(QString::fromStdString(d_resource->author()));
	d_location_edit->setText(QString::fromStdString(d_resource->location()));

	show();
}

void ResourceView::save()
{
	std::string title = d_title_edit->text().toStdString();
	std::string author = d_author_edit->text().toStdString();
	std::string location = d_location_edit->text().toStdString();

	if (d_resource)
	{
		d_resource->setTitle(title);
		d_resource->setAuthor(author);
		d_resource->setLocation(location);

		d_resource.reset();
	}
	else
	{
		boost::shared_ptr<AbstractResource> resource(new AbstractResource());
		resource->setTitle(title);
		resource->setAuthor(author);
		resource->setLocation(location);

		//resourceAdded(resource);
	}

	d_title_edit->setText("");
	d_author_edit->setText("");
	d_location_edit->setText("");

	hide();
}

