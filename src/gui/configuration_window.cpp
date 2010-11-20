/**
 * \file configuration_window.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The configuration window class.
 */

#include "configuration_window.hpp"

#include <QFormLayout>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

ConfigurationWindow::ConfigurationWindow(QWidget* parent) :
	QDialog(parent)
{
	setWindowTitle("KeepStored Configuration Window");

	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(new QLabel("Specific Location Storage"));

	QFormLayout *storage_layout = new QFormLayout;
	storage_layout->addRow(new QCheckBox(), new QLabel("Enable Local Storage"));
	storage_layout->addRow(new QLabel("Path"), new QLineEdit());
	QComboBox* behaviour = new QComboBox();
	behaviour->addItem("Copy");
	behaviour->addItem("Move");
	storage_layout->addRow(new QLabel("Default Behaviour"), behaviour);
	layout->addLayout(storage_layout);

	QHBoxLayout* buttons = new QHBoxLayout();
	buttons->addWidget(new QPushButton("Save"));
	buttons->addWidget(new QPushButton("Cancel"));
	layout->addLayout(buttons);

	setLayout(layout);
}

