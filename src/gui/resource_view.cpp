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
#include "../backend/abstract_category.hpp"

#include <QLabel>
#include <QUrl>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QItemSelection>

#include <boost/foreach.hpp>

ResourceView::ResourceView(CategoryListModel* category_list_model, AbstractResourceListModel* resource_list_model, QWidget* parent) :
	QWidget(parent),
	d_index(QModelIndex()), //TODO: Check if SIGSEV COMES BECAUSE THE QModelIndex is not correct
	d_title_edit(new QLineEdit()),
	d_author_edit(new QLineEdit()),
	d_taglist_edit(new QLineEdit()),
	d_location_edit(new QLineEdit()),
	d_submit_button(new QPushButton(tr("Submit"))),
	d_combo_category_list(new QComboBox()),
	d_category_list_model(category_list_model),
	d_resource_list_model(resource_list_model)
{
	setWindowTitle(tr("Add a resource"));

	QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Category")), d_combo_category_list);
  layout->addRow(new QLabel(tr("Title")), d_title_edit);
  layout->addRow(new QLabel(tr("Author(s)")), d_author_edit);
  layout->addRow(new QLabel(tr("Tags")), d_taglist_edit);
  layout->addRow(new QLabel(tr("Location")), d_location_edit);
  layout->addRow(d_submit_button);

	connect(d_submit_button, SIGNAL(clicked()), this, SLOT(save()));

  setLayout(layout);
}

void ResourceView::setResourceListModel(AbstractResourceListModel* resource_list_model)
{
	d_resource_list_model = resource_list_model;
}

void ResourceView::showEvent(QShowEvent* event)
{
	Q_UNUSED(event);

	d_combo_category_list->clear();

	appendCategories(d_category_list_model->rootCategory());

	if (d_index.isValid())
	{
		//TODO: category title has to be unique ! (findData with QModelIndex isn't reliable)
		int row = d_combo_category_list->findText(d_resource_list_model->category()->title());
		d_combo_category_list->setCurrentIndex(row);
	}
}

void ResourceView::appendCategories(AbstractCategory* parent_category, const QModelIndex& parent)
{
	BOOST_FOREACH(AbstractCategory* category, parent_category->children())
	{
		QModelIndex index = d_category_list_model->index(category->row(), 0, parent);

		d_combo_category_list->addItem(
				d_category_list_model->data(index, Qt::DecorationRole).value<QIcon>(),
				d_category_list_model->data(index, Qt::DisplayRole).toString(),
				QVariant::fromValue<QModelIndex>(index));

		appendCategories(category, index);
	}
}

void ResourceView::loadResource(QModelIndex index)
{
	d_index = index;
	d_title_edit->setText(d_resource_list_model->data(d_resource_list_model->index(index.row(), 0), Qt::DisplayRole).toString());
	d_author_edit->setText(d_resource_list_model->data(d_resource_list_model->index(index.row(), 1), Qt::DisplayRole).toString());
	d_taglist_edit->setText(d_resource_list_model->data(d_resource_list_model->index(index.row(), 2), Qt::DisplayRole).toString());
	d_location_edit->setText(d_resource_list_model->data(d_resource_list_model->index(index.row(), 3), Qt::DisplayRole).toString());

	show();
}

void ResourceView::save()
{
	boost::shared_ptr<AbstractResource> resource;
	QString title = d_title_edit->text();
	QString author = d_author_edit->text();
	QString taglist = d_taglist_edit->text();
	QString location = d_location_edit->text();

	QModelIndex selected_index = d_combo_category_list->itemData(d_combo_category_list->currentIndex()).value<QModelIndex>();
	
	if (d_index.isValid())
	{
		d_resource_list_model->setData(d_resource_list_model->index(d_index.row(), 0), title, Qt::EditRole);
		d_resource_list_model->setData(d_resource_list_model->index(d_index.row(), 1), author, Qt::EditRole);
		d_resource_list_model->setData(d_resource_list_model->index(d_index.row(), 2), taglist, Qt::EditRole);
		d_resource_list_model->setData(d_resource_list_model->index(d_index.row(), 3), location, Qt::EditRole);

		resource = d_resource_list_model->resource(d_index.row());
		d_resource_list_model->removeRows(d_index.row(), 1);
	}
	else
	{
		resource = boost::shared_ptr<AbstractResource>(new DefaultResource());

		resource->setTitle(title);
		resource->setAuthor(author);
		resource->setTagList(qStringToQStringList(taglist));
		resource->setLocation(QUrl::fromUserInput(location));
	}
	
	d_resource_list_model->setCategoryIndex(selected_index);
	d_resource_list_model->addResource(resource);

	// Clean the input fields for next use
	d_title_edit->setText("");
	d_author_edit->setText("");
	d_taglist_edit->setText("");
	d_location_edit->setText("");
	d_index = QModelIndex();

	hide();
}

