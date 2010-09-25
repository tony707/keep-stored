/**
 * \file new_resource_view.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The new resource view class.
 */

#include "resource_view.hpp"

#include "../backend/abstract_resource.hpp"
#include "../backend/category.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>

#include <boost/foreach.hpp>

ResourceView::ResourceView(QList<boost::shared_ptr<Category> > category_list, QWidget* parent) :
	QWidget(parent),
	d_title_edit(new QLineEdit()),
	d_author_edit(new QLineEdit()),
	d_location_edit(new QLineEdit()),
	d_submit_button(new QPushButton(tr("Submit"))),
	d_combo_category_list(new QComboBox()),
	d_category_list(category_list)
{
	setWindowTitle(tr("Add a resource"));

	BOOST_FOREACH(boost::shared_ptr<Category> category, d_category_list)
	{
		d_combo_category_list->addItem(QIcon(":/resources/category.png"), QString::fromStdString(category->title()));
	}

	QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Category")), d_combo_category_list);
  layout->addRow(new QLabel(tr("Title")), d_title_edit);
  layout->addRow(new QLabel(tr("Author(s)")), d_author_edit);
  layout->addRow(new QLabel(tr("Location")), d_location_edit);
  layout->addRow(d_submit_button);

	d_resource.reset();

	connect(d_submit_button, SIGNAL(clicked()), this, SLOT(save()));

  setLayout(layout);
}

void ResourceView::loadResource(boost::shared_ptr<AbstractResource> resource, boost::shared_ptr<Category> category)
{
	d_resource = resource;

	d_combo_category_list->setCurrentIndex(d_category_list.indexOf(category));
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

		emit resourceAdded(d_category_list.at(d_combo_category_list->currentIndex()), resource);
	}

	d_title_edit->setText("");
	d_author_edit->setText("");
	d_location_edit->setText("");
	d_combo_category_list->setCurrentIndex(0);

	hide();
}

void ResourceView::updateCategoryList(QList<boost::shared_ptr<Category> > category_list)
{
	d_category_list = category_list;
	d_combo_category_list->clear();
	BOOST_FOREACH(boost::shared_ptr<Category> category, d_category_list)
	{
		d_combo_category_list->addItem(QIcon(":/resources/category.png"), QString::fromStdString(category->title()));
	}
}

