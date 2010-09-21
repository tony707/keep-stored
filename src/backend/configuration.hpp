/**
 * \file configuration.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The configuration class.
 */

#ifndef KEEP_STORED_CONFIGURATION_HPP
#define KEEP_STORED_CONFIGURATION_HPP

#include <QDir>

#include <boost/shared_ptr.hpp>

static const std::string CONFIGURATION_FILE = "configuration.xml";
static const std::string KEEPSTORED_XML_NAMESPACE = "http://github.com/tinoutinou/keep-stored";

class Category;

class Configuration
{
	public:

		/**
		 * \brief Constructor.
		 */
		Configuration();

		 /**
			* \brief Load the application configuration.
			*/
		 void loadConfigurationFile();

		 /**
			* \brief Load the application configuration.
			*/
		 void saveConfigurationFile();

	private:

		/**
		 * \brief Get the root configuration directory.
		 */
		QDir rootConfigurationDirectory();

		/**
		 * \brief Get the root configuration directory.
		 */
		std::string configurationFilePath();

		/**
		 * \brief The category list.
		 */
		std::list<boost::shared_ptr<Category> > d_category_list;

};

#endif /* KEEP_STORED_CONFIGURATION_HPP */

