/**
 * \file configuration_window.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The configuration window class.
 */

#ifndef KEEP_STORED_CONFIGURATION_WINDOW_HPP
#define KEEP_STORED_CONFIGURATION_WINDOW_HPP

#include <QDialog>

class ConfigurationWindow : public QDialog
{
	Q_OBJECT

	public:

		/**
		 * \brief Constructor.
		 */
		ConfigurationWindow(QWidget* parent = 0);
};

#endif /* KEEP_STORED_CONFIGURATION_WINDOW_HPP */

