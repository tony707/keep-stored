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
		d_combo_category_list->addItem(QIcon(":/resources/category.png"), QString::fromUtf8(category->title().c_str()));
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
	d_title_edit->setText(QString::fromUtf8(d_resource->title().c_str()));
	d_author_edit->setText(QString::fromUtf8(d_resource->author().c_str()));
	d_location_edit->setText(QString::fromUtf8(d_resource->location().c_str()));

	show();
}

void ResourceView::save()
{
	QByteArray utf8_title = d_title_edit->text().toUtf8();
	QByteArray utf8_author = d_author_edit->text().toUtf8();
	QByteArray utf8_location = d_location_edit->text().toUtf8();
	std::string title = std::string(utf8_title.constData(), utf8_title.size());
	std::string author = std::string(utf8_author.constData(), utf8_author.size());
	std::string location = std::string(utf8_location.constData(), utf8_location.size());

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
		d_combo_category_list->addItem(QIcon(":/resources/category.png"), QString::fromUtf8(category->title().c_str()));
	}
}

