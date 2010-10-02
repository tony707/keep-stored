/**
 * \file new_resource_view.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The new resource view class.
 */

#include "resource_view.hpp"

#include "../backend/abstract_resource_list_model.hpp"
#include "../backend/category_list_model.hpp"
#include "../backend/abstract_resource.hpp"
#include "../backend/default_resource.hpp"
#include "../backend/string_tools.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QItemSelection>

#include <boost/foreach.hpp>

ResourceView::ResourceView(CategoryListModel* category_list_model, QWidget* parent) :
	QWidget(parent),
	d_row(-1),
	d_title_edit(new QLineEdit()),
	d_author_edit(new QLineEdit()),
	d_location_edit(new QLineEdit()),
	d_submit_button(new QPushButton(tr("Submit"))),
	d_combo_category_list(new QComboBox()),
	d_category_list_model(category_list_model)
{
	setWindowTitle(tr("Add a resource"));

	for (int row = 0; row < d_category_list_model->rowCount(); ++row)
	{
		d_combo_category_list->addItem(
				d_category_list_model->data(d_category_list_model->index(row, 0), Qt::DecorationRole).value<QIcon>(),
				d_category_list_model->data(d_category_list_model->index(row, 0), Qt::DisplayRole).toString()
		);
	}

	QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Category")), d_combo_category_list);
  layout->addRow(new QLabel(tr("Title")), d_title_edit);
  layout->addRow(new QLabel(tr("Author(s)")), d_author_edit);
  layout->addRow(new QLabel(tr("Location")), d_location_edit);
  layout->addRow(d_submit_button);

	connect(d_submit_button, SIGNAL(clicked()), this, SLOT(save()));

  setLayout(layout);
}

void ResourceView::setResourceListModel(AbstractResourceListModel* resource_list_model)
{
	d_resource_list_model = resource_list_model;
	d_combo_category_list->setCurrentIndex(d_category_list_model->categoryList().indexOf(d_resource_list_model->category()));
}

void ResourceView::loadResource(int row)
{
	d_row = row;
	d_title_edit->setText(d_resource_list_model->data(d_resource_list_model->index(row, 0), Qt::DisplayRole).toString());
	d_author_edit->setText(d_resource_list_model->data(d_resource_list_model->index(row, 1), Qt::DisplayRole).toString());
	d_location_edit->setText(d_resource_list_model->data(d_resource_list_model->index(row, 2), Qt::DisplayRole).toString());

	show();
}

void ResourceView::save()
{
	QString title = d_title_edit->text();
	QString author = d_author_edit->text();
	QString location = d_location_edit->text();

	if (d_row >= 0)
	{
		d_resource_list_model->setData(d_resource_list_model->index(d_row, 0), title, Qt::EditRole);
		d_resource_list_model->setData(d_resource_list_model->index(d_row, 1), author, Qt::EditRole);
		d_resource_list_model->setData(d_resource_list_model->index(d_row, 2), location, Qt::EditRole);
	}
	else
	{
		boost::shared_ptr<AbstractResource> resource(new DefaultResource());

		resource->setTitle(fromQString(title));
		resource->setAuthor(fromQString(author));
		resource->setLocation(fromQString(location));

		d_resource_list_model->addResource(resource);
	}

	d_title_edit->setText("");
	d_author_edit->setText("");
	d_location_edit->setText("");
	d_row = -1;

	hide();
}

